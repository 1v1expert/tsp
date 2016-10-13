#pragma once

#include <memory>
#include <vector>
#include <string>

#include "NodeContainer.hpp"
#include "Converter.hpp"

namespace tsp
{
	using std::istream;
	using std::string;
	using std::unique_ptr;
	using std::vector;
	using std::stringstream;
	using std::regex;

	using std::make_unique;
	using std::getline;
	using std::regex_replace;

	template<typename DistanceType>
	class Node;

	template<typename DistanceType>
	class NodeFactory
	{
		using NodeContainerPtr = unique_ptr<NodeContainer<DistanceType>>;

	public:
		static NodeContainerPtr CreateFromStream(istream& stream);
		static const vector<vector<string>>& GetRawNodes();

	private:
		static regex num_regex_;
		static vector<vector<string>> raw_nodes_;
		static char separator_;
	};

	template<typename DistanceType>
	regex NodeFactory<DistanceType>::num_regex_ ("[^0-9.]");

	template<typename DistanceType>
	vector<vector<string>> NodeFactory<DistanceType>::raw_nodes_;

	template<typename DistanceType>
	char NodeFactory<DistanceType>::separator_ = ';';

	template <typename DistanceType>
	const vector<vector<string>>& NodeFactory<DistanceType>::GetRawNodes()
	{
		return raw_nodes_;
	}

	template <typename DistanceType>
	typename NodeFactory<DistanceType>::NodeContainerPtr
		NodeFactory<DistanceType>::CreateFromStream(istream& stream)
	{
		raw_nodes_.clear();
		string line;
		while (getline(stream, line, '\n'))
		{
			stringstream str_stream(line);
			vector<string> values;
			string value;
			while (getline(str_stream, value, separator_))
				values.push_back(value);
			raw_nodes_.push_back(values);
		}

		auto nodes = make_unique<NodeContainer<DistanceType>>();

		for (const auto& values : raw_nodes_)
		{
			if (values.size() != 3) continue;

			auto str_x = regex_replace(values[1], num_regex_, "");
			auto str_y = regex_replace(values[2], num_regex_, "");

			if (str_x == "" || str_y == "") continue;

			nodes->AddNode(make_shared<Node<DistanceType>>(values[0],
											 Converter<DistanceType>::Convert(str_x),
											 Converter<DistanceType>::Convert(str_y)));
		}

		return move(nodes);
	}
}
