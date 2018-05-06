/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** LibLoader.hpp
*/

#ifndef LIBLOADER_HH_
#define LIBLOADER_HH_

#include <iostream>
#include <string>
#include <dlfcn.h>
#include "ErrorsLoadGraph.hpp"

template<typename T>
class LibLoader
{
	public:
	LibLoader() = default;
	LibLoader(const LibLoader<T> &) = default;

	LibLoader(const char *libPath) :
		_libPath(libPath), _handle(nullptr), _sym(nullptr)
	{
	}
	LibLoader(std::string const &libPath) :
		_libPath(libPath), _handle(nullptr), _sym(nullptr)
	{
	}

	~LibLoader() noexcept(false)
	{
		if (this->_handle && dlclose(this->_handle))
			throw ErrorsLoadGraph(std::cerr, "Dlclose fail.");
	}

	T *load(const std::string &symbol, std::string str = "")
	{
		if (!str.empty()) {
			this->_libPath = str;
		}
		if (this->_handle && dlclose(this->_handle))
			throw ErrorsLoadGraph(std::cerr, "Dlclose fail.");
		this->_handle = dlopen(this->_libPath.c_str(), RTLD_LAZY);
		if (!this->_handle)
			throw ErrorsLoadGraph(std::cerr, "Dlopen fail.");
		void *ptr = dlsym(this->_handle, symbol.c_str());
		this->_sym = reinterpret_cast<T *(*)()>(ptr);
		if (!this->_sym)
			throw ErrorsLoadGraph(std::cerr, "Dlsym fail.");
		return this->_sym();
	}

	private:
		std::string _libPath;
		void *_handle;
		T *(*_sym)();
};

#endif //LIBLOADER_HPP_