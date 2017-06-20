##
## Makefile for makefile in /home/jsx/Epitech/tek2/C++2/plazza/cpp_plazza/Srcs/Objects/Concurrency/
##
## Made by jsx
## Login   <jean-sebastien.herbaux@epitech.eu>
##
## Started on  Mon Apr 17 17:30:10 2017 jsx
## Last update Tue Apr 25 18:17:52 2017 jsx
##

NAME    		=     libconcurrency.a

INCNAME			=			CCRY

CC      		=    	g++

RM      		=  		rm -f

INCSRC			=			./Srcs/Interfaces/IThread.hpp													\
									./Srcs/Interfaces/IMutex.hpp													\
									./Srcs/Interfaces/INamedPipe.hpp											\
									./Srcs/Objects/Thread/Thread.hpp 											\
									./Srcs/Objects/Mutex/Mutex.hpp	 											\
									./Srcs/Objects/ScopedLock/ScopedLock.hpp	 						\
									./Srcs/Objects/CondVar/CondVar.hpp	 									\
									./Srcs/Objects/UniqueLock/UniqueLock.hpp	 						\
									./Srcs/Objects/LockGuard/LockGuard.hpp	 							\
									./Srcs/Objects/NamedPipe/WritePipe.hpp 								\
									./Srcs/Objects/NamedPipe/ReadPipe.hpp 								\
									./Srcs/Objects/Process/Process.hpp 										\

CXXFLAGS  	=   	-W -Wall -Wextra -Werror -std=c++14 -fPIC			\

LDFLAGS			=			-L./../../ -lutils

CXXFLAGS    +=  	-I./Srcs/Interfaces/													\
									-I./Srcs/Interfaces/													\
									-I./Srcs/Objects/Thread/ 											\
									-I./Srcs/Objects/Mutex/	 											\
									-I./Srcs/Objects/ScopedLock/	 								\
									-I./Srcs/Objects/CondVar/	 										\
									-I./Srcs/Objects/UniqueLock/									\
									-I./Srcs/Objects/LockGuard/										\
									-I./Srcs/Objects/NamedPipe/										\
									-I./Srcs/Objects/Process/											\
									-I./../../ \

SRC					= 		./Srcs/Objects/Thread/Thread.cpp												\
									./Srcs/Objects/Mutex/Mutex.cpp													\
									./Srcs/Objects/ScopedLock/ScopedLock.cpp								\
									./Srcs/Objects/CondVar/CondVar.cpp											\
									./Srcs/Objects/UniqueLock/UniqueLock.cpp								\
									./Srcs/Objects/LockGuard/LockGuard.cpp									\
									./Srcs/Objects/NamedPipe/WritePipe.cpp									\
									./Srcs/Objects/NamedPipe/ReadPipe.cpp										\
									./Srcs/Objects/Process/Process.cpp											\


OBJ     		= 		$(SRC:.cpp=.o)																					\

all: $(NAME)

$(NAME): $(OBJ)
	$(RM) -r $(INCNAME)/Includes/
	mkdir $(INCNAME)/Includes/
	cp $(INCSRC) -t $(INCNAME)/Includes/
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)
	cp $(NAME) ../../
	cp -r $(INCNAME) ../../
	$(RM) -r ./CCRY/Includes/
	@printf "\033[0;32mConcurrency library compiled successfully !\n\033[0m"

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) -r $(INCNAME)/Includes/
	$(RM) $(NAME)
	$(RM) ../../$(NAME)
	$(RM) -r ../../$(INCNAME)

re: fclean all

%.o : %.c
	$(CC) $(CXXFLAGS) -c $< -o $@
