//
// CondVar.hpp for condvar in /home/jsx/Epitech/tek2/C++2/plazza/cpp_plazza/Libs/Bin/Concurrency/Srcs/Objects/CondVar/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Wed Apr 19 22:58:40 2017 jsx
// Last update Thu Apr 20 17:47:59 2017 jsx
//

#ifndef COND_VAR_HPP_
#define COND_VAR_HPP_

#include <iostream>
#include <functional>
#include <condition_variable>
#include "UniqueLock.hpp"
#include "LockGuard.hpp"
#include "Mutex.hpp"

namespace ccry {

  enum DPPC {
    CONSUMMER,
    PRODUCER
  };

  class CondVar {
    private:
      bool                          _produced;
      bool                          _consumed;
      ccry::Mutex*                  _mutex;
      std::condition_variable_any   _cv;

    public:
      CondVar ();
      ~CondVar ();

    public:
      void produce();
      void consume(std::function<void*(void*)>, void*);
  };
} /* ccry */

#endif /* end of include guard: COND_VAR_HPP_ */
