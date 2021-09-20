bool insert(int val, TreeNode *&p)
{
  TreeNode *start = p;
  //get the leftmost element
  while (start && start->left)
    start = start->left;
  return insert(val, p, start);
}
bool insert(int val, TreeNode *&p, TreeNode *first, TreeNode *prev = NULL)
{
  //we've reached a leaf node
  if (!p)
  {
    //set p to a new node (passed by reference, so parent auto updates)
    p = new TreeNode(val);
    //this means this element is not the first, so we can just use prev's next
    if (prev)
    {
      p->next = prev->next;
      prev->next = p;
    }
    else //otherwise, p's next is the first element
      p->next = first;
    return true;
  }
  else if (val < p->value) //if we go left, prev should not be changed
    return insert(val, p->left, first, prev);
  else if (val > p->value) //if we go right, prev should be p
    return insert(val, p->right, first, p);
  else //element already exists in the set
    return false;
}
