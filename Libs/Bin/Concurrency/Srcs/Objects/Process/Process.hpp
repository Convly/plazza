//
// Created by julien on 22/04/17.
//

#ifndef RENDU_PROCESS_HPP
#define RENDU_PROCESS_HPP

#include <signal.h>
#include <unistd.h>

namespace ccry {
    class Process {
    private:
        pid_t   pid;

    public:
        bool    create();
        pid_t   getPid() const;

    public:
        Process(void);
        ~Process(void);
    };
}

#endif //RENDU_PROCESS_HPP
