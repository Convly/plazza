//
// Date.hpp for date in /home/jsx/Epitech/tek2/C++2/plazza/cpp_plazza/Srcs/Objects/Date/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Mon Apr 10 22:22:43 2017 jsx
// Last update Mon Apr 10 23:21:03 2017 jsx
//

#ifndef DATE_HPP_
#define DATE_HPP_

#include <iostream>
#include "plazzaTypes.hpp"
#include "../../Modules/plazzaTypes.hpp"

namespace plazza {
  class Date {
    private:
      plazza::time    _date;
  public:
      void setDate(const plazza::time &_date);

  public:
      std::string         beautifier() const ;

      plazza::time        getDate() const;

    public:
      plazza::Date    &operator=(const plazza::time &);
      Date ();
      virtual ~Date ();
  };
}

#endif /* end of include guard: DATE_HPP_ */
