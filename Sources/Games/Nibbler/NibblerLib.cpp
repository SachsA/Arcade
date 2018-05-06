//
// EPITECH PROJECT, 2018
// NibblerLib.cpp
// File description:
// Created by Thomas BLENEAU
//

#include <fstream>
#include <thread>
#include <sys/stat.h>
#include "NibblerLib.hpp"
#include "ErrorsNibbler.hpp"

static Asset Title {
		.name = "Nibbler",
		.path1D = "",
		.path2D = "Resources/Nibbler/2D/game.png",
		.color = {
			.r = 255,
			.g = 255,
			.b = 255,
			.a = 1,
			.pair = 2
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
		.path2D = "Resources/Nibbler/2D/block.png",
		.color = {
			.r = 23,
			.g = 7,
			.b = 237,
			.a = 1,
			.pair = 14
		},
		.width = 23,
		.height = 23
};

static Asset Body {
		.name = BODY,
		.path1D = "",
		.path2D = "Resources/Nibbler/2D/body.png",
		.color = {
			.r = 22,
			.g = 113,
			.b = 0,
			.a = 1,
			.pair = 9
		},
		.width = 23,
		.height = 23
};

static Asset TailRight {
		.name = TAIL_RIGHT,
		.path1D = "",
		.path2D = "Resources/Nibbler/2D/tail_right.png",
		.color = {
			.r = 22,
			.g = 113,
			.b = 0,
			.a = 1,
			.pair = 9
		},
		.width = 23,
		.height = 23
};

static Asset TailLeft {
		.name = TAIL_LEFT,
		.path1D = "",
		.path2D = "Resources/Nibbler/2D/tail_left.png",
		.color = {
			.r = 22,
			.g = 113,
			.b = 0,
			.a = 1,
			.pair = 9
		},
		.width = 23,
		.height = 23
};

static Asset TailUp {
		.name = TAIL_UP,
		.path1D = "",
		.path2D = "Resources/Nibbler/2D/tail_up.png",
		.color = {
			.r = 22,
			.g = 113,
			.b = 0,
			.a = 1,
			.pair = 9
		},
		.width = 23,
		.height = 23
};

static Asset TailDown {
		.name = TAIL_DOWN,
		.path1D = "",
		.path2D = "Resources/Nibbler/2D/tail_down.png",
		.color = {
			.r = 22,
			.g = 113,
			.b = 0,
			.a = 1,
			.pair = 9
		},
		.width = 23,
		.height = 23
};

static Asset HeadRight {
		.name = HEAD_RIGHT,
		.path1D = "",
		.path2D = "Resources/Nibbler/2D/head_right.png",
		.color = {
			.r = 22,
			.g = 113,
			.b = 0,
			.a = 1,
			.pair = 9
		},
		.width = 23,
		.height = 23
};

static Asset HeadLeft {
		.name = HEAD_LEFT,
		.path1D = "",
		.path2D = "Resources/Nibbler/2D/head_left.png",
		.color = {
			.r = 22,
			.g = 113,
			.b = 0,
			.a = 1,
			.pair = 9
		},
		.width = 23,
		.height = 23
};

static Asset HeadUp {
		.name = HEAD_UP,
		.path1D = "",
		.path2D = "Resources/Nibbler/2D/head_up.png",
		.color = {
			.r = 22,
			.g = 113,
			.b = 0,
			.a = 1,
			.pair = 9
		},
		.width = 23,
		.height = 23
};

static Asset HeadDown {
		.name = HEAD_DOWN,
		.path1D = "",
		.path2D = "Resources/Nibbler/2D/head_down.png",
		.color = {
			.r = 22,
			.g = 113,
			.b = 0,
			.a = 1,
			.pair = 9
		},
		.width = 23,
		.height = 23
};

static Asset Apple {
		.name = APPLE,
		.path1D = "",
		.path2D = "Resources/Nibbler/2D/apple.png",
		.color = {
			.r = 255,
			.g = 255,
			.b = 255,
			.a = 1,
			.pair = 8
		},
		.width = 20,
		.height = 20
};

NibblerLib::NibblerLib()
{
	loadMap(1);
	parseHighScore();
	createVectorPause();
}

NibblerLib::~NibblerLib()
{}

void NibblerLib::setGfx(IGfx *gfx)
{
	_libGraph = gfx;
}

std::string const &NibblerLib::getGameName() const
{
	return _gameName;
}

inline bool exist_file(const std::string& name) {
	struct stat buffer;
	return (stat (name.c_str(), &buffer) == 0);
}

void NibblerLib::loadMap(int lvl)
{
	size_t idx = 0;
	std::string level = std::to_string(lvl);
	std::string str = MAP_PATH + level + std::string(EXTENSION);
	if (exist_file(str) == false)
		throw ErrorsNibbler(std::cerr, str + " : file not found.");

	std::ifstream infile(str);
	for (std::string line; getline(infile, line); idx++) {
		std::vector<std::string> tmp;
		size_t jdx;
		for (jdx = 0; jdx < line.size(); jdx++) {
			if (line[jdx] != '0' && line[jdx] != '1'
				&& line[jdx] != '2' && line[jdx] != '3'
				&& line[jdx] != '4' && line[jdx] != '5')
				throw ErrorsNibbler(std::cerr, str + " : format map not correct : must be 0 to 5.");
			std::string ptr = {line.substr(jdx, 1)};
			tmp.emplace_back(ptr);
		}
		if (jdx != 30)
			throw ErrorsNibbler(std::cerr, str + " : size map not correct.");
		_vector_map.emplace_back(tmp);
	}
	if (idx != 30)
		throw ErrorsNibbler(std::cerr, str + " : size map not correct.");
	setScoreMax();
	initPlayer();
}

void NibblerLib::createVectorPause()
{
	_vector_pause.vector.push_back(RESUME_OPTION);
	_vector_pause.vector.push_back(MENU_OPTION);
	_vector_pause.vector.push_back(QUIT_OPTION);
	_vector_pause.iterator = _vector_pause.vector.begin();
}

void NibblerLib::parseHighScore()
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

enum Key NibblerLib::loopIntro()
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

void NibblerLib::chooseOptUp()
{
	if (_vector_pause.iterator == _vector_pause.vector.begin()) {
		_vector_pause.iterator = _vector_pause.vector.end();
		_vector_pause.iterator--;
	} else {
		_vector_pause.iterator--;
	}
}

void NibblerLib::chooseOptDown()
{
	if (_vector_pause.iterator == _vector_pause.vector.end() - 1)
		_vector_pause.iterator = _vector_pause.vector.begin();
	else
		_vector_pause.iterator++;
}

std::size_t NibblerLib::getPosFromVector()
{
	std::size_t i = 0;

	for (i = 0; i != _vector_pause.vector.size() && _vector_pause.vector[i] != *_vector_pause.iterator; i++);
	return i;
}

enum Key NibblerLib::loopPause()
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

enum Key NibblerLib::loopGameOver()
{
	bool running = true;
	enum Key keyPress;

	_libGraph->printGameMap(_vector_map);
	std::this_thread::sleep_for(std::chrono::milliseconds(110));
	_libGraph->clear();
	while (running) {
		_libGraph->display();
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

enum Key NibblerLib::launch()
{
	bool gameOver = false;
	bool running = true;
	enum Key keyPress;
	enum Direction dir = UNDEFINED;

	keyPress = loopIntro();
	if (keyPress != K_SPACE)
		return (keyPress);
	_libGraph->clear();
	initGame();
	_lastDir = UNDEFINED;
	while (running) {
		_libGraph->printTitle(_gameName);
		_libGraph->printScore(_score);
		_libGraph->printHighScore(_highScore);
		keyPress = _libGraph->getEvent();
		if (gameOver)
			return (loopGameOver());
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
			if (_lastDir != DOWN) {
				dir = UP;
				_lastDir = dir;
				gameOver = movePlayer(dir);
			}
			break;
		case K_DOWN:
			if (_lastDir != UP) {
				dir = DOWN;
				_lastDir = dir;
				gameOver = movePlayer(dir);
			}
			break;
		case K_LEFT:
			if (_lastDir != RIGHT) {
				dir = LEFT;
				_lastDir = LEFT;
				gameOver = movePlayer(_lastDir);
			}
			break;
		case K_RIGHT:
			if (_lastDir != LEFT) {
				dir = RIGHT;
				_lastDir = dir;
				gameOver = movePlayer(dir);
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
			gameOver = movePlayer(dir);
			break;
		}
		_libGraph->printGameMap(_vector_map);
		_libGraph->display();
		updateScore();
		if (_object == 0) {
			writeNewScore();
			return K_ESCAPE;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(130));
	}
	return K_UNDEFINED;
}

void NibblerLib::writeNewScore()
{
	Point tmp = {
		.name = "RealPlayer",
		.value = _score
	};
	std::ofstream file;

	_highScore.emplace(_highScore.begin(), tmp);
	file.open(HIGHSCORE_PATH);
	for (auto data : _highScore) {
		file << data.value << " " << data.name << "\n";
	}
	file.close();
}

void NibblerLib::setScoreMax()
{
	size_t coord[2] = {0, 0};

	for (coord[0] = 0; coord[0] < _vector_map.size(); coord[0]++) {
		for (coord[1] = 0; coord[1] < _vector_map[coord[0]].size();
			coord[1]++) {
			_scoreMax += (_vector_map[coord[0]][coord[1]] == APPLE)
				? 100 : 0;
			_object += (_vector_map[coord[0]][coord[1]] == APPLE)
				? 1 : 0;
		}
	}
}

std::size_t NibblerLib::getScoreMax()
{
	return _scoreMax;
}

void NibblerLib::updateScore()
{
	size_t tmp = 0;
	size_t coord[2] = {0, 0};

	for (coord[0] = 0; coord[0] < _vector_map.size(); coord[0]++) {
		for (coord[1] = 0; coord[1] < _vector_map[coord[0]].size();
			coord[1]++) {
			tmp += (_vector_map[coord[0]][coord[1]] == APPLE) ? 1 : 0;
		}
	} if (_object != tmp) {
		_score += 100;
		_object -= 1;
	}
}

bool NibblerLib::movePlayer(Direction dir)
{
	switch (dir) {
	case UP:
		return moveUp();
	case DOWN:
		return moveDown();
	case RIGHT:
		return moveRight();
	case LEFT:
		return moveLeft();
	default:
		return false;
	}
	return false;
}


void NibblerLib::initPlayer()
{
	size_t coord[2] = {0, 0};
	Vector2D tail;
	Vector2D tmp;

	for (coord[0] = 0; coord[0] < _vector_map.size(); coord[0]++) {
		for (coord[1] = 0; coord[1] < _vector_map[coord[0]].size();
			coord[1]++) {
			tmp.x = coord[1];
			tmp.y = coord[0];
			if (_vector_map[coord[0]][coord[1]] == HEAD_LEFT)
				_player.emplace(_player.begin(), tmp);
			else if (_vector_map[coord[0]][coord[1]] == BODY)
				_player.emplace_back(tmp);
			else if (_vector_map[coord[0]][coord[1]] == TAIL_LEFT)
				tail = tmp;
		}
	}
	_player.emplace_back(tail);
}

void NibblerLib::addBody(size_t pos_y, size_t pos_x, std::string head)
{
	std::vector<Vector2D>::iterator iteH = _player.begin();
	Vector2D elem = {
		.x = iteH->x,
		.y = iteH->y
	};

	_player.emplace(iteH + 1, elem);
	_player[0].x = pos_x;
	_player[0].y = pos_y;
	_vector_map[pos_y][pos_x] = head;
	_vector_map[elem.y][elem.x] = BODY;
}

void NibblerLib::updateBody(std::string tail)
{
	size_t inc = 0;

	for (inc = _player.size() - 1; inc > 0; inc--) {
		if ((int)(inc - 1) >= 0) {
			_player[inc].x = _player[inc - 1].x;
			_player[inc].y = _player[inc - 1].y;
			if (inc == _player.size() - 1) {
				_vector_map[_player[inc].y][_player[inc].x] = tail;
			} else
				_vector_map[_player[inc].y][_player[inc].x] = BODY;
		}
	}
}

bool NibblerLib::biteTail(size_t pos_x, size_t pos_y)
{
	if (_vector_map[pos_y][pos_x] == TAIL_RIGHT ||
		_vector_map[pos_y][pos_x] == TAIL_UP ||
		_vector_map[pos_y][pos_x] == TAIL_DOWN ||
		_vector_map[pos_y][pos_x] == TAIL_LEFT)
		return true;
	return false;
}

bool NibblerLib::moveLeft()
{
	std::vector<Vector2D>::iterator iteH = _player.begin();
	std::vector<Vector2D>::iterator iteT = _player.end() - 1;

	if (_vector_map[iteH->y][iteH->x - 1] == WALL ||
	    biteTail(iteH->x - 1, iteH->y))
		return true;
	else {
		if (_vector_map[iteH->y][iteH->x + 1] == APPLE) {
			_vector_map[iteT->y][iteT->x] = VOID;
			addBody(iteH->y, iteH->x + 1, HEAD_LEFT);
			updateBody(TAIL_LEFT);
		} else {
			_vector_map[iteT->y][iteT->x] = VOID;
			updateBody(TAIL_LEFT);
			iteH->x = iteH->x - 1;
			_vector_map[iteH->y][iteH->x] = HEAD_LEFT;
		}
	}
	return false;
}

bool NibblerLib::moveRight()
{
	std::vector<Vector2D>::iterator iteH = _player.begin();
	std::vector<Vector2D>::iterator iteT = _player.end() - 1;

	if (_vector_map[iteH->y][iteH->x + 1] == WALL ||
	    biteTail(iteH->x + 1, iteH->y))
		return true;
	else {
		if (_vector_map[iteH->y][iteH->x + 1] == APPLE) {
			_vector_map[iteT->y][iteT->x] = VOID;
			addBody(iteH->y, iteH->x + 1, HEAD_RIGHT);
			updateBody(TAIL_RIGHT);
		} else {
			_vector_map[iteT->y][iteT->x] = VOID;
			updateBody(TAIL_RIGHT);
			iteH->x = iteH->x + 1;
			_vector_map[iteH->y][iteH->x] = HEAD_RIGHT;
		}
	}
	return false;
}

bool NibblerLib::moveDown()
{
	std::vector<Vector2D>::iterator iteH = _player.begin();
	std::vector<Vector2D>::iterator iteT = _player.end() - 1;

	if (_vector_map[iteH->y + 1][iteH->x] == WALL ||
	    biteTail(iteH->x, iteH->y + 1))
		return true;
	else {
		if (_vector_map[iteH->y + 1][iteH->x] == APPLE) {
			_vector_map[iteT->y][iteT->x] = VOID;
			addBody(iteH->y + 1, iteH->x, HEAD_DOWN);
			updateBody(TAIL_DOWN);
		} else {
			_vector_map[iteT->y][iteT->x] = VOID;
			updateBody(TAIL_DOWN);
			iteH->y = iteH->y + 1;
			_vector_map[iteH->y][iteH->x] = HEAD_DOWN;
		}
	}
	return false;
}

bool NibblerLib::moveUp()
{
	std::vector<Vector2D>::iterator iteH = _player.begin();
	std::vector<Vector2D>::iterator iteT = _player.end() - 1;

	if (_vector_map[iteH->y - 1][iteH->x] == WALL ||
	    biteTail(iteH->x, iteH->y - 1))
		return true;
	else {
		if (_vector_map[iteH->y - 1][iteH->x] == APPLE) {
			_vector_map[iteT->y][iteT->x] = VOID;
			addBody(iteH->y - 1, iteH->x, HEAD_UP);
			updateBody(TAIL_UP);
		} else {
			_vector_map[iteT->y][iteT->x] = VOID;
			updateBody(TAIL_UP);
			iteH->y = iteH->y - 1;
			_vector_map[iteH->y][iteH->x] = HEAD_UP;
		}
	}
	return false;
}

void NibblerLib::initGame()
{
	_libGraph->addAsset(Title.name, Title);
	_libGraph->addAsset(Empty.name, Empty);
	_libGraph->addAsset(Wall.name, Wall);
	_libGraph->addAsset(Body.name, Body);
	_libGraph->addAsset(HeadRight.name, HeadRight);
	_libGraph->addAsset(HeadLeft.name, HeadLeft);
	_libGraph->addAsset(HeadUp.name, HeadUp);
	_libGraph->addAsset(HeadDown.name, HeadDown);
	_libGraph->addAsset(TailRight.name, TailRight);
	_libGraph->addAsset(TailLeft.name, TailLeft);
	_libGraph->addAsset(TailUp.name, TailUp);
	_libGraph->addAsset(TailDown.name, TailDown);
	_libGraph->addAsset(Apple.name, Apple);
}

extern "C" {
	IGame *buildEngine() {
		return new NibblerLib();
	}
}
