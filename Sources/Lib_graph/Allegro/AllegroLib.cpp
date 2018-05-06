//
// EPITECH PROJECT, 2018
// AllegroLib.cpp
// File description:
// Created by Thomas BLENEAU
//

#include <sstream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "AllegroLib.hpp"
#include "ErrorsAllegro.hpp"

AllegroLib::AllegroLib(std::string name, size_t width, size_t height)
	: _width(width), _height(height), _windowTitle(name)
{
	if (!al_init())
		throw ErrorsAllegro(std::cerr, "Allegro init fail.");
	if (!al_init_image_addon())
		throw ErrorsAllegro(std::cerr, "Allegro image addon fail.");
	al_set_new_display_option(ALLEGRO_SINGLE_BUFFER, 1, ALLEGRO_REQUIRE);
	_window = al_create_display(_width, _height);
	if (_window == NULL)
		throw ErrorsAllegro(std::cerr, "Allegro create window fail.");
	al_set_window_title(_window, name.c_str());
	_eventQueue = al_create_event_queue();
	if (_eventQueue == NULL)
		throw ErrorsAllegro(std::cerr, "Allegro create EventQueue fail.");
	if (!al_install_keyboard())
		throw ErrorsAllegro(std::cerr, "Allegro install keyboard fail.");
	if (!al_init_font_addon())
		throw ErrorsAllegro(std::cerr, "Allegro font addon fail.");
	if (!al_init_ttf_addon())
		throw ErrorsAllegro(std::cerr, "Allegro init ttf addon fail.");
	_font = al_load_ttf_font(TTF_FONT, TTF_SIZE, 0);
	if (_font == NULL)
		throw ErrorsAllegro(std::cerr, "Allegro can't load TTF font.");
	_fontTitle = al_load_ttf_font(TTF_FONT, TTF_TITLE_SIZE, 0);
	if (_fontTitle == NULL)
		throw ErrorsAllegro(std::cerr, "Allegro can't load TTF font.");
	al_register_event_source(_eventQueue, al_get_display_event_source(_window));
	al_register_event_source(_eventQueue, al_get_keyboard_event_source());
}

AllegroLib::~AllegroLib()
{
	al_destroy_font(_font);
	if (_fontTitle != nullptr)
		al_destroy_font(_fontTitle);
	al_destroy_bitmap(_background);
	al_destroy_bitmap(_gamepad);
	al_destroy_bitmap(_joystick);
	al_destroy_bitmap(_imageMenu);
	al_destroy_event_queue(_eventQueue);
	al_shutdown_ttf_addon();
	al_shutdown_font_addon();
	al_destroy_display(_window);
}

void AllegroLib::addAsset(std::string name, Asset assets)
{
	_assets.emplace(name, assets);
	createAsset(name);
}

void AllegroLib::createAsset(std::string name)
{
	if (_assets.find(name) != _assets.end()) {
		if (_mapGame[name] != nullptr) {
			al_destroy_bitmap(_mapGame[name]);
		}
		_mapGame[name] = al_load_bitmap(_assets[name].path2D.c_str());
	}
}

void AllegroLib::printAsset(std::string name, int x, int y)
{
	if (_assets.find(name) != _assets.end()) {
		if (_mapGame[name] != NULL) {
			al_set_clipping_rectangle(x, y, _assets[name].width, _assets[name].height);
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_bitmap(_mapGame[name], x, y, 0);
		} else {
			if (_assets[name].name.size() > 1) {
				_assets[name].width = 0;
				_assets[name].height = 0;
				al_draw_text(_font, al_map_rgb(_assets[name].color.r,
							_assets[name].color.g,
							_assets[name].color.b),
						x, y, ALLEGRO_ALIGN_CENTRE,
						_assets[name].name.c_str());
			} else {
				al_set_clipping_rectangle(x, y, _assets[name].width, _assets[name].height);
				al_clear_to_color(al_map_rgb(_assets[name].color.r, _assets[name].color.g, _assets[name].color.b));
			}
		}
	}
}

void AllegroLib::clearAsset()
{
	std::unordered_map<std::string, ALLEGRO_BITMAP *>::iterator itt;

	_assets.clear();
	for (itt = _mapGame.begin(); itt != _mapGame.end(); itt++)
		al_destroy_bitmap(itt->second);
	_mapGame.clear();
}

std::string AllegroLib::getLibName() const
{
	return _libName;
}

size_t AllegroLib::getWidth() const
{
	return _width;
}

size_t AllegroLib::getHeight() const
{
	return _height;
}

void AllegroLib::printScoreWithoutAsset()
{
	al_draw_text(_font, al_map_rgb(8, 18, 212),
			1250, 730, ALLEGRO_ALIGN_CENTRE, "Score");
	al_draw_text(_font, al_map_rgb(8, 18, 212),
			1250, 186, ALLEGRO_ALIGN_CENTRE, "HighScore");
}

void AllegroLib::printTitle(std::string name)
{
	if (_mapGame.find(name) != _mapGame.end()) {
		if (_assets[name].width == 0) {
			printAsset(name, WINDOW_WIDTH / 2, 25);
			printScoreWithoutAsset();
		} else
			printAsset(name, 0, 0);
	}
}

void AllegroLib::printScore(std::size_t score)
{
	std::stringstream ss;

	ss << score;
	al_set_clipping_rectangle(1127, 792, 403, 73);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_text(_font, al_map_rgb(255, 255, 255),
		SCORE_POS_X,
		SCORE_POS_Y - (TTF_SIZE / 2), ALLEGRO_ALIGN_CENTRE,
		ss.str().c_str());
}

void AllegroLib::printHighScore(std::list<Point> highScore)
{
	int pos_y = 254;
	std::string name;
	std::stringstream ss;
	std::list<Point>::iterator ite;

	al_set_clipping_rectangle(1127, 244, 403, 279);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	for (ite = highScore.begin(); ite != highScore.end() &&
			pos_y + TTF_SIZE < 523; ite++) {
		ss << ite->value;
		name = (ite->name + "  " + ss.str());
		al_draw_text(_font, al_map_rgb(255, 255, 255),
				SCORE_POS_X, pos_y, ALLEGRO_ALIGN_CENTRE,
				name.c_str());
		pos_y += 10 + TTF_SIZE;
		ss.str("");
	}
}

void AllegroLib::printGameMap(std::vector<std::vector<std::string>> map)
{
	size_t coord[2] = {0, 0};
	size_t pos_x = MAP_INIT_X;
	size_t pos_y = MAP_INIT_Y;

	al_set_clipping_rectangle(MAP_INIT_Y, MAP_INIT_Y, 690, 690);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	for (coord[0] = 0; coord[0] < map.size(); coord[0]++) {
		pos_x = MAP_INIT_X;
		for (coord[1] = 0; coord[1] < map[coord[0]].size(); coord[1]++) {
			printAsset(map[coord[0]][coord[1]], pos_x, pos_y);
			pos_x += MAP_PAS;
		}
		pos_y += MAP_PAS;
	}
}

void AllegroLib::printGameOptionMenu()
{
	return;
}

void AllegroLib::printGameMenu(std::string name, dataVector<std::string> vector_pause)
{
	std::string path;

	if (_pause == nullptr) {
		al_set_clipping_rectangle(0, 0, _width, _height);
		al_clear_to_color(al_map_rgb(0, 0, 0));
		path = RESOURCES_PATH + name + "/2D/pause.png";
		_pause = al_load_bitmap(path.c_str());
		if (_pause != nullptr)
			al_draw_bitmap(_pause, 0, 0, 0);
		_gamepad = al_load_bitmap(GAMEPAD_RED);
	}
	pauseMenu(vector_pause);
}

void AllegroLib::printGameOver(std::size_t score, std::list<Point> highScore)
{
	std::string path;
	std::string name;
	std::string start = "!! Press SPACE or S to restart the GAME !!";
	std::string quit = "or press ESCAPE to quit the GAME";

	al_set_clipping_rectangle(0, 0, _width, _height);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_text(_fontTitle, al_map_rgb(255, 255, 255),
		     WINDOW_WIDTH / 2, 150,
		     ALLEGRO_ALIGN_CENTRE, "GAME OVER");
	al_draw_text(_font, al_map_rgb(8, 18, 212),
		     WINDOW_WIDTH / 4,
		     150 + TTF_TITLE_SIZE + 60, ALLEGRO_ALIGN_LEFT,
		     "SCORE");
	al_draw_textf(_font, al_map_rgb(255, 255, 255),
		      (WINDOW_WIDTH / 4) + 70,
		      150 + TTF_TITLE_SIZE + 60 + TTF_SIZE + 20,
		      ALLEGRO_ALIGN_LEFT,
		      "%ld", score);
	al_draw_text(_font, al_map_rgb(8, 18, 212),
		     (WINDOW_WIDTH / 2) + (WINDOW_WIDTH / 4),
		     150 + TTF_TITLE_SIZE + 60, ALLEGRO_ALIGN_RIGHT,
		     "HIGHSCORE");
	al_draw_textf(_font, al_map_rgb(255, 255, 255),
		      (WINDOW_WIDTH / 2) + (WINDOW_WIDTH / 4),
		      150 + TTF_TITLE_SIZE + 60 + TTF_SIZE + 20,
		      ALLEGRO_ALIGN_CENTRE,
		      "%s  %ld", highScore.front().name.c_str(),
		      highScore.front().value);
	al_draw_text(_font, al_map_rgb(255, 255, 255),
		     INTRO_POS_X, OVER_POS_Y, ALLEGRO_ALIGN_CENTRE,
		     start.c_str());
	al_draw_text(_font, al_map_rgb(255, 255, 255),
		     INTRO_POS_X, OVER_POS_Y + TTF_SIZE + 15, ALLEGRO_ALIGN_CENTRE,
		     quit.c_str());
}

void AllegroLib::printIntro(std::string name)
{
	std::string path;

	if (_intro == nullptr) {
		path = RESOURCES_PATH + name + "/2D/intro.png";
		_intro = al_load_bitmap(path.c_str());
		if (_intro != nullptr)
			al_draw_bitmap(_intro, 0, 0, 0);
		else
			al_draw_text(_fontTitle, al_map_rgb(255, 255, 255),
					WINDOW_WIDTH / 2, 150,
					ALLEGRO_ALIGN_CENTRE, name.c_str());
		al_flip_display();
	}
	updateIntro();
}

void AllegroLib::printLibSelection(dataMap<std::string, std::string> game,
				   dataMap<std::string, std::string> gfx, bool cursor)
{
	if (_imageMenu == nullptr) {
		_imageMenu = al_load_bitmap(MENU_BACKGROUND);
		if (_imageMenu != nullptr)
			al_draw_bitmap(_imageMenu, 0, 0, 0);
		else {
			al_draw_text(_fontTitle, al_map_rgb(255, 56, 0),
					WINDOW_WIDTH / 2, 50,
					ALLEGRO_ALIGN_CENTRE, "Arcade Menu");
			al_draw_text(_font, al_map_rgb(20, 128, 220),
					MENU_GAME_POS, 370,
					ALLEGRO_ALIGN_CENTRE, "Games Libraries");
			al_draw_text(_font, al_map_rgb(15, 183, 21),
					MENU_LIB_POS, 370,
					ALLEGRO_ALIGN_CENTRE, "Graphics Libraries");
		}
		_gamepad = al_load_bitmap(GAMEPAD);
		al_flip_display();
	}
	printGames(game);
	printLib(gfx);
	printJoystick(cursor, gfx, game);
}

void AllegroLib::display()
{
	al_flip_display();
	al_set_clipping_rectangle(0, 0, _width, _height);
	al_clear_to_color(al_map_rgb(0, 0, 0));
}

void AllegroLib::clear()
{
	_over = 1;
	_iteLib.erase();
	_iteGames.erase();
	_itePause.erase();
	al_destroy_bitmap(_background);
	_background = nullptr;
	al_destroy_bitmap(_intro);
	_intro = nullptr;
	al_destroy_bitmap(_gamepad);
	_gamepad = nullptr;
	al_destroy_bitmap(_joystick);
	_joystick = nullptr;
	al_destroy_bitmap(_imageMenu);
	_imageMenu = nullptr;
	al_destroy_bitmap(_pause);
	_pause = nullptr;
	al_set_clipping_rectangle(0, 0, _width, _height);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();
	clearAsset();
}

void AllegroLib::clearGameMenu()
{
	al_destroy_bitmap(_pause);
	_pause = nullptr;
	_itePause.erase();
	al_flip_display();
	al_set_clipping_rectangle(0, 0, _width, _height);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();
}

enum Key AllegroLib::getEvent()
{
	bool check;
	ALLEGRO_TIMEOUT timeout;

	al_init_timeout(&timeout, 0);
	check = al_wait_for_event_until(_eventQueue, &_event, &timeout);
	if (check && _event.type == ALLEGRO_EVENT_KEY_DOWN) {
		switch (_event.keyboard.keycode) {
		case ALLEGRO_KEY_ESCAPE:
			return K_ESCAPE;
		case ALLEGRO_KEY_SPACE:
			return K_SPACE;
		case ALLEGRO_KEY_LEFT:
			return K_LEFT;
		case ALLEGRO_KEY_RIGHT:
			return K_RIGHT;
		case ALLEGRO_KEY_UP:
			return K_UP;
		case ALLEGRO_KEY_DOWN:
			return K_DOWN;
		case ALLEGRO_KEY_A:
			return K_A;
		case ALLEGRO_KEY_Z:
			return K_Z;
		case ALLEGRO_KEY_E:
			return K_E;
		case ALLEGRO_KEY_R:
			return K_R;
		case ALLEGRO_KEY_Q:
			return K_Q;
		case ALLEGRO_KEY_S:
			return K_S;
		}
	}
	return K_UNDEFINED;
}

void AllegroLib::gamepadMenu(int pos_y)
{
	if (_gamepad != nullptr) {
		al_set_clipping_rectangle(1035 - GAMEPAD_WIDTH, pos_y + TTF_SIZE / 2 - GAMEPAD_HEIGHT / 2,
					  GAMEPAD_WIDTH, GAMEPAD_HEIGHT);
		al_clear_to_color(al_map_rgb(192, 192, 192));
		al_draw_bitmap(_gamepad, 1035 - GAMEPAD_WIDTH, pos_y + TTF_SIZE / 2 - GAMEPAD_HEIGHT / 2, 0);
		al_set_clipping_rectangle(563, pos_y + TTF_SIZE / 2 - GAMEPAD_HEIGHT / 2,
					  GAMEPAD_WIDTH, GAMEPAD_HEIGHT);
		al_clear_to_color(al_map_rgb(192, 192, 192));
		al_draw_bitmap(_gamepad, 563, pos_y + TTF_SIZE / 2 - GAMEPAD_HEIGHT / 2, 0);
	} else {
		al_set_clipping_rectangle(1035 - GAMEPAD_WIDTH, pos_y + TTF_SIZE / 2 - GAMEPAD_HEIGHT / 2,
					GAMEPAD_WIDTH, GAMEPAD_HEIGHT);
		al_clear_to_color(al_map_rgb(194, 67, 35));
		al_set_clipping_rectangle(563, pos_y + TTF_SIZE / 2 - GAMEPAD_HEIGHT / 2,
					GAMEPAD_WIDTH, GAMEPAD_HEIGHT);
		al_clear_to_color(al_map_rgb(194, 67, 35));
	}
	al_flip_display();
}

void AllegroLib::pauseMenu(dataVector<std::string> ref)
{
	int save = 0;
	size_t ite = 0;
	int pos_y = PAUSE_FIRST_POS;

	if (_itePause != *ref.iterator) {
		if (_pause == nullptr) {
			al_set_clipping_rectangle(533, 75, 533, 750);
			al_clear_to_color(al_map_rgb(192, 192, 192));
			al_draw_text(_fontTitle, al_map_rgb(0, 0, 0),
				PAUSE_POS_X, 150, ALLEGRO_ALIGN_CENTRE,
				"PAUSE");
		} else {
			al_set_clipping_rectangle(543, 315, 512, 500);
			al_clear_to_color(al_map_rgb(192, 192, 192));
		} for (ite = 0; ite < ref.vector.size() &&
				pos_y + TTF_SIZE < PAUSE_LAST_POS; ite++) {
			if (*ref.iterator == ref.vector[ite]) {
				al_draw_text(_font, al_map_rgb(194, 67, 35),
					PAUSE_POS_X,
					pos_y, ALLEGRO_ALIGN_CENTRE,
					ref.vector[ite].c_str());
				save = pos_y;
			} else
				al_draw_text(_font, al_map_rgb(91, 91, 93),
					PAUSE_POS_X,
					pos_y, ALLEGRO_ALIGN_CENTRE,
					ref.vector[ite].c_str());
			pos_y += SPACE_POS + TTF_SIZE;
		}
		_itePause = *ref.iterator;
		al_flip_display();
		gamepadMenu(save);
	}
}

std::size_t AllegroLib::posSelector(dataMap<std::string, std::string> ref)
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

void AllegroLib::updateIntro()
{
	std::string start = "!! Press SPACE to continue !!";
	static int temps = 0;

	al_set_clipping_rectangle(353, 430, 910, 250);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	if (temps < 380) {
		al_draw_text(_font, al_map_rgb(255, 255, 255),
				INTRO_POS_X, INTRO_POS_Y, ALLEGRO_ALIGN_CENTRE,
				start.c_str());
		al_flip_display();
		temps += 1;
	} else if (temps >= 380 && temps < 760) {
		temps += 1;
		al_flip_display();
	} else
		temps = 0;
}

void AllegroLib::updateJoystickRight(int pos_x[4])
{
	if (_gamepad != nullptr) {
		al_set_clipping_rectangle(pos_x[2], GAMEPAD_POS_Y, GAMEPAD_WIDTH, GAMEPAD_HEIGHT);
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_bitmap(_gamepad, pos_x[2], GAMEPAD_POS_Y, 0);
		al_set_clipping_rectangle(pos_x[3], GAMEPAD_POS_Y, GAMEPAD_WIDTH, GAMEPAD_HEIGHT);
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_bitmap(_gamepad, pos_x[3], GAMEPAD_POS_Y, 0);
		al_set_clipping_rectangle(pos_x[0], GAMEPAD_POS_Y, GAMEPAD_WIDTH, GAMEPAD_HEIGHT);
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_set_clipping_rectangle(pos_x[1], GAMEPAD_POS_Y, GAMEPAD_WIDTH, GAMEPAD_HEIGHT);
		al_clear_to_color(al_map_rgb(0, 0, 0));
	} else {
		al_set_clipping_rectangle(pos_x[2], GAMEPAD_POS_Y, GAMEPAD_WIDTH, GAMEPAD_HEIGHT);
		al_clear_to_color(al_map_rgb(194, 67, 35));
		al_set_clipping_rectangle(pos_x[3], GAMEPAD_POS_Y, GAMEPAD_WIDTH, GAMEPAD_HEIGHT);
		al_clear_to_color(al_map_rgb(194, 67, 35));
		al_set_clipping_rectangle(pos_x[0], GAMEPAD_POS_Y, GAMEPAD_WIDTH, GAMEPAD_HEIGHT);
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_set_clipping_rectangle(pos_x[1], GAMEPAD_POS_Y, GAMEPAD_WIDTH, GAMEPAD_HEIGHT);
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}
	al_flip_display();
}

void AllegroLib::updateJoystickLeft(int pos_x[4])
{
	if (_gamepad != nullptr) {
		al_set_clipping_rectangle(pos_x[0], GAMEPAD_POS_Y, GAMEPAD_WIDTH, GAMEPAD_HEIGHT);
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_bitmap(_gamepad, pos_x[0], GAMEPAD_POS_Y, 0);
		al_set_clipping_rectangle(pos_x[1], GAMEPAD_POS_Y, GAMEPAD_WIDTH, GAMEPAD_HEIGHT);
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_bitmap(_gamepad, pos_x[1], GAMEPAD_POS_Y, 0);
		al_set_clipping_rectangle(pos_x[2], GAMEPAD_POS_Y, GAMEPAD_WIDTH, GAMEPAD_HEIGHT);
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_set_clipping_rectangle(pos_x[3], GAMEPAD_POS_Y, GAMEPAD_WIDTH, GAMEPAD_HEIGHT);
		al_clear_to_color(al_map_rgb(0, 0, 0));
	} else {
		al_set_clipping_rectangle(pos_x[0], GAMEPAD_POS_Y, GAMEPAD_WIDTH, GAMEPAD_HEIGHT);
		al_clear_to_color(al_map_rgb(194, 67, 35));
		al_set_clipping_rectangle(pos_x[1], GAMEPAD_POS_Y, GAMEPAD_WIDTH, GAMEPAD_HEIGHT);
		al_clear_to_color(al_map_rgb(194, 67, 35));
		al_set_clipping_rectangle(pos_x[2], GAMEPAD_POS_Y, GAMEPAD_WIDTH, GAMEPAD_HEIGHT);
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_set_clipping_rectangle(pos_x[3], GAMEPAD_POS_Y, GAMEPAD_WIDTH, GAMEPAD_HEIGHT);
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}
	al_flip_display();
}

void AllegroLib::printJoystick(bool cursor, dataMap<std::string, std::string> gfx,
			       dataMap<std::string, std::string> game)
{
	static bool tmp = true;
	int pos_x[4] = {
		170 - (GAMEPAD_WIDTH / 2),
		581 - (GAMEPAD_WIDTH / 2),
		1016 - (GAMEPAD_WIDTH / 2),
		1426 - (GAMEPAD_WIDTH / 2),
	};

	if (tmp != cursor || _iteGames != game.iterator->first || _iteLib != gfx.iterator->first) {
		if (cursor) {
			_joystick = al_load_bitmap(JOYSTICK_RIGHT);
			updateJoystickRight(pos_x);
			_iteLib = gfx.iterator->first;
		} else {
			_joystick = al_load_bitmap(JOYSTICK_LEFT);
			updateJoystickLeft(pos_x);
			_iteGames = game.iterator->first;
		}
		if (_joystick != nullptr) {
			al_set_clipping_rectangle(JOYSTICK_POS_X - JOYSTICK_WIDTH / 2,
						JOYSTICK_POS_Y - JOYSTICK_HEIGHT / 2,
						JOYSTICK_WIDTH, JOYSTICK_HEIGHT);
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_bitmap(_joystick, JOYSTICK_POS_X - JOYSTICK_WIDTH / 2,
					JOYSTICK_POS_Y - JOYSTICK_HEIGHT / 2, 0);
			al_flip_display();
		}
		tmp = cursor;
	}
}

void AllegroLib::printSelector(dataMap<std::string, std::string> ref,
				int pos_x)
{
	std::map<std::string, std::string>::iterator ite;

	for (ite = ref.map.begin(); ite != ref.map.end(); ite++) {
		if (ite->first == ref.iterator->first) {
			al_draw_text(_font, al_map_rgb(194, 67, 35),
				pos_x, MENU_FIRST_POS,
				ALLEGRO_ALIGN_CENTRE,
				ref.iterator->first.c_str());
			return;
		}
	}
}

void AllegroLib::printEnd(std::vector<std::string> const &ref,
				int pos_y, int pos_x)
{
	size_t inc = 0;

	for (inc = 0; inc < ref.size() &&
			pos_y + TTF_SIZE < MENU_LAST_POS; inc++) {
		al_draw_text(_font, al_map_rgb(255, 255, 255),
				pos_x, pos_y, ALLEGRO_ALIGN_CENTRE,
				ref[inc].c_str());
		pos_y += SPACE_POS + TTF_SIZE;
	}
}

void AllegroLib::printGames(dataMap<std::string, std::string> ref)
{
	std::vector<std::string> endList;
	std::size_t pos[2] = {posSelector(ref), 0};
	std::map<std::string, std::string>::iterator ite;
	int pos_y = MENU_FIRST_POS + SPACE_POS + TTF_SIZE;

	if (_iteGames != ref.iterator->first) {
		al_set_clipping_rectangle(106, 467, 539, 389);
		al_clear_to_color(al_map_rgb(0, 0, 0));
		printSelector(ref, MENU_GAME_POS);
		for (ite = ref.map.begin(); ite != ref.map.end() &&
				pos_y + TTF_SIZE < MENU_LAST_POS; ite++) {
			if (pos[1] < pos[0])
				endList.push_back(ite->first);
			else if (ite->first != ref.iterator->first) {
				al_draw_text(_font, al_map_rgb(255, 255, 255),
						MENU_GAME_POS,
						pos_y, ALLEGRO_ALIGN_CENTRE,
						ite->first.c_str());
				pos_y += SPACE_POS + TTF_SIZE;
			}
			pos[1] += 1;
		}
		printEnd(endList, pos_y, MENU_GAME_POS);
		al_flip_display();
	}
}

void AllegroLib::printLib(dataMap<std::string, std::string> ref)
{
	std::vector<std::string> endList;
	std::size_t pos[2] = {posSelector(ref), 0};
	std::map<std::string, std::string>::iterator ite;
	int pos_y = MENU_FIRST_POS + SPACE_POS + TTF_SIZE;

	if (_iteLib != ref.iterator->first) {
		al_set_clipping_rectangle(952, 467, 539, 389);
		al_clear_to_color(al_map_rgb(0, 0, 0));
		printSelector(ref, MENU_LIB_POS);
		for (ite = ref.map.begin(); ite != ref.map.end() &&
				pos_y + TTF_SIZE < MENU_LAST_POS; ite++) {
			if (pos[1] < pos[0])
				endList.push_back(ite->first);
			else if (ite->first != ref.iterator->first) {
				al_draw_text(_font, al_map_rgb(255, 255, 255),
						MENU_LIB_POS,
						pos_y, ALLEGRO_ALIGN_CENTRE,
						ite->first.c_str());
				pos_y += SPACE_POS + TTF_SIZE;
			}
			pos[1] += 1;
		}
		printEnd(endList, pos_y, MENU_LIB_POS);
		al_flip_display();
	}
}

extern "C" {
	IGfx *buildEngine() {
		return new AllegroLib("Allegro Window", WINDOW_WIDTH, WINDOW_HEIGHT);
	}
}
