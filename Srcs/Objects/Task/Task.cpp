//
// Task.cpp for task in /home/jsx/Epitech/tek2/C++2/plazza/cpp_plazza/Srcs/Objects/Task/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Mon Apr 10 19:20:19 2017 jsx
// Last update Sun Apr 30 14:54:43 2017 jsx
//

#include "Task.hpp"

size_t plazza::G_TASKID = 0;
size_t plazza::G_DECRYPTFLAG = 0;

plazza::Task::Task(const DataQuery& query, const std::vector<std::string> paths)
:
  _taskid(plazza::G_TASKID),
  _paths(paths),
  _query(query),
  _instanciationDate(plazza::Date())
{
  plazza::G_TASKID += 1;
}

plazza::Task::Task()
:
  _taskid(-1),
  _query(plazza::DataQuery::UNDEFINED),
  _instanciationDate(plazza::Date())
{
  plazza::G_TASKID += 1;
}

plazza::Task::Task(const plazza::TaskMinify & minify)
:
  _taskid(minify.id),
  _paths(utils::split(std::string(minify.paths), '|')),
  _query(static_cast<plazza::DataQuery>(minify.query)),
  _instanciationDate(plazza::Date())
{

}

plazza::Task::~Task() {
}

plazza::Task &  plazza::Task::operator=(const Task & ist) {
  if (this != &ist) {
    this->_taskid = ist.getId();
    this->_paths = ist.getPaths();
    this->_query = ist.getQuery();
    this->_taskResult = ist.getTaskResult();
  }
  return *this;
}

// GETTERS
int                        plazza::Task::getId() const {return this->_taskid;}
plazza::DataQuery          plazza::Task::getQuery() const {return this->_query;}
std::vector<std::string>   plazza::Task::getPaths() const {return this->_paths;}
plazza::TaskResult         plazza::Task::getTaskResult() const {return this->_taskResult;}
plazza::Date               plazza::Task::getInstanciationDate() const {return this->_instanciationDate;}
plazza::Date               plazza::Task::getComputeDate() const {return this->_computeDate;}
plazza::Date               plazza::Task::getCompletionDate() const {return this->_completionDate;}
plazza::duration           plazza::Task::getComputeDelay() const {
  return this->_completionDate.getDate() - this->_computeDate.getDate();
}

// SETTERS
void       plazza::Task::setId(int id) {this->_taskid = id;}
void       plazza::Task::setQuery(DataQuery const& query) {this->_query = query;}
void       plazza::Task::setPaths(const std::vector<std::string> & nPaths) {this->_paths = nPaths;}
void       plazza::Task::setTaskResult(TaskResult const& taskResult) {this->_taskResult = taskResult;}

// TOOLS

bool       plazza::Task::addPath(const std::string & path) {
  if (std::find(this->_paths.begin(), this->_paths.end(), path) != this->_paths.end()) {
    return false;
  }

  this->_paths.push_back(path);
  return true;
}

std::string plazza::Task::getQueryString() const{
  std::string result = "undefined";
  int _query = this->_query;
  switch (_query) {
    case -1:
      result = "STOP";
      break;
    case 0:
      result = "PHONE NUMBER";
      break;
    case 1:
      result = "EMAIL ADDRESS";
      break;
    case 2:
      result = "IP ADDRESS";
      break;
  }
  return result;
}

plazza::TaskMinify* plazza::Task::decompose() const {
  //
  //                        DECOMPOSE
  //
  // Get all paths in a single string (separates by '|')
  std::string paths("");
  for (auto it = this->_paths.begin(); it != this->_paths.end(); it++) {
    paths += (*it) + "|";
  }
  if (paths.size() > 4096)
    return nullptr;
  // ---------------------------------------------------
  // Get alloc size based on number of paths + sizeof TaskMinify struct size
  size_t size = sizeof(plazza::TaskMinify);
  // ---------------------------------------
  // Creating and filling the TaskMinify struct
  plazza::TaskMinify* m_task = new plazza::TaskMinify[size];
  m_task->id = this->_taskid;
  m_task->query = this->_query;
  m_task->size = size;
  std::memset(&(m_task->paths), 0, 4000);
  paths.copy(m_task->paths, paths.size());
  return m_task;
}

void      plazza::Task::startCompute() {this->_computeDate = plazza::Date();}
void      plazza::Task::stopCompute() {this->_completionDate = plazza::Date();}

std::ostream& plazza::operator<<(std::ostream& os, const plazza::Task& obj) {
  os << "Created " << obj.getInstanciationDate().beautifier() << std::endl;
  os << "Query:\t" << obj.getQueryString() << std::endl;
  os << "Paths:\t" << utils::join(obj.getPaths(), ", ") << std::endl;
  return os;
}
