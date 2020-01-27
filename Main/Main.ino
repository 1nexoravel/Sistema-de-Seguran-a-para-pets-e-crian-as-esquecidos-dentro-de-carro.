#include "DHT.h"

bool enviarMensagem;
bool abrirJanela;
bool ligarAlarme;
bool carroLigado;
bool foiDetectadoMovimento; 
bool foiDetectadoGasesToxicos;
float temperatura; 
int debugValor;
int sensorPresenca;
int controlePIR;
float calculoPIR;
int pinoPIR = 32;
int pinoMQ135 = 15;
unsigned long temporizador;
unsigned long periodo_sis = 1000; // 1 minuto = 60000
unsigned long time_sis  = 0;
unsigned long periodo_pir = 10000; // 1 minuto = 60000
unsigned long time_pir    = 0;
int ph1 = 25;
int ph2 = 26;
int ph3 = 27;
int ph4 = 14;
int alarme = 3;
float ppm;

DHT dht = DHT(13, DHT11);

void setup(){
  Serial.begin(9600);
  dht.begin();
  carroLigado = false;
  foiDetectadoMovimento = false;
  foiDetectadoGasesToxicos = false;
  enviarMensagem = false;
  abrirJanela = false;
  ligarAlarme = false;
}

void loop(){
  temperatura = dht.readTemperature();
  sensorGAS(); 
  sisSeg();
}

void debug(int debugValor){
  if(debugValor == 1){
    Serial.print("[DEBUG]");
    Serial.print("Gases Tóxicos: ");
    Serial.print(ppm);
    Serial.print("ppm");
    Serial.print(" | ");
    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.print("°C ");
    Serial.print(" | ");
    Serial.print("Sensor de presença: ");
    Serial.print(sensorPresenca);
    Serial.print(" | ");
    Serial.println(" | ");
  } else {
  }
}

void sisSeg(){
  if(millis() >  time_sis + periodo_sis){
    time_sis = millis();
    if(carroLigado == false){
      if(foiDetectadoMovimento == true){
        if(millis() > temporizador + 120000){
          enviarMensagem = true;
        }      
        if(foiDetectadoGasesToxicos == true){
          if(millis() > temporizador + 180000){
            abrirJanela = true;
            ligarAlarme = true;      
          }
        }        
        if(temperatura > 28){
          if(millis() > temporizador + 300000){
            abrirJanela = true; 
            ligarAlarme = true;    
          }
        }
         else if(temperatura < 13){
          if(millis() > temporizador + 300000){
            ligarAlarme = true;
          }
        }
      }else{
      temporizador = millis(); 
      abrirJanela = false;
      ligarAlarme = false;
     } 
    }
  }
}

void alertar(){
  if(abrirJanela == true){
    digitalWrite(ph1, HIGH);
    digitalWrite(ph2, LOW);
    digitalWrite(ph3, HIGH);
    digitalWrite(ph4, LOW);
  }else{
    digitalWrite(ph1, LOW);
    digitalWrite(ph2, HIGH);
    digitalWrite(ph3, LOW);
    digitalWrite(ph4, HIGH);
  }
  if(ligarAlarme = true){
    digitalWrite(alarme, HIGH);
  }else{
    digitalWrite(alarme, LOW);
  }
}

void sensorPIR(){
  int contador;
  if(millis() >  time_pir + periodo_pir){
    time_pir = millis();
    contador++;
    int controlePIR = controlePIR + digitalRead(pinoPIR); 
    if(contador == 6){
      calculoPIR = controlePIR/6;
      contador = 0;
      if(calculoPIR > 0.65){      
        controlePIR = 0;
        foiDetectadoMovimento = true;
      }
    }
  }
}

void sensorGAS(){
  int RL = 20;
  int Ro = 10; 
  float amostragem = analogRead(pinoMQ135);
  float Vout = (amostragem*3.3)/4095;
  float Rs =(RL*5 - Vout)/Vout;
  float ratio = Rs/Ro;
  ppm = 37143*pow(ratio,-3.178);
  if(ppm > 400){
    foiDetectadoGasesToxicos = true;
  }
}
