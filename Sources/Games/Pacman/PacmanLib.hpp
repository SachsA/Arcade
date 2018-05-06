//
// EPITECH PROJECT, 2018
// PacmanLib.hpp
// File description:
// Created by Thomas BLENEAU
//

#ifndef PACMAN_LIB_HPP
#define PACMAN_LIB_HPP

#include <iostream>
#include "IGame.hpp"
#include "IGfx.hpp"

#ifndef HIGHSCORE_PATH
#define HIGHSCORE_PATH "Resources/Pacman/Score/.highscore"
#endif //HIGHSCORE_PATH

#ifndef WINDOW_WIDTH
#define WINDOW_WIDTH 1600
#endif //WINDOW_WIDTH

#ifndef WINDOW_HEIGHT
#define WINDOW_HEIGHT 900
#endif //WINDOW_HEIGHT

#ifndef MAP_PATH
#define MAP_PATH "./Resources/Pacman/Data/level"
#endif //MAP_PATH

#ifndef EXTENSION
#define EXTENSION ".txt"
#endif //EXTENSION

#ifndef VOID
#define VOID "0"
#endif //VOID

#ifndef WALL
#define WALL "1"
#endif //WALL

#ifndef PLAYER_RIGHT
#define PLAYER_RIGHT "2"
#endif //PLAYER_RIGHT

#ifndef PLAYER_UP
#define PLAYER_UP "10"
#endif //PLAYER_UP

#ifndef PLAYER_DOWN
#define PLAYER_DOWN "11"
#endif //PLAYER_DOWN

#ifndef PLAYER_LEFT
#define PLAYER_LEFT "12"
#endif //PLAYER_LEFT

#ifndef ENEMY_B
#define ENEMY_B "3"
#endif //ENEMY_B

#ifndef ENEMY_P
#define ENEMY_P "4"
#endif //ENEMY_P

#ifndef ENEMY_Y
#define ENEMY_Y "5"
#endif //ENEMY_Y

#ifndef ENEMY_R
#define ENEMY_R "6"
#endif //ENEMY_R

#ifndef GHOST
#define GHOST "7"
#endif //GHOST

#ifndef BONUS
#define BONUS "8"
#endif //BONUS

#ifndef OBJECT
#define OBJECT "9"
#endif //OBJECT

class PacmanLib : public IGame {
public:
	PacmanLib();
	~PacmanLib();
	void loadMap(int);
	enum Key launch();
	void chooseOptUp();
	void setGfx(IGfx *);
	void chooseOptDown();
	enum Key loopPause();
	enum Key loopGameOver();
	enum Key loopIntro();
	void createVectorPause();
	std::size_t getPosFromVector();
	std::string const &getGameName() const;
private:
	std::string _gameName = "Pacman";
	IGfx *_libGraph = nullptr;
	dataVector<std::string> _vector_pause;
	std::list<Point> _highScore;
	std::size_t _score = 0;
	void initGame();
	std::vector<std::vector<std::string>> _vector_map;
	void parseHighScore();
};

#endif // !PACMAN_LIB_HPP
