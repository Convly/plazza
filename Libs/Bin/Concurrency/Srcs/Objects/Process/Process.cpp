//
// Created by julien on 22/04/17.
//

#include <exception>
#include "Process.hpp"

ccry::Process::Process() {
}

ccry::Process::~Process() {
    if (pid > 0) {
        if (kill(pid, SIGKILL) < 0)
            return; // throw exception ? error class ?
    }
}

/* ACTIONS */

bool ccry::Process::create() {
    pid = fork();
    if (pid == -1)
      throw std::exception(); // throw exception ? error class ?
    return true;
}

pid_t ccry::Process::getPid() const {
    return pid;
}
