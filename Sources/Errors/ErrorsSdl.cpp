//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// ErrorsSdl.cpp
//

#include "ErrorsSdl.hpp"

ErrorsSdl::ErrorsSdl(std::ostream &os, const std::string &message) throw()
	: Errors(os, message)
{}

ErrorsSdl::~ErrorsSdl(void) throw()
{}
