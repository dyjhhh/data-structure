/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>
#include <vector>
#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of "StringTriples" (a typedef'd std::tuple, see top of 
 * cartalk_puzzle.h). Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector< StringTriple > cartalk_puzzle(PronounceDict d,
                                      const string& word_list_fname)
{
    /* Your code goes here! */
    vector<string > myvector;
    ifstream words(word_list_fname);
	string word;
	
	if(words.is_open())
	{
        	while(getline(words, word))
    		{
        		myvector.push_back(word);
    		}
    	}

	vector<string >::iterator it;
    	for(it=myvector.begin();it!=myvector.end();it++)
    		{
    			vector<string >::iterator it2;
    			for(it2=it;it2!=myvector.end();it2++)
    			{
    				if(d.homophones(*it,*it2) && *it!=*it2)
				{	vector<string >::iterator it3;
    					for(it3=it2;it3!=myvector.end();it3++)	
    						if(d.homophones(*it3,*it2) && *it3!=*it2)
    						{
    						vector< StringTriple > result = { StringTriple(*it,*it2,*it3) } ;
    							return result;	
    						}		
    				}
    			}
    	
    		}

    return vector< StringTriple >();
}
