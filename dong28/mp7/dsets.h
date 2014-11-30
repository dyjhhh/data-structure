#ifndef DSETS_H
#define DSETS_H
#include<vector>
#include <map>
using namespace std;
class DisjointSets {

	public:

		void addelements(int number);
		void setunion(int element1,int element2);
		int find(int a);
		bool no_moreDsets();
		void remove()
		{
			myvector.clear();
		}
	private: 
		 vector<int> myvector;
		 
		 int max_represtative;
		

};


#endif