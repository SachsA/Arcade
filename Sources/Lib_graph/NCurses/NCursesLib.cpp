//
// EPITECH PROJECT, 2018
// NCursesLib.cpp
// File description:
// Created by Thomas BLENEAU
//

#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <algorithm>
#include <fstream>
#include "NCursesLib.hpp"

NCursesLib::NCursesLib(std::string name, size_t width,
		       size_t height)
	: _key(true), _windowTitle(name)
{
	struct winsize size;

	initTerm();
	initColor();
	setKeys();
	_window = newwin(height, width, 0, 0);
	if (_window == nullptr)
		throw ErrorsNCurses(std::cerr, "Can't create the NCurses Window.");
	if (ioctl(0, TIOCGWINSZ, (char *) &size) < 0)
		throw ErrorsNCurses(std::cerr, "Can't get the NCurses Window size.");
	_height = size.ws_row;
	_width = size.ws_col;
	resizableScreen();
}

NCursesLib::~NCursesLib()
{
	setKeys();
	werase(_window);
	delwin(_window);
	endwin();
}

void NCursesLib::initTerm()
{
	initscr();
	cbreak();
	noecho();
	nodelay(stdscr, true);
	keypad(stdscr, true);
	curs_set(0);
	timeout(0);
}

void NCursesLib::initColor()
{
	start_color();
	init_pair(0, COLOR_BLACK, COLOR_BLACK);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);
	init_pair(8, COLOR_RED, COLOR_RED);
	init_pair(9, COLOR_GREEN, COLOR_GREEN);
	init_pair(10, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(11, COLOR_BLUE, COLOR_BLUE);
	init_pair(12, COLOR_MAGENTA, COLOR_MAGENTA);
	init_pair(13, COLOR_CYAN, COLOR_CYAN);
	init_pair(14, COLOR_WHITE, COLOR_WHITE);
	init_color(COLOR_BLACK, 0, 0, 0);
}

void NCursesLib::setKeys()
{
	if (_key) {
		ioctl(0, TCGETS, &_keyOld);
		ioctl(0, TCGETS, &_keyNew);
		_keyNew.c_lflag &= ~ICANON;
		_keyNew.c_lflag &= ~ECHO;
		_keyNew.c_cc[VMIN] = 0;
		_keyNew.c_cc[VTIME] = 1;
		ioctl(0, TCSETS, &_keyNew);
	}
	else
		ioctl(0, TCSETS, &_keyOld);
	_key = !_key;
}

void NCursesLib::printGameMap(std::vector<std::vector<std::string>> map)
{
	size_t coord[2] = {0, 0};
	size_t pos_x = COLS / 2 - COLS / 3;
	size_t pos_y = LINES / 3;

	resizableScreen();
	for (coord[0] = 0; coord[0] < map.size(); coord[0]++) {
		pos_x = COLS / 2 - COLS / 3;
		for (coord[1] = 0; coord[1] < map[coord[0]].size(); coord[1]++) {
			wattron(_window, COLOR_PAIR(_assets[map[coord[0]][coord[1]]].color.pair));
			mvwprintw(_window, pos_y, pos_x, "   ");
			wattroff(_window, COLOR_PAIR(_assets[map[coord[0]][coord[1]]].color.pair));
			wrefresh(_window);
			pos_x += 3;
		}
		pos_y += 1;
	}
}

void NCursesLib::addAsset(std::string name, Asset assets)
{
	_assets.emplace(name, assets);
}

void NCursesLib::clearAsset()
{
	_assets.clear();
	initColor();
}

void NCursesLib::clearLine(WINDOW *select, size_t pos_y, size_t pos_x)
{
	size_t inc = 0;

	for (inc = 1; inc < pos_x; inc++)
		mvwprintw(select, pos_y, inc, " ");
	wrefresh(select);
}

void NCursesLib::createBorder(WINDOW *select, size_t sides[2], size_t corner)
{
	wborder(select, sides[0], sides[0], sides[1], sides[1],
		corner, corner, corner, corner);
	wrefresh(select);
	refresh();
}

void NCursesLib::printColor(WINDOW *select, size_t color)
{
	wbkgd(select, COLOR_PAIR(color));
	wrefresh(select);
	refresh();
}

void NCursesLib::printSelector(WINDOW *select, std::string const &ref)
{
	size_t max[2] = {0, 0};

	getmaxyx(select, max[0], max[1]);
	clearLine(select, max[0] / 2, max[1] - 1);
	mvwprintw(select, max[0] / 2, (max[1] / 2) - (ref.size() / 2),
			ref.c_str());
	wrefresh(select);
	refresh();
}

void NCursesLib::printOther(WINDOW *select, std::string const &ref,
				std::size_t &pos_y)
{
	size_t max[2] = {0, 0};

	getmaxyx(select, max[0], max[1]);
	clearLine(select, pos_y, max[1] - 1);
	mvwprintw(select, pos_y, (max[1] / 2) - (ref.size() / 2),
			ref.c_str());
	wrefresh(select);
	pos_y += 4;
}

void NCursesLib::printEnd(WINDOW *select, std::vector<std::string> const &ref,
				std::size_t &pos_y)
{
	size_t inc = 0;
	size_t max[2] = {0, 0};

	getmaxyx(select, max[0], max[1]);
	for (inc = 0; inc < ref.size(); inc++) {
		clearLine(select, pos_y, max[1] - 1);
		mvwprintw(select, pos_y, max[1] / 2 - ref[inc].size() / 2,
				ref[inc].c_str());
		wrefresh(select);
		pos_y += 4;
	}
}

std::size_t NCursesLib::posSelector(dataMap<std::string, std::string> ref)
{
	std::size_t position = 0;
	std::map<std::string, std::string>::iterator ite;

	for (ite = ref.map.begin(); ite != ref.map.end(); ite++) {
		if (ite->first == ref.iterator->first)
			return position;
		position += 1;
	}
	return position;
}

std::string NCursesLib::iteSelector(dataMap<std::string, std::string> ref)
{
	std::map<std::string, std::string>::iterator ite;

	for (ite = ref.map.begin(); ite != ref.map.end(); ite++) {
		if (ite->first == ref.iterator->first)
			return ite->first;
	}
	return ite->first;
}

void NCursesLib::gamesList(WINDOW *select, WINDOW *parent,
			   dataMap<std::string, std::string> ref)
{
	std::string tmp;
	std::vector<std::string> endList;
	std::map<std::string, std::string>::iterator ite;
	std::size_t position[3] = {posSelector(ref), 0, 9};

	if (_iteGames != iteSelector(ref)) {
		for (ite = ref.map.begin(); ite != ref.map.end(); ite++) {
			tmp = ite->first;
			transform(tmp.begin(), tmp.end(), tmp.begin(), ::toupper);
			if (position[1] < position[0])
				endList.push_back(tmp);
			else if (ite->first == ref.iterator->first)
				printSelector(select, tmp);
			else
				printOther(parent, tmp, position[2]);
			position[1] += 1;
		}
		printEnd(parent, endList, position[2]);
		_iteGames = iteSelector(ref);
	}
}

void NCursesLib::libList(WINDOW *select, WINDOW *parent,
			   dataMap<std::string, std::string> ref)
{
	std::string tmp;
	std::vector<std::string> endList;
	std::map<std::string, std::string>::iterator ite;
	std::size_t position[3] = {posSelector(ref), 0, 9};

	if (_iteLib != iteSelector(ref)) {
		for (ite = ref.map.begin(); ite != ref.map.end(); ite++) {
			tmp = ite->first;
			transform(tmp.begin(), tmp.end(), tmp.begin(), ::toupper);
			if (position[1] < position[0])
				endList.push_back(tmp);
			else if (ite->first == ref.iterator->first)
				printSelector(select, tmp);
			else
				printOther(parent, tmp, position[2]);
			position[1] += 1;
		}
		printEnd(parent, endList, position[2]);
		_iteLib = iteSelector(ref);
	}
}

void NCursesLib::updateSelector(bool cursor, dataMap<std::string, std::string> game,
					dataMap<std::string, std::string> gfx)
{
	gamesList(_selectorG, _dataGames, game);
	libList(_selectorL, _dataLib, gfx);
	if (cursor) {
		printColor(_selectorL, 1);
		printColor(_selectorG, 7);
	} else {
		printColor(_selectorG, 1);
		printColor(_selectorL, 7);
	}
}

void NCursesLib::fillMenu(WINDOW *select, std::string const &ref)
{
	size_t ite = 0;
	size_t size = 0;
	std::string tmp;
	size_t max[2] = {0, 0};
	std::ifstream content(ARCADE_FONTS + ref + "_menu.txt");

	getmaxyx(select, max[0], max[1]);
	if (content.is_open()) {
		while (getline(content, tmp)) {
			if (ite == 0)
				size = tmp.size();
			mvwprintw(select, ite, (max[1] / 2) - (size / 2), tmp.c_str());
			ite += 1;
		}
	} else {
		if (ref == "menu")
			mvwprintw(select, (max[0] / 2), (max[1] / 2) - 5, "ARCADE  MENU");
		else if (ref == "games") {
			mvwprintw(select, 5, (max[1] / 2) - 2, "GAMES");
			mvwprintw(select, 6, (max[1] / 2), "LIBRAIRIES");
		} else {
			mvwprintw(select, 5, (max[1] / 2) - 4, "GRAPHICS");
			mvwprintw(select, 6, (max[1] / 2) + 2, "LIBRAIRIES");
		}
	}
	wrefresh(select);
}

void NCursesLib::createMenu()
{
	int size_y[2] = {(LINES / 2) + (LINES / 4), (LINES / 2) + (LINES / 4) - 12};
	int size_x[2] = {(COLS / 2), COLS / 3};
	int pos_y[2] = {14, 24};
	int pos_x[4] = {0, COLS - (COLS / 2), ((COLS / 2) / 2) - ((COLS / 3) / 2), (COLS - (COLS / 2)) + ((COLS / 2) / 2) - ((COLS / 3) / 2)};

	_menu = newwin(10, COLS, 2, 0);
	_games = newwin(size_y[0], size_x[0], pos_y[0], pos_x[0]);
	_library = newwin(size_y[0], size_x[0], pos_y[0], pos_x[1]);
	_dataGames = newwin(size_y[1], size_x[1], pos_y[1], pos_x[2]);
	_dataLib = newwin(size_y[1], size_x[1], pos_y[1], pos_x[3]);
	_selectorL = newwin(5, (COLS / 3) - 12, 26, pos_x[3] + 6);
	_selectorG = newwin(5, (COLS / 3) - 12, 26, pos_x[2] + 6);
	if (_menu == nullptr || _games == nullptr || _library == nullptr ||
		_dataLib == nullptr || _dataGames == nullptr ||
		_selectorG == nullptr || _selectorL == nullptr)
		throw ErrorsNCurses(std::cerr, "Can't create the Arcade Menu.");
}

void NCursesLib::updateColorIntro()
{
	static int temps = 0;

	if (temps == 0) {
		printColor(_intro, rand() % 8);
		temps += 1;
	}
	else if (temps >= 1 && temps < 10000)
		temps += 1;
	else
		temps = 0;
}

void NCursesLib::updateColorTitle()
{
	static int temps = 0;

	if (temps == 0) {
		printColor(_title, rand() % 8);
		temps += 1;
	} else if (temps >= 1 && temps < 10000)
		temps += 1;
	else
		temps = 0;
}

void NCursesLib::updateTextIntro(std::string name)
{
	static int temps = 0;

	if (temps < 15000) {
		printColor(_introText, 1);
		printIntroText(name);
		temps += 1;
	}
	else if (temps >= 15000 && temps < 30000) {
		werase(_introText);
		wrefresh(_introText);
		refresh();
		temps += 1;
	} else
		temps = 0;
}

void NCursesLib::printIntroText(std::string name)
{
	std::string tmp;
	std::size_t inc = 0;
	std::size_t size = 0;
	std::size_t max[2] = {0, 0};
	std::ifstream content(RESOURCES_PATH + name + "/1D/intro_text.txt");
	std::string start = "!! PRESS SPACE TO CONTINUE !!";

	getmaxyx(_introText, max[0], max[1]);
	if (content.is_open()) {
		while (getline(content, tmp)) {
			if (inc == 0)
				size = tmp.size();
			mvwprintw(_introText, (max[0] / 2) - 2 + inc,
				  (max[1] / 2) - (size / 2), tmp.c_str());
			inc += 1;
		}
	} else {
		transform(name.begin(), name.end(), name.begin(), ::toupper);
		mvwprintw(_introText, (max[0] / 2), (max[1] / 2) - (start.size() / 2),
				start.c_str());
	}
	wrefresh(_introText);
	refresh();
}

void NCursesLib::fillIntro(std::string name)
{
	std::string tmp;
	std::size_t inc = 0;
	std::size_t size = 0;
	std::size_t max[2] = {0, 0};
	std::ifstream content(RESOURCES_PATH + name + "/1D/intro.txt");

	getmaxyx(_intro, max[0], max[1]);
	if (content.is_open()) {
		while (getline(content, tmp)) {
			if (inc == 0)
				size = tmp.size();
			mvwprintw(_intro, (max[0] / 4) - 3 + inc,
					(max[1] / 2) - (size / 2), tmp.c_str());
			inc += 1;
		}
	} else {
		transform(name.begin(), name.end(), name.begin(), ::toupper);
		mvwprintw(_intro, (max[0] / 4), (max[1] / 2) - (name.size() / 2), name.c_str());
	}
	wrefresh(_intro);
	refresh();
}

void NCursesLib::createPause(dataVector<std::string> ref)
{
	size_t inc = 0;
	int size_y = 5;
	int size_x = (COLS / 4) - 12;
	size_t uniform[2] = {35, 35};
	int pos_x =  (COLS / 2) - ((COLS / 4) /2) + 6;
	int pos_y = (LINES / 2) - ((LINES / 3) * 2 / 2) +
		PAUSE_POS_Y + PAUSE_SIZE + PAUSE_SPACE;

	for (inc = 0; inc < ref.vector.size(); inc++) {
		_selectorP[ref.vector[inc]] = newwin(size_y, size_x, pos_y, pos_x);
		createBorder(_selectorP[ref.vector[inc]], uniform, 35);
		if (ref.vector[inc] == *ref.iterator) {
			printColor(_selectorP[ref.vector[inc]], 1);
			fillPauseTexture(ref.vector[inc], true);
		} else
			fillPauseTexture(ref.vector[inc], false);
		pos_y += size_y + PAUSE_SPACE;
	}
}

void NCursesLib::fillPauseTexture(std::string const &opt, bool select)
{
	size_t pos[2] = {0, 0};
	size_t max[2] = {0, 0};

	getmaxyx(_selectorP[opt], max[0], max[1]);
	for (pos[0] = 1; pos[0] < max[0] - 1; pos[0]++) {
		for (pos[1] = 1; pos[1] < max[1] - 1; pos[1]++) {
			if (pos[0] == (max[0] / 2) &&
				pos[1] == (max[1] / 2) - (opt.size() / 2)) {
				(select) ? wattron(_selectorP[opt], COLOR_PAIR(1)) :
					wattron(_selectorP[opt], COLOR_PAIR(7));
				mvwprintw(_selectorP[opt], pos[0], pos[1], opt.c_str());
				wattroff(_selectorP[opt], COLOR_PAIR(1));
				pos[1] += opt.size() - 1;
			}
		}
	}
	wrefresh(_selectorP[opt]);
	refresh();
}

void NCursesLib::clearMapTexture()
{
	std::map<std::string, WINDOW *>::iterator ite;

	for (ite = _selectorP.begin(); ite != _selectorP.end(); ite++) {
		werase(ite->second);
		delwin(ite->second);
	}
	_selectorP.clear();
}

void NCursesLib::fillPause(std::string const &name)
{
	werase(_pause);
	wrefresh(_pause);
	printPause(name);
	wrefresh(_pause);
	refresh();
}

void NCursesLib::fillWindow(WINDOW *select)
{
	std::size_t pos_x = 0;
	std::size_t pos_y = 0;
	std::size_t max[2] = {0, 0};

	getmaxyx(select, max[0], max[1]);
	wattron(select, COLOR_PAIR(0));
	for (pos_y = 1; pos_y < max[0]; pos_y++)
		for (pos_x = 1; pos_x < max[1]; pos_x++)
			mvwprintw(select, pos_y, pos_x, " ");
	wattroff(select, COLOR_PAIR(1));
	wrefresh(select);
	refresh();
}

void NCursesLib::printPause(std::string const &name)
{
	std::string tmp;
	std::size_t inc = 0;
	std::size_t size = 0;
	std::size_t max[2] = {0, 0};
	std::ifstream content(RESOURCES_PATH + name + "/1D/pause.txt");

	getmaxyx(_pause, max[0], max[1]);
	wattron(_pause, COLOR_PAIR(rand() % 8));
	if (content.is_open()) {
		while (getline(content, tmp)) {
			if (inc == 0)
				size = tmp.size();
			mvwprintw(_pause, PAUSE_POS_Y + inc, (max[1] / 2) - (size / 2),
				  tmp.c_str());
			inc += 1;
		}
	} else
		mvwprintw(_pause, PAUSE_POS_Y, (max[1] / 2) - 3, "PAUSE");
	wattroff(_pause, COLOR_PAIR(1));
}

void NCursesLib::updateScore(std::size_t score)
{
	std::stringstream ss;
	std::size_t max[2] = {0, 0};

	ss << score;
	getmaxyx(_score, max[0], max[1]);
	mvwprintw(_score, (max[0] / 2), (max[1] / 2) - (ss.str().size() / 2),
			ss.str().c_str());
	wrefresh(_score);
	refresh();
}

void NCursesLib::updateHighScore(std::list<Point> highScore)
{
	std::string tmp;
	std::size_t inc = 6;
	std::stringstream ss;
	std::list<Point>::iterator ite;

	for (ite = highScore.begin(); ite != highScore.end()
			&& inc < 18; ite++) {
		ss << ite->value;
		tmp = ite->name + "  " + ss.str();
		mvwprintw(_highScore, inc, 3, tmp.c_str());
		ss.str("");
		tmp.erase();
		inc += 2;
	}
	wrefresh(_highScore);
	refresh();
}

std::string NCursesLib::getLibName() const
{
	return _libName;
}

size_t NCursesLib::getWidth() const
{
	return _width;
}

size_t NCursesLib::getHeight() const
{
	return _height;
}

void NCursesLib::printTitle(std::string title)
{
	size_t ite = 0;
	size_t size = 0;
	std::string tmp;
	size_t max[2] = {0, 0};
	std::ifstream content(RESOURCES_PATH + title + "/1D/game.txt");

	resizableScreen();
	if (_title == nullptr) {
		_title = newwin(10, COLS, 2, 0);
		getmaxyx(_title, max[0], max[1]);
		if (content.is_open()) {
			while (getline(content, tmp)) {
				if (ite == 0)
					size = tmp.size();
				mvwprintw(_title, ite, (max[1] / 2) - (size / 2), tmp.c_str());
				ite += 1;
			}
		} else
			mvwprintw(_title, 2, (max[1] / 2) - (title.size() / 2),
				  title.c_str());
	}
	updateColorTitle();
	wrefresh(_title);
}

void NCursesLib::printScore(std::size_t score)
{
	size_t ite = 0;
	std::string tmp;
	std::string path = "Arcade";
	std::ifstream content(RESOURCES_PATH + path + "/1D/score.txt");
	size_t uniform[2] = {124, 45};

	resizableScreen();
	if (_score == nullptr)
		_score = newwin(10, COLS / 4, LINES - 12, COLS / 4 * 3);
	if (_iteScore != score) {
		wattron(_score, COLOR_PAIR(4));
		createBorder(_score, uniform, 43);
		if (content.is_open()) {
			while (getline(content, tmp)) {
				mvwprintw(_score, ite, 0, tmp.c_str());
				ite += 1;
			}
		} else
			mvwprintw(_score, 0, 0, "SCORE");
		wattroff(_score, COLOR_PAIR(1));
		updateScore(score);
		wrefresh(_score);
		_iteScore = score;
	}
}

void NCursesLib::printHighScore(std::list<Point> highScore)
{
	size_t ite = 0;
	std::string tmp;
	std::string path = "Arcade";
	std::ifstream content(RESOURCES_PATH + path + "/1D/highScore.txt");
	size_t uniform[2] = {124, 45};

	resizableScreen();
	if (_highScore == nullptr)
		_highScore = newwin(20, COLS / 4, 12, COLS / 4 * 3);
	if (_iteHighScore) {
		wattron(_highScore, COLOR_PAIR(4));
		createBorder(_highScore, uniform, 43);
		if (content.is_open()) {
			while (getline(content, tmp)) {
				mvwprintw(_highScore, ite, 0, tmp.c_str());
				ite += 1;
			}
		} else
			mvwprintw(_highScore, 0, 0, "HIGHSCORE");
		wattroff(_highScore, COLOR_PAIR(1));
		updateHighScore(highScore);
		_iteHighScore = 0;
	}
}

void NCursesLib::printGameOptionMenu()
{
	resizableScreen();
	return;
}

void NCursesLib::printGameMenu(std::string name, dataVector<std::string> vector_pause)
{
	size_t different[2] = {124, 45};
	int size_y = (LINES / 3) * 2;
	int size_x = COLS / 4;
	int pos_x = (COLS / 2) - ((COLS / 4) /2);
	int pos_y = (LINES / 2) - ((LINES / 3) * 2 / 2);

	resizableScreen();
	if (_pause == nullptr) {
		werase(_window);
		wrefresh(_window);
		_pause = newwin(size_y, size_x, pos_y, pos_x);
		createBorder(_pause, different, 43);
		createPause(vector_pause);
	} if (_itePause != *vector_pause.iterator) {
		createBorder(_pause, different, 43);
		fillPause(name);
		clearMapTexture();
		createPause(vector_pause);
		_itePause = *vector_pause.iterator;
	}
}

void NCursesLib::printGameOver([[maybe_unused]]std::size_t score,
			[[maybe_unused]]std::list<Point> highScore)
{
	mvprintw(LINES / 2, COLS / 2 - 5, "GAME OVER");
	mvprintw(LINES / 2 + 1, COLS / 2 - 21, "!! PRESS ESPACE OR S TO RESTART THE GAME !!");
	mvprintw(LINES / 2 + 2, COLS / 2 - 19, "!! OR PRESS ESCAPE TO QUIT THE GAME !!");
	refresh();
}

void NCursesLib::printIntro(std::string name)
{
	size_t uniform[2] = {35, 35};
	int pos_x[2] = {LINES / 4,((LINES / 3) * 2) - (LINES / 8)};
	int pos_y[2] = {(COLS / 2) + (COLS / 4),
			(COLS / 2) - (COLS / 2 + COLS / 4) / 2};

	resizableScreen();
	if (_intro == nullptr) {
		_intro = newwin(LINES - 3, COLS - 5, 2, 3);
		_introText = newwin(pos_x[0], pos_y[0], pos_x[1], pos_y[1]);
		createBorder(_intro, uniform, 35);
		fillIntro(name);
	}
	updateColorIntro();
	updateTextIntro(name);
}

void NCursesLib::printLibSelection(dataMap<std::string, std::string> game,
				   dataMap<std::string, std::string> gfx, bool cursor)
{
	size_t uniform[2] = {35, 35};
	size_t different[2] = {124, 45};
	static int temps = 0;

	resizableScreen();
	if (_menu == nullptr) {
		createMenu();
		printColor(_games, 3);
		printColor(_library, 2);
		fillMenu(_menu, "menu");
		fillMenu(_games, "games");
		fillMenu(_library, "lib");
		createBorder(_dataGames, different, 43);
		createBorder(_dataLib, different, 43);
		createBorder(_selectorG, uniform, 35);
		createBorder(_selectorL, uniform, 35);
		printColor(_dataGames, 3);
		printColor(_dataLib, 2);
	}
	updateSelector(cursor, game, gfx);
	if (temps == 0) {
		wbkgd(_menu, COLOR_PAIR(rand() % 8));
		wrefresh(_menu);
		refresh();
		temps += 1;
	} else if (temps >= 1 && temps < 10000)
		temps += 1;
	else
		temps = 0;
}

void NCursesLib::display()
{
}

void NCursesLib::clearGameMenu()
{
	clearMapTexture();
	if (_pause != nullptr) {
		werase(_pause);
		delwin(_pause);
	} if (_title != nullptr) {
		werase(_title);
		delwin(_title);
	}
	_title = nullptr;
	_itePause.erase();
	_iteScore = 0;
	_iteHighScore = 1;
	_pause = nullptr;
	werase(_window);
	wrefresh(_window);
	refresh();
	system("clear");
	initColor();
}
void NCursesLib::clear()
{
	if (_menu != nullptr) {
		werase(_menu);
		delwin(_menu);
	} if (_games != nullptr) {
		werase(_games);
		delwin(_games);
	} if (_library != nullptr) {
		werase(_library);
		delwin(_library);
	} if (_dataLib != nullptr) {
		werase(_dataLib);
		delwin(_dataLib);
	} if (_dataGames != nullptr) {
		werase(_dataGames);
		delwin(_dataGames);
	} if (_selectorG != nullptr) {
		werase(_selectorG);
		delwin(_selectorG);
	} if (_selectorL != nullptr) {
		werase(_selectorL);
		delwin(_selectorL);
	} if (_intro != nullptr) {
		werase(_intro);
		delwin(_intro);
	} if (_introText != nullptr) {
		werase(_introText);
		delwin(_introText);
	} if (_pause != nullptr) {
		werase(_pause);
		delwin(_pause);
	} if (_score != nullptr) {
		werase(_score);
		delwin(_score);
	} if (_highScore != nullptr) {
		werase(_highScore);
		delwin(_highScore);
	} if (_title != nullptr) {
		werase(_title);
		delwin(_title);
	}
	clearMapTexture();
	_title = nullptr;
	_pause = nullptr;
	_score = nullptr;
	_highScore = nullptr;
	_menu = nullptr;
	_games = nullptr;
	_library = nullptr;
	_dataLib = nullptr;
	_dataGames = nullptr;
	_selectorG = nullptr;
	_selectorL = nullptr;
	_intro = nullptr;
	_introText = nullptr;
	_itePause.erase();
	_iteGames.erase();
	_iteLib.erase();
	_iteScore = 0;
	_iteHighScore = 1;
	werase(_window);
	wrefresh(_window);
	refresh();
	system("clear");
	initColor();
}

enum Key NCursesLib::getEvent()
{
	switch (getch()) {
	case 27:
		return K_ESCAPE;
	case KEY_UP:
		return K_UP;
	case KEY_DOWN:
		return K_DOWN;
	case KEY_LEFT:
		return K_LEFT;
	case KEY_RIGHT:
		return K_RIGHT;
	case 32:
		return K_SPACE;
	case 97:
		return K_A;
	case 122:
		return K_Z;
	case 101:
		return K_E;
	case 114:
		return K_R;
	case 113:
		return K_Q;
	case 115:
		return K_S;
	}
	return K_UNDEFINED;
}

void NCursesLib::resizableScreen()
{
	size_t tmp[2] = {0, 0};
	size_t max[2] = {0, 0};
	std::string str1 = "!! YOUR WINDOW IS TOO SMALL !!";
	std::string str2 = "Put it in full screen for better readability or Press Q/ESCAPE to quit.";

	getmaxyx(stdscr, max[0], max[1]);
	if (max[0] < 55 || max[1] < 211) {
		while (max[0] < 55 && max[1] < 211) {
			getmaxyx(stdscr, max[0], max[1]);
			if (tmp[0] != max[0] || tmp[1] != max[1]) {
				tmp[0] = max[0];
				tmp[1] = max[1];
				this->clear();
				move(LINES / 2, (COLS / 2) - (str1.size() / 2));
				printw(str1.c_str());
				move(LINES / 2 + 1, (COLS / 2) - (str2.size() / 2));
				printw(str2.c_str());
			}
			refresh();
		}
		this->clear();
		refresh();
	}
}

extern "C" {
	IGfx *buildEngine() {
		return new NCursesLib("NCurses Window", 0, 0);
	}
}
