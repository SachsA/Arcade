//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// ErrosArcade.cpp
//

#include "ErrorsArcade.hpp"

ErrorsArcade::ErrorsArcade(std::ostream &os, const std::string &message) throw()
	: Errors(os, message)
{}

ErrorsArcade::~ErrorsArcade(void) throw()
{}
