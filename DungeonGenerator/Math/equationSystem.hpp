#pragma once

#include <array>
#include <vector>
#include <assert.h>

#include"matrix.hpp"
#include <optional>

namespace Math
{

	template<int VariableCount>
	class LinearEquation
	{
	private:
		std::array<float, VariableCount> values;
		float rightValue;

	public:
		LinearEquation() = default;

		LinearEquation(float rightValue, std::array<float, VariableCount> variableValues) 
			: rightValue{rightValue}, values{variableValues} {}

		float getRightValue() const { return rightValue; }
		float getVariable(int idx) const { return values[idx]; }

		bool isSolution(std::initializer_list<float> solution) const
		{
			assert(solution.size() == values.size());
			if (solution.size() != values.size())
				return false;
			
			float leftValue = 0.0f;
			int idx = 0;
			for (float s : solution)
				leftValue += s * values[idx++];

			return fabs(leftValue - rightValue) < Math::Constant::epsilon; // 0.01 epsilon
		}
	};

	template<int VariableCount, int EquationCount = VariableCount>
	class LinearEquationSystem
	{
	private:
		std::array<float, VariableCount> solution;
		std::vector<LinearEquation<VariableCount>> equations;
		bool solved = false;
		
		Math::Mat<EquationCount, VariableCount + 1> createMatrix();

	public:

		void addLinearEquation(LinearEquation<VariableCount> newEquation);

		bool solve();

		std::optional<std::vector<float>> getSolution();

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
			matrix(line, VariableCount) = le.getRightValue();
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

		int signal;
		Math::Mat<EquationCount, VariableCount + 1> matrix = createMatrix().gaussianEliminate(signal);

		
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
	inline std::optional<std::vector<float>> LinearEquationSystem<VariableCount, EquationCount>::getSolution()
	{
		std::vector<float> solutionVector(solution.begin(), solution.end());
		if (solutionVector.size() == 0)
			return {};
		return solutionVector;
	}

}