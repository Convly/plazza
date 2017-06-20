//
// Engine.hpp for engine in /home/jsx/Epitech/tek2/C++2/plazza/cpp_plazza/Srcs/Objects/Engine/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Wed Apr 19 18:14:44 2017 jsx
// Last update Tue Apr 25 23:13:14 2017 jsx
//

#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include "IUI.hpp"
#include "Task.hpp"
#include "Scrapper.hpp"
#include "CCRY/all.hpp"

namespace plazza {
  class Engine {
  private:
    ccry::CondVar* _cv;
    plazza::IUI* _ui;
    plazza::Task _task;
    ccry::WritePipe* _write_lbegn;

  public:
    bool   start(ccry::CondVar*, plazza::IUI*);

  private:
    bool   lap();

  public:
    Engine ();
    ~Engine ();
  };
} /* plazza */

#endif /* end of include guard: ENGINE_HPP_ */
