##
## EPITECH PROJECT, 2018
## cpp_arcade
## File description:
## Makefile Arcade
##

CC		= g++

CCOPT		= -o

RM		= rm -rf

NAME		= ../../arcade

SRC		= ../Main.cpp			\
		  ./Arcade.cpp			\
		  ../Errors/Errors.cpp		\
		  ../Errors/ErrorsArcade.cpp	\
		  ../Errors/ErrorsLoadGraph.cpp

OBJ		= $(SRC:.cpp=.o)

CXXFLAGS	+= -I ./
CXXFLAGS	+= -I ../Loader/
CXXFLAGS	+= -I ../Errors/
CXXFLAGS	+= -I ../Lib_graph/
CXXFLAGS	+= -I ../Games/
CXXFLAGS	+= -Wall -Wextra -fPIC
CXXFLAGS	+= -std=c++14

ifeq		($(DEBUG), true)
CXXFLAGS	+= -Werror -g
endif

LDFLAGS		+= -ldl

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(CCOPT) $(NAME) $(OBJ) $(LDFLAGS)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
