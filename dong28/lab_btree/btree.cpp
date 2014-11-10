/**
 * @file btree.cpp
 * Implementation of a B-tree class which can be used as a generic dictionary
 * (insert-only). Designed to take advantage of caching to be faster than
 * standard balanced binary search trees.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

using std::vector;


/**
 * Finds the value associated with a given key.
 * @param key The key to look up.
 * @return The value (if found), the default V if not.
 */
template <class K, class V>
V BTree<K, V>::find(const K& key) const
{
    return root == nullptr ? V() : find(root, key);
}

/**
 * Private recursive version of the find function.
 * @param subroot A reference of a pointer to the current BTreeNode.
 * @param key The key we are looking up.
 * @return The value (if found), the default V if not.
 */
template <class K, class V>
V BTree<K, V>::find(const BTreeNode* subroot, const K& key) const
{
    /* TODO Your code goes here! */
    /* If first_larger_idx is a valid index and the key there is the key we
     * are looking for, we are done. */

    /* Otherwise, we need to figure out which child to explore. For this we
     * can actually just use first_larder_idx directly. E.g.
     * | 1 | 5 | 7 | 8 |
     * Suppose we are looking for 6. first_larger_idx is 2. This means we want to
     * explore the child between 5 and 7. The children vector has a pointer for
     * each of the horizontal bars. The index of the horizontal bar we want is
     * 2, which is conveniently the same as first_larger_idx. If the subroot is
     * a leaf and we didn't find the key in it, then we have failed to find it
     * anywhere in the tree and return the default V.
     */
       /* if(subroot->elements.empty())
		return V();
	size_t ret=insertion_idx(subroot->elements,key);
	if(subroot->elements.at(ret).key==key)
		return subroot->elements.at(ret).value;
        return find(subroot->children.at(ret),key);
	*/
	int pos = insertion_idx(subroot->elements, key);
	if(subroot->is_leaf)
    {
    	
    	if((pos >= 0)||(pos < subroot->elements.size()))
    	{
    		if(subroot->elements[pos] == key)
    		{
    	 	return subroot->elements[pos].value;
			}
		}	    
	    return V();
    }
    
    
    return find(subroot->children[pos], key);
    
}

/**
 * Inserts a key and value into the BTree. If the key is already in the
 * tree do nothing.
 * @param key The key to insert.
 * @param value The value to insert.
 */
template <class K, class V>
void BTree<K, V>::insert(const K& key, const V& value)
{
    /* Make the root node if the tree is empty. */
    if(root == nullptr)
    {
        root = new BTreeNode(true, order);
    }
    insert(root, DataPair(key, value));
    /* Increase height by one by tossing up one element from the old
     * root node. */
    if(root->elements.size() >= order)
    {
        BTreeNode* new_root = new BTreeNode(false, order);
        new_root->children.push_back(root);
        split_child(new_root, 0);
        root = new_root;
    }
}

/**
 * Splits a child node of a BTreeNode. Called if the child became too 
 * large.
 * @param parent The parent whose child we are trying to split.
 * @param child_idx The index of the child in its parent's children
 * vector.
 */
template <class K, class V>
void BTree<K, V>::split_child(BTreeNode* parent, size_t child_idx)
{

    /* TODO Your code goes here! */

    /* Assume we are splitting the 3 6 8 child.
     * We want the following to happen.
     *     | 2 | 
     *    /     \
     * | 1 |   | 3 | 6 | 8 |
     *
     *
     * Insert a pointer into parent's children which will point to the 
     * new right node. The new right node is empty at this point.
     *     | 2 |   | 
     *    /     \
     * | 1 |   | 3 | 6 | 8 |
     *
     * Insert the mid element from the child into its new position in the
     * parent's elements. At this point the median is still in the child.
     *     | 2 | 6 | 
     *    /     \
     * | 1 |   | 3 | 6 | 8 |
     *
     * Now we want to copy over the elements (and children) to the right
     * of the child median into the new right node, and make sure the left
     * node only has the elements (and children) to the left of the child 
     * median.
     *     | 2 | 6 | 
     *    /   /     \
     * | 1 | | 3 | | 8 |
     *
     */
     	
     	 BTreeNode* new_pointer = new BTreeNode(parent->is_leaf, order);
  	
  	 auto it = parent->children.begin()+child_idx;// child pointer
    	 parent->children.insert(it+1,new_pointer);
    	
    	 BTreeNode *temp=*it;
	 auto get_median=temp->elements.begin()+(temp->elements.size()-1)/2;// get median position
	
	
	 auto get_pos=parent->elements.begin()+child_idx;		// get the position to insert median in root
	 parent->elements.insert(get_pos,*get_median);
	 
	 //now get all elements greater than median 
	 // pointers for those median
	 // push them in new_pointer
	 //then remove those elements and pointers from the unnecsaary space
	 auto greater_median_elements=temp->elements.begin()+(parent->elements.size()-1)/2+1;
	 auto greater_median_children=temp->children.begin()+(parent->children.size()-1)/2+1;
	
	 for(;greater_median_elements!=temp->elements.end();greater_median_elements++)
	 	new_pointer->elements.push_back(*greater_median_elements);
	 for(;greater_median_children!=temp->children.end();greater_median_children++)
	 	new_pointer->children.push_back(*greater_median_children);
	 
	 auto remove_median_elements=temp->elements.begin()+(parent->elements.size()-1)/2;
	 auto remove_median_children=temp->children.begin()+(parent->children.size()-1)/2;
	 
	 for(;remove_median_elements!=temp->elements.end();remove_median_elements++)
	 	temp->elements.erase(remove_median_elements);
	 for(;remove_median_children!=temp->children.end();remove_median_children++)
	 	temp->children.erase(remove_median_children);		
	
}

/**
 * Private recursive version of the insert function.
 * @param subroot A reference of a pointer to the current BTreeNode.
 * @param pair The DataPair to be inserted.
 * Note: Original solution used std::lower_bound, but making the students
 * write an equivalent seemed more instructive.
 */
template <class K, class V>
void BTree<K, V>::insert(BTreeNode* subroot, const DataPair& pair)
{
    /* There are two cases to consider. 
     * If the subroot is a leaf node and the key doesn't exist subroot, we 
     * should simply insert the pair into subroot.
     * Otherwise (subroot is not a leaf and the key doesn't exist in subroot)
     * we need to figure out which child to insert into and call insert on it.
     * After this call returns we need to check if the child became too large
     * and thus needs to be split to maintain order. 
     */

    /* TODO Your code goes here! */
    
    	//check for split
   if(subroot->is_leaf && subroot->elements.empty())
    	{
    		subroot->elements.push_back(pair);
    		return;
    	}
    else if( !(subroot->is_leaf) && find(subroot,pair.key)==V())
    {
    	//Find the child to insert on
    	if(pair.value< find(subroot, pair.key))
    	{
    		//left subtree
    		size_t index=insertion_idx(subroot->elements,pair.value);
    		
  		auto left=subroot->children.begin()+index;
  		
    		insert(*left,pair);
    		if(subroot->elements.size()>=order)
    		{
    			split_child(subroot,index);
    		}
    			
    	}
    	else
    	{
    		//right subtree
    		//insert call recursively 
    		size_t index=insertion_idx(subroot->elements,pair.value);
    		auto right=subroot->children.begin()+index;
    		insert(*right,pair);
    		if(subroot->elements.size()>=order)
    		{
    			split_child(subroot,index);
    		}
    	}
	
   }
    	
   
    
    
    
}
