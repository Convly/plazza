//
// join.cpp for join in /home/jsx/Epitech/tek2/C++2/plazza/cpp_plazza/Libs/Bin/Utils/Srcs/Functions/join/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Thu Apr 20 20:32:27 2017 jsx
// Last update Thu Apr 20 20:34:14 2017 jsx
//

#include "join.hpp"

/* JOIN */
std::string   utils::join(std::vector<std::string> v, std::string j) {
  std::string result = "";
  int count = 0;
  int size = v.size();
  for (auto it = v.begin(); it != v.end(); it++) {
    result += *it;
    if (count < size - 1)
      result += j;
    count++;
  }
  return result;
}
