#pragma once

#include <list>

#include "Helper.hpp"
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
    struct NodeContainerTest : public AbstractTest
    {
        using NodeSpecialized = tsp::Node<NodeDistanceType>;

        static bool FullConnected();
        static bool NodesCount();
        static bool GetNodes();
        static bool GetRawNodes();
        static bool FindNode();
    };

    template <typename NodeDistanceType>
    bool NodeContainerTest<NodeDistanceType>::FullConnected()
    {
        return HadPassed();
    }

    template <typename NodeDistanceType>
    bool NodeContainerTest<NodeDistanceType>::NodesCount()
    {
        return HadPassed();
    }

    template <typename NodeDistanceType>
    bool NodeContainerTest<NodeDistanceType>::GetNodes()
    {
        return HadPassed();
    }

    template <typename NodeDistanceType>
    bool NodeContainerTest<NodeDistanceType>::GetRawNodes()
    {
        return HadPassed();
    }

    template <typename NodeDistanceType>
    bool NodeContainerTest<NodeDistanceType>::FindNode()
    {
        return HadPassed();
    }
}
