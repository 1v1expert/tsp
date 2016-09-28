#pragma once

#include <list>

#include "Helper.hpp"
#include "AbstractTest.hpp"
#include "../Utility/HamiltonianPath.hpp"

namespace tsp_tests
{
    using std::unique_ptr;
    using std::string;
    using std::shared_ptr;
    using std::weak_ptr;
    using std::list;
    using std::stringstream;
    using tsp::AddStatus;

    using std::make_unique;
    using std::make_shared;
    using std::to_string;
    using std::get;

    template<typename NodeDistanceType>
    struct HamiltonianPathTest : public AbstractTest
    {
        using NodeSpecialized = tsp::Node<NodeDistanceType>;
        using HamiltonianPathSpecialized = tsp::HamiltonianPath<NodeDistanceType>;
        using NodePtr = shared_ptr<NodeSpecialized>;
        using NodeWeakPtr = weak_ptr<NodeSpecialized>;

        static bool CreatePath();
        static bool AddNodes();
        static bool GetNode();
        static bool Distance();
        static bool Validity();
    };

    template <typename NodeDistanceType>
    bool HamiltonianPathTest<NodeDistanceType>::CreatePath()
    {
        for (auto repeat = 0; repeat < 1000; ++repeat)
        {
            auto node = make_shared<NodeSpecialized>("Node " + to_string(repeat));
            HamiltonianPathSpecialized path{ NodeWeakPtr{ node } };
            AssertThat(path.IsValid());
        }

        return HadPassed();
    }

    template <typename NodeDistanceType>
    bool HamiltonianPathTest<NodeDistanceType>::AddNodes()
    {
        list<NodePtr> nodes;
        for (auto i = 0; i < 50; ++i)
            nodes.emplace_back(make_shared<NodeSpecialized>("Node " + to_string(i)));

        HamiltonianPathSpecialized path{ NodeWeakPtr{ *nodes.begin() } };
        for (const auto& node: nodes)
        {
            if (node == *nodes.begin()) continue;
            auto result = path.TryAddNode(NodeWeakPtr{ node }, 
                                          RandomValue(NodeDistanceType{ 0 }, NodeDistanceType{ 500 }));
            AssertThat(result == AddStatus::Success);
        }

        HamiltonianPathSpecialized path1{ NodeWeakPtr{ *nodes.begin() } };
        for (auto i = 0; i < nodes.size(); ++i)
        {
            auto result = path1.TryAddNode(NodeWeakPtr{ *nodes.begin() },
                                           RandomValue(NodeDistanceType{ 0 }, NodeDistanceType{ 500 }));
            AssertThat(result == AddStatus::AlreadyAdded);
        }

        HamiltonianPathSpecialized path2{ NodeWeakPtr{ *nodes.begin() } };
        for (auto i = 0; i < 10; ++i)
        {
            auto result = path2.TryAddNode(NodeWeakPtr{ },
                                           RandomValue(NodeDistanceType{ 0 }, NodeDistanceType{ 500 }));
            AssertThat(result == AddStatus::InputError);
        }

        return HadPassed();
    }

    template <typename NodeDistanceType>
    bool HamiltonianPathTest<NodeDistanceType>::GetNode()
    {
        list<NodePtr> nodes;
        for (auto i = 0; i < 50; ++i)
            nodes.emplace_back(make_shared<NodeSpecialized>("Node " + to_string(i)));

        HamiltonianPathSpecialized path{ NodeWeakPtr{ *nodes.begin() } };
        for (const auto& node : nodes)
        {
            if (node == *nodes.begin()) continue;
            auto result = path.TryAddNode(NodeWeakPtr{ node },
                                          RandomValue(NodeDistanceType{ 0 }, NodeDistanceType{ 500 }));
            AssertThat(result == AddStatus::Success);
        }

        for (const auto& node : nodes)
        {
            auto taken_node = path.TryGetNode(node->Name());
            AssertThat(!taken_node.expired());
        }

        auto taken_node = path.TryGetNode("Error node");
        AssertThat(taken_node.expired());

        return HadPassed();
    }

    template <typename NodeDistanceType>
    bool HamiltonianPathTest<NodeDistanceType>::Distance()
    {
        list<NodePtr> nodes;
        for (auto i = 0; i < 50; ++i)
            nodes.emplace_back(make_shared<NodeSpecialized>("Node " + to_string(i)));

        HamiltonianPathSpecialized path{ NodeWeakPtr{ *nodes.begin() } };
        for (const auto& node : nodes)
        {
            if (node == *nodes.begin()) continue;
            path.TryAddNode(NodeWeakPtr{ node }, NodeDistanceType{ 100 });
        }

        AssertThat((100 * 50) - 100 == path.CompleteDistance());

        return HadPassed();
    }

    template <typename NodeDistanceType>
    bool HamiltonianPathTest<NodeDistanceType>::Validity()
    {
        list<NodePtr> nodes;
        for (auto i = 0; i < 50; ++i)
            nodes.emplace_back(make_shared<NodeSpecialized>("Node " + to_string(i)));

        HamiltonianPathSpecialized path{ NodeWeakPtr{ *nodes.begin() } };
        for (const auto& node : nodes)
        {
            if (node == *nodes.begin()) continue;
            path.TryAddNode(NodeWeakPtr{ node },
                            RandomValue(NodeDistanceType{ 0 }, NodeDistanceType{ 500 }));
        }
        AssertThat(path.IsValid());

        nodes.pop_back();
        AssertThat(!path.IsValid());

        return HadPassed();
    }
}
