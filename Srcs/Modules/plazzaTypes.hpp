//
// types.hpp for types in /home/jsx/Epitech/tek2/C++2/plazza/cpp_plazza/Srcs/Modules/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Mon Apr 10 19:37:13 2017 jsx
// Last update Sun Apr 30 14:40:38 2017 jsx
//

#ifndef TYPES_HPP_
#define TYPES_HPP_

#include <vector>
#include <string>
#include <chrono>
#include <cstring>
#include "CCRY/lock.hpp"

namespace plazza {
  # define GETNOW         (std::chrono::system_clock::now)

  extern size_t G_TASKID;
  extern size_t G_DECRYPTFLAG;

  // DataQuery => Used to define the type of a query in a command
  enum DataQuery {
    UNDEFINED = -2,
    STOP = -1,
    PHONE_NUMBER = 0,
    EMAIL_ADDRESS,
    IP_ADDRESS
  };

  typedef std::chrono::time_point<std::chrono::system_clock>  time;
  typedef std::chrono::duration<double>    duration;

  typedef struct {
    int                         id;
    int                         query;
    size_t                      size;
    char                        paths[4000];
  } TaskMinify;

  struct                  LoadBalancerStatus {
    int                   nbProcess;
    std::vector<pid_t>    pids;
    std::vector<int>      balance;
    ccry::Mutex           mutex;
  };

  struct TaskResultMinify
  {
    int   idTask;
    int   type;
    char  result[4096];

    TaskResultMinify    *copy()
    {
      TaskResultMinify  *newObj = new plazza::TaskResultMinify[sizeof(plazza::TaskResultMinify)];

      newObj->idTask = this->idTask;
      newObj->type = this->type;
      std::memcpy(newObj->result, this->result, 4096);
      return (newObj);
    }
  };
}

#endif /* end of include guard: TYPES_HPP_ */
