/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
 
/**
 * @return The height of the binary tree. Recall that the height of a binary tree
 *  is just the length of the longest path from the root to a leaf, and that the
 *  height of an empty tree is -1.
 */
 
template <typename T>
int BinaryTree<T>::height() const
{
        // Call recursive helper function on root
        return height(root);
}
 
/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node * subRoot) const
{
        // Base case
        if (subRoot == NULL)
        return -1;
       
        // Recursive definition
        return 1 + max(height(subRoot->left), height(subRoot->right));
}
 
/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that node
 *  itself, and everything to the right of a node will be printed out after that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
        // Call recursive helper function on the root
        printLeftToRight(root);
 
        // Finish the line
        cout << endl;
}
 
/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node * subRoot) const
{
        // Base case - null node
        if (subRoot == NULL)
                return;
 
        // Print left subtree
        printLeftToRight(subRoot->left);
 
        // Print this node
        cout << subRoot->elem << ' ';
 
        // Print right subtree
        printLeftToRight(subRoot->right);
}
 
/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
 
template <typename T>
void BinaryTree<T>::mirror() const
{
    if(!root)
        mirror(root);
}
template <typename T>
void BinaryTree<T>::mirror(Node *subRoot)
{
    if(!subRoot)
        return;
    mirror(subRoot->left);
    mirror(subRoot->right);
 
    Node * foo;
    foo = subRoot->left;
    subRoot->left = subRoot->right;
    subRoot->right = foo;
}
 
/**
 * @return True if an in-order traversal of the tree would produce a nondecreasing list
 *  output values, and false otherwise. This is also the criterion for a binary tree to be
 *  a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrdered() const
{
    T foo, bar;
    bool flag = true;
 
    vector<T> V;
    LR(root,V);
    if(V.size()<=1)
        return true;
    foo = V.back();
    V.pop_back();
 
    while(!V.empty()){
        bar = V.back();
        V.pop_back();
        if(foo>=bar)
            flag = true;
        else
            flag = false;
        foo = bar;
    }
    return flag;
       
}
//helper for isordered
//
template <typename T>
void BinaryTree<T>::LR(const Node * subRoot, vector<T> & V) const
{
    if(subRoot == NULL)
        return;
 
    LR(subRoot->left,V);
 
    V.push_back(subRoot->elem);
 
    LR(subRoot->right, V);
 
}
/**
 * Prints out all the possible paths from the root of the tree to any leaf node.
 * That is, all sequences starting at the root node and continuing downwards, ending at a
 *  leaf node. Paths ending in a left node should be printed before paths ending in a node
 *  further to the right.
 */
template <typename T>
void BinaryTree<T>::printPaths() const
{
    vector<T> foo;
    printPaths(root,foo);
 
}
 
//helper for printPaths
 
template <typename T>
void BinaryTree<T> :: printPaths(const Node * subRoot, vector<T> & foo) const
{
    if(!subRoot)
        return;
    foo.push_back(subRoot->elem);
    if((!subRoot->left)&&(!subRoot->right))
        pa(foo);
 
    printPaths(subRoot->left,foo);
    printPaths(subRoot->right, foo);
 
    foo.pop_back();
   
}
template <typename T>
void BinaryTree<T>::pa(vector<T> foo) const
{
    vector<T> a;
    while(!foo.empty()){
        a.push_back(foo.back());
        foo.pop_back();
    }
 
    cout << "Path : ";
 
    while(!a.empty()){
        cout<<' '<<a.back();
        a.pop_back();
    }
 
    cout<<endl;
    return;
}
/**
 * Each node in a tree has a distance from the root node - the depth of that node,
 *  or the number of edges along the path from that node to the root. This function returns
 *  the sum of the distances of all nodes to the root node (the sum of the depths of all
 *  the nodes). Your solution should take O(n) time, where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    return sumDistances(root,0);
}
 
template <typename T>
int BinaryTree<T>::sumDistances(const Node * subRoot, int count) const
{
    if(!subRoot)
        return 0;
    return count+sumDistances(subRoot->left,count+1)+sumDistances(subRoot->right, count+1);
}