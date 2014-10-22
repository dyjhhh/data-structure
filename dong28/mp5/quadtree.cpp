// **************************************************************
// *               
// *  quadtree.cpp
// *               
// *  Quadtree class
// *               
// *  CS 225 Spring 2008
// *               
// **************************************************************
 
#include "quadtree.h"
#include <iostream>
#include <math.h>
using namespace std;
 
//Default constructor that initializes an empty Quadtree
Quadtree::Quadtree()
{
        root = NULL;
        dimension = 0;
}
 
//Constructor that builds a tree with the specified source and dimension d
Quadtree::Quadtree(const PNG & source, int d)
{
        root = NULL;
        buildTree(source, d);
}
 
//Builds a tree with the specified source and dimension d
void Quadtree::buildTree(const PNG & source, int d)
{
        if (d>source.height() || d>source.width())
                return;
       
        //Delete the current contents of the Quadtree
        clear(root);
        root = buildTree(source, 0, d-1, 0, d-1);
        dimension = d; 
}
 
//Builds a tree with the specified source recursively based on given indices for the image
Quadtree::QuadtreeNode * Quadtree::buildTree(const PNG & source, int x1, int x2, int y1, int y2)
{
        if(x1 == x2 && y1 == y2) //Base case, namely that the indices point to the same pixel
        {
                return new QuadtreeNode(*source(x1,y1));
        }
        else
        {
                //recursively build the tree by repeatedly splitting the given region into fourths
                QuadtreeNode * nw = buildTree(source, x1, (x1+x2)/2, y1, (y1+y2)/2);
                QuadtreeNode * ne = buildTree(source, (x1+x2)/2+1, x2, y1, (y1+y2)/2);
                QuadtreeNode * sw = buildTree(source, x1, (x1+x2)/2, (y1+y2)/2+1, y2);
                QuadtreeNode * se = buildTree(source, (x1+x2)/2+1, x2, (y1+y2)/2+1, y2);
               
                //Average the values of the child pixels and store it in the current pixel
                RGBAPixel average(
                                                ((nw->element.red) + (ne->element.red) + (sw->element.red) + (se->element.red))/4,
                                                ((nw->element.green) + (ne->element.green) + (sw->element.green) + (se->element.green))/4,
                                                ((nw->element.blue) + (ne->element.blue) + (sw->element.blue) + (se->element.blue))/4,
                                                ((nw->element.alpha) + (ne->element.alpha) + (sw->element.alpha) + (se->element.alpha))/4
                                                );
                QuadtreeNode * created = new QuadtreeNode(average);
 
                //Set the children of the current pixel
                created->nwChild = nw;
                created->neChild = ne;
                created->swChild = sw;
                created->seChild = se;
                return created;
        }
 
}
 
//Copy constructor for Quadtree
Quadtree::Quadtree(const Quadtree & source)
{
        copy(source);
}
 
//Overloaded assignment operator for Quadtree
Quadtree Quadtree::operator=(const Quadtree & source)
{
        if (this != &source)
        {
                clear(root);
                copy(source);
        }
        return *this;
}
 
//Helper function that calls the other copy helper function
void Quadtree::copy(const Quadtree & source)
{
        if(source.root == NULL) //if the supplied source is an empty quadtree, just do the default constructor stuff
        {
                root = NULL;
                dimension = 0;
                return;
        }
 
        copy(source.root, root);
        dimension = source.dimension;  
}
 
//Helper function for the copy constructor and assignment operator
void Quadtree::copy(Quadtree::QuadtreeNode * toCopy, QuadtreeNode * & start)
{
        start = new QuadtreeNode(toCopy->element);
       
        //Recursively copy the tree
        if (toCopy->nwChild != NULL)
                copy(toCopy->nwChild, start->nwChild);
        if (toCopy->neChild != NULL)
                copy(toCopy->neChild, start->neChild);
        if(toCopy->swChild != NULL)
                copy(toCopy->swChild, start->swChild);
        if(toCopy->seChild != NULL)
                copy(toCopy->seChild, start->seChild);
}
 
//Destructor for Quadtree
Quadtree::~Quadtree()
{
        clear(root);
}
 
//Helper function for the destructor
void Quadtree::clear(QuadtreeNode * start)
{
        if (start != NULL)
        {
                //Recursively clear the children
                if (start->nwChild != NULL)
                {
                        clear(start->nwChild);
                        clear(start->neChild);
                        clear(start->swChild);
                        clear(start->seChild);
                }              
                delete start;
        }
        dimension = 0;
}
 
//QuadtreeNode default constructor
Quadtree::QuadtreeNode::QuadtreeNode()
{
        nwChild = NULL;
        neChild = NULL;
        swChild = NULL;
        seChild = NULL;
        //element = NULL;
}
 
//Constructs a QuadtreeNode that contains a copy of the specified RGBAPixel
Quadtree::QuadtreeNode::QuadtreeNode(const RGBAPixel & source)
{
        nwChild = NULL;
        neChild = NULL;
        swChild = NULL;
        seChild = NULL;
        element = source;
}
 
//Returns the pixel at the specified coordinates
RGBAPixel Quadtree::getPixel(int x, int y)
{
        //Make sure the x and y coordinates are valid
        if (x > dimension || y > dimension)
        {
                RGBAPixel nothing;
                return nothing;
        }
 
        return getPixel(x,y,root,0, 0, dimension);
}
 
RGBAPixel Quadtree::getPixel(int x, int y, QuadtreeNode * curr, int xlim, int ylim, int width)
{
        if (curr->nwChild == NULL) //if the node is a leaf node, return its element
                return curr->element;
 
        if(x < xlim + width/2) //check to see if we need to go west
        {
                if(y < ylim+width/2)
                        return getPixel(x,y,curr->nwChild, xlim, ylim, width/2);
                else
                        return getPixel(x,y,curr->swChild, xlim, ylim+width/2, width/2);
        }
        else //we go east
        {
                if(y < ylim + width/2)
                        return getPixel(x,y,curr->neChild, xlim+width/2, ylim, width/2);
                else
                        return getPixel(x,y,curr->seChild, xlim+width/2, ylim+width/2, width/2);
        }
}
 
//Returns the PNG that is represented by the quadtree **********************************************************************
PNG Quadtree::decompress()
{
        PNG composite(dimension, dimension);
        decompress(composite, root, 0, dimension-1, 0, dimension-1);
        return composite;      
}
 
//Helper function for decompress
void Quadtree::decompress(PNG & composite, QuadtreeNode * curr, int x1, int x2, int y1, int y2)
{
        if(curr == NULL)
                return;
 
        if(curr->nwChild == NULL) //base case, ie the node is a leaf node
        {
                //In the current x1->x2 and y1->y2 range make that part of the PNG curr's color
                for(int i=x1; i<=x2; i++)
                {
                        for(int j=y1; j<=y2; j++)
                        {
                                *composite(i,j) = curr->element;
                        }
                }
        }
        else
        {
                decompress(composite, curr->nwChild, x1, (x1+x2)/2, y1, (y1+y2)/2);
                decompress(composite, curr->neChild, (x1+x2)/2+1, x2, y1, (y1+y2)/2);
                decompress(composite, curr->swChild, x1, (x1+x2)/2, (y1+y2)/2+1, y2);
                decompress(composite, curr->seChild, (x1+x2)/2+1, x2, (y1+y2)/2+1, y2);
        }
}
 
//Stubbed out functions for MP 5.2
//Rotates the underlying image in the tree clockwise by 90 degrees
void Quadtree::clockwiseRotate()
{
        clockwiseRotate(root);
}
 
void Quadtree::clockwiseRotate(QuadtreeNode * croot)
{
        if(croot == NULL)
                return;
 
        if(croot->nwChild == NULL) //base case, ie croot is a leaf node
        {
                return;
        }
 
        //rotate the child nodes in a clockwise fashion
        QuadtreeNode * nnw = croot->swChild;
        QuadtreeNode * nne = croot->nwChild;
        QuadtreeNode * nsw = croot->seChild;
        QuadtreeNode * nse = croot->neChild;
 
        croot->nwChild = nnw;
        croot->neChild = nne;
        croot->swChild = nsw;
        croot->seChild = nse;
 
        //recursively rotate the four subtrees
        clockwiseRotate(croot->nwChild);
        clockwiseRotate(croot->neChild);
        clockwiseRotate(croot->swChild);
        clockwiseRotate(croot->seChild);
}
 
void Quadtree::prune(int tolerance)
{
        prune(tolerance, root);
}
 
//Helper function for prune
void Quadtree::prune(int tolerance, QuadtreeNode * croot)
{
        if(croot == NULL)
                return;
 
        //If croot is not a leaf, assess whether or not croot can be pruned
        if(croot->nwChild == NULL)
                return;
       
        bool nw = prunable(tolerance,croot,croot->nwChild);
        bool ne = prunable(tolerance,croot,croot->neChild);
        bool sw = prunable(tolerance,croot,croot->swChild);
        bool se = prunable(tolerance,croot,croot->seChild);
 
        //if it is prunable, prune the node
        if(nw && ne && sw && se)
        {
                //cout << "yes" << endl;
                clear2(croot->nwChild);
                clear2(croot->neChild);
                clear2(croot->swChild);
                clear2(croot->seChild);
 
                croot->nwChild = NULL;
                croot->neChild = NULL;
                croot->swChild = NULL;
                croot->seChild = NULL;
        }
 
        //recursively prune the subtree
        prune(tolerance, croot->nwChild);
        prune(tolerance, croot->neChild);
        prune(tolerance, croot->swChild);
        prune(tolerance, croot->seChild);
 
}
 
//computes whether or not the given nodes are prunable
bool Quadtree::prunable(int tolerance, QuadtreeNode * node1, QuadtreeNode * node2)
{
        if(node1 == NULL || node2 == NULL)
                return false;
 
        if(node2->nwChild == NULL) //base case if node2 is a leaf node
        {      
                return ((
                                pow((node1->element.red) - (node2->element.red),2)
                                + pow((node1->element.green) - (node2->element.green),2)
                                + pow((node1->element.blue) - (node2->element.blue),2)) <= tolerance);
        }
        else
        {
                //Recursively determine if subtrees are prunable
                return (
                                prunable(tolerance,node1,node2->nwChild)
                                && prunable(tolerance,node1,node2->neChild)
                                && prunable(tolerance,node1,node2->swChild)
                                && prunable(tolerance,node1,node2->seChild));
        }
}
 
//Deletes the given node and its subtree
void Quadtree::clear2(QuadtreeNode * start)
{
        if (start != NULL)
        {
                //Recursively clear the children
                if (start->nwChild != NULL)
                {
                        clear2(start->nwChild);
                        clear2(start->neChild);
                        clear2(start->swChild);
                        clear2(start->seChild);
                }              
                delete start;
        }
}
 
//Computes the number of leaves that the tree would have if it were pruned
int Quadtree::pruneSize(int tolerance)
{
        return pow(dimension,2) - prunesize(tolerance,root);
}
 
//Helper function for prunesize that returns the number of leaves that would be pruned
int Quadtree::prunesize(int tolerance, QuadtreeNode * croot)
{
        if(croot == NULL)
                return 0;
 
        //If croot is not a leaf, assess whether or not croot can be pruned
        if(croot->nwChild == NULL)
                return 0;
       
        bool nw = prunable(tolerance,croot,croot->nwChild);
        bool ne = prunable(tolerance,croot,croot->neChild);
        bool sw = prunable(tolerance,croot,croot->swChild);
        bool se = prunable(tolerance,croot,croot->seChild);
 
        //if it is prunable, then return the number of leaves that it has - 1
        if(nw && ne && sw && se) //if the node to be pruned is a node with leaf node children
        {
                return numLeaves2(croot)-1;
        }
        else
        {
                return prunesize(tolerance, croot->nwChild) + prunesize(tolerance, croot->neChild) + prunesize(tolerance, croot->swChild) + prunesize(tolerance, croot->seChild);
        }
}
 
//Returns the number of leaf nodes in the subtree of croot
int Quadtree::numLeaves2(QuadtreeNode * croot)
{
        if (croot == NULL)
                return 0;
        if(croot->nwChild == NULL) //base case, namely croot is a leaf node
                return 1;
       
        return (numLeaves2(croot->nwChild) + numLeaves2(croot->neChild) + numLeaves2(croot->swChild) + numLeaves2(croot->seChild));
}
 
int Quadtree::idealPrune(int numLeaves)
{
        //Start at a tolerance of 1000
        int min = 0;
        int max = 195075; //tolerance that will gaurantee the tree will be completely pruned no matter what
        int mid;
        int size;
        while(min <= max)
        {
                mid = (min+max)/2;
                size = pruneSize(mid);
                //cout << mid << endl;
                if(size > numLeaves) //tolerance is not big enough
                {
                        min = mid+1;
                }
                else if(size < numLeaves) //tolerance is too big
                {
                        max = mid-1;
                }
                else //tolerance yields numleaves
                {
                        //since multiple tolerances can yield the same numleaves, find the minimum tolerance that will yield numLeaves
                        int temp = mid;
                        while(pruneSize(temp-1) == numLeaves)
                        {
                                temp--;
                        }
                        return temp;
                }
        }
 
        return mid;                    
}

