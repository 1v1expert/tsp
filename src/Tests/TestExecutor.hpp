#pragma once

#include <iostream>
#include <string>

#include "NodeTests.hpp"
#include "NodeFactoryTest.hpp"
#include "NodeContainerTest.h"
#include "HamiltonianPathTest.hpp"

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

		ExecuteOne(NodeTests<int32_t>::CreateNode(),            "Node creation with int32_t distance type");
		ExecuteOne(NodeTests<float>::CreateNode(),              "Node creation with float distance type");
		ExecuteOne(NodeTests<int32_t>::CompareNodes(),          "Node comparison with int32_t distance type");
		ExecuteOne(NodeTests<float>::CompareNodes(),            "Node comparison with float distance type");
        ExecuteOne(NodeTests<int32_t>::FillNodes(),             "Node filling with int32_t distance type");
        ExecuteOne(NodeTests<float>::FillNodes(),               "Node filling with float distance type");
        ExecuteOne(NodeTests<float>::PrintNode(),               "Node print with float distance type");

        ExecuteOne(NodeFactoryTests<int32_t>::Fixture_1(),      "NodeFactory try parce with fixture 1");
        ExecuteOne(NodeFactoryTests<int32_t>::Fixture_2(),      "NodeFactory try parce with fixture 2");
        ExecuteOne(NodeFactoryTests<int32_t>::Fixture_3(),      "NodeFactory try parce with fixture 3");
        ExecuteOne(NodeFactoryTests<int32_t>::Fixture_4(),      "NodeFactory try parce with fixture 4");
        ExecuteOne(NodeFactoryTests<int32_t>::Fixture_5(),      "NodeFactory try parce with fixture 5");
        ExecuteOne(NodeFactoryTests<int32_t>::Fixture_6(),      "NodeFactory try parce with fixture 6");
        ExecuteOne(NodeFactoryTests<int32_t>::Fixture_7(),      "NodeFactory try parce with fixture 7");
        ExecuteOne(NodeFactoryTests<int32_t>::Fixture_8(),      "NodeFactory try parce with fixture 8");
        ExecuteOne(NodeFactoryTests<int32_t>::Fixture_9(),      "NodeFactory try parce with fixture 9");
        ExecuteOne(NodeFactoryTests<float>::Fixture_1(),        "NodeFactory try parce with fixture 1");
        ExecuteOne(NodeFactoryTests<float>::Fixture_2(),        "NodeFactory try parce with fixture 2");
        ExecuteOne(NodeFactoryTests<float>::Fixture_3(),        "NodeFactory try parce with fixture 3");
        ExecuteOne(NodeFactoryTests<float>::Fixture_4(),        "NodeFactory try parce with fixture 4");
        ExecuteOne(NodeFactoryTests<float>::Fixture_5(),        "NodeFactory try parce with fixture 5");
        ExecuteOne(NodeFactoryTests<float>::Fixture_6(),        "NodeFactory try parce with fixture 6");
        ExecuteOne(NodeFactoryTests<float>::Fixture_7(),        "NodeFactory try parce with fixture 7");
        ExecuteOne(NodeFactoryTests<float>::Fixture_8(),        "NodeFactory try parce with fixture 8");
        ExecuteOne(NodeFactoryTests<float>::Fixture_9(),        "NodeFactory try parce with fixture 9");

        ExecuteOne(NodeContainerTest<int32_t>::FullConnected(), "Node int32_t container full connected test");
        ExecuteOne(NodeContainerTest<float>::FullConnected(),   "Node float container full connected test");
        ExecuteOne(NodeContainerTest<int32_t>::NodesCount(),    "Node int32_t container nodes count test");
        ExecuteOne(NodeContainerTest<float>::NodesCount(),      "Node float container nodes count test");
        ExecuteOne(NodeContainerTest<int32_t>::GetNodes(),      "Node int32_t container get all filled nodes test");
        ExecuteOne(NodeContainerTest<float>::GetNodes(),        "Node foat container get all filled nodes test");
        ExecuteOne(NodeContainerTest<int32_t>::GetRawNodes(),   "Node int32_t container get raw nodes test");
        ExecuteOne(NodeContainerTest<float>::GetRawNodes(),     "Node float container get raw nodes test");
        ExecuteOne(NodeContainerTest<int32_t>::FindNode(),      "Node int32_t container try find node");
        ExecuteOne(NodeContainerTest<float>::FindNode(),        "Node float container try find node");

        ExecuteOne(HamiltonianPathTest<int32_t>::CreatePath(),  "Path with int32_t node try create path");
        ExecuteOne(HamiltonianPathTest<float>::CreatePath(),    "Path with float node try create path");
        ExecuteOne(HamiltonianPathTest<int32_t>::AddNodes(),    "Path with int32_t node try add new nodes");
        ExecuteOne(HamiltonianPathTest<float>::AddNodes(),      "Path with float node try add new nodes");
        ExecuteOne(HamiltonianPathTest<int32_t>::GetNode(),     "Path with int32_t node try get node");
        ExecuteOne(HamiltonianPathTest<float>::GetNode(),       "Path with float node try get node");
        ExecuteOne(HamiltonianPathTest<int32_t>::Distance(),    "Path with int32_t node compute all distance");
        ExecuteOne(HamiltonianPathTest<float>::Distance(),      "Path with float node compute all distance");
        ExecuteOne(HamiltonianPathTest<int32_t>::Validity(),    "Path with int32_t node check validity");
        ExecuteOne(HamiltonianPathTest<float>::Validity(),      "Path with float node check validity");
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
