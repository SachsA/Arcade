//
// EPITECH PROJECT, 2018
// ErrorsNibbler.cpp
// File description:
// Created by Thomas BLENEAU
//

#include "ErrorsNibbler.hpp"

ErrorsNibbler::ErrorsNibbler(std::ostream &os, const std::string &message) throw()
	: Errors(os, message)
{}

ErrorsNibbler::~ErrorsNibbler(void) throw()
{}
