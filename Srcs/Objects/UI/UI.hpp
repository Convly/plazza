//
// UI.hpp for UI in /home/jsx/Epitech/tek2/C++2/plazza/cpp_plazza/Srcs/Objects/UI/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Mon Apr 10 18:39:18 2017 jsx
// Last update Fri Apr 28 22:59:36 2017 jsx
//

#ifndef UI_HPP_
#define UI_HPP_

#include <algorithm>
#include <sstream>
#include "AUI.hpp"

namespace plazza {
  class UI : public AUI
  {
    public:
      UI ();
      virtual ~UI ();

      virtual void    start(ccry::CondVar*, int, plazza::LoadBalancerStatus&, size_t &);

      void            addQueue(Task const& task);
      Task            strToTask(std::string const& cmd);
      bool            parseEntryLine(std::string const& line);
  };
}

#endif /* end of include guard: UI_HPP_ */
