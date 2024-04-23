#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>
#include "fileIOs_wordPairs.h"


// Retrieves text from a file.
std::string getText(std::string& fname) {
    std::ifstream inFS(fname);
    std::string fileText;
    if (!inFS.is_open()) {
        if (inFS.fail()) {
            std::cerr << "Error opening file: " << fname << " (Permission denied)" << std::endl;
        } else {
            std::cerr << "Error opening file: " << fname << std::endl;
        }
        return "";
    }
    std::string line;
    while (std::getline(inFS, line)) {
        fileText += line + '\n';
    }
    inFS.close();
    return fileText;
}


// Adds non-empty string to sentences vector and resets string to empty
void addSentence(std::vector<std::string>& sentences, std::string& currentSentence) {
    if (!currentSentence.empty()) {
        sentences.push_back(currentSentence);
        currentSentence.clear(); // Reset current sentence
    }
}


// Splits file text into sentences
void sentenceSplitter(std::string& fname, std::vector<std::string>& sentences) {
    std::string currentSentence;
    std::string text = getText(fname);

    for (const char& character: text) {
        // Skip if leading character is a whitespace or quotations
        if ((isspace(character) || character == '"') && currentSentence.empty()) {
            continue;
        }

        // End of sentence detected (period, question mark, or newline)
        if (character == '.' || character == '?' || character == '\n') {
            addSentence(sentences, currentSentence);
            continue;
        }

        currentSentence += character;

    } // end for loop
    // Add any remaining sentence at the end of the file; if empty, nothing will be added to sentences list
    addSentence(sentences, currentSentence);
}


// Transcribes each string in stringVector to lowercase and stores them in lowerCaseStrings, leaving stringVector unchanged.
void toLowerCase(const std::vector<std::string>& stringVector, std::vector<std::string>& lowerCaseStrings) {
    std::string tempSentence; // Temporary string to hold each individual sentence from stringVector
    std::string lowerCaseSentence; // Not used in this function

    // Iterate over each sentence within stringVector
    for (const std::string& sentence: stringVector) {
        tempSentence = sentence; // Copy current sentence to tempSentence

        // Use std::transform to convert all characters of tempSentence to lower case in-place
        std::transform(tempSentence.begin(), tempSentence.end(), tempSentence.begin(),
                       [](unsigned char c) { return std::tolower(c); });

        // Push the lower case sentence to lowerCaseStrings
        lowerCaseStrings.push_back(tempSentence);
    }
}


// Tokenizes each sentence in the 'sentences' vector and stores the corresponding list of tokens in 'sentenceTokensList'.
void tokenize(const std::vector<std::string>& sentences, std::vector<std::vector<std::string>>& sentenceTokensList) {
    std::string token; // Variable to hold each token (word) extracted from the current sentence
    std::vector<std::string> sentenceTokens; // Vector to store tokens from each sentence
    std::istringstream iss; // istringstream object to aid in tokenizing the sentence

    // Iterate over each sentence
    for (const std::string& sentence: sentences) {
        iss.str(sentence); // Assign the current sentence to the iss
        iss.clear(); // Clear any flags on iss
        // Reset sentenceTokens for the new sentence
        sentenceTokens.clear();

        // Extract each token (word) and push it into sentenceTokens
        while (std::getline(iss, token, ' ')) {
            sentenceTokens.push_back(token);
        }

        // Add the vector of tokens for the current sentence to the main list
        sentenceTokensList.push_back(sentenceTokens);
    }
}


// Sorts the tokens in each group and removes duplicates
void sortAndRemoveDuplicates(std::vector<std::vector<std::string>>& sentenceTokensList) {
    for (std::vector<std::string>& tokenGroup: sentenceTokensList) {
        std::set<std::string> temp(tokenGroup.begin(), tokenGroup.end());
        tokenGroup.assign(temp.begin(), temp.end());
    }
}


// Function to compute the frequency of unique, unordered word pairs from a list of sentences, storing results in a provided map.
void wordpairMapping(std::vector<std::string>& sentences,std::map<std::pair<std::string, std::string>, int>& wordpairFreq_map) {
    // Perform preprocessing on the sentences to generate token pair
    std::vector<std::string> lowerCaseSentences;
    std::vector<std::vector<std::string>> sentenceTokensList;
    toLowerCase(sentences, lowerCaseSentences);
    tokenize(lowerCaseSentences, sentenceTokensList);
    sortAndRemoveDuplicates(sentenceTokensList);

    // Generate and calculate the frequency of unique word pairs
    for (const std::vector<std::string>& tokenGroup: sentenceTokensList) {
        // Generate unique word pairs within the token group
        for (std::size_t i = 0; i < tokenGroup.size() - 1; ++i) {
            for (std::size_t j = i + 1; j < tokenGroup.size(); ++j) {
                std::pair<std::string, std::string> tokenPairs = {tokenGroup[i], tokenGroup[j]};

                // Check if the word pair is already in the map
                auto result = wordpairFreq_map.find(tokenPairs);
                if (result == wordpairFreq_map.end()) {
                    // If the pair is unique, add it to the map with a frequency of 1
                    wordpairFreq_map.insert({tokenPairs, 1});
                } else {
                    // If the pair already exists, increment its frequency
                    ++result->second;
                }
            }
        }
    }
}

// Flips the mapping from word pairs to frequencies to a mapping from frequencies to word pairs.
void freqWordpairMmap(std::map< std::pair<std::string,std::string>, int> &wordpairFreq_map, std::multimap<int, std::pair<std::string, std::string> > &freqWordpair_mmap ){
    for (const auto& pair : wordpairFreq_map) {
        freqWordpair_mmap.insert(std::make_pair(pair.second, pair.first));
    }
}