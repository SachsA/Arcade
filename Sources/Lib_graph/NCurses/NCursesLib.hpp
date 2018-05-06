//
// EPITECH PROJECT, 2018
// NCursesLib.hpp
// File description:
// Created by Thomas BLENEAU
//

#ifndef NCURSESLIB_HPP_
#define NCURSESLIB_HPP_

#include <iostream>
#include <vector>
#include <map>
#include <ncurses.h>
#include <curses.h>
#include <iomanip>
#include <term.h>
#include <sys/ioctl.h>
#include "IGfx.hpp"
#include "ErrorsNCurses.hpp"

#ifndef WINDOW_HEIGHT
#define WINDOW_HEIGHT 900
#endif //WINDOW_HEIGHT

#ifndef WINDOW_WIDTH
#define WINDOW_WIDTH 1600
#endif //WINDOW_WIDTH

#ifndef PAUSE_POS_Y
#define PAUSE_POS_Y 4
#endif //PAUSE_POS_Y

#ifndef PAUSE_SIZE
#define PAUSE_SIZE 5
#endif //PAUSE_SIZE

#ifndef PAUSE_SPACE
#define PAUSE_SPACE 3
#endif //PAUSE_SPACE

#ifndef RESOURCES_PATH
#define RESOURCES_PATH "Resources/"
#endif //RESOURCES_PATH

#ifndef ARCADE_FONTS
#define ARCADE_FONTS "Resources/Arcade/1D/"
#endif //ARCADE_FONTS

class NCursesLib : public IGfx {
public:
	NCursesLib(std::string, size_t, size_t);
	~NCursesLib();
	void addAsset(std::string, Asset);
	void clearAsset();
	std::string getLibName() const;
	size_t getWidth() const;
	size_t getHeight() const;
	void printTitle(std::string);
	void printScore(std::size_t);
	void printHighScore(std::list<Point>);
	void printGameMap(std::vector<std::vector<std::string>>);
	void printGameOptionMenu();
	void printGameMenu(std::string, dataVector<std::string>);
	void printGameOver(std::size_t, std::list<Point>);
	void printIntro(std::string);
	void printLibSelection(dataMap<std::string, std::string>,
			       dataMap<std::string, std::string>, bool);
	enum Key getEvent();
	void display();
	void clear();
	void clearGameMenu();
private:
	std::map<std::string, Asset> _assets;
	WINDOW *_window = nullptr;
	WINDOW *_intro = nullptr;
	WINDOW *_introText = nullptr;
	WINDOW *_title = nullptr;
	WINDOW *_menu = nullptr;
	WINDOW *_games = nullptr;
	WINDOW *_library = nullptr;
	WINDOW *_dataGames = nullptr;
	WINDOW *_dataLib = nullptr;
	WINDOW *_selectorG = nullptr;
	WINDOW *_selectorL = nullptr;
	WINDOW *_pauseFont = nullptr;
	WINDOW *_pause = nullptr;
	WINDOW *_score = nullptr;
	WINDOW *_highScore = nullptr;
	std::map<std::string, WINDOW *> _selectorP;
	std::map<std::string, WINDOW *> _mapGame;
	bool _key;
	struct termios _keyNew;
	struct termios _keyOld;
	size_t _width;
	size_t _height;
	std::string _windowTitle;
	std::string _libName = "lib_arcade_ncurses";
	std::string _iteGames;
	std::string _iteLib;
	std::string _itePause;
	std::size_t _iteScore;
	std::size_t _iteHighScore = 1;
	void initTerm();
	void initColor();
	void setKeys();
	void eraseWindow(WINDOW *);
	void clearLine(WINDOW *, size_t, size_t);
	void createBorder(WINDOW *, size_t [2], size_t);
	void printColor(WINDOW *, size_t);
	void printSelector(WINDOW *, std::string const &);
	void printOther(WINDOW *, std::string const &, std::size_t &);
	void printEnd(WINDOW *, std::vector<std::string> const &,
			std::size_t &);
	std::string iteSelector(dataMap<std::string, std::string>);
	std::size_t posSelector(dataMap<std::string, std::string>);
	void gamesList(WINDOW *, WINDOW *, dataMap<std::string, std::string>);
	void libList(WINDOW *, WINDOW *, dataMap<std::string, std::string>);
	void updateSelector(bool, dataMap<std::string, std::string>,
				dataMap<std::string, std::string>);
	void createMenu();
	void fillMenu(WINDOW *, std::string const &);
	void fillIntro(std::string);
	void updateScore(std::size_t);
	void updateHighScore(std::list<Point>);
	void updateColorIntro();
	void updateColorTitle();
	void updateTextIntro(std::string);
	void printIntroText(std::string);
	void fillPause(std::string const &);
	void fillWindow(WINDOW *);
	void printPause(std::string const &);
	void pauseSelector();
	void createPause(dataVector<std::string>);
	void clearMapTexture();
	void fillPauseTexture(std::string const &, bool);
	void resizableScreen();
};

#endif //NCURSESLIB_HPP_
