#pragma once

#include <list>

#include "Helper.hpp"
#include "AbstractTest.hpp"
#include "../Utility/NodeFactory.hpp"

namespace tsp_tests
{
	using std::unique_ptr;
	using std::string;
	using std::shared_ptr;
	using std::weak_ptr;
	using std::stringstream;
	using std::list;

	using std::make_unique;
	using std::make_shared;
	using std::to_string;
	using std::get;

	template<typename NodeDistanceType>
	struct NodeContainerTest : AbstractTest
	{
		using NodeSpecialized = tsp::Node<NodeDistanceType>;
		using NodeFactorySpecialized = tsp::NodeFactory<NodeDistanceType>;

		static bool Create() { return true; }

	private:
		static void TryParseWithFixture() {}
	};

	template<>
	struct NodeContainerTest<int32_t> : AbstractTest
	{
		using NodeSpecialized = tsp::Node<int32_t>;
		using NodeFactorySpecialized = tsp::NodeFactory<int32_t>;

		static bool TryParseWithFixture();
	};

	template<>
	struct NodeContainerTest<float> : AbstractTest
	{
		using NodeSpecialized = tsp::Node<float>;
		using NodeFactorySpecialized = tsp::NodeFactory<float>;

		static bool TryParseWithFixture();
	};

	inline bool NodeContainerTest<int32_t>::TryParseWithFixture()
	{
		for (auto iteration = 0; iteration < 1000; ++iteration)
		{
			auto names = RandomNames(100);
			auto x = RandomCoordinates(100, 0, 1000);
			auto y = RandomCoordinates(100, 0, 1000);

			stringstream s;
			for (auto i = 0; i < 100; ++i)
				s << names[i] << "; " << x[i] << "; " << y[i] << ";\n";

			auto node_container = NodeFactorySpecialized::CreateFromStream(s);
			AssertThat(node_container->NodesCount() == 100);
			for (auto i = 0; i < 100; ++i)
			{
				AssertThat((*node_container)[i]->Name() == names[i]);
				AssertThat((*node_container)[i]->X() == x[i]);
				AssertThat((*node_container)[i]->Y() == y[i]);
			}
		}

		return HadPassed();
	}

	inline bool NodeContainerTest<float>::TryParseWithFixture()
	{
		for (auto iteration = 0; iteration < 1000; ++iteration)
		{
			auto names = RandomNames(100);
			auto x = RandomCoordinates(100, 0.f, 1000.f);
			auto y = RandomCoordinates(100, 0.f, 1000.f);

			stringstream s;
			for (auto i = 0; i < 100; ++i)
				s << names[i] << "; " << x[i] << "; " << y[i] << ";\n";

			auto node_container = NodeFactorySpecialized::CreateFromStream(s);
			AssertThat(node_container->NodesCount() == 100);
			for (auto i = 0; i < 100; ++i)
			{
				AssertThat((*node_container)[i]->Name() == names[i]);
				AssertThat(abs((*node_container)[i]->X() - x[i]) < 0.01f);
				AssertThat(abs((*node_container)[i]->Y() - y[i]) < 0.01f);
			}
		}

		return HadPassed();
	}
}
