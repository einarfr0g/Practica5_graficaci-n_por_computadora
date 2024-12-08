#pragma once
#include "../header/OBJ_reader.h"
#include "OBJ_reader_function.cpp"

OBJ_reader::OBJ_reader(std::string OBJ_dir) {
  this->model_buffers = read_OBJ(OBJ_dir);
  this->VBO_size = model_buffers["VBO"].size();
  this->EBO_size = model_buffers["EBO"].size();
}
