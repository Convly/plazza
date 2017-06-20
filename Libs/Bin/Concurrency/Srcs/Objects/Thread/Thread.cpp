//
// Thread.cpp for thread in /home/jsx/Epitech/tek2/C++2/plazza/tmp/bootstrap/ex4/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Mon Apr 10 12:03:13 2017 jsx
// Last update Wed Apr 19 23:57:27 2017 jsx
//

#include "Thread.hpp"

ccry::Thread::Thread(std::function<void*(void*)> func, void* arg)
:
  _thread(std::thread(func, arg))
{

}

ccry::Thread::~Thread() {

}

bool      ccry::Thread::getStatus() const {
  return this->_status;
}

void      ccry::Thread::join() {
  this->_thread.join();
}

void*    ccry::Thread::getReturnValue() const {
  return *(this->_ret);
}
