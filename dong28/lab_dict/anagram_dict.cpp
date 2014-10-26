/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>
#include <iostream>
using namespace std;
using std::string;
using std::vector;
using std::ifstream;

/** 
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */ 
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
	ifstream words(filename);
	string word;
	
	if(words.is_open())
	{	
    		/* Reads a line from words into word until the file ends. */
    		while(getline(words, word))
    		{	string val=word;
        		std::sort(val.begin(), val.end());
			dict[val].push_back(word);
    		}
	}
}	

/** 
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */ 
AnagramDict::AnagramDict(const vector< string >& words)
{
    /* Your code goes here! */
    std::vector<string>::const_iterator it;
    for(it=words.begin();it<words.end();it++)
    {
    	string val=*it;
    	std::sort(val.begin(), val.end());
    	dict[val].push_back(*it);
    }
    
	
}

/**
 * @param word The word to find anagrams of. 
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the 
 * word list.
 */
vector< string > AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    string val=word;
    std::sort(val.begin(), val.end());
    auto lookup = dict.find(val);
 	if(lookup!=dict.end())
 	return lookup->second;
       else
       	 return vector< string >();
	
}
/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector< vector< string > > AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector< vector < string > > myvector;
    
    for(auto it=dict.begin();it!=dict.end();it++)
    	{       //cout<<"data\n"<< it->second;
    		if(it->second.size()>1)
    		myvector.push_back(it->second);
    	}
   
    return myvector;
    //else
    // return vector< vector < string > >();
}
