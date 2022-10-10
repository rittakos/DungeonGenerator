#pragma once

#include <array>
#include <vector>

#include"matrix.hpp"

namespace Math
{

	template<int VariableCount>
	class LinearEquation
	{
	private:
		std::array<float, VariableCount> values;
		float solution;

	public:
		LinearEquation() = default;

		LinearEquation(float solution, std::array<float, VariableCount> variableValues) 
			: solution{solution}, values{variableValues} {}

		float getSolutionValue() const { return solution; }
		float getVariable(int idx) const { return values[idx]; }
	};

	template<int VariableCount, int EquationCount = VariableCount>
	class LinearEquationSystem
	{
	private:
		std::array<float, VariableCount> solution;
		std::vector<LinearEquation<VariableCount>> equations;
		bool solved;
		
		Math::Mat<EquationCount, VariableCount + 1> createMatrix();

	public:

		void addLinearEquation(LinearEquation<VariableCount> newEquation);

		bool solve();

		std::vector<float> getSolution();

	};

	template<int VariableCount, int EquationCount>
	inline Math::Mat<EquationCount, VariableCount + 1> LinearEquationSystem<VariableCount, EquationCount>::createMatrix()
	{
		Math::Mat<EquationCount, VariableCount + 1> matrix;

		int line = 0;
		for (LinearEquation le : equations)
		{
			for (int idx = 0; idx < VariableCount; ++idx)
				matrix(line, idx) = le.getVariable(idx);
			matrix(line, VariableCount) = le.getSolutionValue();
			++line;
		}
		return matrix;
	}

	template<int VariableCount, int EquationCount>
	inline void LinearEquationSystem<VariableCount, EquationCount>::addLinearEquation(LinearEquation<VariableCount> newEquation)
	{
		equations.push_back(newEquation);
	}

	template<int VariableCount, int EquationCount>
	inline bool LinearEquationSystem<VariableCount, EquationCount>::solve()
	{
		if (VariableCount > EquationCount)
			return false;

		Math::Mat<EquationCount, VariableCount + 1> matrix = createMatrix().gaussianEliminate();

		
		for (int idx = VariableCount - 1; idx >= 0; --idx)
		{
			float x = matrix(idx, VariableCount);
			for (int col = idx + 1; col < VariableCount; ++col)
				x -= (matrix(idx, col) * solution[col]);
			solution[idx] = (x) / (matrix(idx, idx));
		}

		return true;
	}

	template<int VariableCount, int EquationCount>
	inline std::vector<float> LinearEquationSystem<VariableCount, EquationCount>::getSolution()
	{
		std::vector<float> solutionVector(solution.begin(), solution.end());
		return solutionVector;
	}

}