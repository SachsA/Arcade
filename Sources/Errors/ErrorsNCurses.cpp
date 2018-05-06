//
// EPITECH PROJECT, 2018
// ErrorsNCurses.cpp
// File description:
// Created by Thomas BLENEAU
//

#include "ErrorsNCurses.hpp"

ErrorsNCurses::ErrorsNCurses(std::ostream &os, const std::string &message) throw()
	: Errors(os, message)
{}

ErrorsNCurses::~ErrorsNCurses(void) throw()
{}
