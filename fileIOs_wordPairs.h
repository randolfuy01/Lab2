#ifndef FILEIOS_WORDPAIRS_FILEIOS_WORDPAIRS_H
#define FILEIOS_WORDPAIRS_FILEIOS_WORDPAIRS_H
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

/**
 * @brief If the string is not empty, adds it to the list of sentences and clears it.
 *
 * @param sentences The current list of sentences.
 * @param currentSentence The current sentence being processed.
 */
void addSentence(std::vector<std::string>& sentences, std::string& currentSentence);

/**
 * @brief Splits the text from the given file into sentences and stores them in a vector.
 *
 * @param fname The name of the file to process.
 * @param sentences The vector in which to store the sentences.
 */
void sentenceSplitter( std::string& fname, std::vector<std::string>& sentences);

/**
 * @brief Retrieves text from a file.
 *
 * @param fname The name of the file to open.
 * @return std::string The text from the file.
 */
std::string getText(std::string& fname);

#endif
