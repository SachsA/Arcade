//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// ErrorsSdl.hpp
//

#ifndef ERRORS_SDL_HPP_
	#define ERRORS_SDL_HPP_

	#include "Errors.hpp"

	class ErrorsSdl: public Errors {
	public:
		ErrorsSdl(std::ostream &, const std::string &) throw();
		virtual ~ErrorsSdl(void) throw();
	};

#endif /* !ERRORS_SDL_HPP_ */
