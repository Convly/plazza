//
// IThread.hpp for Ithread in /home/jsx/Epitech/tek2/C++2/plazza/cpp_plazza/Srcs/Objects/Concurrency/Srcs/Interfaces/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Mon Apr 17 18:01:44 2017 jsx
// Last update Tue Apr 18 17:09:25 2017 jsx
//

#ifndef ITHREAD_HPP
#define ITHREAD_HPP

#include <thread>

namespace ccry {
  class IThread {
  public:
    virtual ~IThread () {};

  public:
    virtual void join() = 0;
    virtual bool getStatus() const = 0;
  };
}

#endif /* end of include guard: ITHREAD_HPP */
