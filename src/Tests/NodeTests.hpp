#pragma once

#include <list>

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
    struct NodeTests : public AbstractTest
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
		NodeSpecialized node1("Node 1");
		AssertThat(node1.Name() == "Node 1");

		string name("Node 2");
		NodeSpecialized node2(name);
		AssertThat(node2.Name() == "Node 2");
		AssertThat(node2.Name() == name);

		auto name_ptr = make_unique<string>("Node 2");
		NodeSpecialized node3(*name_ptr.get());
		AssertThat(node3.Name() == "Node 2");
		AssertThat(node3.Name() == *name_ptr);

		AssertThat(node1.NodesCount() == 0);
		AssertThat(node2.NodesCount() == 0);
		AssertThat(node3.NodesCount() == 0);

		return HadPassed();
	}

	template <typename NodeDistanceType>
	bool NodeTests<NodeDistanceType>::CompareNodes()
	{
		NodeSpecialized node1("Node 1");
		string name("Node 2");
		NodeSpecialized node2(name);
		auto name_ptr = make_unique<string>("Node 2");
		NodeSpecialized node3(*name_ptr.get());

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

		list<NodePtr> nodes;
		for (auto i = 0; i < 50; ++i)
			nodes.emplace_back(make_shared<NodeSpecialized>("Node " + to_string(i)));

		for (auto& node1: nodes)
			for (auto& node2: nodes)
				if (node1 != node2)
					node1->AddNode(weak_ptr<NodeSpecialized>(node2), RandomValue(1, 500));

		AssertThat(nodes.size() == 50);
		for (auto& node : nodes)
		{
			AssertThat(node->NodesCount() == 49);
			for (const auto& node_tuple : node->LinkedNodes())
			{
				AssertThat(!get<0>(node_tuple).expired());
				AssertThat(get<0>(node_tuple).lock() != node);
				AssertThat(get<1>(node_tuple) >= 1 && get<1>(node_tuple) <= 500);
			}
		}

        nodes.erase(nodes.begin());
        for (auto& node : nodes)
        {
            node->ClearInvalidRefs();
            AssertThat(node->NodesCount() == 48);
            node->RemoveNode(get<0>(*node->LinkedNodes().begin()));
            AssertThat(node->NodesCount() == 47);
            for (const auto& node_tuple : node->LinkedNodes())
            {
                AssertThat(!get<0>(node_tuple).expired());
                AssertThat(get<0>(node_tuple).lock() != node);
                AssertThat(get<1>(node_tuple) >= 1 && get<1>(node_tuple) <= 500);
            }
        }

        return HadPassed();
	}

	template <typename NodeDistanceType>
	bool NodeTests<NodeDistanceType>::PrintNode()
	{
        using NodePtr = shared_ptr<NodeSpecialized>;

        list<NodePtr> nodes;
        for (auto i = 0; i < 10; ++i)
            nodes.emplace_back(make_shared<NodeSpecialized>("Node " + to_string(i)));

        for (auto& node1 : nodes)
            for (auto& node2 : nodes)
                if (node1 != node2)
                    node1->AddNode(weak_ptr<NodeSpecialized>(node2), RandomValue(1.f, 500.f));
        AssertThat(nodes.size() == 10);

        stringstream s;
        for (auto node : nodes)
            s << *node << std::endl;
        AssertThat(s.str().size() != 0);

        return HadPassed();
	}
}
