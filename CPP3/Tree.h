#pragma once

template <class NodeType> class Tree
{
public:
	class node
	{
		NodeType _data;
		node *_left, *_right;

	public:
		explicit node(NodeType data) : _left(nullptr), _right(nullptr)
		{
			_data = data;
		}

		node *get_left()
		{
			return _left;
		}

		void set_left(node *left)
		{
			_left = left;
		}

		node *get_right()
		{
			return _right;
		}

		void set_right(node *right)
		{
			_right = right;
		}

		void connect_new_data(NodeType data, const bool left)
		{
			if (left)
			{
				if (_left)
					throw "Right node is not free.";
				_left = new node(data);
			}
			else
			{

				if (_right)
					throw "Right node is not free.";
				_right = new node(data);
			}
		}

		NodeType get_data()
		{
			return _data;
		}

		void set_data(NodeType data)
		{
			_data = data;
		}
	};


private:
	node * _head;
	typedef void(proc(NodeType));

	void pre_order(node *nd, proc prc)
	{
		if (nd)
		{
			prc(nd->get_data());
			pre_order(nd->get_left(), prc);
			pre_order(nd->get_right(), prc);
		}
	}

	void in_order(node *nd, proc prc)
	{
		if (nd)
		{
			in_order(nd->get_left(), prc);
			prc(nd->get_data());
			in_order(nd->get_right(), prc);
		}
	}

	void post_order(node *nd, proc prc)
	{
		if (nd)
		{
			post_order(nd->get_left(), prc);
			post_order(nd->get_right(), prc);
			prc(nd->get_data());
		}
	}

	void finalize(node *nd)
	{
		if (nd)
		{
			if (nd->get_left())
			{
				finalize(nd->get_left());
			}
			if (nd->get_right())
			{
				finalize(nd->get_right());
			}
			delete nd;
		}
	}
public:
	Tree() : _head(nullptr)
	{

	}

	bool is_empty()
	{
		return !_head;
	}

	void find_node_and_connect_new(NodeType node_value, NodeType new_data, bool left)
	{
		node *nd = find_depth(_head, node_value);
		if (!nd)
			throw "No node found with such value.";
		nd->connect_new_data(new_data, left);
	}

	void insert(NodeType data)
	{
		node *nd = new node(data);
		if (!_head)
			_head = nd;
		else
		{
			if (_head->get_data() > data)
				nd->set_right(_head);
			else
				nd->set_left(_head);
			_head = nd;
		}
	}

	node *find_depth(node *nd, NodeType value)
	{
		if (nd)
		{
			if (nd->get_data() == value)
			{
				return nd;
			}
			find_depth(nd->get_left(), value);
			find_depth(nd->get_right(), value);
		}
		return nullptr;
	}

	NodeType find_breadth(node *nd, NodeType value)
	{
		if (true)
		{

		}
		return nullptr;
	}

	void invoke_procedure(proc prc, const char order = 0)
	{
		node *nd = _head;
		switch (order)
		{
		case 0:
			pre_order(nd, prc);
			break;
		case 1:
			in_order(nd, prc);
			break;
		case 2:
			post_order(nd, prc);
			break;
		default:
			throw "Bad argument 'order': 0 - pre-order, 1 - in-order, 2 - post-order.";
		}
	}

	~Tree()
	{
		finalize(_head);
	}
};