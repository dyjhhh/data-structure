/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
#include <iostream>
using namespace std;

template <class T>
List<T>::~List()
{
    clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{
	length = 0;
	ListNode * curr = head;

	while (curr != NULL)
	{
		ListNode * next = curr->next;
		delete curr;
		curr = NULL;
		curr = next;
	}

	head = NULL;
	tail = NULL;
}                              

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const & ndata)
{
	length++;

  	if (head == NULL)
	{
		head = new ListNode(ndata);
		head->prev = NULL;
		head->next = NULL;
		tail = head;
		tail->prev = NULL;
		tail->next = NULL;
	}
	else
	{
		head->prev = new ListNode(ndata);
		ListNode * temp = head;
		head = head->prev;
		head->prev = NULL;
		head->next = temp;
	}	
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack( const T & ndata )
{
    length++;

	if (tail == NULL)
	{
		tail = new ListNode(ndata);
		tail->prev = NULL;
		tail->next = NULL;
		head = tail;
		head->next = NULL;
		head->prev = NULL;
	}
	else
	{
		tail->next = new ListNode(ndata);
		ListNode * temp = tail;
		tail = tail->next;
		tail->next = NULL;
		tail->prev = temp;
	}
}


/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{
	if (head == NULL || tail == NULL)
		return;

    reverse(head, tail);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse( ListNode * & startPoint, ListNode * & endPoint )
{
	ListNode *  temp = NULL;
	ListNode *  curr = startPoint;
	ListNode *  afterEnd = endPoint->next;
	ListNode *  beforeStart = startPoint->prev;
	
	
	while (curr != afterEnd)
	{
		temp = curr->prev;				//swap each node's previous and next
		curr->prev = curr->next;
		curr->next = temp;
		curr = curr->prev;
	}

	if (temp != NULL)  
	{
		temp = startPoint;				//switch the startPoint and endPoint
		startPoint = endPoint;
		endPoint = temp;
	}
    
	endPoint->next = afterEnd;			

	if (afterEnd != NULL)				//works if this is a sublist 
	{
		afterEnd->prev = endPoint;
	}

	startPoint->prev = beforeStart;

	if (beforeStart != NULL)
	{
		beforeStart->next = startPoint;
	} 
}


/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth( int n )
{
	if (head == NULL || tail == NULL || n<=0)
		return;

    ListNode * startPoint = head;
	ListNode * endPoint = head;

	if (n >= size())
	{
		reverse();
		return;
	}

	for (int i=1; i<n; i++)
	{	
		if (endPoint->next != NULL)
		endPoint = endPoint->next;
	}
	reverse(head,endPoint);      				//special case to change the head by reference

	while (endPoint->next != NULL)
	{
		startPoint = endPoint->next;

		for (int i=1; i<=n; i++)
		{	
			if (endPoint->next != NULL)
			endPoint = endPoint->next;
		}

		reverse(startPoint,endPoint);  
	
	}
	if (tail->next != NULL)
		tail = tail->next;
}


/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall()
{
	if (head == NULL || tail == NULL)
		return;

	ListNode * curr = head->next;			//special case, move 1 forward instead of two
	ListNode * temp = curr;

	while (curr != NULL && curr != tail)
	{
		if (curr->next != NULL)					//remove the node
		{
			(curr->next)->prev = curr->prev;
			temp = curr->next;
		}
		(curr->prev)->next = curr->next;
	
		tail->next = curr;						//add to the end
		curr->next = NULL;
		curr->prev = tail;
		tail = curr;
		
		curr = temp->next;				//move two nodes forward
	}
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint)
{
    if (splitPoint > length)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head)
    {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    }
    else
    {
        // set up current list
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        length = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head = secondHead;
    ret.tail = secondHead;
    if (ret.tail != NULL)
    {
        while (ret.tail->next != NULL)
            ret.tail = ret.tail->next;
    }
    ret.length = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint)
{
	ListNode * curr = start;
		
	for (int i=0; i != splitPoint; i++)
	{
		if (curr->next != NULL)
		curr = curr->next;
	}
	if (curr == NULL)
		cout << "NULL" << endl;
	if (curr->prev != NULL)
		(curr->prev)->next = NULL;
	curr->prev = NULL;
   																		
    return curr; 
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T> & otherList)
{
    // set up the current list
    head = merge(head, otherList.head);
    tail = head;

    // make sure there is a node in the new list
    if(tail != NULL)
    {
        while (tail->next != NULL)
            tail = tail->next;
    }
    length = length + otherList.length;

    // empty out the parameter list
    otherList.head = NULL;
    otherList.tail = NULL;
    otherList.length = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode * second)
{
	ListNode * f_temp = first->next;
	ListNode * s_temp = second->next;
	ListNode * r_temp = NULL;

	ListNode * result = NULL;	


	if (first->data < second->data)    //set up result
	{
		result = first;
		result->prev = NULL;
		result->next = NULL;
		r_temp = result;
		first = f_temp;
	}
	else
	{
		result = second;
		result->prev = NULL;
		result->next = NULL;
		r_temp = result;
		second = s_temp;
	}

	while (first != NULL || second != NULL)
	{
		if (first != NULL && second != NULL)
		{
			if (first->data < second->data)
			{
				
				first->prev = r_temp;
				r_temp->next = first;
				first = first->next;
				r_temp = r_temp->next;
			}
			else
			{
				second->prev = r_temp;
				r_temp->next = second;
				second = second->next;
				r_temp = r_temp->next;
			}
		}
		 
		
		else if (first != NULL)
			{	
				if (first == r_temp)
					first = first->next;
				if (first == NULL)
					break;
				first->prev = r_temp;
				r_temp->next = first;
				first = first->next;
				r_temp = r_temp->next;
				
			}
		else if (second != NULL)
			{
				if (second ==  r_temp)
				    second = second->next;
				if (second == NULL)
					break;
				second->prev = r_temp;
				r_temp->next = second;
				second = second->next;
				r_temp = r_temp->next;
			}
		
	}

	return result;	
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort()
{
    if (empty())
        return;
    head = mergesort(head, length);
    tail = head;
    while (tail->next != NULL)
        tail = tail->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode * List<T>::mergesort(ListNode * start, int chainLength)
{
   																	
	if (chainLength <= 1)
		return start;

	int middle = chainLength/2;
	ListNode * left = start;
	ListNode * right = split(start,middle);

	left = mergesort(left,middle);
	right = mergesort(right,chainLength-middle);
	
    return merge(left,right); 
}