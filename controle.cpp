#include "mapeamento.h"
#include <Arduino.h>

//Variáveis globais
RockyMotors motores;
int minEsq = 1023, maxEsq = 0; 
int minDir = 1023, maxDir = 0;
int leituraEsq = 0; 
int leituraDir = 0;

// Variáveis auxiliares
unsigned long inicio;
int esq, dir;
int calibraEsq, calibraDir;
int mapeamentoEsq, mapeamentoDir;

void iniciarPinos() {
  pinMode(PINO_BOTAO, INPUT_PULLUP); 
}

// 1. Leitura e calibração dos sensores
void calibrarSensores() {
    inicio = millis();
    pinMode(PINO_LED, OUTPUT); 
    digitalWrite(PINO_LED, HIGH);

    while (millis() - inicio < TEMPO_CALIBRACAO)
    {
        esq = analogRead(PINO_SENSOR_ESQ);
        dir = analogRead(PINO_SENSOR_DIR);

        if (esq < minEsq) minEsq = esq;
        if (esq > maxEsq) maxEsq = esq;
        if (dir < minDir) minDir = dir;
        if (dir > maxDir) maxDir = dir;
    }
    digitalWrite(PINO_LED, LOW); 
}

void lerSensores() {
  calibraEsq = analogRead(PINO_SENSOR_ESQ);
  calibraDir = analogRead(PINO_SENSOR_DIR);

  mapeamentoEsq = map(calibraEsq, minEsq, maxEsq, 100, 0);
  mapeamentoDir = map(calibraDir, minDir, maxDir, 100, 0);
  
  leituraEsq = constrain(mapeamentoEsq, 0, 100);
  leituraDir = constrain(mapeamentoDir, 0, 100);
}

// 2. Controle dos motores
void controlarMotores(int velEsq, int velDir){
    velEsq = constrain(velEsq, -VELOCIDADE_MAX, VELOCIDADE_MAX);
    velDir = constrain(velDir, -VELOCIDADE_MAX, VELOCIDADE_MAX);

    motors.setSpeedLeft(velEsq);
    motors.setSpeedRight(velDir);
}

// 3. controle proporcional e botão start stop
bool roboLigado = false;
void verificarBotao() {
    if (digitalRead(PINO_BOTAO) == LOW) // botao pressionado
    {
        roboLigado = !roboLigado;
        if(!roboLigado)
        {
            controlarMotores(0, 0);            //para na hora sem esperar soltar
        }
        delay(50);                    //espera o repique passar
        while (digitalRead(PINO_BOTAO) == LOW) { }   // espera soltar
        delay(50);
    }
}

void controleProporcional() {
    int erro = leituraDir - leituraEsq;
    int correcao = (int)(KP * erro);
    
    int velEsq = constrain(VELOCIDADE_BASE + correcao, -VELOCIDADE_MAX, VELOCIDADE_MAX); 
    int velDir = constrain(VELOCIDADE_BASE - correcao, -VELOCIDADE_MAX, VELOCIDADE_MAX);
    
    controlarMotores(velEsq, velDir);
}

// DEBUG 
void debugSensores() {

  Serial.print("Min/Max Esq: "); 
  Serial.print(minEsq); 
  Serial.print("/"); 
  Serial.println(maxEsq);

  Serial.print("Min/Max Dir: "); 
  Serial.print(minDir); 
  Serial.print("/"); 
  Serial.println(maxDir);

  Serial.print("Valores Normalizados -> Esq: ");
  Serial.print(leituraEsq);
  Serial.print(" | Dir: ");
  Serial.println(leituraDir);

  delay(100); 
}