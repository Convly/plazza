//
// ScopedLock.cpp for scopedlock in /home/jsx/Epitech/tek2/C++2/plazza/cpp_plazza/Libs/Bin/Concurrency/Srcs/Objects/ScopedLock/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Wed Apr 19 15:52:18 2017 jsx
// Last update Wed Apr 19 19:11:59 2017 jsx
//

#include "ScopedLock.hpp"

ccry::ScopedLock::ScopedLock(ccry::IMutex* mutex)
{
  this->_mutex = mutex;
  this->_mutex->lock();
}

ccry::ScopedLock::~ScopedLock() {
  this->_mutex->unlock();
}
