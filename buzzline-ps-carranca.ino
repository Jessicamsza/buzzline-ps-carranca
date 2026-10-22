#include "mapeamento.h"

void setup() {
  Serial.begin(9600);
  iniciarPinos(); // configura entradas e saidas
  calibrarSensores(); // para calibrar, deve passar os sensores sobre a linha e o chao branco

  // apos calibrar, o robo espera o botao para comecar

}

void loop() {
  verificarBotao(); // verifica o estado do botao

  if (roboLigado) {    
    
    lerSensores(); // atualiza leituraEsq e leituraDir    
    controleProporcional(); // calcula o erro e ajusta motores

  } else {
    controlarMotores(0, 0);

    //pode verificar a calibracao enquanto robo estiver parado
    //lerSensores();
    //debugSensores();
  }
}