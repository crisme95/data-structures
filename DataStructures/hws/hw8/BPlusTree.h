/* ASSUMPTIONS:
1. When a node must be split and has an odd number of keys, the extra key will go to the new right-hand node.
2. There will never be a duplicate key passed to insert.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#ifndef DS_BPLUSTREE
#define DS_BPLUSTREE

///////////////////////////////////////////////////////////////////////////////
//DO NOT CHANGE THIS CODE
///////////////////////////////////////////////////////////////////////////////

//Do not implement the class here, this is a forward declaration. Implement at
//the bottom of the .h file
template <class T>
class BPlusTree;

template <class T>
class BPlusTreeNode
{
public:
	BPlusTreeNode() : parent(NULL){};
	bool is_leaf();
	bool contains(const T &key);

	//For grading only. This is bad practice to have, because
	//it exposes a private member variable.
	BPlusTreeNode *get_parent() { return parent; }

	//We need this to let BPlusTree access private members
	friend class BPlusTree<T>;

private:
	bool contains(const T &key, std::size_t low, std::size_t high);
	std::vector<T> keys;
	std::vector<BPlusTreeNode *> children;
	BPlusTreeNode *parent;
};

template <class T>
bool BPlusTreeNode<T>::is_leaf()
{
	for (unsigned int i = 0; i < children.size(); i++)
	{
		if (children[i])
		{
			return false;
		}
	}
	return true;
}

template <class T>
bool BPlusTreeNode<T>::contains(const T &key)
{
	return contains(key, 0, keys.size() - 1);
}

//Private method takes advantage of the fact keys are sorted
template <class T>
bool BPlusTreeNode<T>::contains(const T &key, std::size_t low, std::size_t high)
{
	if (low > high)
	{
		return false;
	}
	if (low == high)
	{
		// std::cout << key << " " << keys[low] << std::endl;
		return key == keys[low];
	}
	std::size_t mid = (low + high) / 2;
	if (key <= keys[mid])
	{
		return contains(key, 0, mid);
	}
	else
	{
		return contains(key, mid + 1, high);
	}
}

///////////////////////////////////////////////////////////////////////////////////////
//Your BPlusTree implementation goes below this point.
///////////////////////////////////////////////////////////////////////////////////////

template <class T>
class BPlusTree
{
public:
	// constructor, copy constructor & operator, destructor
	BPlusTree(unsigned int i) : root_(NULL), max_size_(i) {}
	BPlusTree(const BPlusTree<T> &old) : max_size_(old.max_size_)
	{
		root_ = this->copy_tree(old.root_, NULL);
	}
	~BPlusTree()
	{
		this->destroy_tree(root_);
		root_ = NULL;
	}

	BPlusTree &operator=(const BPlusTree<T> &old)
	{
		if (&old != this)
		{
			this->destroy_tree(root_);
			root_ = this->copy_tree(old.root_, NULL);
			max_size_ = old.max_size_;
		}
		return *this;
	}

	// member functions
	BPlusTreeNode<T> *find(const T &key_value);
	void insert(const T &key_value);

	// member print functions
	void print_BFS(std::ofstream &ostr) { print_BFS(ostr, root_); }
	void print_sideways(std::ofstream &ostr) { print_sideways(ostr, root_); }
	void print_BFS_pretty(std::ofstream &ostr);

private:
	BPlusTreeNode<T> *root_; // stores the root of the BPlusTree
	unsigned int max_size_;	 // stores the max amount of elements for the BPlusTree

	// copies the keys and children for each node in the BPlusTree
	BPlusTreeNode<T> *copy_tree(BPlusTreeNode<T> *old_root, BPlusTreeNode<T> *the_parent)
	{
		if (old_root == NULL)
		{
			return NULL;
		}
		BPlusTreeNode<T> *current = new BPlusTreeNode<T>();
		current->keys = old_root->keys;
		current->children = old_root->children;
		current->parent = the_parent;
		return current;
	}

	// goes through each child for each node in the BPlusTree and deletes it
	void destroy_tree(BPlusTreeNode<T> *p)
	{
		if (p == NULL)
		{
			return;
		}
		for (unsigned int i = 0; i < p->children.size(); i++)
		{
			delete p->children[i];
		}
		delete p;
	}

	// prints out each node breadth first
	void print_BFS(std::ofstream &ostr, BPlusTreeNode<T> *p)
	{
		if (p != NULL)
		{
			for (unsigned int i = 0; i < p->keys.size(); i++)
			{
				ostr << p->keys[i] << " ";
			}
			ostr << '\n';

			if (p->is_leaf() == false)
			{
				for (unsigned int i = 0; i < p->children.size(); i++)
				{
					print_BFS(ostr, p->children[i]);
				}
			}
		}
		else
		{
			ostr << "Tree is empty." << std::endl;
		}
	}

	// prints out the tree sideways
	void print_sideways(std::ofstream &ostr, BPlusTreeNode<T> *p)
	{
		if (p != NULL)
		{
		}
		else
		{
			ostr << "Tree is empty." << std::endl;
		}
	}
};

// goes through each node to find the key_value and returns a pointer ot the node
template <class T>
BPlusTreeNode<T> *BPlusTree<T>::find(const T &key_value)
{
	if (root_ == NULL)
	{
		// std::cout << "Tree is empty." << std::endl;
		return NULL;
	}
	else
	{
		BPlusTreeNode<T> *current = root_;

		// goes down until we reach the leaf where the key_value could be
		while (current->is_leaf() == false)
		{
			for (unsigned int i = 0; i < current->keys.size(); i++)
			{
				// if key_value is less than current key, go to the child node
				if (key_value < current->keys[i] && current->children.size() > 0)
				{
					current = current->children[i];
					break;
				}

				// if key_value is greater than all the keys, go to last child node
				if (i == current->keys.size() - 1 && current->children.size() > 0)
				{
					current = current->children.back();
					break;
				}
			}
		}

		// regardless of if we find the key_value or not, we return a pointer to a node
		return current;
	}
}

// searches through the tree to find where the key_value should be inserted
template <class T>
void BPlusTree<T>::insert(const T &key_value)
{
	// initialize the tree if it was previously empty
	if (root_ == NULL)
	{
		root_ = new BPlusTreeNode<T>();
		root_->keys.push_back(key_value);
	}
	else
	{
		BPlusTreeNode<T> *current = root_;
		//BPlusTreeNode<T> *tmp_parent;
		while (current->is_leaf() == false)
		{
			// keeps track of parent to current
			//tmp_parent = current;
			for (unsigned int i = 0; i < current->keys.size(); i++)
			{
				// if key_value is less than current key, go to the child node
				if (key_value < current->keys[i] && current->children.size() > 0)
				{
					current = current->children[i];
					break;
				}

				// if key_value is greater than all the keys, go to last child node
				if (i == current->keys.size() - 1 && current->children.size() > 0)
				{
					current = current->children.back();
					break;
				}
			}
		}

		// checks if adding the key_value meets our max size restriction
		if (current->keys.size() + 1 < max_size_)
		{
			current->keys.push_back(key_value);
			std::sort(current->keys.begin(), current->keys.end()); // sorts the keys for the contain function
		}
	}
}

#endif
