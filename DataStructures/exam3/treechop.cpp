template <class T>
void TreeChop(TreeNode<T> *&root, bool left)
{
  if (left)
  {
    //Find the rightmost thing in the left tree
    TreeNode<T> *search = root->left;
    while (search->right)
    {
      search = search->right;
    }
    search->right = root;       //Link root to the bottom right of left subtree
    root = root->left;          //Update root
    search->right->left = NULL; //Make the old root's left pointer null
  }
  else
  {
    //Find the leftmost thing in the right tree
    TreeNode<T> *search = root->right;
    while (search->left)
    {
      search = search->left;
    }
    search->left = root;        //Link root to the bottom right of left subtree
    root = root->right;         //Update root
    search->left->right = NULL; //Make the old root's right pointer null
  }
}