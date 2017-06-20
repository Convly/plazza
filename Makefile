##
## Makefile for makefile in /home/jsx/Epitech/tek2/C++2/plazza/cpp_plazza/
##
## Made by jsx
## Login   <jean-sebastien.herbaux@epitech.eu>
##
## Started on  Mon Apr 10 18:29:33 2017 jsx
## Last update Fri Apr 28 10:45:40 2017 jsx
##

NAME    		=     plazza

CC      		=    	g++

RM      		=  		rm -f

CXXFLAGS  	=   	-W -Wall -Wextra -Werror -std=c++14 -fPIC				\

CXXFLAGS    +=  	-I./Srcs/Objects/Scrapper 											\
									-I./Srcs/Objects/Core/													\
									-I./Srcs/Objects/Engine/												\
									-I./Srcs/Objects/ThreadPool/												\
									-I./Srcs/Objects/Task/													\
									-I./Srcs/Objects/TaskResult/										\
									-I./Srcs/Objects/LoadBalancing/									\
									-I./Srcs/Objects/Date/													\
									-I./Srcs/Interfaces/	 													\
									-I./Srcs/Abstracts/ 														\
									-I./Srcs/Modules/																\
									-I./Libs/																				\

LDFLAGS			=		 	-ldl -L./Libs/ -lconcurrency -lutils -pthread

SRC					= 		./Srcs/main.cpp																	\
									./Srcs/Objects/Scrapper/Scrapper.cpp						\
									./Srcs/Objects/Task/Task.cpp										\
									./Srcs/Objects/TaskResult/TaskResult.cpp				\
									./Srcs/Objects/Date/Date.cpp										\
									./Srcs/Objects/Core/Core.cpp										\
									./Srcs/Objects/Engine/Engine.cpp								\
									./Srcs/Objects/LoadBalancing/LoadBalancing.cpp								\
									./Srcs/Objects/ThreadPool/ThreadPool.cpp \

OBJ     		= 		$(SRC:.cpp=.o)																	\

all: basis $(NAME)

basis:
	make -C ./Libs/Bin/Utils/
	make -C ./Libs/Bin/Concurrency/

$(NAME):  $(OBJ)
	$(CC) $(OBJ) $(CXXFLAGS) -o $(NAME) $(LDFLAGS)
	make -C ./Srcs/Objects/UI/
	@printf "\033[0;32mPlazza compiled successfully !\n\033[0m"

ui: basis $(OBJ)
	$(CC) $(OBJ) $(CXXFLAGS) -o $(NAME) $(LDFLAGS)
	make -C ./Srcs/Objects/GUI/
	@printf "\033[0;32mPlazza compiled successfully !\n\033[0m"

reui: fclean ui

cleanbasis:
	$(RM) $(OBJ)

clean: cleanbasis
	make clean -C ./Libs/Bin/Concurrency/
	make clean -C ./Libs/Bin/Utils/
	make clean -C ./Srcs/Objects/UI/
	make clean -C ./Srcs/Objects/GUI/

fclean: clean
	$(RM) $(NAME)
	make fclean -C ./Libs/Bin/Concurrency/
	make fclean -C ./Libs/Bin/Utils/
	make fclean -C ./Srcs/Objects/UI/
	make fclean -C ./Srcs/Objects/GUI/

re: fclean all

%.o : %.c
	$(CC) $(CXXFLAGS) -c $< -o $@
