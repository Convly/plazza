//
// fileExist.cpp for fileexist in /home/jsx/Epitech/tek2/C++2/plazza/cpp_plazza/Libs/Bin/Utils/Srcs/Functions/fileExist/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Thu Apr 20 20:37:31 2017 jsx
// Last update Thu Apr 20 20:37:46 2017 jsx
//

#include "fileExist.hpp"

/* FILE EXIST */
bool                  utils::fileExist(std::string const& filepath)
{
  std::ifstream       ifs(filepath);
  bool                doesExist;

  doesExist = ifs.good();
  ifs.close();
  return (doesExist);
}
