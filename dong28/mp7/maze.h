#ifndef MAZE_H
#define MAZE_H
#include<stdio.h>
#include"dsets.h"
#include "png.h"
#include<vector>

using namespace std;
 class SquareMaze
 {

	 public : 
	 	SquareMaze();
	 	void makeMaze (int width, int height);
	 	bool canTravel (int x, int y, int dir) const;
	 	void setWall (int x, int y, int dir, bool exists);
	 	vector< int > solveMaze ();
	 	PNG * 	drawMaze () const;
	 	PNG * 	drawMazeWithSolution ();
	 	
 
 	private:
 		DisjointSets disjSets;
 		bool is_maze;
 		int m_width,m_height;
 		vector<bool> down_wall;
 		vector<bool> right_wall;
 		int final;
 };
 #endif