/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** SdlLib.cpp
*/

#include <cstring>
#include <sstream>
#include <map>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_ttf.h>
#include "ErrorsSdl.hpp"
#include "SdlLib.hpp"

static SDL_Color white {
		.r = 255,
		.g = 255,
		.b = 255,
		.a = 1
};

static SDL_Color red {
		.r = 194,
		.g = 67,
		.b = 35,
		.a = 1
};

static SDL_Rect const joystick_pos {
		.x = JOYSTICK_POS_X - JOYSTICK_WIDTH / 2,
		.y = JOYSTICK_POS_Y - JOYSTICK_HEIGHT / 2,
		.w = JOYSTICK_WIDTH,
		.h = JOYSTICK_HEIGHT
};

static SDL_Rect gamepad_pos {
		.x = 0,
		.y = GAMEPAD_POS_Y,
		.w = GAMEPAD_WIDTH,
		.h = GAMEPAD_HEIGHT
};

static SDL_Rect score_pos {
		.x = 0,
		.y = 0,
		.w = 0,
		.h = 0
};

static SDL_Rect title_pos {
		.x = 0,
		.y = 0,
		.w = 0,
		.h = 0
};

static texture_s texture_pos {
		.x = 0,
		.y = 0
};

SdlLib::SdlLib(std::string name, size_t width, size_t height)
	: _width(width), _height(height)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw ErrorsSdl(std::cerr, "Cannot init SDL2.");
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		throw ErrorsSdl(std::cerr, "could not initialize sdl2_image");
	if (TTF_Init() == -1)
		throw ErrorsSdl(std::cerr, "Could not initialize sdl2_ttf");
	_font = TTF_OpenFont(TTF_FONT, TTF_SIZE);
	if (_font == nullptr)
		throw ErrorsSdl(std::cerr, "Could not open sdl2_font");
	_fontTitle = TTF_OpenFont(TTF_FONT, TTF_TITLE_SIZE);
	if (_fontTitle == nullptr)
		throw ErrorsSdl(std::cerr, "Could not open sdl2_font");
	_window = SDL_CreateWindow(
		name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		_width, _height, SDL_WINDOW_RESIZABLE);
	if (_window == NULL)
		throw ErrorsSdl(std::cerr, "Can't create the SLD Window.");
	SDL_SetWindowResizable(_window, SDL_FALSE);
	_renderer = SDL_CreateRenderer(_window, -1, 0);
}

SdlLib::~SdlLib()
{
	TTF_Quit();
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

void SdlLib::addAsset(std::string name, Asset assets)
{
	_assets.emplace(name, assets);
	createAsset(name);
}

SDL_Rect SdlLib::sizeAsset(std::string name, int x, int y)
{
	SDL_Rect pos = {
		.x = x,
		.y = y,
		.w = _assets[name].width,
		.h = _assets[name].height
	};

	return pos;
}

void SdlLib::createAsset(std::string name)
{
	SDL_Surface *tmp;

	if (_assets.find(name) != _assets.end()) {
		_mapGame.emplace(name, IMG_LoadTexture(_renderer,
						       _assets[name].path2D.c_str()));
		if (_mapGame[name] == nullptr) {
			if (_assets[name].name.size() > 1) {
				tmp = TTF_RenderText_Solid(_font,
							_assets[name].name.c_str(), white);
				_assets[name].width = tmp->w;
				_assets[name].height = tmp->h;
			} else {
				tmp = SDL_CreateRGBSurfaceWithFormat(0, _assets[name].width,
								_assets[name].height, 32,
								SDL_PIXELFORMAT_RGBA32);
				SDL_FillRect(tmp, NULL, SDL_MapRGB(tmp->format,
								_assets[name].color.r,
								_assets[name].color.g,
								_assets[name].color.b));
			}
			_mapGame[name] = SDL_CreateTextureFromSurface(_renderer, tmp);
			SDL_FreeSurface(tmp);
		}
	}
}

void SdlLib::printAsset(std::string name, int x, int y)
{
	SDL_Rect pos;

	if (_mapGame.find(name) != _mapGame.end()) {
		pos = sizeAsset(name, x, y);
		SDL_RenderCopy(_renderer, _mapGame[name], NULL, &pos);
	}
}

void SdlLib::clearAsset()
{
	std::unordered_map<std::string, SDL_Texture *>::iterator itt;

	_assets.clear();
	for (itt = _mapGame.begin(); itt != _mapGame.end(); itt++)
		SDL_DestroyTexture(itt->second);
	_mapGame.clear();
}

size_t SdlLib::getWidth() const
{
	return _width;
}

size_t SdlLib::getHeight() const
{
	return _height;
}

void SdlLib::printScoreWithoutAsset()
{
	SDL_Rect pos;
	SDL_Surface *tmp;
	SDL_Texture *texture;

	tmp = TTF_RenderText_Solid(_font, "Score", {8, 18, 212, 1});
	pos.x = 1250 - tmp->w / 2;
	pos.y = 730;
	pos.w = tmp->w;
	pos.h = tmp->h;
	texture = SDL_CreateTextureFromSurface(_renderer, tmp);
	SDL_RenderCopy(_renderer, texture, NULL, &pos);
	tmp = TTF_RenderText_Solid(_font, "HighScore", {8, 18, 212, 1});
	pos.x = 1250 - tmp->w / 2;
	pos.y = 186;
	pos.w = tmp->w;
	pos.h = tmp->h;
	texture = SDL_CreateTextureFromSurface(_renderer, tmp);
	SDL_RenderCopy(_renderer, texture, NULL, &pos);
	SDL_FreeSurface(tmp);
	SDL_DestroyTexture(texture);
}

void SdlLib::printTitle(std::string name)
{
	if (_mapGame.find(name) != _mapGame.end()) {
		if (_assets[name].width != WINDOW_WIDTH) {
			printAsset(name,
				WINDOW_WIDTH / 2 - _assets[name].width / 2,
				25);
			printScoreWithoutAsset();
		} else
			printAsset(name, 0, 0);
	}
}

void SdlLib::printScore(std::size_t number)
{
	std::stringstream ss;
	SDL_Surface *tmp;
	SDL_Texture *texture;

	ss << number;
	tmp = TTF_RenderText_Solid(_font, ss.str().c_str(), white);
	score_pos.x = SCORE_POS_X - tmp->w / 2;
	score_pos.y = SCORE_POS_Y - tmp->h / 2;
	score_pos.w = tmp->w;
	score_pos.h = tmp->h;
	texture = SDL_CreateTextureFromSurface(_renderer, tmp);
	SDL_RenderCopy(_renderer, texture, NULL, &score_pos);
	SDL_FreeSurface(tmp);
	SDL_DestroyTexture(texture);
}

void SdlLib::printHighScore(std::list<Point> highScore)
{
	SDL_Rect pos;
	SDL_Texture *texture;
	int pos_y = 254;
	SDL_Surface *tmp;
	std::string name;
	std::stringstream ss;
	std::list<Point>::iterator ite;

	for (ite = highScore.begin(); ite != highScore.end() &&
			pos_y + TTF_SIZE < 523; ite++) {
		ss << ite->value;
		name = (ite->name + "  " + ss.str());
		tmp = TTF_RenderText_Solid(_font, name.c_str(), white);
		if (tmp->w < 986) {
			pos.x = SCORE_POS_X - tmp->w / 2;
			pos.y = pos_y;
			pos.w = tmp->w;
			pos.h = tmp->h;
			texture = SDL_CreateTextureFromSurface(_renderer, tmp);
			SDL_RenderCopy(_renderer, texture, NULL, &pos);
			SDL_DestroyTexture(texture);
		}
		ss.str("");
		SDL_FreeSurface(tmp);
		pos_y += TTF_SIZE + 10;
	}
}

void SdlLib::printGameMap(std::vector<std::vector<std::string>> map)
{
	size_t coord[2] = {0, 0};
	size_t pos_x = MAP_INIT_X;
	size_t pos_y = MAP_INIT_Y;

	for (coord[0] = 0; coord[0] < map.size(); coord[0]++) {
		pos_x = MAP_INIT_X;
		for (coord[1] = 0; coord[1] < map[coord[0]].size(); coord[1]++) {
			printAsset(map[coord[0]][coord[1]], pos_x, pos_y);
			pos_x += MAP_PAS;
		}
		pos_y += MAP_PAS;
	}
}

void SdlLib::printGameOptionMenu()
{
	return;
}

void SdlLib::printGameMenu(std::string name, [[maybe_unused]]dataVector<std::string> vector_pause)
{
	std::string path;

	if (_pause == nullptr) {
		path = RESOURCES_PATH + name + "/2D/pause.png";
		_pause = IMG_LoadTexture(_renderer, path.c_str());
		if (_pause != nullptr)
			SDL_QueryTexture(_pause, NULL, NULL, &texture_pos.x, &texture_pos.y);
	} if (_itePause != *vector_pause.iterator) {
		clearMapTexture();
		pauseMenu(vector_pause);
		printPause();
		_itePause = *vector_pause.iterator;
	}
}

void SdlLib::printGameOver(std::size_t score, std::list<Point> highScore)
{
	std::string path;
	SDL_Surface *tmp;
	SDL_Texture *texture;
	SDL_Rect tmpPos;
	std::stringstream ss;
	std::string val;

	tmp = TTF_RenderText_Solid(_fontTitle, "GAME OVER", white);
	tmpPos.x = WINDOW_WIDTH / 2 - tmp->w / 2;
	tmpPos.y = 150;
	tmpPos.w = tmp->w;
	tmpPos.h = tmp->h;
	texture = SDL_CreateTextureFromSurface(_renderer, tmp);
	SDL_RenderCopy(_renderer, texture, NULL, &tmpPos);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(tmp);
	tmp = TTF_RenderText_Solid(_font, "SCORE", {8, 18, 212, 1});
	tmpPos.x = WINDOW_WIDTH / 4;
	tmpPos.y = 150 + TTF_TITLE_SIZE + 60;
	tmpPos.w = tmp->w;
	tmpPos.h = tmp->h;
	texture = SDL_CreateTextureFromSurface(_renderer, tmp);
	SDL_RenderCopy(_renderer, texture, NULL, &tmpPos);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(tmp);
	ss << score;
	tmp = TTF_RenderText_Solid(_font, ss.str().c_str(), white);
	tmpPos.x = WINDOW_WIDTH / 4 + 70;
	tmpPos.y = 150 + TTF_TITLE_SIZE + 60 + TTF_SIZE + 20;
	tmpPos.w = tmp->w;
	tmpPos.h = tmp->h;
	texture = SDL_CreateTextureFromSurface(_renderer, tmp);
	SDL_RenderCopy(_renderer, texture, NULL, &tmpPos);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(tmp);
	tmp = TTF_RenderText_Solid(_font, "HIGHSCORE", {8, 18, 212, 1});
	tmpPos.x = (WINDOW_WIDTH / 2) + (WINDOW_WIDTH / 4) - tmp->w;
	tmpPos.y = 150 + TTF_TITLE_SIZE + 60;
	tmpPos.w = tmp->w;
	tmpPos.h = tmp->h;
	texture = SDL_CreateTextureFromSurface(_renderer, tmp);
	SDL_RenderCopy(_renderer, texture, NULL, &tmpPos);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(tmp);
	ss.str("");
	ss << highScore.front().value;
	val = ss.str() + "  " + highScore.front().name;
	tmp = TTF_RenderText_Solid(_font, val.c_str(), white);
	tmpPos.x = (WINDOW_WIDTH / 2) + (WINDOW_WIDTH / 4) - tmp->w / 2;
	tmpPos.y = 150 + TTF_TITLE_SIZE + 60 + TTF_SIZE + 20;
	tmpPos.w = tmp->w;
	tmpPos.h = tmp->h;
	texture = SDL_CreateTextureFromSurface(_renderer, tmp);
	SDL_RenderCopy(_renderer, texture, NULL, &tmpPos);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(tmp);
	tmp = TTF_RenderText_Solid(_font, "!! Press SPACE or S to restart the GAME !!", white);
	tmpPos.x = INTRO_POS_X - tmp->w / 2;
	tmpPos.y = OVER_POS_Y;
	tmpPos.w = tmp->w;
	tmpPos.h = tmp->h;
	texture = SDL_CreateTextureFromSurface(_renderer, tmp);
	SDL_RenderCopy(_renderer, texture, NULL, &tmpPos);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(tmp);
	tmp = TTF_RenderText_Solid(_font, "or Press ESCAPE to quit the GAME", white);
	tmpPos.x = INTRO_POS_X - tmp->w / 2;
	tmpPos.y = OVER_POS_Y + TTF_SIZE + 15;
	tmpPos.w = tmp->w;
	tmpPos.h = tmp->h;
	texture = SDL_CreateTextureFromSurface(_renderer, tmp);
	SDL_RenderCopy(_renderer, texture, NULL, &tmpPos);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(tmp);
}

void SdlLib::printIntro(std::string name)
{
	std::string path;
	SDL_Surface *tmp;

	if (_intro == nullptr) {
		path = RESOURCES_PATH + name + "/2D/intro.png";
		_intro = IMG_LoadTexture(_renderer, path.c_str());
		if (_intro == nullptr) {
			tmp = TTF_RenderText_Solid(_fontTitle, name.c_str(), white);
			title_pos.x = WINDOW_WIDTH / 2 - tmp->w / 2;
			title_pos.y = 150;
			title_pos.w = tmp->w;
			title_pos.h = tmp->h;
			_intro = SDL_CreateTextureFromSurface(_renderer, tmp);
			SDL_FreeSurface(tmp);
		} else {
			title_pos.x = 0;
			title_pos.y = 0;
			title_pos.w = WINDOW_WIDTH;
			title_pos.h = WINDOW_HEIGHT;
		}
		SDL_QueryTexture(_intro, NULL, NULL, &texture_pos.x, &texture_pos.y);
		SDL_RenderCopy(_renderer, _intro, NULL, &title_pos);
		SDL_RenderPresent(_renderer);
	}
	updateIntro();
}

void SdlLib::printLibSelection(dataMap<std::string, std::string> game,
				dataMap<std::string, std::string> gfx,
				bool cursor)
{
	SDL_Surface *tmp;

	if (_imageMenu == nullptr) {
		_imageMenu = IMG_LoadTexture(_renderer, MENU_BACKGROUND);
		if (_imageMenu == nullptr) {
			tmp = TTF_RenderText_Solid(_fontTitle, "ARCADE  MENU",
							{255, 56, 0, 1});
			_imageMenu = SDL_CreateTextureFromSurface(_renderer, tmp);
			title_pos.x = WINDOW_WIDTH / 2 - tmp->w / 2;
			title_pos.y = 50;
			title_pos.w = tmp->w;
			title_pos.h = tmp->h;
			SDL_FreeSurface(tmp);
		} else {
			title_pos.x = 0;
			title_pos.y = 0;
			title_pos.w = WINDOW_WIDTH;
			title_pos.h = WINDOW_HEIGHT;
		}
		_gamepad = IMG_LoadTexture(_renderer, GAMEPAD);
		if (_gamepad == nullptr) {
			tmp = SDL_CreateRGBSurfaceWithFormat(0, GAMEPAD_WIDTH, GAMEPAD_HEIGHT,
							     32, SDL_PIXELFORMAT_RGBA32);
			SDL_FillRect(tmp, NULL, SDL_MapRGB(tmp->format, 194, 67, 35));
			_gamepad = SDL_CreateTextureFromSurface(_renderer, tmp);
			SDL_FreeSurface(tmp);
		}
		SDL_QueryTexture(_imageMenu, NULL, NULL, &texture_pos.x, &texture_pos.y);
		SDL_QueryTexture(_gamepad, NULL, NULL, &texture_pos.x, &texture_pos.y);
		SDL_RenderCopy(_renderer, _imageMenu, NULL, &title_pos);
		SDL_RenderPresent(_renderer);
	}
	printJoystick(cursor, game, gfx);
}

std::string SdlLib::getLibName() const
{
	return _libName;
}

void SdlLib::display()
{
	SDL_RenderPresent(_renderer);
	SDL_RenderClear(_renderer);
}

void SdlLib::clear()
{
	clearAsset();
	SDL_DestroyTexture(_intro);
	_intro = nullptr;
	SDL_DestroyTexture(_background);
	_background = nullptr;
	SDL_DestroyTexture(_imageMenu);
	_imageMenu = nullptr;
	SDL_DestroyTexture(_joystick);
	_joystick = nullptr;
	SDL_DestroyTexture(_gamepad);
	_gamepad = nullptr;
	SDL_DestroyTexture(_score);
	_score = nullptr;
	clearMapTexture();
	clearMapTexture(0);
	clearMapTexture(1);
	SDL_DestroyTexture(_pause);
	_pause = nullptr;
	_itePause.erase();
	_iteGames.erase();
	_iteLib.erase();
	_iteScore = 0;
	_iteHighScore = 1;
	_iteCursor = !_iteCursor;
	_over = 1;
	SDL_RenderClear(_renderer);
	SDL_RenderPresent(_renderer);
}

void SdlLib::clearGameMenu()
{
	clearMapTexture();
	SDL_DestroyTexture(_pause);
	_pause = nullptr;
	_itePause.erase();
	_iteScore = 0;
	_iteHighScore = 1;
	SDL_RenderClear(_renderer);
	SDL_RenderPresent(_renderer);
}

enum Key SdlLib::getEvent()
{
	while (SDL_PollEvent(&_event)) {
		switch (_event.type) {
		case SDL_KEYDOWN:
			switch (_event.key.keysym.sym) {
			case SDLK_ESCAPE:
				return K_ESCAPE;
			case SDLK_SPACE:
				return K_SPACE;
			case SDLK_RIGHT:
				return K_RIGHT;
			case SDLK_LEFT:
				return K_LEFT;
			case SDLK_UP:
				return K_UP;
			case SDLK_DOWN:
				return K_DOWN;
			case SDLK_a:
				return K_A;
			case SDLK_z:
				return K_Z;
			case SDLK_r:
				return K_R;
			case SDLK_e:
				return K_E;
			case SDLK_q:
				return K_Q;
			case SDLK_s:
				return K_S;
			}
		}
	}
	return _event.type == SDL_QUIT ? K_ESCAPE : K_UNDEFINED;
}

void SdlLib::updateIntro()
{
	SDL_Rect tmpPos;
	SDL_Texture *tmpIntro;
	std::string start = "!! Press SPACE to continue !!";
	SDL_Surface *tmp = TTF_RenderText_Solid(_font, start.c_str(), white);
	static int temps = 0;

	SDL_RenderClear(_renderer);
	tmpPos.x = INTRO_POS_X - tmp->w / 2;
	tmpPos.y = INTRO_POS_Y - tmp->h / 2;
	tmpPos.w = tmp->w;
	tmpPos.h = tmp->h;
	if (temps < 280) {
		tmpIntro = SDL_CreateTextureFromSurface(_renderer, tmp);
		SDL_RenderCopy(_renderer, _intro, NULL, &title_pos);
		SDL_RenderCopy(_renderer, tmpIntro, NULL, &tmpPos);
		SDL_RenderPresent(_renderer);
		SDL_FreeSurface(tmp);
		SDL_DestroyTexture(tmpIntro);
		temps += 1;
	} else if (temps >= 280 && temps < 560)  {
		SDL_RenderCopy(_renderer, _intro, NULL, &title_pos);
		SDL_RenderPresent(_renderer);
		temps += 1;
	} else
		temps = 0;
}

void SdlLib::updateJoystick(bool cursor)
{
	if (cursor) {
		gamepad_pos.x = 1016 - (GAMEPAD_WIDTH / 2);
		SDL_RenderCopy(_renderer, _gamepad, NULL, &gamepad_pos);
		gamepad_pos.x = 1426 - (GAMEPAD_WIDTH / 2);
		SDL_RenderCopy(_renderer, _gamepad, NULL, &gamepad_pos);
	} else {
		gamepad_pos.x = 170 - (GAMEPAD_WIDTH / 2);
		SDL_RenderCopy(_renderer, _gamepad, NULL, &gamepad_pos);
		gamepad_pos.x = 581 - (GAMEPAD_WIDTH / 2);
		SDL_RenderCopy(_renderer, _gamepad, NULL, &gamepad_pos);
	}
}

void SdlLib::printJoystick(bool cursor, dataMap<std::string, std::string> game,
			   dataMap<std::string, std::string> gfx)
{
	SDL_Rect tmpPos;
	SDL_Surface *tmp;

	SDL_RenderClear(_renderer);
	if (_iteCursor != cursor) {
		SDL_DestroyTexture(_joystick);
		if (cursor)
			_joystick = IMG_LoadTexture(_renderer, JOYSTICK_RIGHT);
		else
			_joystick = IMG_LoadTexture(_renderer, JOYSTICK_LEFT);
		SDL_QueryTexture(_joystick, NULL, NULL, &texture_pos.x, &texture_pos.y);
		SDL_RenderCopy(_renderer, _imageMenu, NULL, &title_pos);
		if (title_pos.y == 50) {
			tmp = TTF_RenderText_Solid(_font, "GAMES LIBRARIES",
							{20, 18, 220, 1});
			tmpPos.x = MENU_GAME_POS - tmp->w / 2;
			tmpPos.y = 370;
			tmpPos.w = tmp->w;
			tmpPos.h = tmp->h;
			SDL_RenderCopy(_renderer,
					SDL_CreateTextureFromSurface(_renderer, tmp),
					NULL, &tmpPos);
			tmp = TTF_RenderText_Solid(_font, "GRAPHICS LIBRARIES",
						   {15, 183, 21, 1});
			tmpPos.x = MENU_LIB_POS - tmp->w / 2;
			tmpPos.y = 370;
			tmpPos.w = tmp->w;
			tmpPos.h = tmp->h;
			SDL_RenderCopy(_renderer,
					SDL_CreateTextureFromSurface(_renderer, tmp),
					NULL, &tmpPos);
		}
		updateJoystick(cursor);
		printGames(game);
		printLib(gfx);
		SDL_RenderCopy(_renderer, _joystick, NULL, &joystick_pos);
		SDL_RenderPresent(_renderer);
		_iteCursor = cursor;
	} else {
		if (_joystick == nullptr) {
			_joystick = (_iteCursor) ?
				IMG_LoadTexture(_renderer, JOYSTICK_RIGHT) :
				IMG_LoadTexture(_renderer, JOYSTICK_LEFT);
		}
		SDL_RenderCopy(_renderer, _imageMenu, NULL, &title_pos);
		if (title_pos.y == 50) {
			tmp = TTF_RenderText_Solid(_font, "GAMES LIBRARIES",
							{20, 18, 220, 1});
			tmpPos.x = MENU_GAME_POS - tmp->w / 2;
			tmpPos.y = 370;
			tmpPos.w = tmp->w;
			tmpPos.h = tmp->h;
			SDL_RenderCopy(_renderer,
					SDL_CreateTextureFromSurface(_renderer, tmp),
					NULL, &tmpPos);
			tmp = TTF_RenderText_Solid(_font, "GRAPHICS LIBRARIES",
							{15, 183, 21, 1});
			tmpPos.x = MENU_LIB_POS - tmp->w / 2;
			tmpPos.y = 370;
			tmpPos.w = tmp->w;
			tmpPos.h = tmp->h;
			SDL_RenderCopy(_renderer,
					SDL_CreateTextureFromSurface(_renderer, tmp),
					NULL, &tmpPos);
		}
		updateJoystick(cursor);
		printGames(game);
		printLib(gfx);
		SDL_RenderCopy(_renderer, _joystick, NULL, &joystick_pos);
		SDL_RenderPresent(_renderer);
	}
}

std::size_t SdlLib::posSelector(dataMap<std::string, std::string> ref)
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

void SdlLib::clearMapTexture()
{
	std::unordered_map<SDL_Texture *, SDL_Rect>::iterator ite;

	for (ite = _pauseMenu.begin(); ite != _pauseMenu.end(); ite++)
		SDL_DestroyTexture(ite->first);
	_pauseMenu.clear();
}

void SdlLib::clearMapTexture(std::size_t lib)
{
	std::unordered_map<SDL_Texture *, SDL_Rect>::iterator ite;

	if (lib) {
		for (ite = _textLMenu.begin(); ite != _textLMenu.end(); ite++)
			SDL_DestroyTexture(ite->first);
		_textLMenu.clear();
	} else {
		for (ite = _textGMenu.begin(); ite != _textGMenu.end(); ite++)
			SDL_DestroyTexture(ite->first);
		_textGMenu.clear();
	}
}

void SdlLib::getSelector(dataMap<std::string, std::string> ref, int pos_x)
{
	SDL_Rect tmpPos;
	SDL_Surface *tmp;

	tmp = TTF_RenderText_Solid(_font, ref.iterator->first.c_str(),
					red);
	tmpPos.x = pos_x - tmp->w / 2;
	tmpPos.y = MENU_FIRST_POS;
	tmpPos.w = tmp->w;
	tmpPos.h = tmp->h;
	(pos_x == MENU_GAME_POS) ?
		_textGMenu[SDL_CreateTextureFromSurface(_renderer, tmp)] = tmpPos :
		_textLMenu[SDL_CreateTextureFromSurface(_renderer, tmp)] = tmpPos;
	SDL_FreeSurface(tmp);
}

void SdlLib::updateSelector(dataMap<std::string, std::string> ref, int pos_x)
{
	SDL_Rect tmpPos;
	SDL_Surface *tmp;
	std::map<std::string, std::string>::iterator ite;
	int pos_y = MENU_FIRST_POS + SPACE_POS + TTF_SIZE;

	getSelector(ref, pos_x);
	for (ite = ref.map.begin(); ite != ref.map.end() &&
			pos_y + TTF_SIZE < MENU_LAST_POS; ite++) {
		if (ite->first != ref.iterator->first) {
			tmp = TTF_RenderText_Solid(_font, ite->first.c_str(), white);
			tmpPos.x = pos_x - tmp->w / 2;
			tmpPos.y = pos_y;
			tmpPos.w = tmp->w;
			tmpPos.h = tmp->h;
			(pos_x == MENU_GAME_POS) ?
				_textGMenu[SDL_CreateTextureFromSurface(_renderer, tmp)] = tmpPos :
				_textLMenu[SDL_CreateTextureFromSurface(_renderer, tmp)] = tmpPos;
			SDL_FreeSurface(tmp);
			pos_y += SPACE_POS + TTF_SIZE;
		}
	}
}

void SdlLib::pauseMenu(dataVector<std::string> ref)
{
	std::size_t ite = 0;
	SDL_Rect tmpPos;
	SDL_Surface *tmp;
	int pos_y = PAUSE_FIRST_POS;

	if (_pause == nullptr) {
		tmp = TTF_RenderText_Solid(_fontTitle, "PAUSE", {255, 255, 255, 1});
		tmpPos.x = PAUSE_POS_X - tmp->w / 2;
		tmpPos.y = 150;
		tmpPos.w = tmp->w;
		tmpPos.h = tmp->h;
		_pauseMenu[SDL_CreateTextureFromSurface(_renderer, tmp)] = tmpPos;
		SDL_FreeSurface(tmp);
	}
	for (ite = 0; ite < ref.vector.size() &&
			pos_y + TTF_SIZE < PAUSE_LAST_POS; ite++) {
		if (ref.vector[ite] == *ref.iterator)
			tmp = TTF_RenderText_Solid(_font, ref.vector[ite].c_str(), red);
		else
			tmp = TTF_RenderText_Solid(_font, ref.vector[ite].c_str(), {91, 91, 93, 1});
		tmpPos.x = PAUSE_POS_X - tmp->w / 2;
		tmpPos.y = pos_y;
		tmpPos.w = tmp->w;
		tmpPos.h = tmp->h;
		_pauseMenu[SDL_CreateTextureFromSurface(_renderer, tmp)] = tmpPos;
		SDL_FreeSurface(tmp);
		if (ref.vector[ite] == *ref.iterator)
			gamepadPause(tmpPos, pos_y);
		pos_y += SPACE_POS + TTF_SIZE;
	}
}

void SdlLib::gamepadPause(SDL_Rect tmpPos, int pos_y)
{
	int elemW = tmpPos.w;
	SDL_Surface *tmp;

	tmpPos.x += tmpPos.w + GAMEPAD_WIDTH / 2;
	tmpPos.y = pos_y + (TTF_SIZE / 2) - (GAMEPAD_HEIGHT / 2);
	tmpPos.w = GAMEPAD_WIDTH;
	tmpPos.h = GAMEPAD_HEIGHT;
	if (IMG_LoadTexture(_renderer, GAMEPAD_RED) == nullptr) {
		tmp = SDL_CreateRGBSurfaceWithFormat(0, GAMEPAD_WIDTH, GAMEPAD_HEIGHT,
							32, SDL_PIXELFORMAT_RGBA32);
		SDL_FillRect(tmp, NULL, SDL_MapRGB(tmp->format, 194, 67, 35));
		_pauseMenu[SDL_CreateTextureFromSurface(_renderer, tmp)] = tmpPos;
		tmpPos.x = PAUSE_POS_X - (elemW / 2) - GAMEPAD_WIDTH - GAMEPAD_WIDTH / 2;
		tmpPos.y = pos_y + (TTF_SIZE / 2) - (GAMEPAD_HEIGHT / 2);
		_pauseMenu[SDL_CreateTextureFromSurface(_renderer, tmp)] = tmpPos;
		SDL_FreeSurface(tmp);
	} else {
		_pauseMenu[IMG_LoadTexture(_renderer, GAMEPAD_RED)] = tmpPos;
		tmpPos.x = PAUSE_POS_X - (elemW / 2) - GAMEPAD_WIDTH - GAMEPAD_WIDTH / 2;
		tmpPos.y = pos_y + (TTF_SIZE / 2) - (GAMEPAD_HEIGHT / 2);
		_pauseMenu[IMG_LoadTexture(_renderer, GAMEPAD_RED)] = tmpPos;
	}
}

void SdlLib::printPause()
{
	std::unordered_map<SDL_Texture *, SDL_Rect>::iterator ite;

	SDL_RenderClear(_renderer);
	SDL_RenderCopy(_renderer, _pause, NULL, NULL);
	for (ite = _pauseMenu.begin(); ite != _pauseMenu.end(); ite++)
		SDL_RenderCopy(_renderer, ite->first, NULL, &ite->second);
	SDL_RenderPresent(_renderer);
}

void SdlLib::printGames(dataMap<std::string, std::string> ref)
{
	std::unordered_map<SDL_Texture *, SDL_Rect>::iterator ite;

	if (_iteGames != ref.iterator->first) {
		clearMapTexture(0);
		updateSelector(ref, MENU_GAME_POS);
		_iteGames = ref.iterator->first;
	} for (ite = _textGMenu.begin(); ite != _textGMenu.end(); ite++)
		SDL_RenderCopy(_renderer, ite->first, NULL, &ite->second);
}

void SdlLib::printLib(dataMap<std::string, std::string> ref)
{
	std::unordered_map<SDL_Texture *, SDL_Rect>::iterator ite;

	if (_iteLib != ref.iterator->first) {
		clearMapTexture(1);
		updateSelector(ref, MENU_LIB_POS);
		_iteLib = ref.iterator->first;
	} for (ite = _textLMenu.begin(); ite != _textLMenu.end(); ite++)
		SDL_RenderCopy(_renderer, ite->first, NULL, &ite->second);
}

extern "C" {
	IGfx *buildEngine() {
		return new SdlLib("SDL Window", WINDOW_WIDTH, WINDOW_HEIGHT);
	}
}
