//
// EPITECH PROJECT, 2018
// ErrorsNibbler.hpp
// File description:
// Created by Thomas BLENEAU
//

#ifndef ERRORS_NIBBLER_HPP_
	#define ERRORS_NIBBLER_HPP_

	#include "Errors.hpp"

	class ErrorsNibbler: public Errors {
	public:
		ErrorsNibbler(std::ostream &, const std::string &) throw();
		virtual ~ErrorsNibbler(void) throw();
	};

#endif /* !ERRORS_NIBBLER_HPP_ */
