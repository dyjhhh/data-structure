// **************************************************************
// *               
// *  quadtree.h
// *               
// *  Quadtree class
// *               
// *  CS 225 Spring 2008
// *               
// **************************************************************
 
#ifndef QUADTREE_H
#define QUADTREE_H
 
#include "easypng.h"
 
class Quadtree
{
        public:
        //Constructors for Quadtree taking no values and specified values
        Quadtree();
        Quadtree(const PNG & source, int d);
 
        //Big three: Copy constructor, assignment operator, and destructor
        Quadtree(const Quadtree & source);
        Quadtree operator=(const Quadtree & rhs);
        ~Quadtree();
 
        //Builds a tree with the specified source image and dimension d
        void buildTree(const PNG & source, int d);
 
        //A function that returns the pixel at the specified coordinates
        RGBAPixel getPixel(int x, int y);
 
        //Decompresses the Quadtree by returning the PNG that it represents
        PNG decompress();
 
        //Stubbed out functions for MP 5.2
        void clockwiseRotate();
        void prune(int tolerance);
        int pruneSize(int tolerance);
        int idealPrune(int numLeaves); 
       
        private:
        // A simple class representing a single node of a Quadtree.
        // You may want to add to this class; in particular, it could probably
        // use a constructor or two...
        class QuadtreeNode
        {
                public:
                //Public class constructors
                QuadtreeNode();         //Initializes an empty node
                //Initializes a node with the specified source as the node's element
                QuadtreeNode(const RGBAPixel & source);
 
                QuadtreeNode* nwChild;  // pointer to northwest child
                QuadtreeNode* neChild;  // pointer to northeast child
                QuadtreeNode* swChild;  // pointer to southwest child
                QuadtreeNode* seChild;  // pointer to southeast child
 
                RGBAPixel element;  // the pixel stored as this node's "data"
        };
       
        //Private helper functions for the copy constructor and assignment operator
        void copy(const Quadtree & source);
        void copy(QuadtreeNode * toCopy, QuadtreeNode * & start);
 
        //Private helper function for the destructor
        void clear(QuadtreeNode * start);
 
        //Helper function for buildTree
        QuadtreeNode * buildTree(const PNG & source, int x1, int x2, int y1, int y2);
 
        //Helper for getPixel
        RGBAPixel getPixel(int x, int y, QuadtreeNode * curr, int xlim, int ylim, int width);
 
        //Helper function for decompress
        void decompress(PNG & composite, QuadtreeNode * curr, int x1, int x2, int y1, int y2);
 
        //Helper function for clockwiseRotate
        void clockwiseRotate(QuadtreeNode * croot);
 
        //Helper functions for prune
        void prune(int tolerance, QuadtreeNode * croot);
        bool prunable(int tolerance, QuadtreeNode * node1, QuadtreeNode * node2);
        void clear2(QuadtreeNode * start);
 
        //Helper functions for prunesize
        int prunesize(int tolerance, QuadtreeNode * croot);
        int numLeaves2(QuadtreeNode * croot);
 
        QuadtreeNode* root;    // pointer to root of quadtree
        int dimension;          // Height and width of the PNG represented in the quadtree
 
       
       
       
        /**** Functions added for testing/grading                ****/
        /**** Do not remove this line or copy its contents here! ****/
        #include "quadtree_given.h"
};
 
#endif