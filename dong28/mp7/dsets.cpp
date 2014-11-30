#include "dsets.h"
#include <iostream>
using namespace std;
void DisjointSets:: addelements(size_t number)
{
	max_represtative=0;
        int offset=myvector.size();
	for(unsigned int i=offset;i<number+offset;i++)
		myvector.push_back(-1);	
	
	//cout<<" "<<mymap[number]<<"\n";
	
}
void DisjointSets::setunion(size_t  element1,size_t element2)
{
	//cout<<"elements"<<element1<<" "<<element2<<"\n";
	if( element1<myvector.size() && element2<myvector.size())
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

int DisjointSets::find(size_t number)
{
	if(number < myvector.size())
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
  if(max_represtative>=0)
{
  if((unsigned) max_represtative==myvector.size())
	{
		//for(int i=0;i<myvector.size();i++)
		//	cout<<" "<<myvector[i];
		//cout<<"\n";	
		return true;
	}
	else
		return false;
}
  else 
    return false;
}
