//
// EPITECH PROJECT, 2018
// PacmanLib.cpp
// File description:
// Created by Thomas BLENEAU
//

#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include "PacmanLib.hpp"
#include "ErrorsPacman.hpp"

static Asset Title {
		.name = "Pacman",
		.path1D = "",
		.path2D = "Resources/Pacman/2D/game.png",
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
		.path2D = "Resources/Pacman/2D/block.png",
		.color = {
			.r = 11,
			.g = 67,
			.b = 182,
			.a = 1,
			.pair = 11
		},
		.width = 23,
		.height = 23
};

static Asset Player_up {
		.name = PLAYER_UP,
		.path1D = "",
		.path2D = "Resources/Pacman/2D/player_up.png",
		.color = {
			.r = 255,
			.g = 242,
			.b = 0,
			.a = 1,
			.pair = 10
		},
		.width = 23,
		.height = 23
};

static Asset Player_down {
		.name = PLAYER_DOWN,
		.path1D = "",
		.path2D = "Resources/Pacman/2D/player_down.png",
		.color = {
			.r = 255,
			.g = 242,
			.b = 0,
			.a = 1,
			.pair = 10
		},
		.width = 23,
		.height = 23
};

static Asset Player_left {
		.name = PLAYER_LEFT,
		.path1D = "",
		.path2D = "Resources/Pacman/2D/player_left.png",
		.color = {
			.r = 255,
			.g = 242,
			.b = 0,
			.a = 1,
			.pair = 10
		},
		.width = 23,
		.height = 23
};

static Asset Player_right {
		.name = PLAYER_RIGHT,
		.path1D = "",
		.path2D = "Resources/Pacman/2D/player_right.png",
		.color = {
			.r = 255,
			.g = 242,
			.b = 0,
			.a = 1,
			.pair = 10
		},
		.width = 23,
		.height = 23
};

static Asset Enemy_b {
		.name = ENEMY_B,
		.path1D = "",
		.path2D = "Resources/Pacman/2D/ghost_blue.png",
		.color = {
			.r = 118,
			.g = 210,
			.b = 246,
			.a = 1,
			.pair = 13
		},
		.width = 23,
		.height = 23
};

static Asset Enemy_p {
		.name = ENEMY_P,
		.path1D = "",
		.path2D = "Resources/Pacman/2D/ghost_pink.png",
		.color = {
			.r = 246,
			.g = 144,
			.b = 162,
			.a = 1,
			.pair = 12
		},
		.width = 23,
		.height = 23
};

static Asset Enemy_y {
		.name = ENEMY_Y,
		.path1D = "",
		.path2D = "Resources/Pacman/2D/ghost_yellow.png",
		.color = {
			.r = 254,
			.g = 187,
			.b = 13,
			.a = 1,
			.pair = 10
		},
		.width = 23,
		.height = 23
};

static Asset Enemy_r {
		.name = ENEMY_R,
		.path1D = "",
		.path2D = "Resources/Pacman/2D/ghost_red.png",
		.color = {
			.r = 237,
			.g = 28,
			.b = 36,
			.a = 1,
			.pair = 8
		},
		.width = 23,
		.height = 23
};

static Asset Ghost {
		.name = GHOST,
		.path1D = "",
		.path2D = "Resources/Pacman/2D/ghost_dead.png",
		.color = {
			.r = 11,
			.g = 67,
			.b = 182,
			.a = 1,
			.pair = 11
		},
		.width = 23,
		.height = 23
};

static Asset Bonus {
		.name = BONUS,
		.path1D = "",
		.path2D = "Resources/Pacman/2D/bonus.png",
		.color = {
			.r = 255,
			.g = 0,
			.b = 0,
			.a = 1,
			.pair = 9
		},
		.width = 18,
		.height = 18
};

static Asset Object {
		.name = OBJECT,
		.path1D = "",
		.path2D = "Resources/Pacman/2D/object.png",
		.color = {
			.r = 255,
			.g = 255,
			.b = 255,
			.a = 1,
			.pair = 14
		},
		.width = 12,
		.height = 12
};

PacmanLib::PacmanLib()
{
	loadMap(1);
	parseHighScore();
	createVectorPause();
}

PacmanLib::~PacmanLib()
{}

void PacmanLib::setGfx(IGfx *gfx)
{
	_libGraph = gfx;
}

std::string const &PacmanLib::getGameName() const
{
	return _gameName;
}

inline bool exist_file(const std::string& name) {
	struct stat buffer;
	return (stat (name.c_str(), &buffer) == 0);
}

void PacmanLib::loadMap(int lvl)
{
	size_t idx = 0;
	std::string level = std::to_string(lvl);
	std::string str = MAP_PATH + level + std::string(EXTENSION);
	if (exist_file(str) == false)
		throw ErrorsPacman(std::cerr, str + " : file not found.");

	std::ifstream infile(str);
	for (std::string line; getline(infile, line); idx++) {
		std::vector<std::string> tmp;
		size_t jdx;
		for (jdx = 0; jdx < line.size(); jdx++) {
			if (line[jdx] != '0'
			&& line[jdx] != '1'
			&& line[jdx] != '2'
			&& line[jdx] != '3'
			&& line[jdx] != '4'
			&& line[jdx] != '5'
			&& line[jdx] != '6'
			&& line[jdx] != '7'
			&& line[jdx] != '8'
			&& line[jdx] != '9')
				throw ErrorsPacman(std::cerr, str + " : format map not correct : must be 0 to 9.");
			std::string ptr = {line.substr(jdx, 1)};
			tmp.emplace_back(ptr);
		}
		if (jdx != 30)
			throw ErrorsPacman(std::cerr, str + " : size map not correct.");
		_vector_map.emplace_back(tmp);
	}
	if (idx != 30)
		throw ErrorsPacman(std::cerr, str + " : size map not correct.");
}

void PacmanLib::createVectorPause()
{
	_vector_pause.vector.push_back(RESUME_OPTION);
	_vector_pause.vector.push_back(MENU_OPTION);
	_vector_pause.vector.push_back(QUIT_OPTION);
	_vector_pause.iterator = _vector_pause.vector.begin();
}

void PacmanLib::parseHighScore()
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

enum Key PacmanLib::loopIntro()
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

void PacmanLib::chooseOptUp()
{
	if (_vector_pause.iterator == _vector_pause.vector.begin()) {
		_vector_pause.iterator = _vector_pause.vector.end();
		_vector_pause.iterator--;
	} else {
		_vector_pause.iterator--;
	}
}

void PacmanLib::chooseOptDown()
{
	if (_vector_pause.iterator == _vector_pause.vector.end() - 1)
		_vector_pause.iterator = _vector_pause.vector.begin();
	else
		_vector_pause.iterator++;
}

std::size_t PacmanLib::getPosFromVector()
{
	std::size_t i = 0;

	for (i = 0; i != _vector_pause.vector.size() && _vector_pause.vector[i] != *_vector_pause.iterator; i++);
	return i;
}

enum Key PacmanLib::loopPause()
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

enum Key PacmanLib::loopGameOver()
{
	bool running = true;
	enum Key keyPress;

	_libGraph->clear();
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

enum Key PacmanLib::launch()
{
	bool running = true;
	enum Key keyPress;

	keyPress = loopIntro();
	if (keyPress != K_SPACE)
		return (keyPress);
	_libGraph->clear();
	initGame();
	while (running) {
		_libGraph->display();
		_libGraph->printTitle(_gameName);
		_libGraph->printGameMap(_vector_map);
		_libGraph->printHighScore(_highScore);
		_libGraph->printScore(_score);
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
				break;
			case K_DOWN:
				break;
			case K_LEFT:
				break;
			case K_RIGHT:
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
				break;
		}
	}
	return K_UNDEFINED;
}

void PacmanLib::initGame()
{
	_libGraph->addAsset(Title.name, Title);
	_libGraph->addAsset(Empty.name, Empty);
	_libGraph->addAsset(Wall.name, Wall);
	_libGraph->addAsset(Object.name, Object);
	_libGraph->addAsset(Bonus.name, Bonus);
	_libGraph->addAsset(Player_up.name, Player_up);
	_libGraph->addAsset(Player_down.name, Player_down);
	_libGraph->addAsset(Player_left.name, Player_left);
	_libGraph->addAsset(Player_right.name, Player_right);
	_libGraph->addAsset(Enemy_b.name, Enemy_b);
	_libGraph->addAsset(Enemy_p.name, Enemy_p);
	_libGraph->addAsset(Enemy_y.name, Enemy_y);
	_libGraph->addAsset(Enemy_r.name, Enemy_r);
	_libGraph->addAsset(Ghost.name, Ghost);
}

extern "C" {
	IGame *buildEngine() {
		return new PacmanLib();
	}
}
