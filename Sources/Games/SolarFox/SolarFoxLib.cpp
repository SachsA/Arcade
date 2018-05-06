//
// EPITECH PROJECT, 2018
// SolarFoxLib.cpp
// File description:
// Created by Thomas BLENEAU
//

#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <thread>
#include <ctime>
#include <cstdlib>
#include <string>
#include <cstring>
#include <sys/stat.h>
#include "SolarFoxLib.hpp"
#include "ErrorsSolarFox.hpp"

static Asset Title {
		.name = "SolarFox",
		.path1D = "",
		.path2D = "Resources/SolarFox/2D/game.png",
		.color = {
			.r = 255,
			.g = 255,
			.b = 255,
			.a = 1,
			.pair = 3
		},
		.width = WINDOW_WIDTH,
		.height = WINDOW_HEIGHT
};

static Asset Empty {
		.name = VOID,
		.path1D = "",
		.path2D = "",
		.color = {
			.r = 0,
			.g = 0,
			.b = 0,
			.a = 1,
			.pair = 0
		},
		.width = 23,
		.height = 23
};

static Asset Wall {
		.name = WALL,
		.path1D = "",
		.path2D = "Resources/SolarFox/2D/block.png",
		.color = {
			.r = 211,
			.g = 211,
			.b = 21,
			.a = 1,
			.pair = 14
		},
		.width = 23,
		.height = 23
};

static Asset PlayerUp {
		.name = PLAYER_UP,
		.path1D = "",
		.path2D = "Resources/SolarFox/2D/player_up.png",
		.color = {
			.r = 51,
			.g = 153,
			.b = 255,
			.a = 1,
			.pair = 9
		},
		.width = 23,
		.height = 23
};

static Asset PlayerDown {
		.name = PLAYER_DOWN,
		.path1D = "",
		.path2D = "Resources/SolarFox/2D/player_down.png",
		.color = {
			.r = 51,
			.g = 153,
			.b = 255,
			.a = 1,
			.pair = 9
		},
		.width = 23,
		.height = 23
};

static Asset PlayerLeft {
		.name = PLAYER_LEFT,
		.path1D = "",
		.path2D = "Resources/SolarFox/2D/player_left.png",
		.color = {
			.r = 51,
			.g = 153,
			.b = 255,
			.a = 1,
			.pair = 9
		},
		.width = 23,
		.height = 23
};

static Asset PlayerRight {
		.name = PLAYER_RIGHT,
		.path1D = "",
		.path2D = "Resources/SolarFox/2D/player_right.png",
		.color = {
			.r = 51,
			.g = 153,
			.b = 255,
			.a = 1,
			.pair = 9
		},
		.width = 23,
		.height = 23
};

static Asset EnemyUp {
		.name = ENEMY_UP,
		.path1D = "",
		.path2D = "Resources/SolarFox/2D/enemy.png",
		.color = {
			.r = 255,
			.g = 51,
			.b = 0,
			.a = 1,
			.pair = 8
		},
		.width = 23,
		.height = 23
};

static Asset EnemyDown {
		.name = ENEMY_DOWN,
		.path1D = "",
		.path2D = "Resources/SolarFox/2D/enemy_down.png",
		.color = {
			.r = 255,
			.g = 51,
			.b = 0,
			.a = 1,
			.pair = 8
		},
		.width = 23,
		.height = 23
};

static Asset EnemyLeft {
		.name = ENEMY_LEFT,
		.path1D = "",
		.path2D = "Resources/SolarFox/2D/enemy_right.png",
		.color = {
			.r = 255,
			.g = 51,
			.b = 0,
			.a = 1,
			.pair = 8
		},
		.width = 23,
		.height = 23
};

static Asset EnemyRight {
		.name = ENEMY_RIGHT,
		.path1D = "",
		.path2D = "Resources/SolarFox/2D/enemy_left.png",
		.color = {
			.r = 255,
			.g = 51,
			.b = 0,
			.a = 1,
			.pair = 8
		},
		.width = 23,
		.height = 23
};

static Asset Missile {
		.name = MISSILE,
		.path1D = "",
		.path2D = "Resources/SolarFox/2D/missile_left.png",
		.color = {
			.r = 255,
			.g = 204,
			.b = 0,
			.a = 1,
			.pair = 12
		},
		.width = 23,
		.height = 23
};

static Asset Object {
		.name = OBJECT,
		.path1D = "",
		.path2D = "Resources/SolarFox/2D/object.png",
		.color = {
			.r = 255,
			.g = 204,
			.b = 0,
			.a = 1,
			.pair = 13
		},
		.width = 23,
		.height = 23
};

SolarFoxLib::SolarFoxLib()
{
	loadMap(1);
	initPlayerPos();
	parseHighScore();
	createVectorPause();
	initColectibleNbr();
}

SolarFoxLib::~SolarFoxLib()
{}

void SolarFoxLib::setGfx(IGfx *gfx)
{
	_libGraph = gfx;
}

std::string const &SolarFoxLib::getGameName() const
{
	return _gameName;
}

void SolarFoxLib::initColectibleNbr()
{
	for(auto row : _vector_map) {
		for (auto values : row) {
			if (!std::string{values}.compare(OBJECT)) {
				_colectibleNbr += 1;
			}
		}
	}
}

void SolarFoxLib::initPlayerPos()
{
	int posX = 0;
	int posY = 0;
	for(auto n : _vector_map) {
		posY = 0;
		for (auto b : n) {
			if (std::string{b}.compare(PLAYER_UP) == 0) {
				_playerPosY = posY;
				_playerPosX = posX;
			}
			posY++;
		}
		posX++;
	}
}

inline bool exist_file(const std::string& name) {
	struct stat buffer;
	return (stat (name.c_str(), &buffer) == 0);
}

void SolarFoxLib::loadMap(int lvl)
{
	size_t idx = 0;
	std::string level = std::to_string(lvl);
	std::string str = MAP_PATH + level + std::string(EXTENSION);
	if (exist_file(str) == false)
		throw ErrorsSolarFox(std::cerr, str + " : file not found.");

	std::ifstream infile(str);
	for (std::string line; getline(infile, line); idx++) {
		std::vector<std::string> tmp;
		size_t jdx;
		for (jdx = 0; jdx < line.size(); jdx++) {
			if (line[jdx] != '0' &&
			    line[jdx] != '1' &&
			    line[jdx] != '2' &&
			    line[jdx] != '3' &&
			    line[jdx] != '4' &&
			    line[jdx] != '5' &&
			    line[jdx] != '6' &&
			    line[jdx] != '7' &&
			    line[jdx] != '8')
				throw ErrorsSolarFox(std::cerr, str + " : format map not correct : must be 0 to 8.");
			std::string ptr = {line.substr(jdx, 1)};
			tmp.emplace_back(ptr);
		}
		if (jdx != 30)
			throw ErrorsSolarFox(std::cerr, str + " : size map not correct.");
		_vector_map.emplace_back(tmp);
	}
	if (idx != 30)
		throw ErrorsSolarFox(std::cerr, str + " : size map not correct.");
}

void SolarFoxLib::createVectorPause()
{
	_vector_pause.vector.push_back(RESUME_OPTION);
	_vector_pause.vector.push_back(MENU_OPTION);
	_vector_pause.vector.push_back(QUIT_OPTION);
	_vector_pause.iterator = _vector_pause.vector.begin();
}

void SolarFoxLib::parseHighScore()
{
	Point score;
	std::string tmp;
	std::size_t found = 0;
	std::ifstream content(HIGHSCORE_PATH);

	if (content.is_open()) {
		while (getline(content, tmp)) {
			found = tmp.find(' ');
			if (found != std::string::npos) {
				score.name = tmp.substr(found + 1);
				score.value = std::stoi(tmp.substr(0, found));
				_highScore.push_back(score);
			}
		}
	}
}

int SolarFoxLib::getColectibleNbr()
{
	return _colectibleNbr;
}

enum Key SolarFoxLib::loopIntro()
{
	bool running = true;
	enum Key keyPress;

	while (running) {
		keyPress = _libGraph->getEvent();
		switch (keyPress) {
		case K_A:
		case K_Z:
		case K_E:
		case K_R:
		case K_Q:
		case K_S:
		case K_SPACE:
		case K_ESCAPE:
			return (keyPress);
		default:
			break;
		}
		_libGraph->printIntro(getGameName());
	}
	return (K_UNDEFINED);
}

void SolarFoxLib::chooseOptUp()
{
	if (_vector_pause.iterator == _vector_pause.vector.begin()) {
		_vector_pause.iterator = _vector_pause.vector.end();
		_vector_pause.iterator--;
	} else {
		_vector_pause.iterator--;
	}
}

void SolarFoxLib::chooseOptDown()
{
	if (_vector_pause.iterator == _vector_pause.vector.end() - 1)
		_vector_pause.iterator = _vector_pause.vector.begin();
	else
		_vector_pause.iterator++;
}

std::size_t SolarFoxLib::getPosFromVector()
{
	std::size_t i = 0;

	for (i = 0; i != _vector_pause.vector.size() && _vector_pause.vector[i] != *_vector_pause.iterator; i++);
	return i;
}

enum Key SolarFoxLib::loopGameOver()
{
	bool running = true;
	enum Key keyPress;

	while (running) {
		_libGraph->printGameOver(_score, _highScore);
		keyPress = _libGraph->getEvent();
		switch (keyPress) {
		case K_A:
		case K_Z:
		case K_E:
		case K_R:
		case K_S:
		case K_Q:
		case K_ESCAPE:
			return (keyPress);
		case K_SPACE:
			return (K_S);
		default:
			break;
		}
	}
	return K_UNDEFINED;
}

enum Key SolarFoxLib::loopPause()
{
	std::size_t pos = 0;
	bool running = true;
	enum Key keyPress;

	while (running) {
		_libGraph->printGameMenu(getGameName(), _vector_pause);
		keyPress = _libGraph->getEvent();
		switch (keyPress) {
		case K_A:
		case K_Z:
		case K_E:
		case K_R:
		case K_S:
		case K_Q:
		case K_ESCAPE:
			_libGraph->clear();
			return (keyPress);
		case K_UP:
			chooseOptUp();
			break;
		case K_DOWN:
			chooseOptDown();
			break;
		case K_SPACE:
			pos = getPosFromVector();
			if (pos == 1) {
				_libGraph->clear();
				return (K_ESCAPE);
			}
			else if (pos == 2)
				return (K_Q);
			_libGraph->clearGameMenu();
			running = false;
		default:
			break;
		}
	}
	return K_UNDEFINED;
}

enum Key SolarFoxLib::launch()
{
	bool running = true;
	enum Key keyPress;
	enum Direction dir = UNDEFINED;
	Point pointData;

	keyPress = loopIntro();
	if (keyPress != K_SPACE)
		return (keyPress);
	_libGraph->clear();
	initGame();
	while (running) {
		_libGraph->display();
		_libGraph->printTitle(_gameName);
		_libGraph->printHighScore(_highScore);
		_libGraph->printScore(_score);
		_libGraph->printGameMap(_vector_map);
		keyPress = _libGraph->getEvent();
		switch (keyPress) {
		case K_A:
		case K_Z:
		case K_E:
		case K_R:
		case K_Q:
		case K_S:
		case K_ESCAPE:
			return (keyPress);
		case K_UP:
			if (_lastDir != DOWN) {
				dir = UP;
				_lastDir = dir;
				movePlayer(dir);
			}
			break;
		case K_DOWN:
			if (_lastDir != UP) {
				dir = DOWN;
				_lastDir = dir;
				movePlayer(dir);
			}
			break;
		case K_LEFT:
			if (_lastDir != RIGHT) {
				dir = LEFT;
				_lastDir = dir;
				movePlayer(dir);
			}
			break;
		case K_RIGHT:
			if (_lastDir != LEFT) {
				dir = RIGHT;
				_lastDir = dir;
				movePlayer(dir);
			}
			break;
		case K_SPACE:
			keyPress = loopPause();
			if (keyPress == K_A
			    || keyPress == K_Z
			    || keyPress == K_E
			    || keyPress == K_R
			    || keyPress == K_S
			    || keyPress == K_Q
			    || keyPress == K_ESCAPE)
				return keyPress;
			break;
		default:
			movePlayer(dir);
			break;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(110));
		if (getColectibleNbr() == 0) {
			pointData = {
				.name = "really",
				.value = static_cast<size_t>(_score)
			};
			_highScore.push_back(pointData);
			writeNewScore();
			return K_ESCAPE;
		}
	}
	return K_UNDEFINED;
}

void SolarFoxLib::writeNewScore()
{
	std::ofstream file;
	file.open(HIGHSCORE_PATH);
	for (auto data : _highScore) {
		file << data.value << " " << data.name << "\n";
	}
	file.close();
}

int SolarFoxLib::isColectible(std::string obj)
{
	int value = std::string{obj}.compare(OBJECT);
	return value;
}

int SolarFoxLib::playerCanMove(enum Direction dir)
{
	int returnValue = 0;
	switch (dir) {
	case UP:
		returnValue = std::string{_vector_map[_playerPosX - 1][_playerPosY]}.compare(WALL);
		break;
	case DOWN:
		returnValue = std::string{_vector_map[_playerPosX + 1][_playerPosY]}.compare(WALL);
		break;
	case LEFT:
		returnValue = std::string{_vector_map[_playerPosX][_playerPosY - 1]}.compare(WALL);
		break;
	case RIGHT:
		returnValue = std::string{_vector_map[_playerPosX][_playerPosY + 1]}.compare(WALL);
		break;	default:
		break;
	}
	return returnValue;
}


void SolarFoxLib::movePlayer(Direction dir)
{
	switch (dir) {
	case UP:
		movePlayerUp();
		break;
	case DOWN:
		movePlayerDown();
		break;
	case RIGHT:
		movePlayerRight();
		break;
	case LEFT:
		movePlayerLeft();
		break;
	default:
		return;
	}
}

void SolarFoxLib::movePlayerUp()
{
	int value = playerCanMove(UP);
	if (value == -1 || value == 6) {
		_vector_map[_playerPosX][_playerPosY] = VOID;
		if (std::string{_vector_map[_playerPosX - 1][_playerPosY]}.compare(OBJECT) == 0) {
			_score += 10;
			_colectibleNbr -= 1;
		}
		_playerPosX -= 1;
		_vector_map[_playerPosX][_playerPosY] = PLAYER_UP;
	}
}

void SolarFoxLib::movePlayerDown()
{
	int value = playerCanMove(DOWN);
	if (value == -1 || value == 6) {
		_vector_map[_playerPosX][_playerPosY] = VOID;
		if (std::string{_vector_map[_playerPosX + 1][_playerPosY]}.compare(OBJECT) == 0) {
			_score += 10;
			_colectibleNbr -= 1;
		}
		_playerPosX += 1;
		_vector_map[_playerPosX][_playerPosY] = PLAYER_DOWN;
	}
}

void SolarFoxLib::movePlayerLeft()
{
	int value = playerCanMove(LEFT);
	if (value == -1 || value == 6) {
		_vector_map[_playerPosX][_playerPosY] = VOID;
		if (std::string{_vector_map[_playerPosX][_playerPosY - 1]}.compare(OBJECT) == 0) {
			_score += 10;
			_colectibleNbr -= 1;
		}
		_playerPosY -= 1;
		_vector_map[_playerPosX][_playerPosY] = PLAYER_LEFT;
	}
}

void SolarFoxLib::movePlayerRight()
{
	int value = playerCanMove(RIGHT);
	if (value == -1 || value == 6) {
		_vector_map[_playerPosX][_playerPosY] = VOID;
		if (std::string{_vector_map[_playerPosX][_playerPosY + 1]}.compare(OBJECT) == 0) {
			_score += 10;
			_colectibleNbr -= 1;
		}
		_playerPosY += 1;
		_vector_map[_playerPosX][_playerPosY] = PLAYER_RIGHT;
	}
}

void SolarFoxLib::initGame()
{
	_libGraph->addAsset(Title.name, Title);
	_libGraph->addAsset(Empty.name, Empty);
	_libGraph->addAsset(Wall.name, Wall);
	_libGraph->addAsset(Missile.name, Missile);
	_libGraph->addAsset(Object.name, Object);
	_libGraph->addAsset(PlayerUp.name, PlayerUp);
	_libGraph->addAsset(PlayerDown.name, PlayerDown);
	_libGraph->addAsset(PlayerLeft.name, PlayerLeft);
	_libGraph->addAsset(PlayerRight.name, PlayerRight);
	_libGraph->addAsset(EnemyUp.name, EnemyUp);
	_libGraph->addAsset(EnemyDown.name, EnemyDown);
	_libGraph->addAsset(EnemyLeft.name, EnemyLeft);
	_libGraph->addAsset(EnemyRight.name, EnemyRight);
}

Enemy &Enemy::operator=(Enemy const &enemy)
{
	if (*this != enemy) {
		this->dataMissile = enemy.dataMissile;
		this->dataEnemy = enemy.dataEnemy;
	}
	return *this;
}

bool Enemy::operator!=(Enemy const &enemy) const
{
	if (this->dataMissile != enemy.dataMissile ||
	    this->dataEnemy != enemy.dataEnemy) {
		return true;
	}
	return false;
}

	struct Missile &Missile::operator=(Missile const &missile)
		{
			if (*this != missile) {
				this->dataMissile = missile.dataMissile;
				this->lives = missile.lives;
			}
			return *this;
		}

	bool Missile::operator!=(Missile const &missile) const
	{
		if (this->dataMissile != missile.dataMissile ||
		    this->lives != missile.lives) {
			return true;
		}
		return false;
	}

	Entities &Entities::operator=(Entities const &entity)
		{
			if (*this != entity) {
				this->posX = entity.posX;
				this->posY = entity.posY;
				this->dir = entity.dir;
				this->distanceLeft = entity.distanceLeft;
			}
			return *this;
		}

	bool Entities::operator!=(Entities const &entity) const
	{
		if (this->posX != entity.posX ||
		    this->posY != entity.posY ||
		    this->dir != entity.dir ||
		    this->distanceLeft != entity.distanceLeft) {
			return true;
		}
		return false;
	}


	extern "C" {
		IGame *buildEngine() {
			return new SolarFoxLib();
		}
	}
