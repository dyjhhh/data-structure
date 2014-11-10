/**
 * @file pronounce_dict.cpp
 * Implementation of the PronounceDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "pronounce_dict.h"

#include <iterator>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstring>
#include <algorithm>

//using namespace std;
using std::string;
using std::map;
using std::vector;
using std::ifstream;
using std::istream;
using std::istream_iterator;
using std::stringstream;

/** 
 * Constructs a PronounceDict from a CMU pronunciation dictionary
 * file. See http://www.speech.cs.cmu.edu/cgi-bin/cmudict .
 * @param pronun_dict_filename Filename of the CMU pronunciation
 * dictionary.
 */
PronounceDict::PronounceDict(const string& pronun_dict_filename)
{
    ifstream pronun_dict_file(pronun_dict_filename);
    string line;
    if(pronun_dict_file.is_open())
    {
        while(getline(pronun_dict_file, line))
        {
            /* Used to break the line by whitespace. The CMU Dict does this for
             * separating words from their pronunciations. */
            stringstream line_ss(line);
            istream_iterator< string > line_begin(line_ss);
            istream_iterator< string > line_end;
            if(line[0] != '#' && *line_begin != ";;;")
            {   
                /* Associate the word with the rest of the line
                 * (its pronunciation). */
<<<<<<< .mine
                dict[line_begin] = vector< string > (std::next(&line_begin, 1), 
                                                      &line_end);
=======
                dict[*line_begin] = vector< string > (++line_begin,line_end);
>>>>>>> .r44265
            }
        }
    }
    /* If it's not open then... well... just don't do anything for the sake
     * of simplicity. */
}

/** 
 * Constructs a PronounceDict from a CMU std::map mapping the word
 * to a vector of strings which represent the pronunciation.
 * @param pronun_dict_filename Filename of the CMU pronunciation
 * dictionary.
 * @param pronun_dict Maps a string word to a vector of strings
 * representing its pronunciation.
 */
PronounceDict::PronounceDict(const map< string, vector< string > >& 
                             pronun_dict) : dict(pronun_dict)
{
    /* Nothing to see here. */  
}

/** 
 * Uses the dictionary to determine if the two words are homophones.
 * @param word1 First word to be tested.
 * @param word2 Second word to be tested.
 * @return true if the two words are homophones, false otherwise (or
 * one or both words weren't in the dictionary).
 * Note: The word keys in the dictionary are stored in uppercase.
 */
bool PronounceDict::homophones(const string& word1, const string& word2) const
{
    /* Your code goes here! */
    //std::cout<<"reached";
    		
    
    string w1=word1;
    //cout<<"w1 before "<<w1;
    string w2=word2;
   std::transform(w1.begin(), w1.end(), w1.begin(), toupper);
    //std::cout<<"w1"<<w1;
   std::transform(w2.begin(), w2.end(), w2.begin(), toupper);
   
    auto lookup1=dict.find(w1);
    if(lookup1==dict.end())
    {	//std::cout<<"1st";
    	return false;
    }
    auto lookup2=dict.find(w2);
    if(lookup2==dict.end())	
    	{	//std::cout<<"2nd";
    		return false;
    	}
    	//string key1="";
    	//string key2="";
    for(auto it=lookup1->second.begin(),it2=lookup2->second.begin();it!=lookup1->second.end();it++,it2++)
    	{
    		//std::cout<<"reached";
    		if(*it!=*it2)
    			return false;	
    
    	}	
    	//for(auto it2=lookup2->second.begin();it2!=lookup2->second.end();it2++)
    	//	{	string k=*it2;
    			//strcat(key2,k);	
   	//	}
    //if(strcmp(key1,key2) == 0)
    //return true;		

    return true;
}
