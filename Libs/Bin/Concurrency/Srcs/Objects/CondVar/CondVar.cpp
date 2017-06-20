//
// CondVar.cpp for condvar in /home/jsx/Epitech/tek2/C++2/plazza/cpp_plazza/Libs/Bin/Concurrency/Srcs/Objects/CondVar/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Wed Apr 19 23:00:40 2017 jsx
// Last update Thu Apr 20 18:08:25 2017 jsx
//

#include "CondVar.hpp"

ccry::CondVar::CondVar()
:
  _produced(false),
  _consumed(false),
  _mutex(new ccry::Mutex)
{
}

ccry::CondVar::~CondVar() {
  delete this->_mutex;
}

void      ccry::CondVar::produce() {

  {
    ccry::LockGuard lg(this->_mutex);
    this->_produced = true;
  }

  this->_cv.notify_one();

  {
    ccry::UniqueLock ul(this->_mutex);

    while (!this->_consumed)
      this->_cv.wait(ul.getLock());

    this->_consumed = false;
  }

}

void      ccry::CondVar::consume(std::function<void *(void*)> func, void* arg) {

  ccry::UniqueLock lock(this->_mutex);

  while (!this->_produced)
    this->_cv.wait(lock.getLock());
  this->_produced = false;

  func(arg);

  this->_consumed = true;
  this->_cv.notify_one();
}
