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
		friend class depth_iterator;
		friend class width_iterator;

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
	class iterator
	{
	protected:
		class items
		{
			NodeType _value;
			items *_next;
		public:
			items(NodeType val)
			{
				_value = val;
				_next = nullptr;
			}

			items(const items& i)
			{
				_value = i._value;
				_next = i._next;
			}

			items *get_next()
			{
				return _next;
			}

			void set_next(items *i)
			{
				_next = i;
			}

			bool next_is_not_null() const
			{
				return _next;
			}

			NodeType get_val()
			{
				return _value;
			}
		};
		items *_head;
		items *_ptr;
		void insert(NodeType val)
		{
			items *p = _head;
			items *i = new items(val);
			if (p)
			{
				while (p->next_is_not_null())
				{
					p = p->get_next();
				}
				p->set_next(i);
			}
			else
			{
				_head = i;
				_ptr = _head;
			}
		}

	public:
		iterator(items *head, items *ptr)
		{
			_head = head;
			_ptr = ptr;
		}

		iterator() : _head(nullptr)
		{
			_ptr = _head;
		}

		iterator(const iterator& i)
		{
			if (i._head)
			{
				_head = new items(i._head->get_val());
				items *it = i._head->get_next();
				items *nh = _head;
				while (it)
				{
					nh->set_next(new items(it->get_val()));
					it = it->get_next();
					nh = nh->get_next();
				}
			}

			if (i._ptr)
			{
				_ptr = new items(i._ptr->get_val());
				items *it = i._ptr->get_next();
				items *nh = _ptr;
				while (it)
				{
					nh->set_next(new items(it->get_val()));
					it = it->get_next();
					nh = nh->get_next();
				}
			}
		}

		bool has_next() const
		{
			return _ptr;
		}


		virtual iterator operator ++(int)
		{
			iterator tmp(*this);

			_ptr = _ptr->get_next();

			return tmp;
		}


		NodeType get_val()
		{
			return _ptr->get_val();
		}

		virtual ~iterator()
		{
			items *p = _head;
			if (p)
			{
				while (p->next_is_not_null())
				{
					items * d = p->get_next();
					delete p;
					p = d;
				}
			}
			_head = nullptr;
		}
	};

	class width_iterator : public iterator
	{
		class queue
		{
			struct item
			{
				node *_nd;
				item *_next;
			};

			item *_head;
			item *_tail;

		public:
			queue() : _head(nullptr), _tail(nullptr)
			{

			}

			bool not_empty() const
			{
				return _head;
			}

			void enqueue(node *nd)
			{
				item *i = new item();
				if (!_head)
				{
					i->_next = nullptr;
					i->_nd = nd;
					_head = i;
					_tail = i;
				}
				else
				{
					i->_next = nullptr;
					i->_nd = nd;
					_tail->_next = i;
					_tail = _tail->_next;
				}
			}

			node *dequeue()
			{
				node *nd = _head->_nd;
				if (_head == _tail)
				{
					_head = nullptr;
					_tail = nullptr;
				}
				else
					_head = _head->_next;
				return nd;
			}

			~queue()
			{
				while (_head)
				{
					delete dequeue();
				}
			}
		};

		void generate_iterator(node *head)
		{
			queue _q = queue();
			_q.enqueue(head);
			while (_q.not_empty())
			{
				node *nd = _q.dequeue();
				width_iterator::insert(nd->_data);
				if (nd->_left)
					_q.enqueue(nd->_left);
				if (nd->_right)
					_q.enqueue(nd->_right);
			}
		}

	public:
		explicit width_iterator(node *head)
		{
			generate_iterator(head);
		}

		width_iterator(const width_iterator& wi)
		{
			iterator::_head = wi._head;
			iterator::_ptr = wi._ptr;
		}
	};

	class depth_iterator : public iterator
	{
		void generate_iterator(node *nd)
		{
			if (nd)
			{
				iterator::insert(nd->_data);
				generate_iterator(nd->_left);
				generate_iterator(nd->_right);
			}
		}

	public:
		depth_iterator(node *head)
		{
			depth_iterator::generate_iterator(head);
		}
	};

private:
	node * _head;
	typedef void(proc(node*));

	void pre_order(node *nd, const proc prc)
	{
		if (nd)
		{
			prc(nd);
			pre_order(nd->_left, prc);
			pre_order(nd->_right, prc);
		}
	}
	void in_order(node *nd, const proc prc)
	{
		if (nd)
		{
			in_order(nd->_left, prc);
			prc(nd);
			in_order(nd->_right, prc);
		}
	}
	void post_order(node *nd, const proc prc)
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

	width_iterator width()
	{
		return width_iterator(_head);
	}

	depth_iterator depth()
	{
		return depth_iterator(_head);
	}
	~tree()
	{
		finalize(_head);
	}
};
