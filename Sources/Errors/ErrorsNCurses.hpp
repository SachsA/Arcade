//
// EPITECH PROJECT, 2018
// ErrorsNCurses.hpp
// File description:
// Created by Thomas BLENEAU
//

#ifndef ERRORS_NCURSES_HPP_
	#define ERRORS_NCURSES_HPP_

	#include "Errors.hpp"

	class ErrorsNCurses: public Errors {
	public:
		ErrorsNCurses(std::ostream &, const std::string &) throw();
		virtual ~ErrorsNCurses(void) throw();
	};

#endif /* !ERRORS_NCURSES_HPP_ */
