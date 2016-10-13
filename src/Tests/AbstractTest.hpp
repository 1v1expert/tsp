#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <tuple>

namespace tsp_tests
{
	using std::string;
	using std::vector;
	using std::tuple;
	using std::cerr;

	using std::make_tuple;
	using std::get;

	struct AbstractTest
	{
		static void AssertThat(bool result, string represenatation = "");
		static bool HadPassed(bool print_errors = true);

	private:
		static vector<tuple<bool, string>> results_;
	};

	vector<tuple<bool, string>> AbstractTest::results_;

	inline void AbstractTest::AssertThat(bool result, string represenatation)
	{
		results_.emplace_back(make_tuple(result, represenatation));
	}

	inline bool AbstractTest::HadPassed(bool print_errors)
	{
		auto final_result = true;
		for (const auto& result : results_)
			if (!get<0>(result))
			{
				final_result = false;
				if (print_errors)
					cerr << "Error in test: "
						 << get<1>(result)
						 << '\n';
			}

		results_.clear();
		return final_result;
	}
}
