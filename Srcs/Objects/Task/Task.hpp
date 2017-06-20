//
// Task.hpp for task in /home/jsx/Epitech/tek2/C++2/plazza/cpp_plazza/Srcs/Objects/Task/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Mon Apr 10 19:20:22 2017 jsx
// Last update Thu Apr 27 19:13:13 2017 jsx
//

#ifndef TASK_HPP_
#define TASK_HPP_

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstring>
#include "TaskResult.hpp"
#include "plazzaTypes.hpp"
#include "Date.hpp"
#include "UTILS/all.hpp"

namespace plazza {

  class Task {
    // ATTRIBUTES
    private:
      size_t                      _taskid;
      std::vector<std::string>    _paths;
      plazza::DataQuery           _query;
      plazza::TaskResult          _taskResult;
      plazza::Date                _instanciationDate;
      plazza::Date                _computeDate;
      plazza::Date                _completionDate;

    // GETTERS
    public:
      int                       getId() const;
      plazza::DataQuery         getQuery() const;
      std::vector<std::string>  getPaths() const;
      plazza::TaskResult        getTaskResult() const;
      plazza::Date              getInstanciationDate() const;
      plazza::Date              getComputeDate() const;
      plazza::Date              getCompletionDate() const;
      plazza::duration          getComputeDelay() const;

    // SETTERS
    void                        setId(int);
    void                        setQuery(DataQuery const& query);
    void                        setPaths(const std::vector<std::string> &);
    void                        setTaskResult(TaskResult const& taskResult);
    // TOOLS
    public:
      std::string                 getQueryString() const;
      bool                        addPath(const std::string &);
      void                        startCompute();
      void                        stopCompute();
      plazza::TaskMinify*         decompose() const;

    public:
      Task & operator=(const Task &);
      Task();
      Task(const plazza::TaskMinify &);
      Task (const plazza::DataQuery&, const std::vector<std::string>);
      virtual ~Task ();

  };
  std::ostream& operator<<(std::ostream&, const plazza::Task&);
}



#endif /* end of include guard: TASK_HPP_ */
