//
// Date.cpp for date in /home/jsx/Epitech/tek2/C++2/plazza/cpp_plazza/Srcs/Objects/Date/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Mon Apr 10 22:29:08 2017 jsx
// Last update Mon Apr 10 23:21:01 2017 jsx
//

#include "Date.hpp"
#include "../../Modules/plazzaTypes.hpp"

plazza::Date::Date()
:
  _date(GETNOW())
{

}

plazza::Date::~Date() {

}

plazza::time      plazza::Date::getDate() const {return this->_date;}

std::string       plazza::Date::beautifier() const
{
  std::time_t     cTime = std::chrono::system_clock::to_time_t(this->_date);
  std::string     strTime = std::ctime(&cTime);

  strTime.at(strTime.size() - 1) = '\0';
  return strTime;
}

void plazza::Date::setDate(const plazza::time &date) {
  _date = date;
}
