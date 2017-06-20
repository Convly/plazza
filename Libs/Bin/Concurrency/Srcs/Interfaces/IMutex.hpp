//
// IMutex.hpp for imutex in /home/jsx/Epitech/tek2/C++2/plazza/tmp/bootstrap/ex2/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Mon Apr 10 10:51:39 2017 jsx
// Last update Tue Apr 18 17:50:06 2017 jsx
//

#ifndef IMUTEX_HPP
#define IMUTEX_HPP

#include <mutex>

namespace ccry {
  class IMutex {
  public:
    virtual ~IMutex(void) {};
    virtual void lock(void) = 0;
    virtual void unlock(void) = 0;
    virtual bool trylock(void) = 0;
  };
} /* ccry */

#endif /* end of include guard: IMUTEX_HPP */
