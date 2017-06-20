//
// LoadBalancing.hpp for laodbalancing in /home/jsx/Epitech/tek2/C++2/plazza/cpp_plazza/Srcs/Objects/LoadBalancing/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Mon Apr 24 19:26:08 2017 jsx
// Last update Sun Apr 30 03:04:24 2017 jsx
//

#ifndef LOAD_BALANCING_HPP_
#define LOAD_BALANCING_HPP_

#include <unistd.h>
#include <signal.h>
#include <unordered_map>
#include <cstring>
#include "UTILS/chrono.hpp"
#include "CCRY/all.hpp"
#include "Task.hpp"
#include "Scrapper.hpp"
#include "plazzaTypes.hpp"

namespace plazza {
  class LoadBalancing {
    private:
      int                                          _nbThreads;
      bool                                         _run;
      ccry::ReadPipe*                              _stateReader;
      ccry::ReadPipe*                              _read_lbegn;
      std::vector<ccry::Process*>                  _process;
      std::unordered_map<pid_t, ccry::WritePipe*>  _processTrigger;
      std::unordered_map<pid_t, int>               _remainings;

    public:
      LoadBalancing ();
      virtual ~LoadBalancing ();

    public:
      void balance(const plazza::Task&);
      void start(int, plazza::LoadBalancerStatus&);
      bool addProcess();
      void listenProcessStates();
  };
} /* plazza */

#endif /* end of include guard: LOAD_BALANCING_HPP_ */
