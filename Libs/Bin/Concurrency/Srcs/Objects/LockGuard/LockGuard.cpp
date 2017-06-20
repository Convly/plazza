//
// LockGuard.cpp for lockguard in /home/jsx/Epitech/tek2/C++2/plazza/cpp_plazza/Libs/Bin/Concurrency/Srcs/Objects/LockGuard/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Thu Apr 20 12:15:02 2017 jsx
// Last update Thu Apr 20 15:19:09 2017 jsx
//

#include "LockGuard.hpp"

ccry::LockGuard::LockGuard(ccry::IMutex* mutex)
:
  _mutex(mutex)
{
  this->_mutex->lock();
}

ccry::LockGuard::~LockGuard() {
  this->_mutex->unlock();
}
