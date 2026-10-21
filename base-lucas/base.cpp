#include "base.h" // inclui as funcoes de controle do robo

// variaveis 

int  minEsq = 1023, maxEsq = 0; // calibracao do sensor esquerdo
int  minDir = 1023, maxDir = 0; // calibracao do sensor direito
int  leituraEsq = 0; // valor normalizado (0 a 100)
int  leituraDir = 0; // 100 = linha preta, 0 = branco
bool roboLigado = false; // true = andando, false = parado

// configuracao dos pinos

void iniciarPinos() {

  pinMode(PINO_IN1, OUTPUT); // pwm
  pinMode(PINO_IN2, OUTPUT); // referencia
  pinMode(PINO_IN3, OUTPUT); // pwm
  pinMode(PINO_IN4, OUTPUT); // referencia
  pinMode(PINO_BOTAO, INPUT_PULLUP);

}

// calibracao: mover o robo sobre a linha preta e sobre o chao branco
// o codigo guarda o menor e o maior valor lido e define o que é preto e o que é branco

void calibrarSensores() {

  unsigned long inicio = millis(); // tempo inicial da calibracao

  while (millis() - inicio < TEMPO_CALIBRACAO) {

    int esq = analogRead(PINO_SENSOR_ESQ); // leitura do sensor esquerdo
    int dir = analogRead(PINO_SENSOR_DIR); // leitura do sensor direito

    if (esq < minEsq) minEsq = esq; // guarda o menor valor lido
    if (esq > maxEsq) maxEsq = esq; // guarda o maior valor lido
    if (dir < minDir) minDir = dir; // guarda o menor valor lido
    if (dir > maxDir) maxDir = dir; // guarda o maior valor lido

  }
}

// leitura: converte cada sensor para uma escala de 0 a 100
// 100 = preto (linha) | 0 = branco

void lerSensores() {

  int calibraEsq = analogRead(PINO_SENSOR_ESQ); // leitura do sensor esquerdo
  int calibraDir = analogRead(PINO_SENSOR_DIR);

  leituraEsq = constrain(map(calibraEsq, minEsq, maxEsq, 100, 0), 0, 100);
  leituraDir = constrain(map(calibraDir, minDir, maxDir, 100, 0), 0, 100);

  // transforma o valor de preto em minimo e o valor de branco em maximo pra facilitar o controle proporcional
  // 100 a 0 -> 0 a 100 | deixa mais intuitivo

}

// controle dos motores

void controlarMotores(int velEsq, int velDir) {

  // velocidade positiva = frente | negativa = re | 0 = parado
  // valores de -255 a 255

  velEsq = constrain(velEsq, -255, 255); // limita a velocidade para o intervalo permitido
  velDir = constrain(velDir, -255, 255);

  // motor esquerdo

  if (velEsq >= 0) {

    analogWrite(PINO_IN1, velEsq); // pwm
    digitalWrite(PINO_IN2, LOW); // referencia menor

  } else {

    analogWrite(PINO_IN1, 255 + velEsq); // pwm invertido
    digitalWrite(PINO_IN2, HIGH); // referencia maior
    
  }

  // motor direito

  if (velDir >= 0) {

    analogWrite(PINO_IN3, velDir); // pwm
    digitalWrite(PINO_IN4, LOW); // referencia menor

  } else {

    analogWrite(PINO_IN3, 255 + velDir); // pwm invertido
    digitalWrite(PINO_IN4, HIGH); // referencia maior

  }
}

// controle proporcional

void controleProporcional() {

  // erro > 0 = linha mais para a esquerda -> vira para a esquerda
  // erro < 0 = linha mais para a direita -> vira para a direita

  int erro = leituraEsq - leituraDir; // para inverter o sinal -> erro = leituraDir - leituraEsq
  int correcao = KP * erro; // se o robo virar pro lado errado inverta o sinal do erro

  int velEsq = VELOCIDADE_BASE - correcao;
  int velDir = VELOCIDADE_BASE + correcao;

  controlarMotores(velEsq, velDir); // manda a velocidade para os motores

}

// ligar e desligar o robo com o botao

void verificarBotao() {

  if (digitalRead(PINO_BOTAO) == LOW) {

    roboLigado = !roboLigado; // inverte o estado
    delay(300); // delay para evitar ler varias vezes

    // espera soltar o botao

    while (digitalRead(PINO_BOTAO) == LOW) {

    }
  }
}