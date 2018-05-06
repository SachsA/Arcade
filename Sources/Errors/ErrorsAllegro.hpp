//
// EPITECH PROJECT, 2018
// ErrorsAllegro.hpp
// File description:
// Created by Thomas BLENEAU
//

#ifndef ERRORS_ALLEGRO_HPP_
	#define ERRORS_ALLEGRO_HPP_

	#include "Errors.hpp"

	class ErrorsAllegro: public Errors {
	public:
		ErrorsAllegro(std::ostream &, const std::string &) throw();
		virtual ~ErrorsAllegro(void) throw();
	};

#endif /* !ERRORS_ALLEGRO_HPP_ */
