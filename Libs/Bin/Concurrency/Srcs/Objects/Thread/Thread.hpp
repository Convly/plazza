//
// Thread.hpp for thread in /home/jsx/Epitech/tek2/C++2/plazza/cpp_plazza/Srcs/Objects/Concurrency/Srcs/Objects/Thread/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Mon Apr 17 18:00:32 2017 jsx
// Last update Tue Apr 18 17:11:45 2017 jsx
//

#ifndef THREAD_HPP
#define THREAD_HPP

#include "IThread.hpp"

namespace ccry {
  class Thread : public IThread {
  private:
    bool        _status;
    std::thread _thread;
    void**      _ret;

  public:
    virtual void  join();
    virtual bool  getStatus() const;
    virtual void* getReturnValue() const;

  public:
    Thread (std::function<void*(void*)>, void*);
    virtual ~Thread ();
  };
}

#endif /* end of include guard: THREAD_HPP */
