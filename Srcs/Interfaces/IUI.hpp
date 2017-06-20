//
// IUI.hpp for IUI in /home/jsx/Epitech/tek2/C++2/plazza/cpp_plazza/Srcs/Interfaces/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Mon Apr 10 19:07:06 2017 jsx
// Last update Fri Apr 28 22:58:30 2017 jsx
//

#ifndef IUI_HPP
#define IUI_HPP

#include <list>
#include <map>
#include "CCRY/all.hpp"
#include "Task.hpp"

namespace plazza {
  class IUI {

    // GETTERS
    public:
      virtual Task    getTask() = 0; // Return the oldest task in the queue
      virtual void    start(ccry::CondVar*, int, plazza::LoadBalancerStatus&, size_t &) = 0;

    public:
      virtual ~IUI () {};
  };
}

#endif /* end of include guard: IUI_HPP */
