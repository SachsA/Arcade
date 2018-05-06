//
// EPITECH PROJECT, 2018
// ErrorsPacman.cpp
// File description:
// Created by Thomas BLENEAU
//

#include "ErrorsPacman.hpp"

ErrorsPacman::ErrorsPacman(std::ostream &os, const std::string &message) throw()
	: Errors(os, message)
{}

ErrorsPacman::~ErrorsPacman(void) throw()
{}
