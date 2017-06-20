//
// LoadBalancing.cpp for loadbalancing in /home/jsx/Epitech/tek2/C++2/plazza/cpp_plazza/Srcs/Objects/LoadBalancing/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Mon Apr 24 19:27:02 2017 jsx
// Last update Sun Apr 30 03:36:34 2017 jsx
//

#include "LoadBalancing.hpp"
#include "ThreadPool.hpp"

plazza::LoadBalancing::LoadBalancing()
:
  _run(false),
  _stateReader(new ccry::ReadPipe("_LINKER_PROCESS(w)_LOAD_BALANCING(r)_")),
  _read_lbegn(new ccry::ReadPipe("_LINK_ENGINE(w)_LOAD_BALANCING(r)_"))
{
  this->_read_lbegn->create();
}

plazza::LoadBalancing::~LoadBalancing() {
  delete this->_stateReader;
  delete this->_read_lbegn;
}

// ----------------------------------------------------------

void          plazza::LoadBalancing::start(int nbThreads, plazza::LoadBalancerStatus& lbstatus) {
  bool _exit = false;
  this->_run = true;
  this->_nbThreads = nbThreads;
  this->_stateReader->create();
  std::vector<pid_t>    vpid;
  std::vector<int>      balance;
  plazza::TaskMinify* m_task = new plazza::TaskMinify[sizeof(plazza::TaskMinify)];
  this->addProcess();
  int rd;
  utils::Timer timer(10000);

  while (this->_run) {
    vpid.clear();
    balance.clear();
    for (auto it = this->_process.begin(); it != this->_process.end(); it++) {
      vpid.push_back((*it)->getPid());
      balance.push_back(this->_remainings[(*it)->getPid()]);
    }
    {
      ccry::ScopedLock lock(&(lbstatus.mutex));
      lbstatus.nbProcess = this->_process.size();
      lbstatus.pids = vpid;
      lbstatus.balance = balance;
    }

    timer.lap();
    this->listenProcessStates();
    while (this->_process.size() >= 10) {
      this->listenProcessStates();
    }

    if (_exit && this->_process.size() == 0) {
      this->_run = false;
    }
    if (_exit == false) {
      std::memset(m_task, 0, sizeof(plazza::TaskMinify));
      if ((rd = this->_read_lbegn->Read(m_task, sizeof(plazza::TaskMinify))) > 0) {
        if (m_task->query == -1) {
          _exit = true;
        }
        if (m_task->query >= -1) {
          this->balance(plazza::Task(*m_task));
        }
      }
    }
  }
  delete[] m_task;
}

void              plazza::LoadBalancing::listenProcessStates() {
  char                      buffer[4096];
  std::string               resultString;
  std::vector<std::string>  result;
  std::vector<std::string>  unitR;

  std::memset(&buffer, 0, 4096);
  if (this->_stateReader->Read(&buffer, 4096) > 0) {
    resultString = buffer;
    result = utils::split(buffer, '\n');
    for (auto it = result.begin(); it != result.end(); it++) {
      unitR = utils::split(*it, ':');
      if (unitR.size() == 2) {
        pid_t key = std::stoi(unitR.at(0));
        if (unitR.at(1) == "EXIT_PROCESS") {
          for (auto itP = this->_process.begin(); itP != this->_process.end(); itP++) {
            if ((*itP)->getPid() == key) {
              delete *itP;
              this->_process.erase(itP);
              this->_remainings.erase(key);
              delete this->_processTrigger[key];
              this->_processTrigger.erase(key);
              break;
            }
          }
        } else {
          this->_remainings[key] = std::stoi(unitR.at(1));
        }
      }
    }
  }
}

void        plazza::LoadBalancing::balance(const plazza::Task& task) {
  int minPl = (this->_nbThreads * 2) + 1;
  pid_t key = -1;
  if (task.getQuery() == plazza::DataQuery::STOP) {
    if (this->_process.size() == 0) {
      return ;
    } else {
      for (auto it = this->_process.begin(); it != this->_process.end(); it++) {
        {
          plazza::TaskMinify tm = *(task.decompose());
          this->_processTrigger[(*it)->getPid()]->Write(&tm, tm.size);
        }
      }
    }
  }

  for (auto it = this->_remainings.begin(); it != this->_remainings.end(); it++) {
    if ((it->second < minPl || key == -1) && it->second > 0) {
      key = it->first;
      minPl = it->second;
    }
  }
  if (key == -1) {
    this->addProcess();
    this->balance(task);
  } else {
    plazza::TaskMinify* tm = task.decompose();
    this->_processTrigger[key]->Write(tm, tm->size);
    this->_remainings[key] -= 1;
    delete[] tm;
  }
}

bool        plazza::LoadBalancing::addProcess() {
  ccry::Process* p = new ccry::Process();
  try {
   p->create();
  } catch (std::exception const &e) {
      std::cerr << "Can't create process" << std::endl;
      pid_t pid;
      for (unsigned int itP = 0; itP < this->_process.size(); itP++) {
          pid = _process.at(itP)->getPid();
              delete _process.at(itP);
              this->_process.erase(_process.begin() + itP);
              this->_remainings.erase(pid);
              delete this->_processTrigger[pid];
              this->_processTrigger.erase(pid);

          }

    std::exit(1);
  }
  if (!(p->getPid())) {
    {
      plazza::ThreadPool threadPool(this->_nbThreads);
    }
    std::exit(0);
  } else {
    this->_process.push_back(p);
    std::string pname = "_LINKER_LOAD_BALANCING(w)_PROCESS" + std::to_string(p->getPid()) + "(r)_";
    this->_processTrigger[p->getPid()] = new ccry::WritePipe(pname);
    this->_processTrigger[p->getPid()]->create();
    this->_remainings[p->getPid()] = this->_nbThreads * 2;
  }
  return true;
}
