/*
** TaskResult.hpp for Rendu in /home/cauvin_m/Rendu/cpp_plazza/Srcs/Objects/TaskResult
**
** Made by cauvin-m
** Login   <cauvin_m@epitech.net>
**
** Started on  Thu Apr 20 15:09:21 2017 cauvin-m
** Last update Tue Apr 25 18:18:24 2017 cauvin-m
*/

#ifndef TASKRESULT_HPP_
#define  TASKRESULT_HPP_

# include <vector>
# include <iostream>

namespace plazza
{
  enum DecryptionType
  {
    UNCRYPTED = 0,
    CAESAR = 1,
    XOR = 2
  };

  struct DataTaskResult
  {
    DataTaskResult(size_t const& i, std::string const& d, DecryptionType const& t) : id(i), data(d), type(t) {}
    virtual ~DataTaskResult() {};

    size_t          id;
    std::string     data;
    DecryptionType  type;
  };

  class TaskResult
  {
  private:
    std::vector<DataTaskResult>   _result;

  public:
    TaskResult();
    virtual ~TaskResult();

    void                          addResult(size_t const& id, std::string const& data, DecryptionType const& type);

    std::vector<DataTaskResult>   getResult() const;

    TaskResult &operator=(TaskResult const& taskResult);
    TaskResult &operator+=(TaskResult const& taskResult);
  };
}

#endif /* TASKRESULT_HPP_ */
