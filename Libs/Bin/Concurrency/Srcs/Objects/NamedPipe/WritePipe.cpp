//
// Created by julien on 20/04/17.
//

#include "WritePipe.hpp"

ccry::WritePipe::WritePipe(std::string _name) {
    name = "./.pfifos/" + _name;
}

ccry::WritePipe::~WritePipe() {
  std::remove(this->name.c_str());
}

/* ACTIONS */

void ccry::WritePipe::create() {
  if(mkfifo(name.c_str(), 0644) != 0) {
    if (errno != EEXIST) {
      std::exit(EXIT_FAILURE);
    }
  }

  if((fd = open(name.c_str(), O_WRONLY)) == -1) {
    std::cout << strerror(errno) << std::endl;
    std::exit(EXIT_FAILURE);
  }
}

void ccry::WritePipe::Write(void* obj, size_t size) const {
  write(fd, reinterpret_cast<char*>(obj), size);
}
