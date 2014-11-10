/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */
#include<iostream>

using namespace std;
template<int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim> & first, const Point<Dim> & second, int curDim) const
{
    /**
     * @todo Implement this function
     */
     bool val=true;
     if(first[curDim]<second[curDim])
     	return val;
     else if(first[curDim]>second[curDim])
     	return false;	
     return first<second ;
}
template<int Dim>
int KDTree<Dim>::distance_dim(const Point<Dim> & target, const Point<Dim> & currentBest,int axis) const
{
	int sum=0;
	sum=(target[axis]-currentBest[axis])*(target[axis]-currentBest[axis]);
	return sum;
} 

template<int Dim>
int KDTree<Dim>::distance(const Point<Dim> & target, const Point<Dim> & currentBest) const
{
    int max_dim=Dim;
    int sum_1=0;
    for(int i=0;i<max_dim;i++)
    {
    	sum_1+=(currentBest[i]-target[i])*(currentBest[i]-target[i]);
    }
    return sum_1;
}
template<int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim> & target, const Point<Dim> & currentBest, const Point<Dim> & potential) const
{
    /**
     * @todo Implement this function!
     */
    int max_dim=Dim;
    int sum_1=0,sum_2=0;
    for(int i=0;i<max_dim;i++)
    {
    	sum_1+=(currentBest[i]-target[i])*(currentBest[i]-target[i]);
    }
    for(int i=0;i<max_dim;i++)
    {
    	sum_2+=(potential[i]-target[i])*(potential[i]-target[i]);
    }
    if(sum_1<sum_2)
    	return false;//donot replace
    else if(sum_1 > sum_2)	
    	return true;// replace
	else
		return potential<currentBest;
}

template<int Dim>
KDTree<Dim>::KDTree(const vector< Point<Dim> > & newPoints)
{
    /**
     * @todo Implement this function!
     */
     
     dimension=Dim;
     points=newPoints;
     if (points.size()!=0)
     KDTree_build_helper(points,0,0,newPoints.size()-1);
     
}
template<int Dim>
void KDTree<Dim>::KDTree_build_helper(vector< Point<Dim> > & newPoints, int curr_dim,int left,int right)
{	
	if(left==right)
		return;
	int axis = curr_dim%dimension;
	//cout<<"axis\n"<<axis;
	select(newPoints,left,right,((left+right)/2),axis);
	int mid=(left+right)/2;
	if(left<mid)
		KDTree_build_helper(newPoints,curr_dim+1,left,((left+right)/2) -1);
	if(right>mid)	
		KDTree_build_helper(newPoints,curr_dim+1,((left+right)/2)+1,right);
	
	
	
}
/*Helper function select */
template<int Dim>
void KDTree<Dim>:: select(vector< Point<Dim> > & newPoints,int left, int right,int n,int axis)
{
	if(left==right)
		return;
	int pivotIndex;	
	pivotIndex = partition(newPoints, left, right,n,axis);
	if(n==pivotIndex)
		return ;
	else if(n<pivotIndex)
		 select(newPoints,left,pivotIndex-1,n,axis);
       
     	else
     		 select(newPoints, pivotIndex + 1, right, n,axis);

}
/*HELPER PARTION FUNCTION CALLED FROM select HELPER*/
template<int Dim>
int KDTree<Dim>:: partition(vector< Point<Dim> > & newPoints,int low, int high,int pivotIndex,int axis)
{
	//cout<<"pivotIndex size\n"<<pivotIndex<<newPoints.size();
	Point<Dim> pivotValue = newPoints[pivotIndex];
	//cout<<"here\n";
	Point<Dim> temp= newPoints[high]; 
	newPoints[high]= newPoints[pivotIndex];
	newPoints[pivotIndex]=temp;
	int temp_low=low;
	for(int i=low;i<high;i++)
	{
         if(smallerDimVal(newPoints[i],pivotValue,axis) || newPoints[i]==pivotValue) 
         {
         	temp= newPoints[i]; 
		newPoints[i]= newPoints[temp_low];
		newPoints[temp_low]=temp;
		temp_low++;
         }
        }
    temp= newPoints[temp_low]; 
	newPoints[temp_low]= newPoints[high];
	newPoints[high]=temp;
	return temp_low;
}
template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> & query) const
{
    /**
     * @todo Implement this function!
     */
     
    
     //set root as curr_bst initially 
	
	 return find_helper(query,0,points.size()-1,0);
   	// return Point<Dim>();
}



template<int Dim>
Point<Dim> KDTree<Dim>:: find_helper(const Point<Dim> & query,int left,int right,int axis) const
{
	int curr_axis=axis%Dim;
	int median=(left+right)/2;
	bool left_entered=false;	
	Point<Dim> curr_bst;
	Point<Dim> may_curr_bst;
	int bst_distance;
	if(left>=right)
	{	//base case
		
			return points.at(median);
		
	}
	else
	{
		if(smallerDimVal(query,points.at(median),curr_axis))
		{
			//left subtrree
			curr_bst =find_helper(query,left,median-1,axis+1);
			left_entered=true;
   
		}
		else if(!(smallerDimVal(query,points.at(median),curr_axis)))
		{
			//right subtree
			curr_bst=find_helper(query,median+1,right,axis+1);
		}
	}
	
	//should replace
	if(shouldReplace(query,curr_bst,points.at(median)))
	{
		curr_bst=points.at(median);
	}
		//now check for particular dimension
		bst_distance=distance(query,curr_bst);
		int dx=distance_dim(query,points.at(median),curr_axis);
		if(dx<=bst_distance)
		{
			//again recurse
			if(left_entered==false) // previously entered the right subtree
			 may_curr_bst=find_helper(query,left,median-1,axis+1);
			else // now enter the right subtree previous was left(target)
			 may_curr_bst=find_helper(query,median+1,right,axis+1);
		
			if(shouldReplace(query,curr_bst,may_curr_bst))
				curr_bst=may_curr_bst;
		}
			
	
	return curr_bst;
}