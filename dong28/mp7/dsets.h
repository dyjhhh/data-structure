#ifndef DSETS_H
#define DSETS_H
#include<vector>
#include <map>
using namespace std;
class DisjointSets {

	public:

		void addelements(size_t number);
		void setunion(size_t element1,size_t element2);
		int find(size_t number);
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
