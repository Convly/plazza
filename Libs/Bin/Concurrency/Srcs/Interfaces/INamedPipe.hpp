//
// Created by julien on 18/04/17.
//

#ifndef CCRY_INAMEDPIPE_HPP
#define CCRY_INAMEDPIPE_HPP

namespace ccry {

    #define MESSAGE_SIZE 4096

    class INamedPipe {
    public:
        virtual ~INamedPipe(void) {};
        virtual void create(void) = 0;
    };
}

#endif //CCRY_INAMEDPIPE_HPP
