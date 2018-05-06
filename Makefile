##
## EPITECH PROJECT, 2018
## cpp_arcade
## File description:
## Makefile global cpp_arcade
##

MAKE	= make

all:	sdl allegro ncurses nibbler pacman solarfox core

core:
	$(MAKE) -C ./Sources/Arcade

games: nibbler pacman solarfox

graphicals: sdl allegro ncurses

sdl:
	$(MAKE) -C ./Sources/Lib_graph/SDL

allegro:
	$(MAKE) -C ./Sources/Lib_graph/Allegro

ncurses:
	$(MAKE) -C ./Sources/Lib_graph/NCurses

nibbler:
	$(MAKE) -C ./Sources/Games/Nibbler

pacman:
	$(MAKE) -C ./Sources/Games/Pacman

solarfox:
	$(MAKE) -C ./Sources/Games/SolarFox

clean:
	$(MAKE) clean -C ./Sources/Arcade
	$(MAKE) clean -C ./Sources/Lib_graph/SDL
	$(MAKE) clean -C ./Sources/Lib_graph/Allegro
	$(MAKE) clean -C ./Sources/Lib_graph/NCurses
	$(MAKE) clean -C ./Sources/Games/Nibbler
	$(MAKE) clean -C ./Sources/Games/Pacman
	$(MAKE) clean -C ./Sources/Games/SolarFox

fclean:	clean
	$(MAKE) fclean -C ./Sources/Arcade
	$(MAKE) fclean -C ./Sources/Lib_graph/SDL
	$(MAKE) fclean -C ./Sources/Lib_graph/Allegro
	$(MAKE) fclean -C ./Sources/Lib_graph/NCurses
	$(MAKE) fclean -C ./Sources/Games/Nibbler
	$(MAKE) fclean -C ./Sources/Games/Pacman
	$(MAKE) fclean -C ./Sources/Games/SolarFox

re:	fclean all

.PHONY:	all arcade sdl allegro ncurses nibbler pacman solarfox clean fclean re
