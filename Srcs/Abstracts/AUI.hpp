//
// AUI.hpp for AUI in /home/jsx/Epitech/tek2/C++2/plazza/cpp_plazza/Srcs/Abstracts/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Mon Apr 10 19:51:50 2017 jsx
// Last update Fri Apr 28 22:58:28 2017 jsx
//

#ifndef AUI_HPP
#define AUI_HPP

#include "IUI.hpp"
#include "UTILS/all.hpp"

namespace plazza {
  class AUI : public IUI {
    protected:
      std::list<plazza::Task>           _tasksToDo;
      std::list<plazza::Task>           _tasksProcessing;
      std::list<plazza::Task>           _tasksCompleted;
      std::map<std::string, DataQuery>  _map;
      ccry::CondVar*                    _cv;
      ccry::ReadPipe                    *_rPipe;
      TaskResultMinify                  *_tmp;
      std::vector<TaskResultMinify *>   _resultList;
      int                               _nbThread;

    public:
      virtual void    readPipeTaskResultMinified(plazza::TaskResultMinify* obj)
      {
        std::memset(obj, 0, sizeof(plazza::TaskResultMinify));
        if (this->_rPipe->Read(obj, sizeof(plazza::TaskResultMinify)) > 0)
        {
          TaskResultMinify                  *newObj;

          newObj = obj->copy();
          this->_resultList.push_back(newObj);
          for (auto it = this->_tasksProcessing.begin(); it != this->_tasksProcessing.end(); it++) {
            if (it->getId() == newObj->idTask) {
              if (newObj->type == -1) {
                Task task = *it;
                this->_tasksCompleted.push_back(task);
                this->_tasksProcessing.erase(it);
                break;
              } else {
                it->getTaskResult().addResult(-1, newObj->result, static_cast<plazza::DecryptionType>(newObj->type));
                std::cout << newObj->result << std::endl;
              }
            }
          }
        }
      }
      // It should be the only "not pure" method in this abstract, it's implementation must not change from one UI to another
      virtual Task    getTask() {
        plazza::Task task;
        if (this->_tasksToDo.size() > 0) {
          task = *(this->_tasksToDo.begin());
          this->_tasksToDo.pop_front();
          if (task.getQuery() >= 0) {
            this->_tasksProcessing.push_back(task);
          }
        }
        return task;
      }

      virtual void  stop() {
        plazza::Task task;
        task.setQuery(plazza::DataQuery::STOP);
        this->_tasksToDo.push_back(task);
        this->_cv->produce();
      }

      virtual void    start(ccry::CondVar*, int, plazza::LoadBalancerStatus&, size_t &) = 0;

    public:
      AUI ()
      :
        _map({
          {"PHONE_NUMBER", DataQuery::PHONE_NUMBER},
          {"EMAIL_ADDRESS", DataQuery::EMAIL_ADDRESS},
          {"IP_ADDRESS", DataQuery::IP_ADDRESS}}),
        _cv(nullptr),
        _rPipe(new ccry::ReadPipe("_LINK_SCRAPPER(w)_UI(r)_")),
        _tmp(new plazza::TaskResultMinify[sizeof(plazza::TaskResultMinify)])
         {
           this->_rPipe->create();
         };
      virtual ~AUI () {
        delete this->_rPipe;
      };
  };
}

#endif /* end of include guard: AUI_HPP */
