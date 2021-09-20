#include <iostream>
#include <string>

// Note: It's ok that all the member variables are public for this
// tiny class.  We'll build up to a more robust and complete linked
// list implementation in lecture 10.
template <class T>
class Node
{
public:
  T value;
  Node<T> *ptr;
};

template <class T>
void print(Node<T> *data, const std::string &label)
{
  std::cout << label;
  Node<T> *tmp = data;
  while (tmp != NULL)
  {
    std::cout << " " << tmp->value;
    tmp = tmp->ptr;
  }
  std::cout << std::endl;
}

template <class T>
void reverse_itr(Node<T> *&input)
{
  Node<T> *tmp_list = NULL;
  while (input != NULL)
  {
    Node<T> *tmp = input;
    input = tmp->ptr;
    tmp->ptr = NULL;
    tmp->ptr = tmp_list;
    tmp_list = tmp;
  }
  input = tmp_list;
}

// template <class T>
// void reverse_rec(Node<T> *&input, Node<T>){
//   if (input == NULL){
//     return input;
//   }
//   if (input->ptr == NULL){
//     return input;
//   }
// }

int main()
{
  // manually create a linked list of notes with 4 elements
  Node<int> *my_list = new Node<int>;
  my_list->value = 1;
  my_list->ptr = new Node<int>;
  my_list->ptr->value = 2;
  // my_list->ptr->ptr = new Node<int>;
  // my_list->ptr->ptr->value = 3;
  // my_list->ptr->ptr->ptr = new Node<int>;
  // my_list->ptr->ptr->ptr->value = 4;
  // my_list->ptr->ptr->ptr->ptr = NULL;

  print(my_list, "my_list before");
  reverse_itr(my_list);
  print(my_list, "my_list after ");
  //reverse_rec()

  // Note: We are not deleting any of the Nodes we created...  so this
  // program has memory leaks!  More on this in Checkpoint 2!
}

// ===========================================================================
