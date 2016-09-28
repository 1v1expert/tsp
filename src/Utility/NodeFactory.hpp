#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "NodeContainer.hpp"

namespace tsp
{
    using std::cin;

    using std::istream;
    using std::string;
    using std::unique_ptr;
    using std::vector;

    using std::make_unique;
    using std::getline;

    template<typename DistanceType>
    class NodeFactory
    {
        using NodeContainerPtr = unique_ptr<NodeContainer<DistanceType>>;

    public:
        static NodeContainerPtr Create(istream& stream);

    private:
        static char separator_;
    };


    template<typename DistanceType>
    char NodeFactory<DistanceType>::separator_ = ';';

    
    template <typename DistanceType>
    typename NodeFactory<DistanceType>::NodeContainerPtr 
        NodeFactory<DistanceType>::Create(istream& stream)
    {
        vector<vector<string>> raw_nodes;

        string line;
        while (getline(stream, line, '\n'))
        {
            stringstream str_stream(line);
            vector<string> values;
            string value;
            while (getline(str_stream, value, separator_))
                values.push_back(value);
            raw_nodes.push_back(values);
        }

        return make_unique<NodeContainer<DistanceType>>(raw_nodes);
    }
}
