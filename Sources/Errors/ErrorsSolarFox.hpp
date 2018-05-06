//
// EPITECH PROJECT, 2018
// ErrorsSolarFox.hpp
// File description:
// Created by Thomas BLENEAU
//

#ifndef ERRORS_SOLARFOX_HPP_
	#define ERRORS_SOLARFOX_HPP_

	#include "Errors.hpp"

	class ErrorsSolarFox: public Errors {
	public:
		ErrorsSolarFox(std::ostream &, const std::string &) throw();
		virtual ~ErrorsSolarFox(void) throw();
	};

#endif /* !ERRORS_SOLARFOX_HPP_ */
