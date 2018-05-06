//
// EPITECH PROJECT, 2018
// SolarFoxLib.hpp
// File description:
// Created by Thomas BLENEAU
//

#ifndef SOLARFOX_LIB_HPP
#define SOLARFOX_LIB_HPP

#ifndef HIGHSCORE_PATH
#define HIGHSCORE_PATH "Resources/SolarFox/Score/.highscore"
#endif //HIGHSCORE_PATH

#ifndef MAP_PATH
#define MAP_PATH "./Resources/SolarFox/Data/level"
#endif //MAP_PATH

#ifndef EXTENSION
#define EXTENSION ".txt"
#endif //EXTENSION

#ifndef LIMIT_RIGHT
#define LIMIT_RIGHT 25
#endif //LIMIT_RIGHT

#ifndef LIMIT_LEFT
#define LIMIT_LEFT 5
#endif //LIMIT_RIGHT

#ifndef LIMIT_BOTTOM
#define LIMIT_BOTTOM 25
#endif //LIMIT_BOTTOM

#ifndef LIMIT_TOP
#define LIMIT_TOP 5
#endif //LIMIT_TOP

#ifndef WINDOW_WIDTH
#define WINDOW_WIDTH 1600
#endif //WINDOW_WIDTH

#ifndef WINDOW_HEIGHT
#define WINDOW_HEIGHT 900
#endif //WINDOW_HEIGHT

#ifndef VOID
#define VOID "0"
#endif //VOID

#ifndef WALL
#define WALL "1"
#endif //WALL

#ifndef PLAYER_UP
#define PLAYER_UP "2"
#endif //PLAYER_UP

#ifndef PLAYER_DOWN
#define PLAYER_DOWN "9"
#endif //PLAYER_DOWN

#ifndef PLAYER_LEFT
#define PLAYER_LEFT "10"
#endif //PLAYER_LEFT

#ifndef PLAYER_RIGHT
#define PLAYER_RIGHT "11"
#endif //PLAYER_RIGHT

#ifndef ENEMY_UP
#define ENEMY_UP "3"
#endif //ENEMY

#ifndef ENEMY_DOWN
#define ENEMY_DOWN "4"
#endif //ENEMY_DOWN

#ifndef ENEMY_LEFT
#define ENEMY_LEFT "5"
#endif //ENEMY_LEFT

#ifndef ENEMY_RIGHT
#define ENEMY_RIGHT "6"
#endif //ENEMY_RIGHT

#ifndef OBJECT
#define OBJECT "7"
#endif //OBJECT

#ifndef MISSILE
#define MISSILE "8"
#endif //MISSILE

#include <iostream>
#include <vector>
#include "IGame.hpp"
#include "IGfx.hpp"

enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	UNDEFINED
};

struct Entities {
	Entities &operator=(const Entities &entity);
	bool operator!=(Entities const &entity) const;
	int posX;
	int posY;
	Direction dir;
	int distanceLeft;
};

struct Missile {
	Missile &operator=(Missile const &missile);
	bool operator!=(Missile const &missile) const;
	struct Entities dataMissile;
	const int maxDistance = 15;
	int lives = 0;
};

struct Enemy {
	Enemy &operator=(const Enemy &enemy);
	bool operator!=(Enemy const &enemy) const;
	struct Missile dataMissile;
	struct Entities dataEnemy;
};

class SolarFoxLib : public IGame {
public:
	SolarFoxLib();
	~SolarFoxLib();
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
	std::string _gameName = "SolarFox";
	IGfx *_libGraph = nullptr;
	dataVector<std::string> _vector_pause;
	int _colectibleNbr = 0;
	std::vector<std::vector<std::string>> _vector_map;
	std::list<Point> _highScore;
	std::size_t _score = 0;
	int _playerPosX;
	int _playerPosY;
	enum Direction _lastDir;
	std::unordered_map<std::string, Enemy> _enemyMap;
	void initColectibleNbr();
	int getColectibleNbr();
	int playerCanMove(enum Direction);
	int isColectible(std::string obj);
	void movePlayer(Direction dir);
	void initGame();
	void movePlayerUp();
	void movePlayerDown();
	void movePlayerLeft();
	void movePlayerRight();
	void parseHighScore();
	void initPlayerPos();
	void writeNewScore();
};

#endif // !SOLARFOX_LIB_HPP
