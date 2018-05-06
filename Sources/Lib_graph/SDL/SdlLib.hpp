/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** SdlLib.hpp
*/

#ifndef SDLLIB_HPP_
#define SDLLIB_HPP_

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <SDL2/SDL.h>
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

#ifndef TTF_TITLE_SIZE
#define TTF_TITLE_SIZE 110
#endif //TTF_TITLE_SIZE

#ifndef TTF_SIZE
#define TTF_SIZE 45
#endif //TTF_SIZE

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

#ifndef SCORE_POS_Y
#define SCORE_POS_Y 792 + ((865 - 792) / 2)
#endif //SCORE_POS_Y

#ifndef SCORE_POS_X
#define SCORE_POS_X 1127 + ((1530 - 1127) / 2)
#endif //SCORE_POS_X

#ifndef HIGHSCORE_POS_Y
#define HIGHSCORE_POS_Y 244 + ((523 - 244) / 2)
#endif //HIGHSCORE_POS_Y

#ifndef HIGHSCORE_POS_X
#define HIGHSCORE_POS_X 1127 + ((1530 - 1127) / 2)
#endif //HIGHSCORE_POS_X

typedef struct texture_t {
	int x;
	int y;
} texture_s;

class SdlLib : public IGfx {
public:
	SdlLib(std::string name, size_t width, size_t height);
	~SdlLib();
	void addAsset(std::string, Asset);
	void createAsset(std::string);
	void printAsset(std::string, int, int);
	SDL_Rect sizeAsset(std::string, int, int);
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
	void printLibSelection(dataMap<std::string, std::string> games,
			       dataMap<std::string, std::string> gfx, bool cursor);
	enum Key getEvent();
	void display();
	void clear();
	void clearGameMenu();
private:
	std::map<std::string, Asset> _assets;
	SDL_Window *_window = nullptr;
	SDL_Renderer *_renderer = nullptr;
	SDL_Texture *_intro = nullptr;
	SDL_Texture *_background = nullptr;
	SDL_Texture *_pause = nullptr;
	SDL_Texture *_imageMenu = nullptr;
	SDL_Texture *_joystick = nullptr;
	SDL_Texture *_gamepad = nullptr;
	SDL_Texture *_score = nullptr;
	TTF_Font *_font = nullptr;
	TTF_Font *_fontTitle = nullptr;
	std::unordered_map<SDL_Texture *, SDL_Rect> _textGMenu;
	std::unordered_map<SDL_Texture *, SDL_Rect> _textLMenu;
	std::unordered_map<SDL_Texture *, SDL_Rect> _pauseMenu;
	std::unordered_map<std::string, SDL_Texture *> _mapGame;
	SDL_Event _event;
	size_t _width;
	size_t _height;
	bool _iteCursor = true;
	std::string _itePause;
	std::string _iteGames;
	std::string _iteLib;
	std::size_t _iteScore;
	std::size_t _iteHighScore = 1;
	std::size_t _over = 1;
	std::string _libName = "lib_arcade_sdl2";
	std::size_t posSelector(dataMap<std::string, std::string>);
	void updateSelector(dataMap<std::string, std::string>, int);
	void printJoystick(bool, dataMap<std::string, std::string>,
				dataMap<std::string, std::string>);
	void updateJoystick(bool);
	void updateIntro();
	void printGames(dataMap<std::string, std::string>);
	void printLib(dataMap<std::string, std::string>);
	void getSelector(dataMap<std::string, std::string>, int);
	void clearMapTexture(std::size_t);
	void clearMapTexture();
	void clearGameMap();
	void createGameMap(std::vector<std::vector<std::string>>);
	void pauseMenu(dataVector<std::string>);
	void printPause();
	void gamepadPause(SDL_Rect, int);
	void printScoreWithoutAsset();
};

#endif //SDLLIB_HPP_
