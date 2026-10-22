#ifndef MAPEAMENTO_H
#define MAPEAMENTO_H

#include <Arduino.h>
#include <RoboCore_Rocky.h>

// --- PINOS ---
// Sensores
const int PINO_SENSOR_ESQ = 36; 
const int PINO_SENSOR_DIR = 39;

// Botão Start/Stop
const int PINO_BOTAO = 0;
const int PINO_LED = 15;

// --- CONFIGURAÇÕES ---
const int ADC_MAX = 4095;          // O ESP32 lê de 0 a 4095
const int VELOCIDADE_MAX = 100;    // Escala da biblioteca RoboCore
const int VELOCIDADE_BASE = 60;
const float KP = 0.5;              // se oscilar muito, diminuir | se lento, aumentar
const int TEMPO_CALIBRACAO = 8000; // 8 segundos

//--- VARIÁVEIS GLOBAIS ---
extern RockyMotors motors;

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