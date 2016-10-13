#pragma once

#include <memory>

namespace tsp
{
	using std::weak_ptr;
	using std::shared_ptr;
	using std::string;
	using std::ostream;

	template<typename DistanceValueType>
	class Node
	{
		using NodePtr = shared_ptr<Node<DistanceValueType>>;
		using NodeWeakPtr = weak_ptr<Node<DistanceValueType>>;

	public:
		explicit Node(string name, DistanceValueType x, DistanceValueType y);
		~Node() = default;

		bool operator==(const Node<DistanceValueType>& rhs) const;
		bool operator!=(const Node<DistanceValueType>& rhs) const;

		friend ostream& operator<<(ostream& lhs, const Node<DistanceValueType>& rhs)
		{
			lhs << "["
				<< rhs.name_
				<< "]:\t"
				<< "X: "
				<< rhs.x_
				<< '\t'
				<< "Y: "
				<< rhs.y_
				<< '\n';
			return lhs;
		}
		friend ostream& operator<<(ostream& lhs, NodeWeakPtr rhs)
		{
			if (rhs.expired()) return lhs;

			lhs << "["
				<< rhs.lock()->name_
				<< "]:\t"
				<< "X: "
				<< rhs.lock()->x_
				<< '\t'
				<< "Y: "
				<< rhs.lock()->y_
				<< '\n';
			return lhs;
		}
		friend ostream& operator<<(ostream& lhs, NodePtr rhs)
		{
			lhs << "["
				<< rhs->name_
				<< "]:\t"
				<< "X: "
				<< rhs->x_
				<< '\t'
				<< "Y: "
				<< rhs->y_
				<< '\n';
			return lhs;
		}

		const string& Name() const;
		const DistanceValueType& X() const;
		const DistanceValueType& Y() const;
		void SetX(DistanceValueType);
		void SetY(DistanceValueType);

	private:
		string name_;
		DistanceValueType x_;
		DistanceValueType y_;
	};


	template <typename DistanceValueType>
	Node<DistanceValueType>::Node(string name, DistanceValueType x, DistanceValueType y) :
		name_(name),
		x_(x),
		y_(y)
	{
	}

	template <typename DistanceValueType>
	bool Node<DistanceValueType>::operator==(const Node<DistanceValueType>& rhs) const
	{
		return rhs.name_ == name_ && rhs.x_ == x_ && rhs.y_ == y_;
	}

	template <typename DistanceValueType>
	bool Node<DistanceValueType>::operator!=(const Node<DistanceValueType>& rhs) const
	{
		return rhs.name_ != name_ || rhs.x_ != x_ || rhs.y_ != y_;
	}

	template <typename DistanceValueType>
	const string& Node<DistanceValueType>::Name() const
	{
		return name_;
	}

	template <typename DistanceValueType>
	const DistanceValueType& Node<DistanceValueType>::X() const
	{
		return x_;
	}

	template <typename DistanceValueType>
	const DistanceValueType& Node<DistanceValueType>::Y() const
	{
		return y_;
	}

	template <typename DistanceValueType>
	void Node<DistanceValueType>::SetX(DistanceValueType x)
	{
		x_ = x;
	}

	template <typename DistanceValueType>
	void Node<DistanceValueType>::SetY(DistanceValueType y)
	{
		y_ = y;
	}
}
