#pragma once

#include <vector>
#include <memory>
#include <regex>

#include "Node.hpp"
#include "Distance.hpp"

namespace tsp
{
	using std::vector;
	using std::shared_ptr;

	using std::make_shared;
	using std::find_if;

	template<typename DistanceType>
	class NodeContainer
	{
		using DistancedNode = Node<DistanceType>;
		using NodePtr = shared_ptr<DistancedNode>;
		using NodeWeakPtr = weak_ptr<DistancedNode>;

	public:
		NodeContainer();
		NodeContainer(NodeContainer& lhs);
		NodeContainer& operator=(NodeContainer& lhs);
		~NodeContainer() = default;

		friend ostream& operator<<(ostream& lhs, const NodeContainer<DistanceType>& rhs)
		{
			if (rhs.nodes_.size() <= 1) return lhs;

			for (auto i = 0; i < rhs.nodes_.size() - 1; ++i)
			{
				auto distance = Distance<DistancedNode>::Count(*rhs.nodes_[i], 
															   *rhs.nodes_[i + 1]);
				lhs << rhs.nodes_[i]->Name()
					<< " --"
					<< distance
					<< "-> ";
			}
			lhs << rhs.nodes_[rhs.nodes_.size() - 1]->Name();

			lhs << "\nTotal distance: "
				<< rhs.CompleteDistance();

			return lhs;
		}

		typename vector<NodePtr>::iterator begin();
		typename vector<NodePtr>::iterator end();

		typename vector<NodePtr>::const_iterator cbegin() const;
		typename vector<NodePtr>::const_iterator cend() const;

		NodePtr& operator[](size_t position);
		const NodePtr& operator[](size_t position) const;

		float CompleteDistance() const;
		size_t NodesCount() const;
		void AddNode(const NodePtr&);
		const vector<NodePtr>& GetNodes() const;
		NodeWeakPtr FindNode(string name) const;

	private:
		vector<NodePtr> nodes_;
	};

	template <typename DistanceType>
	NodeContainer<DistanceType>::NodeContainer()
	{
	}

	template <typename DistanceType>
	NodeContainer<DistanceType>::NodeContainer(NodeContainer& lhs)
	{
		for (auto& n: lhs)
		{
			this->nodes_.emplace_back(make_shared<Node<DistanceType>>(*n));
		}
	}

	template <typename DistanceType>
	NodeContainer<DistanceType>& NodeContainer<DistanceType>::operator=(NodeContainer& lhs)
	{
		for (auto& n : lhs)
		{
			this->nodes_.emplace_back(make_shared<Node<DistanceType>>(*n));
		}
		return *this;
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
	typename NodeContainer<DistanceType>::NodePtr& 
		NodeContainer<DistanceType>::operator[](size_t position)
	{
		return nodes_[position];
	}

	template <typename DistanceType>
	const typename NodeContainer<DistanceType>::NodePtr& 
		NodeContainer<DistanceType>::operator[](size_t position) const
	{
		return nodes_[position];
	}

	template <typename DistanceType>
	float NodeContainer<DistanceType>::CompleteDistance() const
	{
		float all_distance = 0;
		for (auto i = 0; i < nodes_.size() - 1; ++i)
		{
			all_distance += Distance<DistancedNode>::Count(*nodes_[i],
				*nodes_[i + 1]);
		}
		return all_distance;
	}

	template <typename DistanceType>
	size_t NodeContainer<DistanceType>::NodesCount() const
	{
		return nodes_.size();
	}

	template <typename DistanceType>
	void NodeContainer<DistanceType>::AddNode(const NodePtr& node)
	{
		nodes_.emplace_back(node);
	}

	template <typename DistanceType>
	const vector<typename NodeContainer<DistanceType>::NodePtr>&
		NodeContainer<DistanceType>::GetNodes() const
	{
		return nodes_;
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
		return NodeWeakPtr{};
	}
}
