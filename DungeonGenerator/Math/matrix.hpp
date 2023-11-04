#pragma once

#include <vector>

#include "math.hpp"
#include "isAllSame.hpp"
#include "vector.hpp"

namespace Math
{
	template<int X, int Y, VecNumber Type = float>
	class Mat;

	using Mat3x3f = Mat<3, 3, float>;

	template<int H, int W, VecNumber Type>
	class Mat final
	{
		Type coords[W * H];

		int length;
		int width = W;
		int height = H;

	public:

		//Constructors
		Mat()
		{
			length = W * H;

			for (int idx = 0; idx < length; ++idx)
				coords[idx] = 0;
		}

		template<typename ...T>
		explicit Mat(T... args) : Mat()
		{
			static_assert(is_all_same<Type, T...>::value, "Type mismatch!");

			std::vector<Type> vec = { args... };

			if (length != vec.size())
				throw new TooMuchParametersException(/*length, vec.size()*/);

			for (unsigned i = 0; i < vec.size(); ++i) {
				coords[i] = vec[i];
			}
		}

		//explicit Mat(std::initializer_list<Vec<X, Type>> vecs) : Mat()
		//{
		//	//std::vector<Type> vec = { args... };
		//	if (length != vecs.size())
		//		throw new TooMuchParametersException(/*length, vec.size()*/);
		//	for (unsigned i = 0; i < vecs.size(); ++i) {
		//		coords[i] = vecs[i];
		//	}
		//}


		//logical operators
		bool	operator==(const Mat& other) const
		{
			for (int idx = 0; idx < length; ++idx)
				if (!isEqual(this->coords[idx], other.coords[idx]))
					return false;
			return true;
		}
		bool	operator<(const Mat& other) = delete;
		bool	operator>(const Mat& other) = delete;

		//arithmetic operator
		Mat		operator+(const Mat& other) const
		{
			Mat<H, W, Type> result;
			for (int idx = 0; idx < length; ++idx)
				result.coords[idx] = coords[idx] + other.coords[idx];

			return result;
		}
		Mat		operator-(const Mat& other) const
		{
			return *this + (-1.0 * other);
		}
		Mat		operator-() const
		{
			return *this * -1.0;
		}

		//index operator
		Type&	operator()(int row, int col)
		{
			return coords[row * width + col];
		}
		Type	operator()(int row, int col) const
		{
			return coords[row * width + col];
		}

		//inverse operator
		
		Mat		operator~() const
		{
			Mat result;

			// TODO inverz implemetalasa
			return result;
		}

		//other functions

		bool hasInverse() { return width == height && !isEqual(Det(*this), 0.0f); }


		void swapRows(int row1, int row2)
		{
			std::vector<Type> tempRow1;
			for (int idx = 0; idx < width; ++idx)
			{
				tempRow1.push_back((*this)(row1, idx));
				(*this)(row1, idx) = (*this)(row2, idx);
			}

			for (int idx = 0; idx < width; ++idx)
			{
				(*this)(row2, idx) = tempRow1[idx];
			}
		}


		Mat gaussianEliminate(int& sign)
		{
			sign = 1;

			Mat result(*this);

			int rows = height;
			int cols = width;
			int Acols = cols - 1;
			float eps = Math::Constant::epsilon;

			int row = 0; // row tracker
			int col = 0; // column tracker

			// iterate through the rows
			while (row < rows)
			{
				// find a pivot for the row
				bool pivot_found = false;
				while (col < Acols && !pivot_found)
				{
					if (result(row, col) != 0) { // pivot not equal to 0
						pivot_found = true;
					}
					else { // check for a possible swap
						int max_row = row;
						double max_val = 0;
						for (int k = row + 1; k < rows; ++k)
						{
							double cur_abs = result(k, col) >= 0 ? result(k, col) : -1 * result(k, col);
							if (cur_abs > max_val)
							{
								max_row = k;
								max_val = cur_abs;
							}
						}
						if (max_row != row) {
							result.swapRows(max_row, row);
							pivot_found = true;
							sign *= -1;
						}
						else {
							col++;
						}
					}
				}

				// perform elimination as normal if pivot was found
				if (pivot_found)
				{
					for (int t = row + 1; t < rows; ++t) {
						for (int s = col + 1; s < cols; ++s) {
							result(t, s) = result(t, s) - result(row, s) * (result(t, col) / result(row, col));
							if (result(t, s) < eps && result(t, s) > -1 * eps)
								result(t, s) = 0;
						}
						result(t, col) = 0;
					}
				}

				row++;
				col++;
			}

			return result;
		}


		Vec<W, Type> getVectorFromRow(int row = 0) const
		{
			Vec<W, Type> result;

			for (int idx = 0; idx < width; ++idx)
				result[idx] = (*this)(row, idx);

			return result;
		}


		Vec<H, Type> getVectorFromCol(int col = 0) const
		{
			Vec<H, Type> result;

			for (int idx = 0; idx < height; ++idx)
				result[idx] = (*this)(idx, col);

			return result;
		}

		//external functions

		template<int W1, int H1, class Type1 >	friend Mat<W1, H1, Type1>	T(const Mat<H1, W1, Type1>& m);
		template<int W1, int H1, class Type1 >	friend float	det(Mat<H1, W1, Type1> m);


		//external operators
		template<int H1, int W1, class Type1 >	friend std::ostream& operator<<(std::ostream& os, const Mat<H1, W1, Type1>& m);
		template<int H1, int W1, class Type1 >	friend std::istream& operator>>(std::istream& is, Mat<W1, H1, Type1>& m);
		template<int H1, int W1, class Type1 >	friend Mat<H1, W1, float>	operator*(const Mat<H1, W1, Type1>& m, float skalar);
		template<int H1, int W1, class Type1 >	friend Mat<H1, W1, float>	operator*(float skalar, const Mat<H1, W1, Type1>& m);
		template<int H1, int W1, class Type1 >	friend Mat<H1, W1, float>	operator/(const Mat<H1, W1, Type1>& m, float skalar);
		
		template<int W1, int W2, int H1, int H2, class Type1 >	
		friend Mat<H1, W2, Type1>	operator*(const Mat<H1, W1, Type1>& m1, const Mat<H2, W2, Type1>& m2);
	};

	template<int D, class Type>
	Mat<1, D, Type> createMatrixFromVector(Math::Vec<D, Type> vec)
	{
		Mat<1, D, Type> m;

		for (int idx = 0; idx < D; ++idx)
			m(0, idx) = vec[idx];

		return m;
	}

	template<int W1, int H1, class Type1 >	//Transponate
	Mat<W1, H1, Type1>	T(const Mat<H1, W1, Type1>& m)
	{
		Mat<W1, H1, Type1> result;

		for (int row = 0; row < m.height; ++row) 
			for (int col = 0; col < m.width; ++col) 
				result(col, row) = m(row, col);

		return result;
	}

	template<int W1, int H1, class Type1 >	//Determinant
	float	det(Mat<W1, H1, Type1> m)
	{
		if (W1 != H1)
			throw new std::exception();
		float det = 1.0f;
		int signal;

		Mat gauss = m.gaussianEliminate(signal);
		for (int idx = 0; idx < W1 && idx < H1; ++idx)
			det *= gauss(idx, idx);

		det *= (float)signal;

		return det;
	}

	template<int H1, int W1, class Type1 >
	std::ostream& operator<<(std::ostream& os, const Mat<H1, W1, Type1>& m)
	{
		/*os << m.height << "\t" << m.width << "\n";*/
		for (int idx = 0; idx < m.length - 1; ++idx)
		{
				os << m.coords[idx] << "\t";
		}
		os << m.coords[m.length - 1];
		return os;
	}

	template<int W1, int H1, class Type1 >	
	std::istream& operator>>(std::istream& is, Mat<H1, W1, Type1>& m)
	{
		float coord;
		for (int idx = 0; idx < H1 * W1; ++idx)
		{
			is >> coord;
			m.coords[idx] = coord;
		}

		return is;
	}

	template<int H1, int W1, class Type1 >	
	Mat<H1, W1, float>	operator*(const Mat<H1, W1, Type1>& m, float skalar)
	{
		Mat<H1, W1, float> result;
		for (int idx = 0; idx < m.length; ++idx)
			result.coords[idx] = m.coords[idx] * skalar;

		return result;
	}

	template<int H1, int W1, class Type1 >	
	Mat<H1, W1, float>	operator*(float skalar, const Mat<H1, W1, Type1>& m)
	{
		return m * skalar;
	}

	template<int H1, int W1, class Type1 >	
	Mat<H1, W1, float>	operator/(const Mat<H1, W1, Type1>& m, float skalar)
	{
		if (skalar == 0.0f)
			throw new ZeroDivisionException();
		return m * (1.0f / skalar);
	}

	template<int W1, int W2, int H1, int H2, class Type1 >
	Mat<H1, W2, Type1>	operator*(const Mat<H1, W1, Type1>& m1, const Mat<H2, W2, Type1>& m2)
	{
		static_assert(W1 == H2, "Can not multiple these matrixes!!'");
		Mat<H1, W2, Type1> result;

		for (int row = 0; row < m1.height; ++row) {
			for (int col = 0; col < m2.width; ++col) {
				for (int k = 0; k < m1.width; ++k) {
					result(row, col) += (m1(row, k) * m2(k, col));
				}
			}
		}

		return result;
	}

	template<int W1, int H1, int D, class Type1 >
	Vec<D, Type1>	operator*(const Vec<D, Type1>& v, const Mat<W1, H1, Type1>& m)
	{
		return (createMatrixFromVector(v) * m).getVectorFromRow();
	}

	template<int W1, int H1, int D, class Type1 >
	Vec<D, Type1>	operator*(const Mat<W1, H1, Type1>& m, const Vec<D, Type1>& v)
	{
		Mat vm = T(createMatrixFromVector(v));
		return (m * vm).getVectorFromCol();
	}

	namespace Constant
	{
		const Mat3x3f	E(	1.0f, 0.0f, 0.0f,
							0.0f, 1.0f, 0.0f,
							0.0f, 0.0f, 1.0f);
	}
}