//
// Core.hpp for core in /home/jsx/Epitech/tek2/C++2/plazza/cpp_plazza/Srcs/Objects/Core/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Wed Apr 19 16:35:23 2017 jsx
// Last update Fri Apr 28 22:37:53 2017 jsx
//

#ifndef CORE_HPP_
#define CORE_HPP_

#include <unistd.h>
#include <functional>
#include <iostream>
#include <unordered_map>
#include "IUI.hpp"
#include "Engine.hpp"
#include "LoadBalancing.hpp"
#include "CCRY/all.hpp"
#include "DLLoader.hpp"

namespace plazza {
  class Core {
    private:
      int                                               _pop;
      const std::string                                 _libPath;
      const bool                                        _noise;
      plazza::IUI                                       *_ui;
      plazza::Engine                                    *_engine;
      plazza::LoadBalancing                             *_loadBalancing;
      std::unordered_map<std::string, ccry::IMutex*>    _mutexs;
      std::unordered_map<std::string, ccry::IThread*>   _threads;
      DLLoader<plazza::IUI>                             _uiLoader;
      ccry::CondVar                                     *_cvLinker;
      plazza::LoadBalancerStatus                        _lbStatus;

    private:
      void initIUIInstance();

    public:
      std::unordered_map<std::string, ccry::IThread*> getThreads() const;
      std::unordered_map<std::string, ccry::IMutex*> getMutexs() const;
      const std::string & getLibPath() const;
      plazza::IUI* getUI() const;
      plazza::Engine* getEngine() const;
      bool isVerbose() const;

    public:
      bool startUi();
      bool startEngine();
      bool startLoadBalancing();

    public:
      Core (const std::string & libPath, int pop, bool noiseMode = false);
      virtual ~Core ();
  };
} /* plazza */

#endif /* end of include guard: CORE_HPP_ */
