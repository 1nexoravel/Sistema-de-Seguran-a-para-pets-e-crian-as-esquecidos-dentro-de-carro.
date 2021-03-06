#include "MayaLDR.h"

  MayaLDR::MayaLDR(int pino){
    periodo_ = 3000; //20 mintutos = 1200000
    tempo_   = 0;
    pino_    = pino;
    claro_   = 0;
    sombra_  = 0;
    escuro_  = 0;
  }

  void MayaLDR::setPeriodo(int periodo){
    periodo_ = periodo;
  }

  void MayaLDR::setTempo(int tempo){
    tempo_ = tempo;
  }

  int (&MayaLDR::getDados(int (&dados)[3]))[3] {
    dados[1] = claro_;
    dados[2] = sombra_;
    dados[3] = escuro_;
    claro_ = sombra_ = escuro_ = 0;
    return dados;
  }

  void MayaLDR::ativar(int tipo){
    if( millis() >  tempo_ + periodo_ ){
      luminosidade_ = analogRead(pino_);
      tempo_        = millis();
      
      if ( luminosidade_ > 500 ) {
        claro_++;
      } else if (luminosidade_ <= 500 && luminosidade_ > 100) {
        sombra_++;
      } else { //luminosidade <= 100
        escuro_++;
      }

      if ( tipo == 1 ){
        Serial.println("[LUMINOSIDADE - POR MINUTO]");
        Serial.print("Claro: ");
        Serial.println(claro_);
        Serial.print("Sombra: ");
        Serial.println(sombra_);
        Serial.print("Escuro: ");
        Serial.println(escuro_);
        Serial.print("Luminosidade: ");
        Serial.println(luminosidade_);
        Serial.println("");
      }
    }
  }
