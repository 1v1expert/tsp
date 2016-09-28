#pragma once

#include <memory>
#include <tuple>
#include <list>
#include <algorithm>

#include "Node.hpp"

namespace tsp
{
    using std::list;
    using std::tuple;
    using std::weak_ptr;

    using std::make_tuple;
    using std::find_if;
    using std::get;

    enum class AddStatus
    {
        Success, AlreadyAdded, InputError
    };

    template<typename NodeDistanceType>
    class HamiltonianPath
    {
        using NodeWeakPtr = weak_ptr<Node<NodeDistanceType>>;

    public:
        explicit HamiltonianPath(NodeWeakPtr start_node);
        HamiltonianPath(const HamiltonianPath&) = delete;
        HamiltonianPath& operator=(const HamiltonianPath&) = delete;
        HamiltonianPath(HamiltonianPath&&) = default;
        HamiltonianPath& operator=(HamiltonianPath&&) = default;
        ~HamiltonianPath() = default;

        AddStatus TryAddNode(NodeWeakPtr node, NodeDistanceType distance_from_last_node);
        NodeWeakPtr TryGetNode(string name) const;
        NodeDistanceType CompleteDistance() const;
        bool IsValid() const;

        typename list<tuple<NodeWeakPtr, NodeDistanceType>>::iterator begin();
        typename list<tuple<NodeWeakPtr, NodeDistanceType>>::iterator end();
        typename list<tuple<NodeWeakPtr, NodeDistanceType>>::const_iterator cbegin();
        typename list<tuple<NodeWeakPtr, NodeDistanceType>>::const_iterator cend();

        friend ostream& operator<<(ostream& lhs, const HamiltonianPath<NodeDistanceType>& rhs)
        {
            if (rhs.path_.size() == 0 || !rhs.IsValid()) return lhs;

            lhs << get<0>(*rhs.path_.begin()).lock()->Name();

            for (const auto& node_tup : rhs.path_)
            {
                if (get<0>(node_tup).lock() == get<0>(*rhs.path_.begin()).lock()) continue;
                lhs << " -- "
                    << get<1>(node_tup)
                    << " -- "
                    << get<0>(node_tup).lock()->Name();
            }
            
            lhs << '\n' 
                << "Total distance: "
                << rhs.CompleteDistance();

            return lhs;
        }

    private:

        /**
         * \brief Tuple of node reference and distance for previous node in the list. First node with 0 distance
         */
        list<tuple<NodeWeakPtr, NodeDistanceType>> path_;
    };

    template <typename NodeDistanceType>
    HamiltonianPath<NodeDistanceType>::HamiltonianPath(NodeWeakPtr start_node)
    {
        path_.emplace_back(make_tuple(start_node, NodeDistanceType{}));
    }

    template <typename NodeDistanceType>
    AddStatus HamiltonianPath<NodeDistanceType>::TryAddNode(NodeWeakPtr node,
                                                            NodeDistanceType distance_from_last_node)
    {
        if (node.expired()) return AddStatus::InputError;
        auto node_ptr = node.lock();

        auto it = find_if(path_.cbegin(), path_.cend(), [&node_ptr](const auto& node_tup)
        {
            if (get<0>(node_tup).expired()) return false;
            return node_ptr == get<0>(node_tup).lock();
        });
        if (it != path_.cend()) return AddStatus::AlreadyAdded;
        
        path_.emplace_back(make_tuple(node, distance_from_last_node));
        return AddStatus::Success;
    }

    template <typename NodeDistanceType>
    typename HamiltonianPath<NodeDistanceType>::NodeWeakPtr 
        HamiltonianPath<NodeDistanceType>::TryGetNode(string name) const
    {
        auto it = find_if(path_.cbegin(), path_.cend(), [&name](const auto& node_tup)
        {
            if (get<0>(node_tup).expired()) return false;
            return name == get<0>(node_tup).lock()->Name();
        });
        if (it != path_.cend()) 
            return get<0>(*it);
        return NodeWeakPtr{ };
    }

    template <typename NodeDistanceType>
    NodeDistanceType HamiltonianPath<NodeDistanceType>::CompleteDistance() const
    {
        NodeDistanceType distance{};
        for (const auto& node_tup: path_)
            distance += get<1>(node_tup);
        return distance;
    }

    template <typename NodeDistanceType>
    bool HamiltonianPath<NodeDistanceType>::IsValid() const
    {
        for (const auto& node_tup: path_)
            if (get<0>(node_tup).expired()) return false;
        return true;
    }

    template <typename NodeDistanceType>
    typename list<tuple<typename HamiltonianPath<NodeDistanceType>::NodeWeakPtr, NodeDistanceType>>::iterator
        HamiltonianPath<NodeDistanceType>::begin()
    {
        return path_.begin();
    }

    template <typename NodeDistanceType>
    typename list<tuple<typename HamiltonianPath<NodeDistanceType>::NodeWeakPtr, NodeDistanceType>>::iterator
        HamiltonianPath<NodeDistanceType>::end()
    {
        return path_.end();
    }

    template <typename NodeDistanceType>
    typename list<tuple<typename HamiltonianPath<NodeDistanceType>::NodeWeakPtr, NodeDistanceType>>::const_iterator
        HamiltonianPath<NodeDistanceType>::cbegin()
    {
        return path_.cbegin();
    }

    template <typename NodeDistanceType>
    typename list<tuple<typename HamiltonianPath<NodeDistanceType>::NodeWeakPtr, NodeDistanceType>>::const_iterator
        HamiltonianPath<NodeDistanceType>::cend()
    {
        return path_.cend();
    }
}
