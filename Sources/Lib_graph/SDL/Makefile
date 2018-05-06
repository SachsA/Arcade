##
## EPITECH PROJECT, 2018
## cpp_arcade
## File description:
## Makefile SdlLib
##

CC		= g++

CCOPT		= -o

RM		= rm -rf

NAME		= ../../../lib/lib_arcade_sdl2.so

SRC		= SdlLib.cpp			\
		  ../../Errors/Errors.cpp	\
		  ../../Errors/ErrorsSdl.cpp

OBJ		= $(SRC:.cpp=.o)

CXXFLAGS	+= -I ./
CXXFLAGS	+= -I ../
CXXFLAGS	+= -I ../../Errors/
CXXFLAGS	+= -Wall -Wextra -fPIC
CXXFLAGS	+= -std=c++14

ifeq		($(DEBUG), true)
CXXFLAGS	+= -Werror -g
endif

LDFLAGS		+= -lSDL2 -lSDL2_image -lSDL2_ttf
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
