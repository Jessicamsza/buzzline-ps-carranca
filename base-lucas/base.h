#ifndef BASE_H // funcao para nao incluir o mesmo arquivo mais de uma vez

// se base.h ja foi incluido ele ignora o resto do codigo

#define BASE_H

#include <Arduino.h>

// sensores analogicos
// alterar caso use outro pino

const int PINO_SENSOR_ESQ = A0; 
const int PINO_SENSOR_DIR = A1;

// ponte h (IN1/IN2 = motor esquerdo | IN3/IN4 = motor direito)

const int PINO_IN1 = 5; // pwm
const int PINO_IN2 = 4; // referencia
const int PINO_IN3 = 6; // pwm
const int PINO_IN4 = 7; // referencia

const int PINO_BOTAO = 2;

// ajustes iniciais

const int VELOCIDADE_BASE = 120; // 0 a 255
const float KP = 1.5; // se oscilar muito, diminuir | se lento, aumentar
const int TEMPO_CALIBRACAO = 5000; // tempo pra calibrar

// variaveis

extern int minEsq, maxEsq; // calibracao do sensor esquerdo
extern int minDir, maxDir; // calibracao do sensor direito

extern int leituraEsq; // valor normalizado (0 a 100)
extern int leituraDir; // 100 = linha preta, 0 = branco

extern bool roboLigado; // true = andando, false = parado

void iniciarPinos(); // configura entradas e saidas
void calibrarSensores(); // le min e max dos sensores
void lerSensores(); // atualiza leituraEsq e leituraDir
void controlarMotores(int velEsq, int velDir); // -255 a 255
void controleProporcional(); // calcula o erro e ajusta motores
void verificarBotao(); // liga e desliga o robo

#endif // fim da parte ignorada do codigo