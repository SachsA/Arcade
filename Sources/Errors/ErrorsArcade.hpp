//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// ErrorsArcade.hpp
//

#ifndef ERRORS_ARCADE_HPP_
#define ERRORS_ARCADE_HPP_

#include "Errors.hpp"

class ErrorsArcade: public Errors {
public:
	ErrorsArcade(std::ostream &, const std::string &) throw();
	virtual ~ErrorsArcade(void) throw();
};

#endif /* !ERRORS_ARCADE_HPP_ */
