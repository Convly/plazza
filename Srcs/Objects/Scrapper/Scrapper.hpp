/*
** Scrapper.hpp for Rendu in /home/cauvin_m/Rendu/cpp_plazza/Objects/Scrapper
**
** Made by cauvin-m
** Login   <cauvin_m@epitech.net>
**
** Started on  Mon Apr 10 07:25:08 2017 cauvin-m
** Last update Thu Apr 27 18:56:14 2017 jsx
*/

#ifndef SCRAPPER_HPP_
#define  SCRAPPER_HPP_

# include <iostream>
# include <regex>
# include <fstream>
# include <cstring>
# include "Task.hpp"
# include "TaskResult.hpp"
# include "plazzaTypes.hpp"
# include "CCRY/all.hpp"

namespace plazza
{
  class Scrapper
  {
    Task                      _task;
    std::vector<std::string>  _paths;
    DataQuery                 _query;
    std::string               _regexStr;
    ccry::WritePipe           *_wPipe;

  public:
    Scrapper(Task const& task);
    virtual ~Scrapper();

    Task        run();

    void        writePipeTaskResultMinified(int const& idTask,
                                            int const& type,
                                            std::string const& result);
    void        scrapFile(std::string const& filepath);
    void        scrapUncrypted(std::string const& filebuff);
    void        scrapCaesar(std::string filebuff);
    void        scrapXor(std::string const& filebuff);
  };
}

#endif
