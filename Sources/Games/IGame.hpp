/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** IGame.hpp
*/

#ifndef IGAME_HPP_
#define IGAME_HPP_

#include <iostream>
#include "IGfx.hpp"

#ifndef QUIT_OPTION
#define QUIT_OPTION "QUIT"
#endif /*QUIT_OPTION*/
#ifndef MENU_OPTION
#define MENU_OPTION "ARCADE MENU"
#endif /*MENU_OPTION*/
#ifndef RESUME_OPTION
#define RESUME_OPTION "RESUME"
#endif /*RESUME_OPTION*/

class IGame {
public:
	virtual ~IGame(){};
	virtual std::string const &getGameName() const = 0;
	virtual enum Key launch() = 0;
	virtual void setGfx(IGfx *) = 0;
};

#endif //IGAME_HPP_
