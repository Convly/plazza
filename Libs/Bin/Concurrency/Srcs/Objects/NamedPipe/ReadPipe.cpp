//
// Created by julien on 20/04/17.
//

#include "ReadPipe.hpp"

ccry::ReadPipe::ReadPipe(std::string _name) {
    name = "./.pfifos/" + _name;
}

ccry::ReadPipe::~ReadPipe() {
  std::remove(this->name.c_str());
}

/* ACTIONS */

void ccry::ReadPipe::create() {
  if(mkfifo(name.c_str(), 0644) != 0) {
    if (errno != EEXIST) {
      std::exit(EXIT_FAILURE);
    }
  }

  if((fd = open (name.c_str(), O_RDONLY | O_NONBLOCK)) == -1) {
    std::cout << strerror(errno) << std::endl;
    exit(EXIT_FAILURE);
  }
}

int ccry::ReadPipe::Read(void* buff, size_t size) {
  utils::Timer timer(4200);

  timer.lap();
  int rd = read(fd, reinterpret_cast<char*>(buff), size);
  timer.lap();
  return rd;
}
