#include <iostream>
#include <queue>
#include <stack>

template <typename T>
struct Node 
{

	T value;
	Node* left = nullptr;
	Node* right = nullptr;

	Node(const T& value, Node* left = nullptr, Node* right = nullptr) : value(value), left(left), right(right) {}	
	Node(const Node<T>& other) = delete;
	Node& operator = (const Node<T>& other) = delete;
	~Node() { free(); }

private:

	void free() 
	{

		delete left;
		delete right;
		left = right = nullptr;

	}

};

template <typename T>
class BinarySearchTree 
{
private:

	Node<T>* root = nullptr;

	Node<T>* _insert(Node<T>* current, const T& value);
	bool _contains(const Node<T>* current, const T& value) const;
	Node<T>* _remove(Node<T>* current, const T& value);
	void _dfs(const Node<T>* current) const;

public:

	BinarySearchTree() = default;
	BinarySearchTree(const BinarySearchTree<T>& other) = delete;
	BinarySearchTree<T>& operator=(const BinarySearchTree<T>& other) = delete;
	~BinarySearchTree() { free(); }

	bool contains(const T&) const;
	void insert(const T&);
	void remove(const T&);

	void dfs() const;
	void iterativeDfs() const;
	void bfs() const;

private:

	void free();

};

template <typename T>
void BinarySearchTree<T>::free() 
{

	delete root;

}

template <typename T>
Node<T>* BinarySearchTree<T>::_insert(Node<T>* current, const T& value) 
{

	if (!current) 
	{

		return new Node<T>(value);

	}

	if (current->value < value) 
	{

		current->right = _insert(current->right, value);

	}
	else if (value < current->value) 
	{

		current->left = _insert(current->left, value);

	}

	return current;

}

template <typename T>
bool BinarySearchTree<T>::_contains(const Node<T>* current, const T& value) const 
{

	if (!current) 
	{

		return false;

	}

	if (current->value == value) 
	{

		return true;

	}

	return current->value > value ? contains(current->left, value) : contains(current->right, value);

}

template <typename T>
Node<T>* BinarySearchTree<T>::_remove(Node<T>* current, const T& value)
{

	if (!current) 
	{

		return nullptr;

	}

	if (value < current->value) 
	{

		current->left = _remove(current->left, value);

	}
	else if (current->value < value) 
	{

		current->right = _remove(current->right, value);

	}
	else 
	{

		if (!current->left && !current->right) 
		{

			return nullptr;

		}
		if (!current->left) 
		{

			return current->right;

		}
		if (!current->right) 
		{

			return current->left;

		}

		Node<T>* iter = current->right;

		while (iter->left) 
		{

			iter = iter->left;

		}

		current->value = iter->value;
		current->right = _remove(current->right, current->value);

	}

	return current;

}

template <typename T>
bool BinarySearchTree<T>::contains(const T& value) const 
{

	return _contains(root, value);

}

template <typename T>
void BinarySearchTree<T>::insert(const T& value) 
{

	root = _insert(root, value);

}

template <typename T>
void BinarySearchTree<T>::remove(const T& value) 
{

	root = _remove(root, value);

}

template <typename T>
void BinarySearchTree<T>::_dfs(const Node<T>* current) const 
{

	if (!current) 
	{

		return;

	}

	_dfs(current->left);
	std::cout << current->value << " ";
	_dfs(current->right);

}

template <typename T>
void BinarySearchTree<T>::dfs() const
{

	_dfs(root);

}

template <typename T>
void BinarySearchTree<T>::iterativeDfs() const 
{

	std::stack<Node<T>*> stack;
	Node<T>* current = root;

	while (current != nullptr || !stack.empty()) 
	{

		while (current != nullptr)
		{

			stack.push(current);
			current = current->left;

		}

		current = stack.top();
		stack.pop();
		std::cout << current->value << " ";
		current = current->right;

	}

}

template <typename T>
void BinarySearchTree<T>::bfs() const 
{

	std::queue<Node<T>*> container;
	container.push(root);

	while (!container.empty())
	{

		size_t levelSize = container.size();

		while (levelSize > 0)
		{

			Node<T>* current = container.front();
			container.pop();

			if (current) 
			{

				std::cout << current->value << " ";
				container.push(current->left);
				container.push(current->right);

			}

			levelSize--;

		}

		std::cout << std::endl;

	}

}

