//
// split.hpp for split in /home/jsx/Epitech/tek2/C++2/plazza/cpp_plazza/Libs/Bin/Utils/Srcs/Functions/split/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Thu Apr 20 20:34:56 2017 jsx
// Last update Thu Apr 20 20:38:38 2017 jsx
//

#ifndef UTILS_SPLIT_HPP_
#define UTILS_SPLIT_HPP_

#include <vector>
#include <string>
#include <sstream>

namespace utils {
  template<typename Out>
  void split(const std::string &s, char delim, Out result);
  std::vector<std::string> split(const std::string &s, char delim);
} /* utils */

#endif /* end of include guard: UTILS_SPLIT_HPP_ */
