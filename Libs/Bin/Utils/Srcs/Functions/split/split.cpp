//
// split.cpp for split in /home/jsx/Epitech/tek2/C++2/plazza/cpp_plazza/Libs/Bin/Utils/Srcs/Functions/split/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Thu Apr 20 20:35:47 2017 jsx
// Last update Thu Apr 20 20:36:08 2017 jsx
//

#include "split.hpp"

/* SPLIT */
template<typename Out>
void utils::split(const std::string &s, char delim, Out result) {
  std::stringstream ss;
  ss.str(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
    if (item != "")
    *(result++) = item;
  }
}

std::vector<std::string> utils::split(const std::string &s, char delim) {
  std::vector<std::string> elems;
  split(s, delim, std::back_inserter(elems));
  return elems;
}
/* -------- */
