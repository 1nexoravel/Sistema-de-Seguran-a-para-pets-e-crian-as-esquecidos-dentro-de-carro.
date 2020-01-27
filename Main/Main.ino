#include "DHT.h"

<<<<<<< HEAD
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

=======
char ssid[] = "inexoravel";
char pass[] = "size1080p";

char auth[] = "zwLH8Wds5_mmLxfSrmNppgiwMv5bCaTs";
char LER;
bool DEBUG;
bool LIGADO;
bool FAROL;
bool LUZ;
bool FLUXO;
bool QUEIMADO;
bool QUEIMADOF;
float U; 
float T; 
int LDRfarol;
int LDRinterno;
int PIR;
int pinoLDRfarol = 34;
int pinoLDRinterno = 35;
int pinoPIR = 32;
int pinoLEDfarol = 15; //15 2 0 4
int pinoLEDinterno = 2; //15 2 0 4
int pinoLEDdentro = 18;
int pinoLEDjanela = 4;
int pinoLEDtemperatura = 0;
>>>>>>> 58585d5887669d8375ead2239c35b5e80f3f12a5
DHT dht = DHT(13, DHT11);

void setup(){
  Serial.begin(9600);
  dht.begin();
<<<<<<< HEAD
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
=======
  pinMode(pinoLEDdentro, OUTPUT); //VERDE, GENTE
  pinMode(pinoLEDjanela, OUTPUT); //AZUL, JANELA
  pinMode(pinoLEDinterno, OUTPUT); //BRANCO, LATERNA INTERNA
  pinMode(pinoLEDfarol, OUTPUT); //BRANCO, FAROL
  pinMode(pinoLEDtemperatura, OUTPUT); //VERMELHO, FAROL
  pinMode(pinoPIR, INPUT); 
  pinMode(pinoLDRfarol, INPUT); 
  pinMode(pinoLDRinterno, INPUT);
  LIGADO = false;
  FAROL = false;
  LUZ = false;
  DEBUG = false;
  Serial.println("SETUP OK");
}

void loop(){
  Blynk.run();
  timer.run();
  delay(1000);
  LDRfarol = analogRead(pinoLDRfarol);
  LDRinterno = analogRead(pinoLDRinterno);
  PIR = digitalRead(pinoPIR);
  LER = Serial.read();
  U = dht.readHumidity();
  T = dht.readTemperature();
  if(LER == 'L'){
    LIGADO = true;
    Serial.println("Ligou o carro.");
    }
  if(LER == 'D'){
    LIGADO = false;
    Serial.println("Desligou o carro.");
    }
  if(LER == '1'){
    FAROL = true;
    Serial.println("Ligou o farol.");
  }
  if(LER == '0'){
    FAROL = false;
    Serial.println("Desligou o farol.");
  }

  if(LER == '3'){
    LUZ = true;
    Serial.println("Ligou a luz.");
  }
    
  if(LER == '2'){
    LUZ = false;
    Serial.println("Desligou a luz.");
  }

  if(DEBUG == true){
    debug(1);
    }else{debug(0);}
if(FLUXO == true){
  if(LIGADO == false){ 
    Serial.print("Carro está desligado. -> ");    
   
    if(FAROL == true && LUZ == true){
      digitalWrite(pinoLEDfarol, HIGH);
      if(LDRfarol < 3000){
          Serial.println("Farol e luz interna estão ligados!!!");
          delay(1000);
          Serial.println("Desligando o farol e luz interna em 5 segundos.");
          delay(5000);
          digitalWrite(pinoLEDfarol, LOW);
          digitalWrite(pinoLEDinterno, LOW);
          FAROL = false;
          LUZ = false;
          Serial.println("Farol está desligado!!!");
        }else{
        Serial.println("");
        }
    }

    
    if(FAROL == true){
      digitalWrite(pinoLEDfarol, HIGH);
      if(LDRfarol < 3000){
          Serial.println("Farol está ligado!!!");
          delay(1000);
          Serial.println("Desligando o farol em 5 segundos.");
          delay(5000);
          digitalWrite(pinoLEDfarol, LOW);
          FAROL = false;
          Serial.println("Farol está desligado!!!");
        }else{
        Serial.println("");
        }
    }
    if(LUZ == true){
      digitalWrite(pinoLEDinterno, HIGH);
      if(LDRinterno < 4000){
          Serial.println("Luz interna está ligada!!!");
          delay(1000);
          Serial.println("Desligando a luz interna em 5 segundos.");
          delay(5000);
          digitalWrite(pinoLEDinterno, LOW);
          LUZ = false;
          Serial.println("Luz interna está desligada!!!");
        }else{
        Serial.println("");
        }
    }
    if(PIR == 1){
      Serial.print("Animal ou criança dentro do carro! | ");
      Serial.print("Temperatura: ");
      Serial.print(T);
      Serial.print(" | ");
      digitalWrite(pinoLEDdentro, HIGH);
      if(T > 31){
        Serial.print("Temperatura alta: ");

        digitalWrite(pinoLEDtemperatura, HIGH);
        Serial.print("Descendo as janelas."); 
        delay(5000);  
        digitalWrite(pinoLEDjanela, HIGH);
          }
      }else{
         digitalWrite(pinoLEDdentro, LOW);
         digitalWrite(pinoLEDjanela, LOW);
        } 
      //Serial.println("");
  }else{
    Serial.print("Carro está ligado. -> ");
    if(FAROL == true){
      digitalWrite(pinoLEDfarol, HIGH);
      delay(1000);
      LDRfarol = analogRead(pinoLDRfarol);
      if(LDRfarol < 3000){
        Serial.print("Farol está ligado | ");
        QUEIMADOF = false;
      }else{
        Serial.print("Farol está queimado | ");
        QUEIMADOF = true;
      }
    }
    if(FAROL == false){
      digitalWrite(pinoLEDfarol, LOW);
      Serial.print("Farol está desligado | ");
    }
    if(LUZ == true){
      digitalWrite(pinoLEDinterno, HIGH);
      delay(1000);
      LDRinterno = analogRead(pinoLDRinterno);
      if(LDRinterno < 4000){
        Serial.print("Luz interna está ligada | ");
        QUEIMADO = false;
      }else{
        Serial.print("Luz interna está está queimada | ");
        QUEIMADO = true;
      }
    }
    if(LUZ == false){
      digitalWrite(pinoLEDinterno, LOW);
      Serial.print("Luz interna está desligada.");
    }
    if(QUEIMADO == true || QUEIMADOF == true){
      Serial.print("Enviando SMS para o motorista");
      }
  }Serial.println("");
}else{}
>>>>>>> 58585d5887669d8375ead2239c35b5e80f3f12a5
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
