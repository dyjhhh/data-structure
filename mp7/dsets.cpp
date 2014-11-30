#include "dsets.h"
#include <iostream>
using namespace std;
void DisjointSets:: addelements(int number)
{
	max_represtative=0;
	int offset=myvector.size();
	for(int i=offset;i<number+offset;i++)
		myvector.push_back(-1);	
	
	//cout<<" "<<mymap[number]<<"\n";
	
}
void DisjointSets::setunion(int element1,int element2)
{
	//cout<<"elements"<<element1<<" "<<element2<<"\n";
	if(element1>=0 && element1<myvector.size() && element2>=0 && element2<myvector.size())
	{
		element1=find(element1);
		element2=find(element2);
		int newsize=myvector[element1] +  myvector[element2];
		if(-(newsize)>=max_represtative)
			max_represtative=-newsize;
		if(element1>element2)
		{
			myvector[element2]=element1;
			myvector[element1]=newsize;
		}
		else
		{
			myvector[element1]=element2;
			myvector[element2]=newsize;
		}	
	}
}

int DisjointSets::find(int number)
{
	if(number >=0 && number < myvector.size())
	{
		if( ( myvector[number]<0) )
		{
			return number;
		}
			
		myvector[number]=find(myvector[number]);
		return myvector[number];
	}
	else
		return number;
}

bool DisjointSets:: no_moreDsets()
{
	//cout<<max_represtative;
	if(max_represtative==myvector.size())
	{
		//for(int i=0;i<myvector.size();i++)
		//	cout<<" "<<myvector[i];
		//cout<<"\n";	
		return true;
	}
	else
		return false;
}