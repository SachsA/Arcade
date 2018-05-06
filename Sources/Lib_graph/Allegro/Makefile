##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Created by Thomas BLENEAU
##

CC		= g++

CCOPT		= -o

RM		= rm -rf

NAME		= ../../../lib/lib_arcade_allegro.so

SRC		= AllegroLib.cpp		\
		  ../../Errors/Errors.cpp	\
		  ../../Errors/ErrorsAllegro.cpp

OBJ		= $(SRC:.cpp=.o)

CXXFLAGS	+= -I ./
CXXFLAGS	+= -I ../
CXXFLAGS	+= -I ../../Errors/
CXXFLAGS	+= -Wall -Wextra -fPIC
CXXFLAGS	+= -std=c++14

ifeq		($(DEBUG), true)
CXXFLAGS	+= -Werror -g
endif

LDFLAGS		= -lallegro -lallegro_image -lallegro_ttf -lallegro_font
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
