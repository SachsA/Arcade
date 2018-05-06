//
// EPITECH PROJECT, 2018
// ErrorsPacman.hpp
// File description:
// Created by Thomas BLENEAU
//

#ifndef ERRORS_PACMAN_HPP_
	#define ERRORS_PACMAN_HPP_

	#include "Errors.hpp"

	class ErrorsPacman: public Errors {
	public:
		ErrorsPacman(std::ostream &, const std::string &) throw();
		virtual ~ErrorsPacman(void) throw();
	};

#endif /* !ERRORS_PACMAN_HPP_ */
