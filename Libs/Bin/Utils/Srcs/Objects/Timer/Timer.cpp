//
// Timer.cpp for timer in /home/jsx/Epitech/tek2/C++2/plazza/cpp_plazza/Libs/Bin/Utils/Srcs/Objects/Timer/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Sun Apr 30 02:55:46 2017 jsx
// Last update Sun Apr 30 03:03:55 2017 jsx
//

#include "Timer.hpp"

utils::Timer::Timer()
:
  _tps(1000000)
{

}

utils::Timer::Timer(size_t ttime)
:
  _tps(ttime)
{

}

utils::Timer::~Timer() {

}

void  utils::Timer::lap() const {
  usleep(this->_tps);
}

void  utils::Timer::set(size_t ttime) {
  this->_tps = ttime;
}
