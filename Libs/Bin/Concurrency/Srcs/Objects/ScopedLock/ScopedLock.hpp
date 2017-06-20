//
// ScopedLock.hpp for Scopedlock in /home/jsx/Epitech/tek2/C++2/plazza/cpp_plazza/Libs/Bin/Concurrency/Srcs/Objects/ScopedLock/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Wed Apr 19 15:52:34 2017 jsx
// Last update Wed Apr 19 18:32:21 2017 jsx
//

#ifndef SCOPEDLOCK_HPP
#define SCOPEDLOCK_HPP

#include "Mutex.hpp"

namespace ccry {
  class ScopedLock {
  private:
    ccry::IMutex* _mutex;

  public:
    ScopedLock (ccry::IMutex*);
    virtual ~ScopedLock ();
  };
}

#endif /* end of include guard: SCOPEDLOCK_HPP */
