#include "../header/model.h"
#include "../header/OBJ_reader.h"
#include "../header/shader.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>

Model::Model(std::string OBJ_dir) {
  std::cout << "llegamos al consturctor" << "\n";
  OBJ_reader *model = new OBJ_reader(OBJ_dir);
  this->vertices_vec = model->model_buffers["VBO"];

  std::cout << "llegamos al for" << "\n";

  for (auto e : model->model_buffers["EBO"]) {
    this->indices_vec.push_back(static_cast<GLuint>(round(e)) - 1);
  }

  std::cout << "salimos del for" << "\n";

  this->normales_vec = model->model_buffers["NV"];

  delete model;

  std::cout << " finalizamos el consturctor" << "\n";
}

// Model::Model(GLfloat* vertices, GLuint indices){}

void Model::initModel() {

  // creando los arreglos para los vertices normales e indices_vec
  int VBO_size = vertices_vec.size();
  int EBO_size = indices_vec.size();
  int NV_size = normales_vec.size();

  GLfloat *vertices = new GLfloat[VBO_size];
  GLuint *indices = new GLuint[EBO_size];
  GLfloat *normales = new GLfloat[NV_size];

  for (int i = 0; i < VBO_size; i++) {
    vertices[i] = this->vertices_vec[i];
  }

  for (int i = 0; i < EBO_size; i++) {
    indices[i] = this->indices_vec[i];
  }
  for (int i = 0; i < NV_size; i++) {
    normales[i] = this->normales_vec[i];
  }

  modelmat = glm::mat4(1.0f);
  shader = new Shader("./shader/cubo_shade.vert", "./shader/cubo_shade.frag");
  // Crear y enlazar el VAO y VBO

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  glGenBuffers(1, &NVBO);
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, VBO_size * sizeof(GLfloat), vertices,
               GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, EBO_size * sizeof(GLuint), indices,
               GL_STATIC_DRAW);
  // Especificar el layout del vertex shader
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                        (GLvoid *)0);

  glEnableVertexAttribArray(0);
  // bind las normales
  glBindBuffer(GL_ARRAY_BUFFER, NVBO);
  glBufferData(GL_ARRAY_BUFFER, NV_size * sizeof(GLfloat), normales,
               GL_STATIC_DRAW);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                        (GLvoid *)0);
  glEnableVertexAttribArray(1);

  delete[] vertices;
  delete[] indices;
  delete[] normales;
}

void Model::updateModel(float timeValue) {
  angle = timeValue * glm::radians(50.0f); // 50 grados por segundo

  modelmat = glm::rotate(
      glm::mat4(1.0), angle,
      glm::vec3(0.0f, 1.0f, 0.0f)); // Rotar alrededor de (0.5, 1.0, 0.0)
}

void Model::renderModel(glm::mat4 view, glm::mat4 projection) {

  shader->use();

  // Enviar las matrices al shader
  shader->setVec3("posCam", glm::vec3(0.0f, 0.0f, -10.0f));
  shader->setMat4x4("model", modelmat);
  shader->setMat4x4("view",
                    glm::lookAt(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0),
                                glm::vec3(0.0, 1.0, 0.0)));
  shader->setMat4x4("projection", projection);

  // Dibujar el cubo
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, indices_vec.size(), GL_UNSIGNED_INT, 0);
}
void Model::finish() {

  shader->terminate();
  delete (shader);

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
}
