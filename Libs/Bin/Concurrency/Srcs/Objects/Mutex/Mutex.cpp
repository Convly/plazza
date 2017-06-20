//
// Mutex.cpp for Mutex in /home/jsx/Epitech/tek2/C++2/plazza/cpp_plazza/Srcs/Objects/Concurrency/Srcs/Objects/Mutex/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Mon Apr 17 18:13:56 2017 jsx
// Last update Thu Apr 20 14:17:16 2017 jsx
//

#include "Mutex.hpp"

ccry::Mutex::Mutex()
:
  _mutex()
{
}

ccry::Mutex::~Mutex() {
}

/* ACTIONS */

void ccry::Mutex::lock() {
  this->_mutex.lock();
}

void ccry::Mutex::unlock() {
  this->_mutex.unlock();
}

bool ccry::Mutex::trylock() {
  return this->_mutex.try_lock();
}

std::mutex & ccry::Mutex::getMutex() {
  return this->_mutex;
}
