##
## Makefile for utils in /home/jsx/Epitech/tek2/C++2/plazza/cpp_plazza/Libs/Bin/Utils/
##
## Made by jsx
## Login   <jean-sebastien.herbaux@epitech.eu>
##
## Started on  Thu Apr 20 20:39:32 2017 jsx
## Last update Sun Apr 30 03:02:16 2017 jsx
##

NAME    		=     libutils.a

INCNAME			=			UTILS

CC      		=    	g++

RM      		=  		rm -f

INCSRC			=			./Srcs/Functions/join/join.hpp \
									./Srcs/Functions/split/split.hpp \
									./Srcs/Functions/fileExist/fileExist.hpp \
									./Srcs/Objects/Timer/Timer.hpp 			 \

CXXFLAGS  	=   	-W -Wall -Wextra -Werror -std=c++14 -fPIC	\

CXXFLAGS    +=  	-I./Srcs/Functions/join/ 			 \
									-I./Srcs/Functions/split/ 			 \
									-I./Srcs/Functions/fileExist/ 			 \
									-I./Srcs/Objects/Timer/ 			 \


SRC					= 		./Srcs/Functions/join/join.cpp												\
									./Srcs/Functions/split/split.cpp									\
									./Srcs/Functions/fileExist/fileExist.cpp									\
									./Srcs/Objects/Timer/Timer.cpp 			 \


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
	$(RM) -r $(INCNAME)/Includes/
	@printf "\033[0;32mUtils library compiled successfully !\n\033[0m"

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
