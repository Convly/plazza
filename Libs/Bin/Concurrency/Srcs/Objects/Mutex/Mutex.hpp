//
// Mutex.hpp for mutex in /home/jsx/Epitech/tek2/C++2/plazza/cpp_plazza/Srcs/Objects/Concurrency/Srcs/Objects/Mutex/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Mon Apr 17 18:14:04 2017 jsx
// Last update Thu Apr 20 14:17:21 2017 jsx
//

#ifndef MUTEX_HPP
#define MUTEX_HPP

#include "IMutex.hpp"

namespace ccry {
  class Mutex : public IMutex {
  private:
    std::mutex _mutex;

  public:
    virtual void lock(void);
    virtual void unlock(void);
    virtual bool trylock(void);

  public:
    std::mutex & getMutex();

  public:
    Mutex ();
    virtual ~Mutex ();
  };
} /* ccry */

#endif /* end of include guard: MUTEX_HPP */
