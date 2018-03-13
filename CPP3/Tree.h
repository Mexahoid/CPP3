#pragma once

template <class NodeType> class Tree
{
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

		NodeType get_data()
		{
			return _data;
		}

		void set_data(NodeType data)
		{
			_data = data;
		}
	};

	typedef void(proc(NodeType));

private:
	node *_head;

	void pre_order(node *nd, proc prc)
	{
		if(nd)
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
		if(nd)
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
	Tree() : _head(0)
	{

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

	NodeType find_depth(node *nd, NodeType value)
	{
		if(nd)
		{
			if(nd->get_data() == value)
			{
				return nd->get_data();
			}
			else
			{
				find_depth(nd->get_left(), value);
				find_depth(nd->get_right(), value);
			}
		}
		return nullptr;
	}

	NodeType find_breadth(node *nd ,NodeType value)
	{
		if (true)
		{

		}
		return nullptr;
	}

	void print(proc prc, const char order = 0)
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