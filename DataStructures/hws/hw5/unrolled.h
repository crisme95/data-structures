#ifndef _unrolled_h_
#define _unrolled_h_
#include <iostream>
#include <cassert>

const int NUM_ELEMENTS_PER_NODE = 6;

// -----------------------------------------------------------------
// NODE CLASS
template <class T>
class Node
{
public:
  Node() : num_elements_(0), next_(NULL), prev_(NULL) {}

  // REPRESENTATION
  T value_[NUM_ELEMENTS_PER_NODE];
  unsigned int num_elements_;
  Node<T> *next_;
  Node<T> *prev_;
};

// A "forward declaration" of this class is needed
template <class T>
class UnrolledLL;

// -----------------------------------------------------------------
// LIST ITERATOR
template <class T>
class list_iterator
{
public:
  // default constructor, copy constructor, assignment operator, & destructor
  list_iterator(Node<T> *p = NULL) : offset_(0), ptr_(p) {}
  // NOTE: the implicit compiler definitions of the copy constructor,
  // assignment operator, and destructor are correct for this class

  // dereferencing operator gives access to the value at the pointer
  T &operator*() { return ptr_->value_[offset_]; }

  // post-increment, e.g., iter++
  list_iterator<T> operator++(int)
  {
    list_iterator<T> temp(*this);
    // If offset reaches last element in array,
    // move ptr to next node
    if (offset_ == ptr_->num_elements_ - 1)
    {

      ptr_ = ptr_->next_;
      offset_ = 0;
    }
    else
    {
      offset_++;
    }

    return temp;
  }

  // post-decrement, e.g., iter--
  list_iterator<T> operator--(int)
  {
    list_iterator<T> temp(*this);

    if (offset_ == 0)
    {
      ptr_ = ptr_->prev_;
      offset_ = ptr_->num_elements_ - 1;
    }
    else
    {
      offset_--;
    }

    return temp;
  }

  // the UnrolledLL class needs access to the private ptr_ member variable
  friend class UnrolledLL<T>;

  // Comparions operators are straightforward
  bool operator==(const list_iterator<T> &r) const
  {
    return ptr_ == r.ptr_;
  }
  bool operator!=(const list_iterator<T> &r) const
  {
    return ptr_ != r.ptr_;
  }

private:
  // REPRESENTATION
  unsigned int offset_;
  Node<T> *ptr_; // ptr to node in the list
};

// -----------------------------------------------------------------
// LIST CLASS DECLARATION
// Note that it explicitly maintains the size of the list.
template <class T>
class UnrolledLL
{
public:
  // default constructor, copy constructor, assignment operator, & destructor
  UnrolledLL() : head_(NULL), tail_(NULL), size_(0) {}
  UnrolledLL(const UnrolledLL<T> &old) { copy_list(old); }
  UnrolledLL &operator=(const UnrolledLL<T> &old);
  ~UnrolledLL() { destroy_list(); }

  typedef list_iterator<T> iterator;

  // simple accessors & modifiers
  unsigned int size() const { return size_; }
  bool empty() const { return head_ == NULL; }
  void clear() { destroy_list(); }

  // read/write access to contents
  const T &front() const { return head_->value_[0]; }
  T &front() { return head_->value_[0]; }
  const T &back() const { return tail_->value_[tail_->num_elements_ - 1]; }
  T &back() { return tail_->value_[tail_->num_elements_ - 1]; }

  // modify the linked list structure
  void push_front(const T &v);
  void pop_front();
  void push_back(const T &v);
  void pop_back();
  void print(std::ostream &out);

  iterator erase(iterator itr);
  iterator insert(iterator itr, const T &v);
  iterator begin() { return iterator(head_); }
  iterator end() { return iterator(NULL); }

private:
  // private helper functions
  void copy_list(const UnrolledLL<T> &old);
  void destroy_list();

  //REPRESENTATION
  Node<T> *head_;
  Node<T> *tail_;
  unsigned int size_;
};

// -----------------------------------------------------------------
// LIST CLASS IMPLEMENTATION
template <class T>
UnrolledLL<T> &UnrolledLL<T>::operator=(const UnrolledLL<T> &old)
{
  // check for self-assignment
  if (&old != this)
  {
    destroy_list();
    copy_list(old);
  }
  return *this;
}

// do these lists look the same (length & contents)?
template <class T>
bool operator==(UnrolledLL<T> &left, UnrolledLL<T> &right)
{
  if (left.size() != right.size())
    return false;
  typename UnrolledLL<T>::iterator left_itr = left.begin();
  typename UnrolledLL<T>::iterator right_itr = right.begin();
  // walk over both lists, looking for a mismatched value
  while (left_itr != left.end())
  {
    if (*left_itr != *right_itr)
      return false;
    left_itr++;
    right_itr++;
  }
  return true;
}

// tests for inequality
template <class T>
bool operator!=(UnrolledLL<T> &left, UnrolledLL<T> &right) { return !(left == right); }

template <class T>
void UnrolledLL<T>::push_front(const T &v)
{
  Node<T> *newp = new Node<T>();
  // special case: initially empty list
  if (!head_)
  {
    tail_ = head_ = newp;
    head_->value_[0] = v;
    head_->num_elements_++;
  }
  else if (head_->num_elements_ == NUM_ELEMENTS_PER_NODE)
  {
    newp->value_[0] = v;
    head_->prev_ = newp;
    newp->next_ = head_;
    newp->prev_ = 0;
    head_ = newp;
    head_->num_elements_++;
  }
  else
  {
    head_->num_elements_++;

    // puts new element at front of array
    for (unsigned int i = 0; i < head_->num_elements_; i++)
    {
      if (i == 0)
      {
        newp->value_[i] = v;
      }
      else
      {
        newp->value_[i] = head_->value_[i - 1];
      }
      newp->num_elements_++;
    }

    head_->next_->prev_ = newp;
    newp->next_ = head_->next_;
    delete head_;
    head_ = newp;
  }
  ++size_;
}

template <class T>
void UnrolledLL<T>::pop_front()
{
  if (head_->num_elements_ == 1)
  {
    head_ = head_->next_;
    delete head_->prev_;
    head_->prev_ = 0;
  }
  else
  {
    Node<T> *newp = new Node<T>();
    // shifts all array elements down
    for (unsigned int i = 1; i < head_->num_elements_; i++)
    {
      newp->value_[i - 1] = head_->value_[i];
    }

    head_->num_elements_--;
    newp->num_elements_ = head_->num_elements_;
    newp->next_ = head_->next_;
    head_->next_->prev_ = newp;
    delete head_;
    head_ = newp;
  }

  --size_;
}
template <class T>
void UnrolledLL<T>::push_back(const T &v)
{

  // special case: initially empty list
  if (!tail_)
  {
    Node<T> *newp = new Node<T>();
    head_ = tail_ = newp;
    tail_->value_[0] = v;
    tail_->num_elements_++;
  }
  else if (tail_->num_elements_ == NUM_ELEMENTS_PER_NODE)
  {
    Node<T> *newp = new Node<T>();
    newp->prev_ = tail_;
    tail_->next_ = newp;
    newp->next_ = 0;
    tail_ = newp;
    tail_->value_[0] = v;
    tail_->num_elements_++;
  }
  else
  {
    tail_->num_elements_++;
    tail_->value_[tail_->num_elements_ - 1] = v;
  }
  ++size_;
}

template <class T>
void UnrolledLL<T>::pop_back()
{
  // if tail only has one element, delete tail
  // and shift it back
  if (tail_->num_elements_ == 1)
  {
    tail_ = tail_->prev_;
    delete tail_->next_;
    tail_->next_ = 0;
  }
  else
  {
    Node<T> *newp = new Node<T>();
    // copies all elements in array except last one
    for (unsigned int i = 0; i < tail_->num_elements_ - 1; i++)
    {
      newp->value_[i] = tail_->value_[i];
    }

    tail_->num_elements_--;
    tail_->prev_->next_ = newp;
    newp->prev_ = tail_->prev_;
    newp->next_ = 0;
    newp->num_elements_ = tail_->num_elements_;
    delete tail_;
    tail_ = newp;
  }

  --size_;
}

template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::erase(iterator itr)
{
  assert(size_ > 0);
  --size_;
  iterator result(itr);

  // One node left in the list and only one element in array
  if (itr.ptr_ == head_ && head_ == tail_ && itr.ptr_->num_elements_ == 1)
  {
    head_ = tail_ = 0;
    result++;
  }
  // Removing the head in a list with at least two nodes and only one element in array
  else if (itr.ptr_ == head_ && itr.ptr_->num_elements_ == 1)
  {
    head_ = head_->next_;
    delete head_->prev_;
    head_->prev_ = 0;
    result++;
  }
  // Removing the tail in a list with at least two nodes and only one element in array
  else if (itr.ptr_ == tail_ && itr.ptr_->num_elements_ == 1)
  {
    tail_ = tail_->prev_;
    delete tail_->next_;
    tail_->next_ = 0;
    result++;
  }
  // Normal remove and only one element in array
  else if (itr.ptr_->num_elements_ == 1)
  {
    itr.ptr_->prev_->next_ = itr.ptr_->next_;
    itr.ptr_->next_->prev_ = itr.ptr_->prev_;
    result++;
    delete itr.ptr_;
  }
  else
  {
    if (itr.offset_ == itr.ptr_->num_elements_ - 1)
    {
      result++;
    }

    itr.ptr_->num_elements_--;

    // shift all the elements down
    for (unsigned int i = itr.offset_; i < itr.ptr_->num_elements_; i++)
    {
      itr.ptr_->value_[i] = itr.ptr_->value_[i + 1];
    }
  }

  return result;
}

template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::insert(iterator itr, const T &v)
{
  ++size_;

  // checks if the node is full
  if (itr.ptr_->num_elements_ == NUM_ELEMENTS_PER_NODE)
  {
    Node<T> *newp1 = new Node<T>();
    Node<T> *newp2 = new Node<T>();

    // copies items before offset into first temp node
    for (unsigned int i = 0; i < itr.offset_; i++)
    {
      newp1->value_[i] = itr.ptr_->value_[i];
    }

    newp1->value_[itr.offset_] = v; // adds in new value to end
    newp1->num_elements_ = itr.offset_ + 1;

    // copies rest of the array into second temp node
    for (unsigned int n = itr.offset_; n < itr.ptr_->num_elements_; n++)
    {
      newp2->value_[n - itr.offset_] = itr.ptr_->value_[n];
    }
    newp2->num_elements_ = itr.ptr_->num_elements_ - itr.offset_;

    if (itr.ptr_ == head_)
    {
      head_->next_->prev_ = newp1;
      head_->next_->next_->prev_ = newp2;
      newp2->next_ = head_->next_->next_;
      newp1->prev_ = 0;
      head_ = newp1;
      head_->next_ = newp2;
    }
    else
    {
      // Have pointer before point to newp1
      // have newp1 point to newp2 then have
      // newp2 point to pointer after

      itr.ptr_->next_->prev_ = newp2;
      newp2->next_ = itr.ptr_->next_;
      itr.ptr_->prev_->next_ = newp1;
      newp1->prev_ = itr.ptr_->prev_;
      newp1->next_ = newp2;
      newp2->prev_ = newp1;
      itr.ptr_->next_ = newp2;
      delete itr.ptr_;
      itr.ptr_ = newp1;
    }
  }
  else
  {
    T temp[NUM_ELEMENTS_PER_NODE];
    temp[itr.offset_] = v;

    // copy elements before offset into temp array
    for (unsigned int i = 0; i < itr.offset_; i++)
    {
      temp[i] = itr.ptr_->value_[i];
    }

    // copy elements that occur on and after the offset
    for (unsigned int n = itr.offset_ + 1; n < itr.ptr_->num_elements_ + 1; n++)
    {
      temp[n] = itr.ptr_->value_[n - 1];
    }

    itr.ptr_->num_elements_++;

    // copy temp array into the array in the node
    for (unsigned int k = 0; k < itr.ptr_->num_elements_; k++)
    {
      itr.ptr_->value_[k] = temp[k];
    }
  }

  return itr;
}

template <class T>
void UnrolledLL<T>::copy_list(const UnrolledLL<T> &old)
{
  size_ = old.size_;
  // Handle the special case of an empty list.
  if (size_ == 0)
  {
    head_ = tail_ = 0;
    return;
  }
  // Create a new head node.
  head_ = new Node<T>();
  for (unsigned int i = 0; i < old.head_->num_elements_; i++)
  {
    head_->value_[i] = old.head_->value_[i];
  }

  head_->num_elements_ = old.head_->num_elements_;
  // tail_ will point to the last node created and therefore will move
  // down the new list as it is built
  tail_ = head_;
  // old_p will point to the next node to be copied in the old list
  Node<T> *old_p = old.head_->next_;
  // copy the remainder of the old list, one node at a time
  while (old_p)
  {

    tail_->next_ = new Node<T>();
    for (unsigned int i = 0; i < old_p->num_elements_; i++)
    {
      tail_->next_->value_[i] = old_p->value_[i];
    }
    tail_->next_->num_elements_ = old_p->num_elements_;
    tail_->next_->prev_ = tail_;
    tail_ = tail_->next_;
    old_p = old_p->next_;
  }
}

// deletes each pointer
template <class T>
void UnrolledLL<T>::destroy_list()
{
  Node<T> *newp;
  while (head_)
  {
    newp = head_->next_;
    delete head_;
    head_ = newp;
  }
  size_ = 0;
}

// prints out total elements in UnrolledLL and
// then prints out num_elements in node and the elements
template <class T>
void UnrolledLL<T>::print(std::ostream &out)
{
  out << "UnrolledLL, size: " << size() << std::endl;
  Node<T> *temp = head_;
  while (temp != tail_->next_)
  {
    out << " Node[" << temp->num_elements_ << "]";
    for (unsigned int i = 0; i < temp->num_elements_; i++)
    {
      out << " " << temp->value_[i];
    }
    out << std::endl;
    temp = temp->next_;
  }
}

#endif