/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** IGfx.hpp
*/

#ifndef IGFX_HPP_
#define IGFX_HPP_

#include <iostream>
#include <map>
#include <vector>
#include <list>

template<typename T, typename U>
class dataMap {
public:
	dataMap() = default;
	dataMap(const dataMap<T, U> &) = default;
	~dataMap() = default;
	typename std::map<T, U> map;
	typename std::map<T, U>::iterator iterator;
};

template<typename T>
class dataVector {
public:
	dataVector() = default;
	dataVector(const dataVector<T> &) = default;
	~dataVector() = default;
	typename std::vector<T> vector;
	typename std::vector<T>::iterator iterator;
};

struct Point {
	std::string name;
	std::size_t value;
};

enum Key {
	K_UP,
	K_DOWN,
	K_LEFT,
	K_RIGHT,
	K_ESCAPE,
	K_SPACE,
	K_A,
	K_Z,
	K_E,
	K_R,
	K_Q,
	K_S,
	K_UNDEFINED
};

struct Color {
	int r;
	int g;
	int b;
	int a;
	int pair;
};

struct Asset {
	std::string name;
	std::string path1D;
	std::string path2D;
	Color color;
	int width;
	int height;
};

class IGfx {
public:
	virtual ~IGfx(){};
	virtual void addAsset(std::string, Asset) = 0;
	virtual void clearAsset() = 0;
	virtual std::string getLibName() const = 0;
	virtual size_t getWidth() const = 0;
	virtual size_t getHeight() const = 0;
	virtual void printTitle(std::string) = 0;
	virtual void printScore(std::size_t) = 0;
	virtual void printHighScore(std::list<Point>) = 0;
	virtual void printGameMap(std::vector<std::vector<std::string>>) = 0;
	virtual void printGameOptionMenu() = 0;
	virtual void printGameMenu(std::string, dataVector<std::string>) = 0;
	virtual void printGameOver(std::size_t, std::list<Point>) = 0;
	virtual void printIntro(std::string) = 0;
	virtual void printLibSelection(dataMap<std::string, std::string>,
				dataMap<std::string, std::string>, bool) = 0;
	virtual void display() = 0;
	virtual void clear() = 0;
	virtual void clearGameMenu() = 0;
	virtual enum Key getEvent() = 0;
};

#endif //IGFX_HPP_
