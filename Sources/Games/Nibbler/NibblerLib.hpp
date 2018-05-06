//
// EPITECH PROJECT, 2018
// NibblerLib.hpp
// File description:
// Created by Thomas BLENEAU
//

#ifndef NIBBLER_LIB_HPP
#define NIBBLER_LIB_HPP

#include <iostream>
#include "IGame.hpp"
#include "IGfx.hpp"

#ifndef HIGHSCORE_PATH
#define HIGHSCORE_PATH "Resources/Nibbler/Score/.highscore"
#endif //HIGHSCORE_PATH

#ifndef WINDOW_WIDTH
#define WINDOW_WIDTH 1600
#endif //WINDOW_WIDTH

#ifndef WINDOW_HEIGHT
#define WINDOW_HEIGHT 900
#endif //WINDOW_HEIGHT

#ifndef EXTENSION
#define EXTENSION ".txt"
#endif //EXTENSION

#ifndef MAP_PATH
#define MAP_PATH "./Resources/Nibbler/Data/level"
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

#ifndef BODY
#define BODY "2"
#endif //BODY

#ifndef HEAD_RIGHT
#define HEAD_RIGHT "6"
#endif //HEAD_RIGHT

#ifndef TAIL_RIGHT
#define TAIL_RIGHT "9"
#endif //TAIL_RIGHT

#ifndef APPLE
#define APPLE "5"
#endif //APPLE

#ifndef HEAD_LEFT
#define HEAD_LEFT "3"
#endif //HEAD_LEFT

#ifndef HEAD_UP
#define HEAD_UP "7"
#endif //HEAD_UP

#ifndef HEAD_DOWN
#define HEAD_DOWN "8"
#endif //HEAD_DOWN

#ifndef TAIL_LEFT
#define TAIL_LEFT "4"
#endif //TAIL_LEFT

#ifndef TAIL_UP
#define TAIL_UP "10"
#endif //TAIL_UP

#ifndef TAIL_DOWN
#define TAIL_DOWN "11"
#endif //TAIL_DOWN

#ifndef APPLE_POINT
#define APPLE_POINT 100
#endif //APPLE_POINT

enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	UNDEFINED
};

struct Vector2D {
	size_t x;
	size_t y;
};

class NibblerLib : public IGame {
public:
	NibblerLib();
	~NibblerLib();
	void loadMap(int);
	enum Key launch();
	void chooseOptUp();
	void setGfx(IGfx *);
	void chooseOptDown();
	enum Key loopPause();
	enum Key loopIntro();
	enum Key loopGameOver();
	void createVectorPause();
	std::size_t getPosFromVector();
	std::string const &getGameName() const;
private:
	IGfx *_libGraph = nullptr;
	std::size_t _score = 0;
	std::size_t _scoreMax = 0;
	std::size_t _object = 0;
	std::list<Point> _highScore;
	std::string _gameName = "Nibbler";
	dataVector<std::string> _vector_pause;
	std::vector<std::vector<std::string>> _vector_map;
	std::vector<Vector2D> _player;
	enum Direction _lastDir;
	void parseHighScore();
	std::size_t getScoreMax();
	void setScoreMax();
	void updateScore();
	void initGame();
	void initPlayer();
	void addBody(std::size_t, std::size_t, std::string);
	void printPositionPlayer(); //DEBUG
	bool moveUp();
	bool moveRight();
	bool moveDown();
	bool moveLeft();
	void updateBody(std::string);
	bool movePlayer(Direction);
	bool biteTail(size_t, size_t);
	void writeNewScore();
};

#endif // !NIBBLER_LIB_HPP
