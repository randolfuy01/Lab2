#ifndef FILEIOS_WORDPAIRS_FILEIOS_WORDPAIRS_H
#define FILEIOS_WORDPAIRS_FILEIOS_WORDPAIRS_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>

/**
 * @brief Retrieves text from a file.
 *
 * @param fname The name of the file to open.
 * @return std::string The text from the file.
 */
std::string getText(std::string& fname);

/**
 * @brief Splits the text from the given file into sentences and stores them in a vector.
 *
 * @param fname The name of the file to process.
 * @param sentences The vector in which to store the sentences.
 */
void sentenceSplitter(std::string& fname, std::vector<std::string>& sentences);

/**
 * @brief If the string is not empty, adds it to the list of sentences and clears it.
 *
 * @param sentences The current list of sentences.
 * @param currentSentence The current sentence being processed.
 */
void addSentence(std::vector<std::string>& sentences, std::string& currentSentence);

/**
 * @brief Generates a mapping of unique word pairs from sentences to their frequency.
 *
 * This function receives a vector of sentences and generates a map where the keys are word pairs and the values
 * are their frequency. The word pairs are case insensitive and stored in lexicographical (alphabetical) order.
 * Word pairs only contain unique words.
 *
 * @param sentences A vector of raw sentences to be processed.
 * @param wordpairFreq_map A map to hold the output data: word pairs and their frequency.
 *
 * @note
 * Domain of the function: Tokens are case insensitive and white space is the token delimiter.
 * The two words in a word-pair are different (e.g., <the, the> is not valid).
 * Order does not matter between two words in a word-pair (e.g., <college, that> is the same as <that, college>).
 *
 * @warning The function does not return anything, it directly updates the wordpairFreq_map variable.
 */
void wordpairMapping(std::vector<std::string>& sentences,std::map<std::pair<std::string, std::string>, int> &wordpairFreq_map);

#endif
