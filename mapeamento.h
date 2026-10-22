#ifndef MAPEAMENTO_H
#define MAPEAMENTO_H

#include <Arduino.h>

// --- PINOS (AJUSTAR) ---
// Sensores
const int PINO_SENSOR_ESQ = A0; 
const int PINO_SENSOR_DIR = A1;

// Ponte H 
const int PINO_IN1 = 5; // PWM Motor Esquerdo
const int PINO_IN2 = 4; // Ref Motor Esquerdo
const int PINO_IN3 = 6; // PWM Motor Direito
const int PINO_IN4 = 7; // Ref Motor Direito

// Botão Start/Stop
const int PINO_BOTAO = 2;

// --- CONFIGURAÇÕES ---

const int VELOCIDADE_BASE = 120;   // 0 a 255
const float KP = 1.5;              // se oscilar muito, diminuir | se lento, aumentar
const int TEMPO_CALIBRACAO = 8000; // 8s

//--- VARIÁVEIS GLOBAIS ---

extern int minEsq, maxEsq; // calibracao do sensor esquerdo
extern int minDir, maxDir; // calibracao do sensor direito

extern int leituraEsq; // valor normalizado (0 a 100)
extern int leituraDir; // 100 = linha preta, 0 = branco

extern bool roboLigado; // true = andando, false = parado

// --- ASSINATURAS DAS FUNÇÕES ---

void iniciarPinos();
void calibrarSensores();
void lerSensores();
void controlarMotores(int velEsq, int velDir);
void controleProporcional();
void verificarBotao();
void debugSensores();

#endif