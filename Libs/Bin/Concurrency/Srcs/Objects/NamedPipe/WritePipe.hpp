//
// Created by julien on 20/04/17.
//

#ifndef RENDU_WRITEPIPE_HPP
#define RENDU_WRITEPIPE_HPP


#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "cerrno"
#include "INamedPipe.hpp"

namespace ccry {
    class WritePipe: public INamedPipe {
    private:
        int             fd;
        std::string     name;
    public:
        virtual void    create(void);
        void            Write(void*, size_t) const ;

    public:
        WritePipe(std::string);
        virtual ~WritePipe();
    };
}

#endif //RENDU_WRITEPIPE_HPP
