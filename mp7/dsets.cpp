#include "dsets.h"
#include <iostream>
using namespace std;
void DisjointSets:: addelements(size_t number)
{
	max_represtative=0;
        int offset=myvector.size();
	for(unsigned int a=offset;a<number+offset;a++)
		myvector.push_back(-1);	
	
	}
void DisjointSets::setunion(size_t element1,size_t element2)
{
       	if( element1<myvector.size() && element2<myvector.size())
	{
		element1=find(element1);
		element2=find(element2);
		int size=myvector[element1] +  myvector[element2];
		if(-(size)>=max_represtative)
			max_represtative=-size;
		if(element1>element2)
		{
			myvector[element2]=element1;
			myvector[element1]=size;
		}
		else
		{
			myvector[element1]=element2;
			myvector[element2]=size;
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
  if(max_represtative>=0)
{
  if((unsigned) max_represtative==myvector.size())
	{
		return true;
	}
	else
		return false;
}
  else 
    return false;
}
