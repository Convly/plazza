/*
** main.cpp for Rendu in /home/cauvin_m/Rendu/cpp_plazza
**
** Made by cauvin-m
** Login   <cauvin_m@epitech.net>
**
** Started on  Mon Apr 10 07:18:27 2017 cauvin-m
** Last update Sun Apr 30 14:53:54 2017 jsx
*/

#include <dirent.h>
#include <exception>
#include "Core.hpp"

static bool  removeFifos() {
  DIR *dir;
  struct dirent *ent;
  std::string path;

  if ((dir = opendir ("./.pfifos/")) != nullptr) {
    while ((ent = readdir(dir)) != nullptr) {
      if (ent->d_type == DT_FIFO) {
        path = "./.pfifos/" + std::string(ent->d_name);
        std::remove(path.c_str());
      }
    }
    closedir (dir);
  } else {
    std::perror("[Fatal error] ./.pfifos/");
    std::cerr << "[Tips] Try the following command: \"mkdir .pfifos\"" << std::endl;
    return false;
  }
  return true;
}

static bool checkForDecryptFlag(char**av, int ac) {
  std::vector<std::string> tokens;
  std::string str;
  if (ac == 3) {
    str = av[2];
    tokens = utils::split(str, '=');
    if (tokens.size() == 2 && tokens.at(0) == "--decrypt") {
      if (tokens.at(1) == "xor") {
        plazza::G_DECRYPTFLAG += 1;
      } else if (tokens.at(1) == "caesar") {
        plazza::G_DECRYPTFLAG += 2;
      } else if (tokens.at(1) == "all") {
        plazza::G_DECRYPTFLAG = 3;
      } else {
        return false;
      }
    } else {
      return false;
    }
  } else {
    return false;
  }
  return true;
}

int   main(int ac, char **av, char** env)
{
  if (env == nullptr || (env != nullptr && *env == nullptr)) {
      std::cerr << av[0] << ": Bring back my environment you dummy!" << std::endl;
      return -1;
    }
  if (ac < 2 || ac > 3) {
    std::cerr << av[0] << ": Invalid arguments number." << std::endl << "Usage: " << av[0] << " [number of threads per process] {--decrypt}" << std::endl;
    return -1;
  }

  if (ac == 3 && checkForDecryptFlag(av, ac) == false) {
    std::cerr << av[0] << ": Invalid option \"" << av[2] << "\"" << std::endl;
    return 1;
  }

  try {
    int  max_threads = std::stoi(av[1]);
    if (max_threads < 1) {
        std::cerr << "Please enter a positive number" << std::endl;
        return 1;
    }
    if (!removeFifos()) {
      return 1;
    }
    plazza::Core core("./Libs/lib_plazza_ui.so", max_threads, false);
    core.startUi();
    core.startLoadBalancing();
    core.startEngine();
  } catch (std::exception const &e) {
      std::cerr << e.what() << std::endl;
    return 1;
  }

  return 0;
}
