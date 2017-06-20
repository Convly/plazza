//
// ThreadPool.hpp for threadpool in /home/jsx/Epitech/tek2/C++2/plazza/cpp_plazza/Srcs/Objects/ThreadPool/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Mon Apr 24 11:52:08 2017 jsx
// Last update Sat Apr 29 21:14:19 2017 jsx
//

#ifndef THREAD_POOL_
#define THREAD_POOL_

#include <unordered_map>
#include <cstring>
#include <list>
#include "CCRY/all.hpp"
#include "Scrapper.hpp"
#include "Task.hpp"

namespace plazza {
  class ThreadPool {
  private:
      ccry::Mutex       mutex;
      ccry::ReadPipe*   _reader;
      ccry::WritePipe*  _lbWriter;
      bool              leave;
      int               _nbThread;
      std::list<plazza::Task>      _tasks;
      std::unordered_map<size_t, ccry::IThread*> _threads;
      std::unordered_map<size_t, bool> _states;

  public:
    ThreadPool (size_t);
    ~ThreadPool ();

  public:
    void  notifyLoadBalancing(const std::string &) const;
    int   getAvailableWorker();
  };
} /* plazza */

#endif /* end of include guard: THREAD_POOL_ */
