//
// Created by julien on 20/04/17.
//

#ifndef RENDU_READPIPE_HPP
#define RENDU_READPIPE_HPP

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "UTILS/chrono.hpp"
#include "INamedPipe.hpp"

namespace ccry {
    class ReadPipe: public INamedPipe {
    private:
        int             fd;
        std::string     name;

    public:
        virtual void    create(void);
        int            Read(void*, size_t);

    public:
        ReadPipe(std::string);
        virtual ~ReadPipe();
    };
}


#endif //RENDU_READPIPE_HPP
