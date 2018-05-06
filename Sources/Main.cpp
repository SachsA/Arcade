//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// Main.cpp
//

#include <unistd.h>
#include <time.h>
#include <string>
#include "Arcade.hpp"
#include "Errors.hpp"

int main(const int argc, char **argv)
{
	std::string path;
	Arcade *arcade;

	srand(time(NULL));
	try {
		if (argc != 2) {
			throw Errors(std::cerr, "Bad number of arguments.\n"
			"Usage: ./arcade [Graphic Library]");
		}
		path = argv[1];
		arcade = new Arcade(path);
		arcade->loadLibGfx(true, arcade->getPosGfx());
		if (arcade->run() != K_Q)
			delete(arcade);
	} catch (const Errors &e) {
		std::cerr << "Error(s): " << e.what() << std::endl;
		return 84;
	} catch (...) {
		std::cerr << "Unknown Error(s)." << std::endl;
		return 84;
	}
	return 0;
}
