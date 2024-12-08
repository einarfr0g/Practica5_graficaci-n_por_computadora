#include "./header/model.h"
#include "./header/ventana.h"
#include <iostream>

Ventana *ventana;
Model *model;

void finish() {
  glfwTerminate();
  delete (model);
  delete (ventana);
}

void init() {
  ventana = new Ventana(600, 600);
  // Inicializar GLFW
  ventana->initGLFW();
  // Inicializar GLEW
  ventana->initGLEW();
  model = new Model("Cube_Triangles.obj");
  ventana->initModels(model);
  ventana->initViewProyection();
}

int main() {
  /*
  Model model("Cube_Triangles.obj");

  std::cout << "Los vertices son :" << "\n";
  int contador = 0;
  for (auto num : model.vertices_vec) {
    std::cout << num << " ";
    if (contador == 2) {
      std::cout << "\n";
      contador = 0;
    } else {
      contador++;
    }
  }
  contador = 0;
  std::cout << "\n" << "Los indices son:" << "\n";
  for (auto num : model.indices_vec) {
    std::cout << num << " ";
    if (contador == 2) {
      std::cout << "\n";
      contador = 0;
    } else {
      contador++;
    }
  }
  contador = 0;
  std::cout << "\n" << "Las normales son:" << "\n";
  for (auto num : model.normales_vec) {
    std::cout << num << " ";
    if (contador == 2) {
      std::cout << "\n";
      contador = 0;
    } else {
      contador++;
    }
  }
  */

  init();
  ventana->render();
  finish();

  return 0;
}
