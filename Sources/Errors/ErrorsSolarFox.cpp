//
// EPITECH PROJECT, 2018
// ErrorsSolarFox.cpp
// File description:
// Created by Thomas BLENEAU
//

#include "ErrorsSolarFox.hpp"

ErrorsSolarFox::ErrorsSolarFox(std::ostream &os, const std::string &message) throw()
	: Errors(os, message)
{}

ErrorsSolarFox::~ErrorsSolarFox(void) throw()
{}
