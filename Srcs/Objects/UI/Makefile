##
## Makefile for plazza in /home/jsx/Epitech/tek2/C++2/plazza/cpp_plazza/Interfaces/
##
## Made by jsx
## Login   <jean-sebastien.herbaux@epitech.eu>
##
## Started on  Mon Apr 10 18:24:58 2017 jsx
## Last update Thu Apr 20 20:48:13 2017 jsx
##

NAME 			= 	lib_plazza_ui.so

CXX  			= 	g++

RPATH			=		../../

LPATH			=		../../../Libs/

CXXFLAGS  = 	-W -Wall -Werror -Wextra -std=c++14 \

CXXFLAGS	+=	-I./ 																					\
							-I./$(RPATH)/Interfaces/	 										\
							-I./$(RPATH)/Abstracts/ 											\
							-I./$(RPATH)/Modules/													\
							-I./$(RPATH)/Objects/Task/										\
							-I./$(RPATH)/Objects/TaskResult/							\
							-I./$(RPATH)/Objects/UI/											\
							-I./$(RPATH)/Objects/Date/										\
							-I$(LPATH)																		\

CXXFLAGS	+=	-fPIC


LXXFLAGS 	= 	-shared -L$(LPATH) -lconcurrency -lutils -pthread

SRC 			= 	./UI.cpp																			\
							./$(RPATH)/Objects/Task/Task.cpp							\
							./$(RPATH)/Objects/TaskResult/TaskResult.cpp	\
							./$(RPATH)/Objects/Date/Date.cpp							\


OBJ 			= 	$(SRC:.cpp=.o)

RM				=		rm -f

all: $(NAME)

$(NAME): $(OBJ)
	 $(CXX) $(OBJ) -o $(NAME) $(LXXFLAGS)
	 cp -f $(NAME) $(LPATH)
	 @printf "\033[0;32mLib plazza UI compiled successfully <3 !\n\033[0m"

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LPATH)/$(NAME)

re: fclean all

.PHONY: all clean fclean re
