#pragma once

#include <vector>
#include <vector>
#include <memory>
#include <regex>

#include "Node.hpp"

namespace tsp
{
    using std::vector;
    using std::vector;
    using std::shared_ptr;
    using std::regex;

    using std::regex_replace;
    using std::make_shared;
    using std::find_if;

    template<typename DistanceType>
    struct Converter
    {
        static DistanceType Convert(string value) { return{}; }
    };

    template<>
    struct Converter<int32_t>
    {
        static int32_t Convert(string value)
        {
            try
            {
                return stoi(value);
            }
            catch(const std::out_of_range&)
            {
                return 0;
            }
            catch (const std::invalid_argument&)
            {
                return 0;
            }
        }
    };

    template<>
    struct Converter<float>
    {
        static float Convert(string value)
        {
            try
            {
                return stof(value);
            }
            catch (const std::out_of_range&)
            {
                return 0.f;
            }
            catch (const std::invalid_argument&)
            {
                return 0.f;
            }
        }
    };

    template<typename DistanceType>
    class NodeContainer
    {
        using DistancedNode = Node<DistanceType>;
        using NodePtr = shared_ptr<DistancedNode>;
        using NodeWeakPtr = weak_ptr<DistancedNode>;

    public:
        explicit NodeContainer(vector<vector<string>> nodes);
        NodeContainer(const NodeContainer&) = delete;
        NodeContainer& operator=(const NodeContainer&) = delete;
        NodeContainer(NodeContainer&&) = default;
        NodeContainer& operator=(NodeContainer&&) = default;
        ~NodeContainer() = default;

        typename vector<NodePtr>::iterator begin();
        typename vector<NodePtr>::iterator end();

        typename vector<NodePtr>::const_iterator cbegin() const;
        typename vector<NodePtr>::const_iterator cend() const;

        bool IsFullConnected() const;
        size_t NodesCount() const;
        const vector<NodePtr>& GetNodes() const;
        const vector<vector<string>>& GetRawNodes() const;

        NodeWeakPtr FindNode(string name) const;

    private:
        const char none_symbol = 'x';
        const regex num_regex_ {"[^0-9.]"};

        vector<vector<string>> raw_nodes_;
        vector<NodePtr> nodes_;

        void Fill();
    };

    template <typename DistanceType>
    NodeContainer<DistanceType>::NodeContainer(vector<vector<string>> nodes) :
        raw_nodes_(nodes)
    {
        Fill();
    }

    template <typename DistanceType>
    typename vector<typename NodeContainer<DistanceType>::NodePtr>::iterator
        NodeContainer<DistanceType>::begin()
    {
        return nodes_.begin();
    }

    template <typename DistanceType>
    typename vector<typename NodeContainer<DistanceType>::NodePtr>::iterator
        NodeContainer<DistanceType>::end()
    {
        return nodes_.end();
    }

    template <typename DistanceType>
    typename vector<typename NodeContainer<DistanceType>::NodePtr>::const_iterator
        NodeContainer<DistanceType>::cbegin() const
    {
        return nodes_.cbegin();
    }

    template <typename DistanceType>
    typename vector<typename NodeContainer<DistanceType>::NodePtr>::const_iterator
        NodeContainer<DistanceType>::cend() const
    {
        return nodes_.cend();
    }

    template <typename DistanceType>
    bool NodeContainer<DistanceType>::IsFullConnected() const
    {
        for (const auto& node : nodes_)
            if (node->NodesCount() != NodesCount() - 1)
                return false;
        return true;
    }

    template <typename DistanceType>
    size_t NodeContainer<DistanceType>::NodesCount() const
    {
        return nodes_.size();
    }

    template <typename DistanceType>
    const vector<typename NodeContainer<DistanceType>::NodePtr>& 
        NodeContainer<DistanceType>::GetNodes() const
    {
        return nodes_;
    }

    template <typename DistanceType>
    const vector<vector<string>>& NodeContainer<DistanceType>::GetRawNodes() const
    {
        return raw_nodes_;
    }

    template <typename DistanceType>
    typename NodeContainer<DistanceType>::NodeWeakPtr 
        NodeContainer<DistanceType>::FindNode(string name) const
    {
        auto iter = find_if(nodes_.cbegin(), 
                            nodes_.cend(), 
                            [name](auto& node) { return name == node->Name(); });
        if (iter != nodes_.cend())
            return NodeWeakPtr{ *iter };
        return NodeWeakPtr{ };
    }

    template <typename DistanceType>
    void NodeContainer<DistanceType>::Fill()
    {
        for (const auto& values: raw_nodes_)
            nodes_.emplace_back(make_shared<DistancedNode>(values[0]));

        for (auto& node: nodes_)
        {
            for (const auto& values : raw_nodes_)
            {
                if (node->Name() != values[0]) continue;

                for (auto i = 1; i < values.size(); ++i)
                {
                    auto str_result = regex_replace(values[i], num_regex_, "");
                    if (str_result == "" || nodes_.size() < i) continue;
                    node->AddNode(NodeWeakPtr{ nodes_[i - 1] }, Converter<DistanceType>::Convert(str_result));
                }
            }
        }
    }
}
