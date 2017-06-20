//
// Core.cpp for core in /home/jsx/Epitech/tek2/C++2/plazza/cpp_plazza/Srcs/Objects/Core/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Wed Apr 19 16:38:06 2017 jsx
// Last update Fri Apr 28 23:02:23 2017 jsx
//

#include "Core.hpp"

plazza::Core::Core(const std::string & libPath, int pop, bool noiseMode)
:
  _pop(pop),
  _libPath(libPath),
  _noise(noiseMode),
  _ui(nullptr),
  _engine(nullptr),
  _loadBalancing(nullptr),
  _uiLoader("UI Loader", false),
  _cvLinker(new ccry::CondVar)
{
  this->initIUIInstance();
  this->_lbStatus.nbProcess = 0;
}

plazza::Core::~Core() {
  for (auto it = this->_threads.begin(); it != this->_threads.end(); it++) {
    it->second->join();
    delete it->second;
  }
  for (auto it = this->_mutexs.begin(); it != this->_mutexs.end(); it++) {
    delete it->second;
  }

  if (this->_engine != nullptr) {
    delete this->_engine;
  }
  if (this->_loadBalancing != nullptr) {
    delete this->_loadBalancing;
  }

  if (this->_cvLinker) {
    delete this->_cvLinker;
  }

}

const std::string & plazza::Core::getLibPath() const {return this->_libPath;}
bool plazza::Core::isVerbose() const {return this->_noise;}
std::unordered_map<std::string, ccry::IThread*> plazza::Core::getThreads() const {return this->_threads;}
std::unordered_map<std::string, ccry::IMutex*> plazza::Core::getMutexs() const {return this->_mutexs;}
plazza::IUI* plazza::Core::getUI() const {return this->_ui;}
plazza::Engine* plazza::Core::getEngine() const {return this->_engine;}

// PRIVATE TOOLS

void      plazza::Core::initIUIInstance() {
  // Adding lib to the dlloader
  this->_uiLoader.addLib(this->_libPath);
  // Getting instance to the lib pointed by the key "libPath"
  this->_ui = this->_uiLoader.getInstance(this->getLibPath());
  if (this->_ui == nullptr) {
    std::exit(-1);
  }
}

// PUBLIC TOOLS

// Start user interface
bool plazza::Core::startUi() {
  std::function<void*(void*)> func = [&] (void*) {
    this->_ui->start(this->_cvLinker, this->_pop, this->_lbStatus, plazza::G_DECRYPTFLAG);
    return nullptr;
  };

  this->_threads["LINKER-UI"] = new ccry::Thread(func, nullptr);
  return true;
}

// Start engine for loaded UI
bool plazza::Core::startEngine() {
  this->_engine = new plazza::Engine;

  std::function<void*(void*)> func = [&] (void*) {
    this->_engine->start(this->_cvLinker, this->_ui);
    return nullptr;
  };

  this->_threads["LINKER-ENGINE"] = new ccry::Thread(func, nullptr);
  return true;
}

// Start engine for loaded UI
bool plazza::Core::startLoadBalancing() {
  this->_loadBalancing = new plazza::LoadBalancing;

  std::function<void*(void*)> func = [&] (void*) {
    this->_loadBalancing->start(this->_pop, this->_lbStatus);
    return nullptr;
  };

  this->_threads["LINKER-LOADBALANCING"] = new ccry::Thread(func, nullptr);
  return true;
}
