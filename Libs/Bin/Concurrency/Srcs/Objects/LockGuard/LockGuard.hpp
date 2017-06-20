//
// LockGuard.hpp for lockguard in /home/jsx/Epitech/tek2/C++2/plazza/cpp_plazza/Libs/Bin/Concurrency/Srcs/Objects/LockGuard/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Thu Apr 20 12:15:17 2017 jsx
// Last update Thu Apr 20 15:18:54 2017 jsx
//

#ifndef LOCK_GUARD_HPP_
#define LOCK_GUARD_HPP_

#include "Mutex.hpp"

namespace ccry {
  class LockGuard {
  private:
    ccry::IMutex* _mutex;

  public:
    LockGuard (ccry::IMutex*);
    ~LockGuard ();
  };
} /* ccry */

#endif /* end of include guard: LOCK_GUARD_HPP_ */
