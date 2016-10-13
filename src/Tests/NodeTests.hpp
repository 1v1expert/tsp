#pragma once

#include <list>
#include <sstream>

#include "Helper.hpp"
#include "AbstractTest.hpp"
#include "../Utility/Node.hpp"

namespace tsp_tests
{
	using std::unique_ptr;
	using std::string;
	using std::shared_ptr;
	using std::weak_ptr;
	using std::list;
    using std::stringstream;

	using std::make_unique;
	using std::make_shared;
	using std::to_string;
	using std::get;

	template<typename NodeDistanceType>
    struct NodeTests : AbstractTest
	{
		using NodeSpecialized = tsp::Node<NodeDistanceType>;

		static bool CreateNode();
		static bool CompareNodes();
		static bool FillNodes();
		static bool PrintNode();
	};

	template <typename NodeDistanceType>
	bool NodeTests<NodeDistanceType>::CreateNode()
	{
		NodeSpecialized node1("Node 1", 
			                  RandomValue(NodeDistanceType{ 0 }, NodeDistanceType{ 500 }), 
							  RandomValue(NodeDistanceType{ 0 }, NodeDistanceType{ 500 }));
		AssertThat(node1.Name() == "Node 1");
		AssertThat(node1.X() >= NodeDistanceType{ 0 } && node1.X() <= NodeDistanceType{ 500 });
		AssertThat(node1.Y() >= NodeDistanceType{ 0 } && node1.Y() <= NodeDistanceType{ 500 });

		string name("Node 2");
		NodeSpecialized node2(name,
							  RandomValue(NodeDistanceType{ 0 }, NodeDistanceType{ 500 }),
							  RandomValue(NodeDistanceType{ 0 }, NodeDistanceType{ 500 }));
		AssertThat(node2.Name() == "Node 2");
		AssertThat(node2.Name() == name);
		AssertThat(node2.X() >= NodeDistanceType{ 0 } && node2.X() <= NodeDistanceType{ 500 });
		AssertThat(node2.Y() >= NodeDistanceType{ 0 } && node2.Y() <= NodeDistanceType{ 500 });

		auto name_ptr = make_unique<string>("Node 3");
		NodeSpecialized node3(*name_ptr.get(),
							  RandomValue(NodeDistanceType{ 0 }, NodeDistanceType{ 500 }),
						      RandomValue(NodeDistanceType{ 0 }, NodeDistanceType{ 500 }));
		AssertThat(node3.Name() == "Node 3");
		AssertThat(node3.Name() == *name_ptr);
		AssertThat(node3.X() >= NodeDistanceType{ 0 } && node3.X() <= NodeDistanceType{ 500 });
		AssertThat(node3.Y() >= NodeDistanceType{ 0 } && node3.Y() <= NodeDistanceType{ 500 });

		return HadPassed();
	}

	template <typename NodeDistanceType>
	bool NodeTests<NodeDistanceType>::CompareNodes()
	{
		auto x1 = RandomValue(NodeDistanceType{ 0 }, NodeDistanceType{ 500 });
		auto y1 = RandomValue(NodeDistanceType{ 0 }, NodeDistanceType{ 500 });

		auto x2 = RandomValue(NodeDistanceType{ 0 }, NodeDistanceType{ 500 });
		auto y2 = RandomValue(NodeDistanceType{ 0 }, NodeDistanceType{ 500 });

		NodeSpecialized node1("Node 1", x1, y1);
		string name("Node 2");
		NodeSpecialized node2(name, x2, y2);
		auto name_ptr = make_unique<string>("Node 2");
		NodeSpecialized node3(*name_ptr.get(), x2, y2);

		AssertThat(node1 != node2);
		AssertThat(node2 != node1);
		AssertThat(node1 != node3);
		AssertThat(node3 != node1);
		AssertThat(node1 == node1);
		AssertThat(node2 == node2);
		AssertThat(node2 == node3);
		AssertThat(node3 == node2);
		AssertThat(node3 == node3);

        return HadPassed();
	}

	template <typename NodeDistanceType>
	bool NodeTests<NodeDistanceType>::FillNodes()
	{
		using NodePtr = shared_ptr<NodeSpecialized>;

		auto x1 = RandomValue(NodeDistanceType{ 0 }, NodeDistanceType{ 500 });
		auto y1 = RandomValue(NodeDistanceType{ 0 }, NodeDistanceType{ 500 });

		vector<NodePtr> nodes;
		for (auto i = 0; i < 50; ++i)
			nodes.emplace_back(make_shared<NodeSpecialized>("Node " + to_string(i),
							   x1,
							   y1));

		for (auto i = 0; i < nodes.size(); ++i)
		{
			AssertThat(nodes[i]->Name() == "Node " + to_string(i));
			AssertThat(nodes[i]->X() == x1);
			AssertThat(nodes[i]->Y() == y1);
		}

        return HadPassed();
	}

	template <typename NodeDistanceType>
	bool NodeTests<NodeDistanceType>::PrintNode()
	{
        using NodePtr = shared_ptr<NodeSpecialized>;

		auto x1 = RandomValue(NodeDistanceType{ 0 }, NodeDistanceType{ 500 });
		auto y1 = RandomValue(NodeDistanceType{ 0 }, NodeDistanceType{ 500 });

		list<NodePtr> nodes;
		for (auto i = 0; i < 50; ++i)
			nodes.emplace_back(make_shared<NodeSpecialized>("Node " + to_string(i),
				x1,
				y1));

        stringstream s;
        for (auto node : nodes)
            s << *node << std::endl;
        AssertThat(s.str().size() != 0);

        return HadPassed();
	}
}
