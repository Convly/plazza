//
// UI.cpp for UI in /home/jsx/Epitech/tek2/C++2/plazza/cpp_plazza/Srcs/Objects/UI/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Mon Apr 10 18:39:23 2017 jsx
// Last update Sat Apr 29 19:46:44 2017 jsx
//

#include "UI.hpp"

plazza::UI::UI() : AUI()
{

}

plazza::UI::~UI()
{
}

plazza::Task                  plazza::UI::strToTask(std::string const& cmd)
{
  bool                        isWrong = false;
  std::stringstream           ss;
  std::string                 word;
  std::vector<std::string>    listWords;
  plazza::DataQuery           query;
  std::vector<std::string>    paths;

  ss << cmd;
  while (ss >> word)
    listWords.push_back(word);
  if (listWords.size() == 1 && *(listWords.begin()) == "exit")
    query = DataQuery::STOP;
  else if (listWords.size() < 2 || this->_map.find(listWords[static_cast<int>(listWords.size() - 1)]) == this->_map.end())
    isWrong = true;
  else
  {
    for (int i = 0; i < static_cast<int>(listWords.size() - 1) && !isWrong; i++)
    {
      if (utils::fileExist(listWords[i]))
        paths.push_back(listWords[i]);
      else
        isWrong = true;
    }
    query = this->_map[listWords[static_cast<int>(listWords.size() - 1)]];
  }
  if (isWrong)
  {
    query = DataQuery::UNDEFINED;
    std::cerr << "La commande est mauvaise" << std::endl;
  }
  return (plazza::Task(query, paths));
}

bool                          plazza::UI::parseEntryLine(std::string const& line)
{
  std::vector<std::string>    list = utils::split(line, ';');
  Task                        task;

  for (int i = 0; i < static_cast<int>(list.size()); i++)
  {
    task = this->strToTask(list[i]);
    if (task.getQuery() != DataQuery::UNDEFINED) {
      this->_tasksToDo.push_back(task);
      this->_cv->produce();
      if (task.getQuery() == DataQuery::STOP)
        return (false);
    }
  }
  return (true);
}

void                          plazza::UI::start(ccry::CondVar* cv, int nbThread, plazza::LoadBalancerStatus&, size_t &)
{
  std::string               line;
  ccry::IThread*            th;
  bool                      nth = true;

  std::function<void*(void*)> func = [&] (void*) {
    while(getline(std::cin, line)) {
      if (line == "exit") {
        break;
      }
      if (!this->parseEntryLine(line)) {
        break;
      }
      //std::cout << "> ";
    }
    this->parseEntryLine("exit");
    nth = false;
    return nullptr;
  };

  th = new ccry::Thread(func, nullptr);

  //std::cout << "> ";
  this->_nbThread = nbThread;
  this->_cv = cv;
  while (nth || this->_tasksProcessing.size())
  {
    this->readPipeTaskResultMinified(this->_tmp);
    if (line == "exit" || std::cin.bad())
      nth = false;
  }
  th->join();
  delete th;
  delete[] this->_tmp;
}

extern "C" plazza::UI*        CObject(void)
{
  return (new plazza::UI);
}

extern "C" void               DObject(plazza::UI *ui)
{
  delete ui;
}
