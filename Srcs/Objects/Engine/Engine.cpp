//
// Engine.cpp for engine in /home/jsx/Epitech/tek2/C++2/plazza/cpp_plazza/Srcs/Objects/Engine/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Wed Apr 19 18:14:47 2017 jsx
// Last update Fri Apr 28 23:02:46 2017 jsx
//

#include "Engine.hpp"

plazza::Engine::Engine()
:
  _cv(nullptr),
  _ui(nullptr),
  _write_lbegn(new ccry::WritePipe("_LINK_ENGINE(w)_LOAD_BALANCING(r)_"))
{
  _write_lbegn->create();
}

plazza::Engine::~Engine() {
  delete this->_write_lbegn;
}


bool   plazza::Engine::start(ccry::CondVar* cv, plazza::IUI* ui) {
  this->_ui = ui;
  this->_cv = cv;

  if (this->_ui == nullptr || this->_cv == nullptr) {
    return false;
  }

  while (this->_task.getQuery() != plazza::DataQuery::STOP) {
    std::function<void*(void*)> func = [&] (void*) {
      this->lap();
      return nullptr;
    };
    this->_cv->consume(func, nullptr);
  }
  return true;
}

bool plazza::Engine::lap() {
  this->_task = this->_ui->getTask();
  if (this->_task.getQuery() != plazza::DataQuery::UNDEFINED) {
    plazza::TaskMinify* minifiedTask = this->_task.decompose();
    if (!minifiedTask)
      return false;
    // ------------------------------------------
    // Write the struct content on the named pipe
    this->_write_lbegn->Write(minifiedTask, minifiedTask->size);
    // ------------------------------------------
    delete[] minifiedTask;
  }
  return true;
}
