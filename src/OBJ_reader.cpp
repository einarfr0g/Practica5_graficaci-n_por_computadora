#pragma once
#include "../header/OBJ_reader.h"
#include "OBJ_reader_function.cpp"
#include <map>

OBJ_reader::OBJ_reader(std::string OBJ_dir) {
  std::map<std::string, std::vector<GLfloat>> mapa;
  obj obj_struct = read_obj(OBJ_dir);
  mapa["VBO"] = obj_struct.points;
  mapa["NV"] = obj_struct.normals;
  for (auto e : obj_struct.indices) {
    mapa["EBO"].push_back((GLfloat)e.index1.v);
    mapa["EBO"].push_back((GLfloat)e.index2.v);
    mapa["EBO"].push_back((GLfloat)e.index3.v);
  }
  this->model_buffers = mapa;
  this->VBO_size = model_buffers["VBO"].size();
  this->EBO_size = model_buffers["EBO"].size();
}
