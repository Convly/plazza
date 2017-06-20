//
// UniqueLock.cpp for uniquelock in /home/jsx/Epitech/tek2/C++2/plazza/cpp_plazza/Libs/Bin/Concurrency/Srcs/Objects/UniqueLock/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Thu Apr 20 12:14:28 2017 jsx
// Last update Thu Apr 20 17:53:33 2017 jsx
//

#include <iostream>
#include "UniqueLock.hpp"

ccry::UniqueLock::UniqueLock(ccry::Mutex* mutex)
:
  _mutex(mutex),
  _lock(mutex->getMutex())
{
}

ccry::UniqueLock::~UniqueLock() {
  this->_lock.unlock();
}

void ccry::UniqueLock::lock() {
  this->_lock.lock();
}

bool ccry::UniqueLock::try_lock() {
  return this->_lock.try_lock();
}

void ccry::UniqueLock::unlock() {
  this->_lock.unlock();
}

std::unique_lock<std::mutex> & ccry::UniqueLock::getLock() {
  return this->_lock;
}
