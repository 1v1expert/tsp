#pragma once

#include <memory>
#include <tuple>
#include <list>
#include <sstream>

namespace tsp
{
	using std::list;
	using std::weak_ptr;
    using std::shared_ptr;
	using std::tuple;
	using std::string;
	using std::ostream;
	using std::stringstream;

	using std::get;
	using std::make_tuple;

	template<typename DistanceValueType>
	class Node
	{
        using NodePtr = shared_ptr<Node<DistanceValueType>>;
        using NodeWeakPtr = weak_ptr<Node<DistanceValueType>>;

	public:
		explicit Node(string name);
		Node(const Node<DistanceValueType>&) = delete;
		Node<DistanceValueType>& operator=(const Node<DistanceValueType>&) = delete;
		Node(Node<DistanceValueType>&&) noexcept = default ;
		Node<DistanceValueType>& operator=(Node<DistanceValueType>&&) noexcept = default;
		~Node() = default;

		bool operator==(const Node<DistanceValueType>& rhs) const;
		bool operator!=(const Node<DistanceValueType>& rhs) const;

        friend ostream& operator<<(ostream& lhs, const Node<DistanceValueType>& rhs)
        {
            stringstream stream;
            stream << "["
                << rhs.name_
                << "]:\t";
            for (const auto& list_tuple : rhs.linked_nodes_)
            {
                if (!get<0>(list_tuple).expired())
                    stream << "\t ["
                    << get<0>(list_tuple).lock()->Name()
                    << ": "
                    << get<1>(list_tuple)
                    << "]";
                else
                    stream << "\t [xxx: "
                    << get<1>(list_tuple)
                    << "]";
            }
            return lhs << stream.str() << '\n';
        }
        friend ostream& operator<<(ostream& lhs, NodeWeakPtr rhs)
        {
            if (rhs.expired()) return lhs;

            stringstream stream;
            stream << "["
                << rhs.lock()->Name()
                << "]:\t";
            for (const auto& list_tuple : rhs.lock()->LinkedNodes())
            {
                if (!get<0>(list_tuple).expired())
                    stream << "\t ["
                    << get<0>(list_tuple).lock()->Name()
                    << ": "
                    << get<1>(list_tuple)
                    << "]";
                else
                    stream << "\t [xxx: "
                    << get<1>(list_tuple)
                    << "]";
            }
            return lhs << stream.str() << '\n';
        }
        friend ostream& operator<<(ostream& lhs, NodePtr rhs)
        {
            stringstream stream;
            stream << "["
                << rhs->Name()
                << "]:\t";
            for (const auto& list_tuple : rhs->LinkedNodes())
            {
                if (!get<0>(list_tuple).expired())
                    stream << "\t ["
                    << get<0>(list_tuple).lock()->Name()
                    << ": "
                    << get<1>(list_tuple)
                    << "]";
                else
                    stream << "\t [xxx: "
                    << get<1>(list_tuple)
                    << "]";
            }
            return lhs << stream.str() << '\n';
        }

        typename list<tuple<NodeWeakPtr, DistanceValueType>>::iterator begin();
        typename list<tuple<NodeWeakPtr, DistanceValueType>>::iterator end();
        typename list<tuple<NodeWeakPtr, DistanceValueType>>::const_iterator cbegin() const;
        typename list<tuple<NodeWeakPtr, DistanceValueType>>::const_iterator cend() const;

	    const string& Name() const;
		const list<tuple<NodeWeakPtr, DistanceValueType>>& LinkedNodes() const;

		void AddNode(NodeWeakPtr node, DistanceValueType distance_to_node);
		void RemoveNode(NodeWeakPtr node);

        void ClearInvalidRefs();
		size_t NodesCount() const;

	private:
		string name_;
		list<tuple<NodeWeakPtr, DistanceValueType>> linked_nodes_;
	};


	template <typename DistanceValueType>
	Node<DistanceValueType>::Node(string name) :
		name_(name)
	{
	}

	template <typename DistanceValueType>
	bool Node<DistanceValueType>::operator==(const Node<DistanceValueType>& rhs) const
	{
		return rhs.name_ == name_;
	}

	template <typename DistanceValueType>
	bool Node<DistanceValueType>::operator!=(const Node<DistanceValueType>& rhs) const
	{
		return rhs.name_ != name_;
	}

    template <typename DistanceValueType>
    typename list<tuple<typename Node<DistanceValueType>::NodeWeakPtr, DistanceValueType>>::iterator 
        Node<DistanceValueType>::begin()
    {
        return linked_nodes_.begin();
    }

    template <typename DistanceValueType>
    typename list<tuple<typename Node<DistanceValueType>::NodeWeakPtr, DistanceValueType>>::iterator 
        Node<DistanceValueType>::end()
    {
        return linked_nodes_.end();
    }

    template <typename DistanceValueType>
    typename list<tuple<typename Node<DistanceValueType>::NodeWeakPtr, DistanceValueType>>::const_iterator 
        Node<DistanceValueType>::cbegin() const
    {
        return linked_nodes_.cbegin();
    }

    template <typename DistanceValueType>
    typename list<tuple<typename Node<DistanceValueType>::NodeWeakPtr, DistanceValueType>>::const_iterator 
        Node<DistanceValueType>::cend() const
    {
        return linked_nodes_.cend();
    }

    template <typename DistanceValueType>
	const string& Node<DistanceValueType>::Name() const
	{
		return name_;
	}

	template <typename DistanceValueType>
	const list<tuple<typename Node<DistanceValueType>::NodeWeakPtr, DistanceValueType>>& 
		Node<DistanceValueType>::LinkedNodes() const
	{
		return linked_nodes_;
	}

	template <typename DistanceValueType>
	void Node<DistanceValueType>::AddNode(NodeWeakPtr node, DistanceValueType distance_to_node)
	{
		linked_nodes_.emplace_back(make_tuple(node, distance_to_node));
	}

	template <typename DistanceValueType>
	void Node<DistanceValueType>::RemoveNode(NodeWeakPtr node)
	{
		linked_nodes_.remove_if([node](const auto& list_tuple)
		{
			if (!node.expired())
				return get<0>(list_tuple).expired() ? true : node.lock() == get<0>(list_tuple).lock();
			return false;
		});
	}

    template <typename DistanceValueType>
    void Node<DistanceValueType>::ClearInvalidRefs()
    {
        linked_nodes_.remove_if([](auto& list_tuple) { return get<0>(list_tuple).expired(); });
    }

    template <typename DistanceValueType>
	size_t Node<DistanceValueType>::NodesCount() const
	{
		return linked_nodes_.size();
	}
}
