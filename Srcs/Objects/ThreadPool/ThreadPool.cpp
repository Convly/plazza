//
// ThreadPool.cpp for threadpool in /home/jsx/Epitech/tek2/C++2/plazza/cpp_plazza/Srcs/Objects/ThreadPool/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Mon Apr 24 11:52:45 2017 jsx
// Last update Sun Apr 30 03:35:10 2017 jsx
//

#include <vector>
#include <algorithm>
#include <chrono>
#include "ThreadPool.hpp"

plazza::ThreadPool::ThreadPool(size_t nbThread)
:
  _reader(new ccry::ReadPipe(("_LINKER_LOAD_BALANCING(w)_PROCESS" + std::to_string(getpid()) + "(r)_"))),
  _lbWriter(new ccry::WritePipe("_LINKER_PROCESS(w)_LOAD_BALANCING(r)_")),
  leave(false),
  _nbThread(nbThread)
{

  this->_reader->create();
  this->_lbWriter->create();
  for (size_t i = 0; i < nbThread; i++) {
      {
        ccry::ScopedLock scopedLock(&mutex);
        this->_states[i] = false;
      }
      std::function<void*(void*)> func = [&] (void*) {
        plazza::Task task;
        int id = i - 1;
        bool activated = false;
        bool nothingIn = true;
        while(!leave || !nothingIn) {
          {
            ccry::ScopedLock scopedLock(&mutex);
            if (this->_tasks.size() > 0) {
              nothingIn = false;
              task = this->_tasks.back();
              this->_tasks.pop_back();
              this->_states[id] = true;
              activated = true;
            } else {
              nothingIn = true;
              this->_states[id] = false;
            }
          }
          if (activated) {
            plazza::Scrapper scrapper(task);
            scrapper.run();
            activated = false;
            {
              ccry::ScopedLock scopedLock(&mutex);
              this->_states[id] = false;
            }
            this->notifyLoadBalancing(std::to_string(getpid()) + ":" + std::to_string(this->getAvailableWorker()) + "\n");
          }
        }
        return nullptr;
    };
    this->_threads[i] = new ccry::Thread(func, nullptr);
  }

  int             ntm = this->_nbThread;
  std::time_t     start;

  start = std::time(nullptr);
  plazza::TaskMinify  m_task;

  while (!leave && std::time(nullptr) - start < 5) {
    // Listen for new tasks
      std::memset(&m_task, 0, sizeof(plazza::TaskMinify));
      if (this->_reader->Read(&m_task, sizeof(plazza::TaskMinify)) > 0) {
        if (m_task.query == -1) {
          leave = true;
        } else {
          {
            ccry::ScopedLock scopedLock(&mutex);
            this->_tasks.push_front(plazza::Task(m_task));
          }
        }
      }
      // -----------------
      ntm = this->getAvailableWorker();
      if (ntm != this->_nbThread * 2) {
        start = std::time(nullptr);
      }
  }
  leave = true;
}

int   plazza::ThreadPool::getAvailableWorker() {
  ccry::ScopedLock scopedLock(&mutex);
  int count = this->_nbThread * 2;
  for (int i = 0; i < this->_nbThread; i++) {
    if (this->_states[i] == true) count--;
  }
  return count - this->_tasks.size();
}

void  plazza::ThreadPool::notifyLoadBalancing(const std::string & msg) const {
  char plbBuffer[4096];
  std::memset(&plbBuffer, 0, 4096);
  msg.copy(plbBuffer, msg.size());
  this->_lbWriter->Write(&plbBuffer, 4096);
}

plazza::ThreadPool::~ThreadPool() {
  // Wait for all threads to complete their jobs
  for (auto it = this->_threads.begin(); it != this->_threads.end(); it++) {
    it->second->join();
    delete it->second;
  }
  // Then notify the loadbalancer that we're out
  this->notifyLoadBalancing(std::to_string(getpid()) + ":" + "EXIT_PROCESS" + "\n");

  delete this->_reader;
}
