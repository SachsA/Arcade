##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Created by Thomas BLENEAU
##

CC		= g++

CCOPT		= -o

RM		= rm -rf

NAME		= ../../../games/lib_arcade_solarfox.so

SRC		= SolarFoxLib.cpp			\
		../../Errors/Errors.cpp			\
		../../Errors/ErrorsSolarFox.cpp		\

OBJ		= $(SRC:.cpp=.o)

CXXFLAGS	+= -I ./
CXXFLAGS	+= -I ../
CXXFLAGS	+= -I ../../Lib_graph
CXXFLAGS	+= -I ../../Errors/
CXXFLAGS	+= -Wall -Wextra -fPIC
CXXFLAGS	+= -std=c++17

ifeq		($(DEBUG), true)
CXXFLAGS	+= -Werror -g
endif

LDFLAGS		+= -shared

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(CCOPT) $(NAME) $(OBJ) $(LDFLAGS)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
