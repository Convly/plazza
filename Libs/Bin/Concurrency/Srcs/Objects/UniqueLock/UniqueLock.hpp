//
// UniqueLock.hpp for uniquelock in /home/jsx/Epitech/tek2/C++2/plazza/cpp_plazza/Libs/Bin/Concurrency/Srcs/Objects/UniqueLock/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Thu Apr 20 12:13:47 2017 jsx
// Last update Thu Apr 20 15:55:01 2017 jsx
//

#ifndef UNIQUE_LOCK_HPP_
#define UNIQUE_LOCK_HPP_

#include "Mutex.hpp"

namespace ccry {
  class UniqueLock {
  private:
    ccry::IMutex* _mutex;
    std::unique_lock<std::mutex> _lock;

  public:
    UniqueLock (ccry::Mutex*);
    ~UniqueLock ();

  public:
    void lock();
    bool try_lock();
    void unlock();
    std::unique_lock<std::mutex>& getLock();
  };
} /* ccry */

#endif /* end of include guard: UNIQUE_LOCK_HPP_ */
