//
// EPITECH PROJECT, 2018
// AllegroLib.hpp
// File description:
// Created by Thomas BLENEAU
//

#ifndef ALLEGROLIB_HPP_
#define ALLEGROLIB_HPP_

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include "IGfx.hpp"

#ifndef WINDOW_HEIGHT
#define WINDOW_HEIGHT 900
#endif //WINDOW_HEIGHT

#ifndef WINDOW_WIDTH
#define WINDOW_WIDTH 1600
#endif //WINDOW_WIDTH

#ifndef MAP_PAS
#define MAP_PAS 23
#endif //MAP_PAS

#ifndef MAP_INIT_X
#define MAP_INIT_X 145
#endif //MAP_INIT_X

#ifndef MAP_INIT_Y
#define MAP_INIT_Y 190
#endif //MAP_INIT_Y

#ifndef INTRO_POS_Y
#define INTRO_POS_Y 430 + ((680 - 430) / 2)
#endif //INTRO_POS_Y

#ifndef INTRO_POS_X
#define INTRO_POS_X 353 + ((1263 - 353) / 2)
#endif //INTRO_POS_X

#ifndef OVER_POS_Y
#define OVER_POS_Y INTRO_POS_Y + 100
#endif //OVER_POS_Y

#ifndef TTF_SIZE
#define TTF_SIZE 45
#endif //TTF_SIZE

#ifndef TTF_TITLE_SIZE
#define TTF_TITLE_SIZE 120
#endif //TTF_TITLE_SIZE

#ifndef TTF_FONT
#define TTF_FONT "Resources/Fonts/sf_slapstick_comic_shaded.ttf"
#endif //TTF_FONT

#ifndef MENU_BACKGROUND
#define MENU_BACKGROUND "Resources/Arcade/2D/menu.png"
#endif //MENU_BACKGROUND

#ifndef MENU_GAME_POS
#define MENU_GAME_POS 106 + ((645 - 106) / 2)
#endif //MENU_GAME_POS

#ifndef MENU_LIB_POS
#define MENU_LIB_POS 952 + ((1490 - 952) / 2)
#endif //MENU_LIB_POS

#ifndef MENU_FIRST_POS
#define MENU_FIRST_POS 507
#endif //MENU_FIRST_POS

#ifndef MENU_LAST_POS
#define MENU_LAST_POS 856
#endif //MENU_LAST_POS

#ifndef SPACE_POS
#define SPACE_POS 40
#endif //SPACE_POS

#ifndef GAMEPAD
#define GAMEPAD "Resources/Arcade/2D/gamepad@48.png"
#endif //GAMEPAD

#ifndef GAMEPAD_RED
#define GAMEPAD_RED "Resources/Arcade/2D/gamepad_red@48.png"
#endif //GAMEPAD_RED

#ifndef GAMEPAD_WIDTH
#define GAMEPAD_WIDTH 48
#endif //GAMEPAD_WIDTH

#ifndef GAMEPAD_HEIGHT
#define GAMEPAD_HEIGHT 27
#endif //GAMEPAD_HEIGHT

#ifndef GAMEPAD_POS_Y
#define GAMEPAD_POS_Y 507 + (TTF_SIZE / 2) - (GAMEPAD_HEIGHT / 2)
#endif //GAMEPAD_POS_Y

#ifndef JOYSTICK_LEFT
#define JOYSTICK_LEFT "Resources/Arcade/2D/joystick_left@96.png"
#endif //JOYSTICK_LEFT

#ifndef JOYSTICK_RIGHT
#define JOYSTICK_RIGHT "Resources/Arcade/2D/joystick_right@96.png"
#endif //JOYSTICK_RIGHT

#ifndef JOYSTICK_POS_X
#define JOYSTICK_POS_X 645 + ((952 - 645) / 2)
#endif //JOYSTICK_POS_X

#ifndef JOYSTICK_POS_Y
#define JOYSTICK_POS_Y 467 + ((856 - 465) / 2)
#endif //JOYSTICK_POS_Y

#ifndef JOYSTICK_WIDTH
#define JOYSTICK_WIDTH 96
#endif //JOYSTICK_WIDTH

#ifndef JOYSTICK_HEIGHT
#define JOYSTICK_HEIGHT 96
#endif //JOYSTICK_HEIGHT

#ifndef RESOURCES_PATH
#define RESOURCES_PATH "Resources/"
#endif //RESOURCES_PATH

#ifndef PAUSE_POS_X
#define PAUSE_POS_X 543 + ((1055 - 543) / 2)
#endif //PAUSE_POS_X

#ifndef PAUSE_LAST_POS
#define PAUSE_LAST_POS 815
#endif //PAUSE_LAST_POS

#ifndef PAUSE_FIRST_POS
#define PAUSE_FIRST_POS 440
#endif //PAUSE_FIRST_POS

#ifndef PAUSE_WIDTH
#define PAUSE_WIDTH 533
#endif //PAUSE_WIDTH

#ifndef PAUSE_HEIGHT
#define PAUSE_HEIGHT 750
#endif //PAUSE_HEIGHT

#ifndef SCORE_POS_Y
#define SCORE_POS_Y 792 + ((865 - 792) / 2)
#endif //SCORE_POS_Y

#ifndef SCORE_POS_X
#define SCORE_POS_X 1127 + ((1530 - 1127) / 2)
#endif //SCORE_POS_X

class AllegroLib : public IGfx {
public:
	AllegroLib(std::string, size_t, size_t);
	~AllegroLib();
	void createAsset(std::string);
	void addAsset(std::string, Asset);
	void printAsset(std::string, int, int);
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
	size_t _width;
	size_t _height;
	std::string _windowTitle;
	std::map<std::string, Asset> _assets;
	std::string _libName = "lib_arcade_allegro";
	std::string _iteLib;
	std::string _itePause;
	std::string _iteGames;
	std::size_t _over = 1;
	ALLEGRO_DISPLAY *_window = nullptr;
	ALLEGRO_BITMAP *_imageMenu = nullptr;
	ALLEGRO_BITMAP *_background = nullptr;
	ALLEGRO_BITMAP *_intro = nullptr;
	ALLEGRO_BITMAP *_pause = nullptr;
	ALLEGRO_BITMAP *_joystick = nullptr;
	ALLEGRO_BITMAP *_gamepad = nullptr;
	ALLEGRO_FONT *_font = nullptr;
	ALLEGRO_FONT *_fontTitle = nullptr;
	ALLEGRO_EVENT _event;
	ALLEGRO_EVENT_QUEUE *_eventQueue = nullptr;
	std::unordered_map<std::string, ALLEGRO_BITMAP *> _mapGame;
	std::size_t posSelector(dataMap<std::string, std::string>);
	void printSelector(dataMap<std::string, std::string>, int);
	void printGames(dataMap<std::string, std::string>);
	void printLib(dataMap<std::string, std::string>);
	void printEnd(std::vector<std::string> const &, int, int);
	void printJoystick(bool, dataMap<std::string, std::string>,
	dataMap<std::string, std::string>);
	void updateJoystickLeft(int[4]);
	void updateJoystickRight(int[4]);
	void updateIntro();
	void pauseMenu(dataVector<std::string>);
	void gamepadMenu(int);
	void printScoreWithoutAsset();
};

#endif //ALLEGROLIB_HPP_
