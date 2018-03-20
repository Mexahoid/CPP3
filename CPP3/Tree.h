#pragma once


template <class NodeType> class tree
{
public:
	class tree_exception
	{
		friend class tree;
		enum type
		{
			RIGHT_NOT_EMPTY,
			LEFT_NOT_EMPTY,
			HEAD_NOT_EMPTY,
			PROC_BAD_ARGS
		};
		type _t;

		explicit tree_exception(const type ex)
		{
			_t = ex;
		}
	public:
		const char* get_message() const
		{
			switch (_t) {
			case RIGHT_NOT_EMPTY:
				return "Cannot add new node to the right. Right is not empty.";
			case LEFT_NOT_EMPTY:
				return "Cannot add new node to the left. Left is not empty.";
			case HEAD_NOT_EMPTY:
				return "Head is not null. Cannot pass null-pointer.";
			case PROC_BAD_ARGS:
				return "Bad argument 'order': 0 - pre-order, 1 - in-order, 2 - post-order.";
			default:
				return "Unknown exception.";
			}
		}
	};
	class node
	{
		friend class tree;
		NodeType _data;
		node *_left, *_right;
		explicit node(NodeType data) : _left(nullptr), _right(nullptr)
		{
			_data = data;
		}
	public:
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
	typedef void(proc(node*));

	void pre_order(node *nd, proc prc)
	{
		if (nd)
		{
			prc(nd);
			pre_order(nd->_left, prc);
			pre_order(nd->_right, prc);
		}
	}
	void in_order(node *nd, proc prc)
	{
		if (nd)
		{
			in_order(nd->_left, prc);
			prc(nd);
			in_order(nd->_right, prc);
		}
	}
	void post_order(node *nd, proc prc)
	{
		if (nd)
		{
			post_order(nd->_left, prc);
			post_order(nd->_right, prc);
			prc(nd);
		}
	}
	node *find_depth(node *nd, NodeType value)
	{
		if (nd)
		{
			if (nd->_data == value)
			{
				return nd;
			}
			find_depth(nd->_left, value);
			find_depth(nd->_right, value);
		}
		return nullptr;
	}

	void finalize(node *nd)
	{
		if (nd)
		{
			if (nd->_left)
			{
				finalize(nd->_left);
			}
			if (nd->_right)
			{
				finalize(nd->_right);
			}
			delete nd;
		}
	}
public:
	tree() : _head(nullptr)
	{

	}

	bool is_empty()
	{
		return !_head;
	}

	node* get_node(NodeType value, node* nd = nullptr)
	{
		if (!nd)
			return find_depth(_head, value);
		return find_depth(nd, value);
	}

	void insert(NodeType value, const bool left, node *nd = nullptr)
	{
		if (!nd)
		{
			if (_head)
				throw tree_exception(tree_exception::HEAD_NOT_EMPTY);
			_head = new node(value);
		}
		else
		{
			if (left)
			{
				if (nd->_left)
					throw tree_exception(tree_exception::LEFT_NOT_EMPTY);
				nd->_left = new node(value);
			}
			else
			{
				if (nd->_right)
					throw tree_exception(tree_exception::RIGHT_NOT_EMPTY);
				nd->_right = new node(value);
			}
		}
	}

	// Можно как print
	void invoke_procedure(const proc prc, const char order = 0)
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
			throw tree_exception(tree_exception::PROC_BAD_ARGS);
		}
	}

	~tree()
	{
		finalize(_head);
	}
};