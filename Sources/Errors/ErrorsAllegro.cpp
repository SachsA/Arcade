//
// EPITECH PROJECT, 2018
// ErrorsAllegro.cpp
// File description:
// Created by Thomas BLENEAU
//

#include "ErrorsAllegro.hpp"

ErrorsAllegro::ErrorsAllegro(std::ostream &os, const std::string &message) throw()
	: Errors(os, message)
{}

ErrorsAllegro::~ErrorsAllegro(void) throw()
{}
