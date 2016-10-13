#pragma once

#include <cassert>

namespace tsp
{
	constexpr double pi = 3.141592653589793238463;

	template<typename T, typename M1, typename M2>
	vector<vector<T>> MatrixMultiply(const M1& maxtrix_1, const M2& maxtrix_2)
	{
		assert(maxtrix_1.size() > 0);
		assert(maxtrix_2.size() > 0);

		assert(maxtrix_1[0].size() > 0);
		assert(maxtrix_2[0].size() > 0);

		assert(maxtrix_1[0].size() == maxtrix_2.size());

		vector<vector<T>> result;
		for (auto i = 0; i < maxtrix_1.size(); ++i)
		{
			result.emplace_back(vector<T>());
			for (auto j = 0; j < maxtrix_2[0].size(); ++j)
			{
				T res{};
				for (auto t = 0; t < maxtrix_1[0].size(); ++t)
					res += (maxtrix_1[i][t] * maxtrix_2[t][j]);
				result.back().emplace_back(res);
			}
		}

		return result;
	}

	template<typename T, typename M>
	vector<vector<T>> MatrixTranspose(const M& maxtrix)
	{
		vector<vector<T>> result;
		for (auto j = 0; j < maxtrix[0].size(); ++j)
		{
			result.emplace_back(vector<T>());
			for (auto i = 0; i < maxtrix.size(); ++i)
				result.back().emplace_back(maxtrix[i][j]);
		}

		return result;
	}

	template<typename M1, typename M2>
	decltype(auto) MatrixesMinus(const M1& matrix_1, const M2& matrix_2)
	{
		assert(matrix_1.size() > 0);
		assert(matrix_2.size() > 0);

		assert(matrix_1[0].size() > 0);
		assert(matrix_2[0].size() > 0);

		assert(matrix_1.size() == matrix_2.size());
		assert(matrix_1[0].size() == matrix_2[0].size());

		M1 result{};

		for (auto i = 0; i < matrix_1.size(); ++i)
		{
			result.push_back({});
			for (auto j = 0; j < matrix_1[i].size(); ++j)
				result.back().push_back({ matrix_1[i][j] - matrix_2[i][j] });
		}
		return result;
	}

	template<typename M1, typename M2>
	decltype(auto) MatrixesPlus(const M1& matrix_1, const M2& matrix_2)
	{
		assert(matrix_1.size() > 0);
		assert(matrix_2.size() > 0);

		assert(matrix_1.size() == matrix_2.size());
		assert(matrix_2.size() == matrix_2.size());

		assert(matrix_1[0].size() > 0);
		assert(matrix_2[0].size() > 0);

		assert(matrix_1.size() == matrix_2.size());
		assert(matrix_1[0].size() == matrix_2[0].size());

		M1 result{};

		for (auto i = 0; i < matrix_1.size(); ++i)
		{
			result.push_back({});
			for (auto j = 0; j < matrix_1[i].size(); ++j)
				result.back().push_back({ matrix_1[i][j] + matrix_2[i][j] });
		}
		return result;
	}

	template<typename T, typename M>
	decltype(auto) MatrixMultiplyNum(const T& num, const M& matrix)
	{
		assert(matrix.size() > 0);
		assert(matrix[0].size() > 0);

		M result{};

		for (auto i = 0; i < matrix.size(); ++i)
		{
			result.push_back({});
			for (auto j = 0; j < matrix[i].size(); ++j)
				result.back().push_back({ matrix[i][j] * num });
		}

		return result;
	}

	template<typename V1, typename V2>
	decltype(auto) VectorsMinus(const V1& vector_1, const V2& vector_2)
	{
		assert(vector_1.size() > 0);
		assert(vector_2.size() > 0);
		assert(vector_1.size() == vector_2.size());

		V1 result{};

		for (auto i = 0; i < vector_1.size(); ++i)
			result.push_back({ vector_1[i] - vector_2[i] });

		return result;
	}

	template<typename V1, typename V2>
	decltype(auto) VectorsPlus(const V1& vector_1, const V2& vector_2)
	{
		assert(vector_1.size() > 0);
		assert(vector_2.size() > 0);
		assert(vector_1.size() == vector_2.size());

		V1 result{};

		for (auto i = 0; i < vector_1.size(); ++i)
			result.push_back({ vector_1[i] + vector_2[i] });

		return result;
	}

	template<typename T, typename V>
	decltype(auto) VectorsMultiplyNum(const T& num, const V& vector)
	{
		assert(vector.size() > 0);

		V result{};

		for (auto i = 0; i < vector.size(); ++i)
			result.push_back({ vector[i] * num });

		return result;
	}
}