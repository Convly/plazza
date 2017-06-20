/*
** Scrapper.cpp for Rendu in /home/cauvin_m/Rendu/cpp_plazza/Objects/Scrapper
**
** Made by cauvin-m
** Login   <cauvin_m@epitech.net>
**
** Started on  Mon Apr 10 07:25:51 2017 cauvin-m
// Last update Sun Apr 30 14:57:42 2017 jsx
*/

#include "Scrapper.hpp"

plazza::Scrapper::Scrapper(Task const& task)
{

  this->_task = task;
  this->_query = this->_task.getQuery();
  this->_paths = this->_task.getPaths();
  this->_wPipe = new ccry::WritePipe("_LINK_SCRAPPER(w)_UI(r)_");
  this->_wPipe->create();
}

plazza::Scrapper::~Scrapper()
{
  this->writePipeTaskResultMinified(this->_task.getId(), -1, "");
}

void    plazza::Scrapper::writePipeTaskResultMinified(int const& idTask, int const& type, std::string const& result)
{
  if (result.size() <= 4096)
  {
    plazza::TaskResultMinify  *tmp = new plazza::TaskResultMinify[sizeof(plazza::TaskResultMinify)];

    tmp->idTask = idTask;
    tmp->type = type;
    std::memset(&(tmp->result), 0, 4096);
    std::string str(result);
    str.copy(tmp->result, str.size());
    this->_wPipe->Write(tmp, sizeof(plazza::TaskResultMinify));
    delete[] tmp;
  }
}

void  plazza::Scrapper::scrapXor(std::string const& filebuff)
{
  std::string       tmp;
  unsigned char     key[2];

  key[0] = 0;
  key[1] = 0;
  for (int i1 = 0; i1 < 256; i1++)
  {
    for (int i2 = 0; i2 < 256; i2++)
    {
      tmp = filebuff;
      for (size_t j = 0; j < tmp.size(); j++)
        tmp[j] = tmp[j] ^ key[j % 2];
      std::regex            r(this->_regexStr);
      std::sregex_iterator  next(tmp.begin(), tmp.end(), r);
      std::sregex_iterator  end;
      while (next != end)
      {
        std::smatch sm = *next;
        writePipeTaskResultMinified(this->_task.getId(), DecryptionType::XOR, sm.str());
        next++;
      }
      key[1] += 1;
    }
    key[1] = 0;
    key[0] += 1;
  }
}

void  plazza::Scrapper::scrapCaesar(std::string filebuff)
{
  for (size_t i = 0; i < 256; i++)
  {
    for (auto it = filebuff.begin(); it != filebuff.end(); ++it)
      *it += 1;
    std::regex            r(this->_regexStr);
    std::sregex_iterator  next(filebuff.begin(), filebuff.end(), r);
    std::sregex_iterator  end;
    while (next != end)
    {
      std::smatch sm = *next;
      writePipeTaskResultMinified(this->_task.getId(), DecryptionType::CAESAR, sm.str());
      next++;
    }
  }
}

void  plazza::Scrapper::scrapUncrypted(std::string const& filebuff)
{
  std::regex            r(this->_regexStr);
  std::sregex_iterator  next(filebuff.begin(), filebuff.end(), r);
  std::sregex_iterator  end;
  while (next != end)
  {
    std::smatch sm = *next;
    writePipeTaskResultMinified(this->_task.getId(), DecryptionType::UNCRYPTED, sm.str());
    next++;
  }
}

void  plazza::Scrapper::scrapFile(std::string const& filepath)
{
  std::ifstream               ifs(filepath);
  std::string                 regexStr;
  std::string                 filebuff;

  if (ifs)
    std::getline(ifs, filebuff, '\0');
  else
    std::cerr << "Error on opening the file '" << filepath << "'" << std::endl;
  ifs.close();

  if (this->_query == DataQuery::EMAIL_ADDRESS)
    this->_regexStr = "[a-zA-Z0-9_\\.-]+@[a-zA-Z0-9_\\.-]+\\.[a-zA-Z0-9_\\.-]+";
  else if (this->_query == DataQuery::PHONE_NUMBER)
    this->_regexStr = "(0[1-9]) ?([0-9][0-9] ?){4}";
  else if (this->_query == DataQuery::IP_ADDRESS)
    this->_regexStr = "(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.){3}(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9][0-9]|[0-9])";

  this->scrapUncrypted(filebuff);
  int flag = plazza::G_DECRYPTFLAG;
  if (flag >= 2) {
    this->scrapCaesar(filebuff);
    flag -= 2;
  }
  if (flag >= 1) {
    this->scrapXor(filebuff);
    flag -= 1;
  }
}

plazza::Task        plazza::Scrapper::run()
{
  TaskResult        taskResult;

  for (size_t i = 0; i < this->_paths.size(); i++)
    this->scrapFile(this->_paths[i]);
  this->_task.setTaskResult(taskResult);
  return (this->_task);
}
