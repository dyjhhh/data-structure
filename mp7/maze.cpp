#include"maze.h"
#include <time.h> 
#include <map>
#include<iostream>
#include<vector>
#include <queue>  
#include <algorithm>
using namespace std;
SquareMaze::SquareMaze()
{
	is_maze=false;
}

void SquareMaze:: makeMaze (int width, int height)
{
	if(is_maze==true)
	{
		is_maze=false;
		down_wall.clear();
		right_wall.clear();
		disjSets.remove();
		is_maze=false;
	}
	if(is_maze==false)
	{
		is_maze=true;
		m_width=width;
		m_height=height;
		srand (time(NULL));
		//start creating maze
		disjSets.addelements(width*height);
		for(int i=0;i<width*height;i++)
		{
			down_wall.push_back(true);
			right_wall.push_back(true);
		}
		/*for(int i=0;i<down_wall.size();i++)
			cout<<" "<<down_wall[i];
		cout<<"\n";
		for(int i=0;i<right_wall.size();i++)
			cout<<" "<<right_wall[i];
		cout<<"\n";			
		*/
		
		//need some way to run below lines recursively
		while(disjSets.no_moreDsets()!=true)
		{
			int down_index = rand() % down_wall.size();
			int right_index= down_index;
			//int right_index=rand() % right_wall.size();
		
			if(down_wall[down_index]==true && !(down_index>=down_wall.size()-m_width))
			{
				if(disjSets.find(down_index)!=disjSets.find(down_index+m_width))
				{
					down_wall[down_index]=false;
					disjSets.setunion(down_index,down_index+width);	
				}
			}
			if(right_wall[right_index]==true && (right_index%(m_width)!=m_width-1))
				
			{
				if(disjSets.find(down_index)!=disjSets.find(down_index+1))
				{
					right_wall[right_index]=false;
					disjSets.setunion(right_index,right_index+1);	
				}
			}	
		}
			/*
			cout<<"Removed the wall=0 \nThe wall exist=1 \n down wall \n";
			for(int i=0;i<down_wall.size();i++)
				cout<<" "<<down_wall[i];
			cout<<"\n right walls\n";
			for(int i=0;i<right_wall.size();i++)
				cout<<" "<<right_wall[i];
			cout<<"\n";
			*/			
	}//is maze==false
}

bool SquareMaze::canTravel (int x, int y, int dir) const
{	
	bool ret_val=false;
	if(x>=m_width || y>=m_height)
		return ret_val;	
	else
	{
		int index=m_width*y+x;
		//cout<<"index"<<index<<"\n";
		if(dir==0)//right step
		{
			if(right_wall[index]==false )
				ret_val=true;
		}
		else if(dir==1)// down step
		{
			if(down_wall[index]==false )
				ret_val=true;

		}
		else if(dir==2)// left step
		{
			if(index>0)
			{
				if(right_wall[index-1]==false )
					ret_val=true;
			}
		}
		else if(dir==3)//up step
		{
			if(index>m_width-1)//make sure go up from second row only
			{
				
				if(down_wall[index-m_width]==false)
					ret_val=true;
			}	
		}
		return ret_val;
	}
	
}

void SquareMaze:: setWall (int x, int y, int dir, bool exists)
{
	int index=m_width*y+x;
	if(dir==0)
	{
		if(exists)
			right_wall[index]=true;
		else
			right_wall[index]=false;
		
	}
	if(dir==1)
	{
		if(exists)
			down_wall[index]=true;
		else
			down_wall[index]=false;
		
	}
}


vector< int > SquareMaze:: solveMaze ()
{	
	//create adjacency list
	 map<int,vector<int> > adjacency_list;
	 for(int i=0;i<m_width;i++)
	 {
	 	for(int j=0;j<m_width;j++)
	 	{	vector<int> adjacent_cells;
	 		int index=m_width*i+j;
	 		//cout<<index<<endl;
	 		if(canTravel(j,i,2))
	 		{
	 			//push left neighbour 
	 			//cout<<"left free for "<<i<<j<<endl;
	 			adjacent_cells.push_back(index-1);
	 		}
	 		if(canTravel(j,i,0))
	 		{
	 			//push right neighbour
	 			//cout<<"right free for "<<i<<j<<endl; 
	 			adjacent_cells.push_back(index+1);
	 		}
	 		if(canTravel(j,i,1))
	 		{
	 			//push down neighbour 
	 			//cout<<"down free for "<<i<<j<<endl;
	 			adjacent_cells.push_back(index+m_width);
	 		}
	 		if(canTravel(j,i,3))
	 		{
	 			//push up neighbour 
	 			//cout<<"up free for "<<i<<j<<endl;
	 			adjacent_cells.push_back(index-m_width);
	 		}
	 		//cout<<adjacent_cells.size()<<endl;
	 		adjacency_list.insert((make_pair(index, adjacent_cells)));
	 	}
	 }
	//initalize predecssor and distance
	int p[m_width*m_height],d[m_width*m_height];
	//start bfs
	vector<int> vertices;
	for(int i=0;i<m_width*m_height;i++)
	{
		// mark all vertices unvisted
		vertices.push_back(-1);
		d[i]=0;
	}
	for(int i=0;i<m_width*m_height;i++)
	{
		if(vertices[0]==-1)
		{
			//start bfs on the vertex
			queue<int> myqueue;	
			vertices[0]=1; //mark as visted
			d[0]=0;
			p[0]=-1;	
			myqueue.push(0);
			while(!myqueue.empty())
			{
				int front=myqueue.front();
				//cout<<"ran ";
				myqueue.pop();
				vector<int> adj_vertex=adjacency_list[front];
				for(int j=0;j<adj_vertex.size();j++)
				{
					if(vertices[adj_vertex[j]]==-1)
					{
						vertices[adj_vertex[j]]=1;//mark as visited
						p[adj_vertex[j]]=front;
						d[adj_vertex[j]]=1+d[front];
						//cout<<d[i]<<" ";
						myqueue.push(adj_vertex[j]);
						//cout<<"ran ";
					}
				}
			}
			//cout<<"\n";
		}
	}
	
	
	//check the distances
	vector<int> long_path;
	for(int i=m_width*m_height-m_width;i<m_width*m_height;i++)
		long_path.push_back(d[i]);
		
	//return the path
	std::sort (long_path.begin(), long_path.end()); 
	//for(int i=0;i<long_path.size();i++)
	//	cout<<long_path[i]<<endl;
	int path_length=long_path[long_path.size()-1];
	int path_index;
	for(int i=m_width*m_height-m_width;i<m_width*m_height;i++)
	{
		if(path_length==d[i])
		{
			path_index=i;
			final=i;
			break;
		}	
	}
	//cout<<path_index;
	vector<int> final_path;
	while(path_index!=0)
	{
		//cout<<path_index<<endl;
		int curr_x=path_index%m_width;
		int curr_y=path_index/m_width;
		int prev=p[path_index];
		//cout<<prev<<endl;
		int prev_x=prev%m_width;
		int prev_y=prev/m_width;
		if(curr_x==prev_x+1 && curr_y==prev_y)
		{
			//cout<<"right";
			final_path.push_back(0);
		}
		if(curr_x==prev_x-1 && curr_y==prev_y)
		{
			//cout<<"left";
			final_path.push_back(2);
		}
		if(curr_x==prev_x && curr_y==prev_y+1)
		{
			//cout<<"down";
			final_path.push_back(1);
		}
		if(curr_x==prev_x && curr_y==prev_y-1)
		{
			//cout<<"up";	
			final_path.push_back(3);
		}
		path_index=prev;
	}
	std::reverse(final_path.begin(),final_path.end());
	return final_path;	
}





PNG * SquareMaze::drawMaze () const
{	
	PNG *image=new PNG(m_width*10+1,m_height*10+1);
	image->operator()(0,0)->blue=0;
	image->operator()(0,0)->green=0;
	image->operator()(0,0)->red=0;
	for ( int i = 10; i < (m_width*10)+1; i++)
	{
		image->operator()(i,0)->blue=0;
		image->operator()(i,0)->green=0;
		image->operator()(i,0)->red=0;
	}
	for ( int j  = 0; j < (m_height*10+1); j++)
	{
		image->operator()(0,j)->blue=0;
		image->operator()(0,j)->green=0;
		image->operator()(0,j)->red=0;
	}
	for(int i = 0; i < m_width; i++) 
	{
		for(int j = 0; j < m_height; j++)
		 {
			int index =m_width*j+i ;
			if(right_wall[index]==true) 
			{
				for(int k = 0; k <= 10; k++) 
				{
					image->operator()((i + 1) * 10, j * 10 + k)->red = 0;
					image->operator()((i + 1) * 10, j * 10 + k)->green = 0;
					image->operator()((i + 1) * 10, j * 10 + k)->blue = 0;
				}
			}
			if(down_wall[index]==true) 
			{
				for(int k = 0; k <= 10; k++) 
				{
					image->operator()(i * 10 + k, (j + 1) * 10)->red = 0;
					image->operator()(i * 10 + k, (j + 1) * 10)->green = 0;
					image->operator()(i * 10 + k, (j + 1) * 10)->blue = 0;
				}
			}
		}
	}		
	return image;	
}
	 	



PNG * SquareMaze::drawMazeWithSolution ()
{
	vector<int> solution=solveMaze();
	PNG *image=drawMaze();
	int x=5,y=5;
	
 	for(int i=0;i<solution.size();i++)
 	{     
 		
		if(solution[i]==0) 	
 		{
 			for(int k=0;k<11;k++)
			{
				image->operator()(x+k,y)->blue=0;
				image->operator()(x+k,y)->green=0;
				image->operator()(x+k,y)->red=255;
					
			}
			x=x+10;
			
		}
		if(solution[i]==1) 	
 		{
 			for(int k=0;k<11;k++)
			{
				image->operator()(x,y+k)->blue=0;
				image->operator()(x,y+k)->green=0;
				image->operator()(x,y+k)->red=255;	
			}
			y=y+10;
			
		}
		if(solution[i]==2) 	
 		{
 			for(int k=0;k<11;k++)
			{
				image->operator()(x-k,y)->blue=0;
				image->operator()(x-k,y)->green=0;
				image->operator()(x-k,y)->red=255;	
			}
			x=x-10;
			
		}
		if(solution[i]==3) 	
 		{
 			for(int k=0;k<11;k++)
			{
				image->operator()(x,y-k)->blue=0;
				image->operator()(x,y-k)->green=0;
				image->operator()(x,y-k)->red=255;	
			}
			y=y-10;
			
		}
	}
	//cout<<path_index;
	x=final%m_width;
	y=final/m_width;
	
	for(int k=1;k<=9;k++)
	{
		image->operator()(x*10+k,(y+1)*10)->blue=255;
		image->operator()(x*10+k,(y+1)*10)->green=255;
		image->operator()(x*10+k,(y+1)*10)->red=255;	
	}
	
	return image;	
}