// programa principal do robo seguidor de linha

#include "base.h" // inclui as funcoes de controle do robo

void setup() {

  iniciarPinos(); // configura entradas e saidas
  calibrarSensores(); // para calibrar, deve passar os sensores sobre a linha e o chao branco

  // apos calibrar, o robo espera o botao para comecar

}

void loop() {

  verificarBotao(); // ve o estado do botao

  if (roboLigado) {

    // se o robo estiver ligado, ele le os sensores e ajusta os motores
    
    lerSensores(); // atualiza leituraEsq e leituraDir
    controleProporcional(); // calcula o erro e ajusta motores

  } else {

    // se o robo estiver desligado, ele para os motores

    controlarMotores(0, 0);

  }
}