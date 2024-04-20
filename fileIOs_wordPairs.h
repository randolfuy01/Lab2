#ifndef FILEIOS_WORDPAIRS_FILEIOS_WORDPAIRS_H
#define FILEIOS_WORDPAIRS_FILEIOS_WORDPAIRS_H
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

void sentenceSplitter( std::string& fname, std::vector<std::string>& sentences);

std::string getText(std::string& fname);

#endif
