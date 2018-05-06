/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Arcade.hpp
*/

#ifndef ARCADE_HPP_
#define ARCADE_HPP_

#include <string>
#include <map>
#include "IGfx.hpp"
#include "IGame.hpp"

class Arcade {
public:
	Arcade(std::string);
	Arcade(Arcade const &) = default;
	Arcade &operator=(Arcade const &) = default;
	~Arcade();

	std::string slugify(std::string);
	void createMapLib(std::string const &);
	bool goodStartFile(const std::string &, const std::string &);
	bool goodExtensionFile(const std::string &, const std::string &);

	void loadLibGame(int);
	void loadLibGfx(bool, int);

	int getPosGfx();
	int getPosGame();
	IGfx *getLibGraph();
	std::string const& getGfxPosGfx(int);
	std::string const& getGamePosGame(int);

	enum Key run();
	enum Key launchGame();
	enum Key intermediateLoop();
	void chooseLibUp(std::size_t map);
	void chooseLibDown(std::size_t map);

	void prevLib(bool);
	void nextLib(bool);
	void prevGame();
	void nextGame();
private:
	int _pos_gfx;
	IGfx *_lib_graph;
	IGfx *_current_graph;
	dataMap<std::string, std::string> _map_gfx;
	int _pos_game;
	IGame *_lib_game;
	dataMap<std::string, std::string> _map_game;
};

#endif //ARCADE_HPP_