//
// Timer.hpp for timer in /home/jsx/Epitech/tek2/C++2/plazza/cpp_plazza/Libs/Bin/Utils/Srcs/Objects/Timer/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Sun Apr 30 02:55:42 2017 jsx
// Last update Sun Apr 30 03:04:01 2017 jsx
//

#ifndef TIMER_UTILS_HPP_
#define TIMER_UTILS_HPP_

#include <unistd.h>

namespace utils {
  class Timer {
    private:
      size_t  _tps;

    public:
      Timer ();
      Timer (size_t);
      virtual ~Timer ();

      void  lap() const;
      void  set(size_t);
  };
} /* utils */

#endif /* end of include guard: TIMER_UTILS_HPP_ */
