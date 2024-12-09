#pragma once
#include <fstream>
#include <iostream>
#include <map>
#include <stdlib.h>
#include <string>
#include <vector>

/**
 * @brief genera un par con dos vectores de coordenas, first:representa a los
 * vertices second:representa a los indices;
 * @param name_document string que contiene el nombre del obj a renderizar
 * @return par con dos vectores de Vector4
 */
std::map<std::string, std::vector<float>> read_OBJ(std::string name_document) {

  std::ifstream obj(name_document);
  std::string renglon;

  if (!obj.is_open())
    std::cout << "error al abrir el archivo" << "\n";
  // variable para guardar indices
  int aux_index = 0;

  // coordenadas de los vectores
  double x, y, z, w;

  std::vector<float> points;
  // vector de indices
  std::vector<float> indexes;
  // vector de normales
  std::vector<float> normales;
  // vector maximo para la camara
  std::vector<float> vecmax;
  // string auxiliar
  std::string txt_storage;

  double max_x = 0;
  double max_y = 0;
  double max_z = 10;

  while (!obj.eof()) {

    std::getline(obj, renglon);

    if (renglon == "")
      continue;

    if (renglon[0] == 'v' && renglon[1] == ' ') {

      renglon.erase(0, 2);
      // x
      aux_index = renglon.find(" ");

      x = stod(renglon.substr(0, aux_index));

      renglon.erase(0, aux_index + 1);

      // y
      aux_index = renglon.find(" ");

      y = stod(renglon.substr(0, aux_index));

      renglon.erase(0, aux_index + 1);

      // z
      aux_index = renglon.find(" ");

      z = stod(renglon.substr(0, aux_index));

      points.push_back(x);
      points.push_back(y);
      points.push_back(z);
      // std::cout << "pasoo un vector:" << x << " " << y << " " << z << "\n";
    }

    if (renglon[0] == 'v' && renglon[1] == 'n') {
      renglon.erase(0, 3);
      // x
      aux_index = renglon.find(" ");

      x = stod(renglon.substr(0, aux_index));

      renglon.erase(0, aux_index + 1);

      // y
      aux_index = renglon.find(" ");

      y = stod(renglon.substr(0, aux_index));

      renglon.erase(0, aux_index + 1);

      // z
      aux_index = renglon.find(" ");

      z = stod(renglon.substr(0, aux_index));

      if (max_x < x)
        max_x = x;
      if (max_y < y)
        max_y = y;
      if (max_z < z)
        max_z = z;

      normales.push_back(x);
      normales.push_back(y);
      normales.push_back(z);
      // std::cout << "pasoo un normal:" << x << " " << y << " " << z << "\n";
    }

    if (renglon[0] == 'f') {
      renglon.erase(0, 2);
      w = -1;

      // x
      aux_index = renglon.find(" ");

      txt_storage = renglon.substr(0, aux_index + 1);

      // cout<<txt_storage.substr(0,txt_storage.find("/"))<<"\n";

      x = stod(txt_storage.substr(0, txt_storage.find("/")));

      renglon.erase(0, aux_index + 1);

      // y
      aux_index = renglon.find(" ");

      txt_storage = renglon.substr(0, aux_index + 1);

      y = stod(txt_storage.substr(0, txt_storage.find("/")));

      renglon.erase(0, aux_index + 1);
      // z

      if (renglon.find(" ") == -1) {
        // cout<<renglon.substr(0,renglon.find("/"))<<"\n";

        z = stod(renglon.substr(0, renglon.find("/")));

        indexes.push_back(x);
        indexes.push_back(y);
        indexes.push_back(z);

        continue;
      } else {

        aux_index = renglon.find(" ");

        txt_storage = renglon.substr(0, aux_index + 1);

        z = stod(txt_storage.substr(0, txt_storage.find("/")));

        renglon.erase(0, aux_index + 1);
      }

      // w = stod(renglon.substr(0, renglon.find("/")));

      // std::cout << "pasoo un indice:" << x << " " << y << " " << z << "\n";

      indexes.push_back(x);
      indexes.push_back(y);
      indexes.push_back(z);
      // indexes.push_back(w);
    }

    // std::cout<<renglon<<"\n";
  }

  vecmax.push_back(max_x);
  vecmax.push_back(max_y);
  vecmax.push_back(max_z);

  std::cout << vecmax.size() << "\n";

  std::map<std::string, std::vector<float>> model_data;
  model_data["VBO"] = points;
  model_data["EBO"] = indexes;
  model_data["NV"] = normales;
  model_data["MAXVEC"] = vecmax;

  return model_data;
}
