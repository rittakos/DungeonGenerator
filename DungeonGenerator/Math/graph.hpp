#ifndef GRAPH_HPP
#define GRAPH_HPP

#pragma once

#include <memory>

#include "log.h"

#include "internalGraph.hpp"
#include "LEMONGraph.hpp"

namespace Math
{

	enum InternalGraphType {LEMON};



	template<class Type>
	class Graph
	{
	private:
		InternalGraph* internalGraph;
		const InternalGraphType type;

	public:
		Graph(InternalGraphType type = InternalGraphType::LEMON) : type{type}
		{
			switch (this->type)
			{
				case LEMON:
					internalGraph = new LEMONGraph<Type>();
					break;
				default:
					Log::error("Unhandled Internal Graph Type!!");
					throw std::exception();
					break;
			}
		}


	};

}

#endif