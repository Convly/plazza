/*
** TaskResult.cpp for Rendu in /home/cauvin_m/Rendu/cpp_plazza/Srcs/Objects/TaskResult
**
** Made by cauvin-m
** Login   <cauvin_m@epitech.net>
**
** Started on  Thu Apr 20 15:09:19 2017 cauvin-m
** Last update Tue Apr 25 18:10:05 2017 cauvin-m
*/

#include "TaskResult.hpp"

plazza::TaskResult::TaskResult()
{

}

plazza::TaskResult::~TaskResult()
{

}

void    plazza::TaskResult::addResult(size_t const& id, std::string const& data, DecryptionType const& type)
{
  this->_result.push_back(DataTaskResult(id, data, type));
}

std::vector<plazza::DataTaskResult>   plazza::TaskResult::getResult() const
{
  return (this->_result);
}

plazza::TaskResult    &plazza::TaskResult::operator=(TaskResult const& taskResult)
{
  if (this != &taskResult)
    this->_result = taskResult.getResult();
  return (*this);
}

plazza::TaskResult                  &plazza::TaskResult::operator+=(TaskResult const& taskResult)
{
  std::vector<DataTaskResult>       result = taskResult.getResult();

  for (size_t i = 0; i < result.size(); i++)
    this->_result.push_back(result[i]);
  return (*this);
}
