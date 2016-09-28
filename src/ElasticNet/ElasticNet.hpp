#pragma once

#include <memory>

namespace tsp
{
    using std::unique_ptr;

    template<typename DistanceType>
    class NodeContainer;

    template<typename DistanceType>
    class HamiltonianPath;

    template<typename DistanceType>
    class ElasticNet
    {
    public:
        static unique_ptr<HamiltonianPath<DistanceType>> Run(unique_ptr<NodeContainer<DistanceType>>);
    };

    template <typename DistanceType>
    unique_ptr<HamiltonianPath<DistanceType>>
        ElasticNet<DistanceType>::Run(unique_ptr<NodeContainer<DistanceType>> container)
    {
        return {};
    }
}
