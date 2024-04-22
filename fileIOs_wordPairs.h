#ifndef FILEIOS_WORDPAIRS_FILEIOS_WORDPAIRS_H
#define FILEIOS_WORDPAIRS_FILEIOS_WORDPAIRS_H
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream> 
#include <string>
#include <map>
#include <algorithm>
#include <set>

void sentenceSplitter( std::string& fname, std::vector<std::string>& sentences);

std::string getText(std::string& fname);

void wordpairMapping( std::vector<std::string>& sentences, std::map< std::pair<std::string,std::string>, int> &wordpairFreq_map);

void freqWordpairMmap(std::map< std::pair<std::string,std::string>, int> &wordpairFreq_map, std::multimap<int, std::pair<std::string, std::string> > &freqWordpair_mmap );

#endif
