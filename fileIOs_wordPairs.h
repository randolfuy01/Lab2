#ifndef FILEIOS_WORDPAIRS_FILEIOS_WORDPAIRS_H
#define FILEIOS_WORDPAIRS_FILEIOS_WORDPAIRS_H

#include <string>
#include <vector>
#include <map>

/**
 * @brief Retrieves text from a file.
 *
 * @param fname The name of the file to open.
 * @return std::string The text from the file.
 */
std::string getText(std::string& fname);

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
void sentenceSplitter(std::string& fname, std::vector<std::string>& sentences);

/**
 * @brief Transcribes all the strings in an input vector into lowercase versions and stores them in an output vector.
 *
 * @param stringVector The vector of strings to be transcribed into lowercase. The vector is passed by reference but remains unchanged.
 * @param lowerCaseStrings An output parameter (passed as a non-const reference) to hold the transcribed lowercase strings.
 *
 * @note The original input vector (stringVector) remains unchanged. A new vector (lowerCaseStrings) is created with all the strings transcribed to lowercase.
 */
void toLowerCase(const std::vector<std::string>& stringVector, std::vector<std::string>& lowerCaseStrings);

/**
 * @brief Splits each sentence in the input vector into words (tokens) and stores
 * them in the output list where each item is a vector of tokens corresponding to a sentence.
 *
 * @param sentences Input vector of sentences to be tokenized. Each string in the vector is treated as a separate sentence.
 * @param sentenceTokensList Output parameter to hold the list of token vectors. Each element in this vector corresponds
 * to a sentence in the input and is a vector of its tokens (words).
 *
 * @note The input vector (sentences) remains unchanged. A new list
 * (sentenceTokensList) is populated with vectors of tokens.
 */
void tokenize(const std::vector<std::string>& sentences, std::vector<std::vector<std::string>>& sentenceTokensList);

/**
 * @brief Sorts the tokens in each group and removes duplicates
 *
 * For each group of tokens in the given list, this function removes duplicate tokens and
 * sorts the remaining tokens in lexicographical order.
 *
 * @param sentenceTokensList A reference to a list of token groups. Each group is a vector
 *                           of strings, and the list is also a vector. The function
 *                           modifies this list in place.
 */
void sortAndRemoveDuplicates(std::vector<std::vector<std::string>>& sentenceTokensList);

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
void wordpairMapping(std::vector<std::string>& sentences,
                     std::map<std::pair<std::string, std::string>, int>& wordpairFreq_map);

#endif
