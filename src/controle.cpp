#include "mapeamento.h"
#include <Arduino.h>

//Variáveis globais

RockyMotors motors;
int minEsq = ADC_MAX, maxEsq = 0;
int minDir = ADC_MAX, maxDir = 0;
int leituraEsq = 0; 
int leituraDir = 0;

void iniciarPinos()
{
    pinMode(PINO_BOTAO, INPUT_PULLUP);
}

void calibrarSensores()
{
    unsigned long inicio = millis();
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);

    while (millis() - inicio < TEMPO_CALIBRACAO)
    {
        int esq = analogRead(PINO_SENSOR_ESQ);
        int dir = analogRead(PINO_SENSOR_DIR);

        if (esq < minEsq) minEsq = esq;
        if (esq > maxEsq) maxEsq = esq;
        if (dir < minDir) minDir = dir;
        if (dir > maxDir) maxDir = dir;
    }
    digitalWrite(13, LOW);
}

void lerSensores()
{
    int brutoEsq = analogRead(PINO_SENSOR_ESQ);
    int brutoDir = analogRead(PINO_SENSOR_DIR);

    leituraEsq = constrain(map(brutoEsq, minEsq, maxEsq, 100, 0), 0, 100);
    leituraDir = constrain(map(brutoDir, minDir, maxDir, 100, 0), 0, 100);
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
}

// Parte 3:controle proporcional e botão start stop

bool roboLigado = false;
void verificarBotao()
{
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

void controlarMotores(int velEsq, int velDir)
{
    velEsq = constrain(velEsq, -VELOCIDADE_MAX, VELOCIDADE_MAX);
    velDir = constrain(velDir, -VELOCIDADE_MAX, VELOCIDADE_MAX);

    motors.setSpeedLeft(velEsq);
    motors.setSpeedRight(velDir);
}

void controleProporcional()
{
    int erro = leituraDir - leituraEsq;
    int correcao = (int)(KP * erro);

    int velEsq = constrain(VELOCIDADE_BASE + correcao, -VELOCIDADE_MAX, VELOCIDADE_MAX); 
    int velDir = constrain(VELOCIDADE_BASE - correcao, -VELOCIDADE_MAX, VELOCIDADE_MAX);

    controlarMotores(velEsq, velDir);
}