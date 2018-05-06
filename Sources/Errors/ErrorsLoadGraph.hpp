//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// ErrorsLoadGraph.hpp
//

#ifndef ERRORS_LOADGRAPH_HPP_
	#define ERRORS_LOADGRAPH_HPP_

	#include "Errors.hpp"

	class ErrorsLoadGraph: public Errors {
	public:
		ErrorsLoadGraph(std::ostream &, const std::string &) throw();
		virtual ~ErrorsLoadGraph(void) throw();
	};

#endif /* !ERRORS_LOADGRAPH_HPP_ */
