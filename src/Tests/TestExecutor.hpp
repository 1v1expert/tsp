#pragma once

#include <iostream>
#include <string>

#include "NodeTests.hpp"
#include "NodeContainerTest.hpp"
#include "ElasticTest.hpp"

namespace tsp_tests
{
	using std::string;
	using std::ostream;

	using std::cout;
	using std::cerr;
	using std::endl;

	struct TestExecutor
	{
		static void ExecuteAllTests();
		static ostream& PrintStat(ostream& stream);
	private:
		static void ExecuteOne(bool result, string name);
		static vector<bool> results;
	};

	vector<bool> TestExecutor::results;

	inline void TestExecutor::ExecuteAllTests()
	{
		results.clear();

		ExecuteOne(NodeTests<int32_t>::CreateNode(), "Node creation with int32_t distance type");
		ExecuteOne(NodeTests<float>::CreateNode(), "Node creation with float distance type");
		ExecuteOne(NodeTests<int32_t>::CompareNodes(), "Node comparison with int32_t distance type");
		ExecuteOne(NodeTests<float>::CompareNodes(), "Node comparison with float distance type");
		ExecuteOne(NodeTests<int32_t>::FillNodes(), "Node filling with int32_t distance type");
		ExecuteOne(NodeTests<float>::FillNodes(), "Node filling with float distance type");
		ExecuteOne(NodeTests<float>::PrintNode(), "Node print with float distance type");

		ExecuteOne(NodeContainerTest<int32_t>::TryParseWithFixture(), "NodeFactory try parce with int random fixtures");
		ExecuteOne(NodeContainerTest<float>::TryParseWithFixture(), "NodeFactory try parce with float random fixtures");

		ExecuteOne(ElasticTest<int32_t>::Go(), "");
		ExecuteOne(ElasticTest<int32_t>::Go(), "");
	}

	inline ostream& TestExecutor::PrintStat(ostream& stream)
	{
		auto all_count = results.size();

		auto success_count = 0;
		for (const auto& result : results)
			if (result) success_count += 1;

		auto error_count = 0;
		for (const auto& result : results)
			if (!result) error_count += 1;

		stream << all_count
			   << " tests passed. "
			   << success_count
			   << " successfull. "
			   << error_count
			   << " with error\n";

		return stream;
	}

	inline void TestExecutor::ExecuteOne(bool result, string name)
	{
		results.emplace_back(result);

		if (result)
			cout << "Test [" << name << "]" << " passing status: [OK]" << endl;
		else
			cerr << "Test [" << name << "]" << " passing status: [ERROR]" << endl;
	}
}
