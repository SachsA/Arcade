//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// Arcade.cpp
//

#include <dirent.h>
#include <string.h>
#include "Arcade.hpp"
#include "Errors.hpp"
#include "LibLoader.hpp"
#include "ErrorsArcade.hpp"

Arcade::Arcade(std::string lib_graph)
{
	int i = 0;
	bool exist = false;
	std::map<std::string, std::string>::iterator it;

	createMapLib("./lib/");
	createMapLib("./games/");
	if (_map_game.map.empty())
		throw ErrorsArcade(std::cerr, "There is no game in ./games.");
	if (_map_gfx.map.empty())
		throw ErrorsArcade(std::cerr, "There is no lib in ./lib.");
	if (lib_graph.find("./") && lib_graph.find("/"))
		lib_graph = "./" + lib_graph;
	for (it = this->_map_gfx.map.begin(); it != this->_map_gfx.map.end(); it++) {
		if (it->second == lib_graph) {
			this->_pos_gfx = i;
			this->_map_gfx.iterator = it;
			this->_map_game.iterator = this->_map_game.map.begin();
			exist = true;
		}
		i++;
	}
	if (exist == false)
		throw ErrorsArcade(std::cerr, "Lib_graph not found.");
}

Arcade::~Arcade()
{
	delete _lib_graph;
}

void Arcade::createMapLib(std::string const &folder)
{
	DIR *dir;
	struct dirent *ent;
	std::string verif;
	std::string slug;

	if ((dir = opendir(folder.c_str())) != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			if (ent->d_name[0] != '.') {
				verif = std::string(ent->d_name);
				if (goodStartFile(verif, "lib_arcade_") &&
				    goodExtensionFile(verif, ".so")) {
					slug = slugify(verif);
					if (folder == "./lib/")
						this->_map_gfx.map[slug] = folder + verif;
					else
						this->_map_game.map[slug] = folder + verif;
				}
			}
		}
		closedir (dir);
	} else {
		throw ErrorsArcade(std::cerr, "Couldn't open directory.");
	}
}

bool Arcade::goodStartFile(const std::string &str, const std::string &start)
{
	if (strncmp(str.c_str(), start.c_str(), start.size()) == 0) {
		return true;
	}
	return false;
}

bool Arcade::goodExtensionFile(const std::string &str, const std::string &suf)
{
    return str.size() >= suf.size() &&
           str.compare(str.size() - suf.size(), suf.size(), suf) == 0;
}

std::string Arcade::slugify(std::string verif)
{
	std::string pattern = "lib_arcade_";
	size_t pattern_size = verif.find(pattern) + pattern.size();
	std::string tmp = verif.substr(pattern_size, verif.size());
	return tmp.substr(0, tmp.size() - 3);
}

void Arcade::loadLibGfx(bool first, int it)
{
	LibLoader <IGfx> *loader = new LibLoader <IGfx>(getGfxPosGfx(it));

	_current_graph = loader->load("buildEngine");
	if (first == true)
		_lib_graph = _current_graph;
	if (_lib_graph == NULL) {
		throw ErrorsArcade(std::cerr, "Lib_graph not found.");
	}
}

void Arcade::loadLibGame(int it)
{
	LibLoader <IGame> *loader = new LibLoader <IGame>(getGamePosGame(it));

	_lib_game = loader->load("buildEngine");
	if (_lib_game == NULL) {
		throw ErrorsArcade(std::cerr, "Lib_game not found.");
	}
}

std::string const& Arcade::getGfxPosGfx(int idx)
{
	int i = 0;
	std::map<std::string, std::string>::iterator it;

	for (it = this->_map_gfx.map.begin(); it != this->_map_gfx.map.end() && i != idx; it++)
	i++;
	return it->second;
}

std::string const& Arcade::getGamePosGame(int idx)
{
	int i = 0;
	std::map<std::string, std::string>::iterator it;

	for (it = this->_map_game.map.begin(); it != this->_map_game.map.end() && i != idx; it++)
	i++;
	return it->second;
}

IGfx *Arcade::getLibGraph()
{
	return _lib_graph;
}

int Arcade::getPosGfx()
{
	return _pos_gfx;
}

int Arcade::getPosGame()
{
	return _pos_game;
}

void Arcade::chooseLibUp(std::size_t map)
{
	if (map == 1) {
		if (_map_gfx.iterator == _map_gfx.map.begin()) {
			_map_gfx.iterator = _map_gfx.map.end();
			_map_gfx.iterator--;
		} else {
			_map_gfx.iterator--;
		}
	} else {
		if (_map_game.iterator == _map_game.map.begin()) {
			_map_game.iterator = _map_game.map.end();
			_map_game.iterator--;
		} else {
			_map_game.iterator--;
		}
	}
}

void Arcade::chooseLibDown(std::size_t map)
{
	if (map == 1) {
		if (_map_gfx.iterator->first == _map_gfx.map.rbegin()->first)
			_map_gfx.iterator = _map_gfx.map.begin();
		else
			_map_gfx.iterator++;
	} else {
		if (_map_game.iterator->first == _map_game.map.rbegin()->first)
			_map_game.iterator = _map_game.map.begin();
		else
			_map_game.iterator++;
	}
}

void Arcade::prevGame()
{
	int index;

	chooseLibUp(0);
	index = std::distance(_map_game.map.begin(), _map_game.iterator);
	delete _lib_game;
	loadLibGame(index);
}

void Arcade::nextGame()
{
	int index;

	chooseLibDown(0);
	index = std::distance(_map_game.map.begin(), _map_game.iterator);
	delete _lib_game;
	loadLibGame(index);
}

void Arcade::prevLib(bool menu)
{
	int index;

	chooseLibUp(1);
	index = std::distance(_map_gfx.map.begin(), _map_gfx.iterator);
	if (menu == false) {
		delete _current_graph;
		loadLibGfx(false, index);
	} else {
		delete _lib_graph;
		loadLibGfx(true, index);
	}
}

void Arcade::nextLib(bool menu)
{
	int index;

	chooseLibDown(1);
	index = std::distance(_map_gfx.map.begin(), _map_gfx.iterator);
	if (menu == false) {
		delete _current_graph;
		loadLibGfx(false, index);
	} else {
		delete _lib_graph;
		loadLibGfx(true, index);
	}
}

enum Key Arcade::launchGame()
{
	bool running = true;
	enum Key keyPress;

	_current_graph->clear();
	_lib_game->setGfx(_current_graph);
	while (running) {
		keyPress = _lib_game->launch();
		switch (keyPress) {
			case K_A:
			case K_Z:
			case K_E:
			case K_R:
			case K_Q:
			case K_S:
			case K_ESCAPE:
				return (keyPress);
			default:
				break;
		}
	}
	return K_UNDEFINED;
}

enum Key Arcade::intermediateLoop()
{
	int index;
	enum Key keyPress;
	bool running = true;

	index = std::distance(_map_gfx.map.begin(), _map_gfx.iterator);
	if (_pos_gfx != index) {
		delete _lib_graph;
		loadLibGfx(false, index);
	}
	index = std::distance(_map_game.map.begin(), _map_game.iterator);
	loadLibGame(index);
	while (running) {
		keyPress = launchGame();
		switch (keyPress) {
			case K_A:
				prevGame();
				break;
			case K_Z:
				nextGame();
				break;
			case K_E:
				prevLib(false);
				break;
			case K_R:
				nextLib(false);
				break;
			case K_S:
				delete _lib_game;
				loadLibGame(index);
				break;
			case K_ESCAPE:
			case K_Q:
				delete _current_graph;
				delete _lib_game;
				if (keyPress == K_Q)
					return (keyPress);
				loadLibGfx(true, _pos_gfx);
				running = false;
				break;
			default:
			 	break;
		}
	}
	return K_UNDEFINED;
}

enum Key Arcade::run()
{
	enum Key keyPress;
	bool running = true;
	bool cursor = false;

	while (running) {
		keyPress = _lib_graph->getEvent();
		_lib_graph->printLibSelection(_map_game, _map_gfx, cursor);
		switch (keyPress) {
			case K_UP:
				(cursor == true) ? chooseLibUp(1) : chooseLibUp(0);
				break;
			case K_DOWN:
				(cursor == true) ? chooseLibDown(1) : chooseLibDown(0);
				break;
			case K_LEFT:
				cursor = !cursor;
				break;
			case K_RIGHT:
				cursor = !cursor;
				break;
			case K_SPACE:
				keyPress = intermediateLoop();
				if (keyPress == K_Q)
					return (keyPress);
				break;
			case K_E:
				prevLib(true);
				break;
			case K_R:
				nextLib(true);
				break;
			case K_ESCAPE:
			case K_Q:
				running = false;
				break;
			default:
			 	break;
		}
	}
	return K_UNDEFINED;
}
