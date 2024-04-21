#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "fileIOs_wordPairs.h"

void toLowerCase(std::vector<std::string>& vector, std::string basicString);

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

// Splits file text into sentences
void sentenceSplitter(std::string& fname, std::vector<std::string>& sentences) {
    std::string currentSentence;
    std::string text = getText(fname);

    for (const char& character : text) {
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

// Adds non-empty string to sentences vector and resets string to empty
void addSentence(std::vector<std::string>& sentences, std::string& currentSentence) {
    if (!currentSentence.empty()) {
        sentences.push_back(currentSentence);
        currentSentence.clear(); // Reset current sentence
    }
}

// Function to compute the frequency of unique, unordered word pairs from a list of sentences, storing results in a provided map.
void wordpairMapping(std::vector<std::string>& sentences,std::map<std::pair<std::string, std::string>, int> &wordpairFreq_map) {
  std::vector<std::string> lowerCaseSentences;
  toLowerCase(sentences, lowerCaseSentences);


  std::vector<std::string> sentenceTokens;
  std::string token;
  std::istringstream iss;
  for (const std::string& sentence : sentences) {
    iss.str(sentence);
    iss.clear();
    while (std::getline(iss, token, ' ')) {
      sentenceTokens.push_back(token);
    }

  }

  // For each sentence (The big red fox went down the street)
  // Lower case each word
  // Tokenize: 1. The 2. big 3. red 4.fox 5.went ...
  // Alphabatize the list of words
  // Compare each word with each other,
  // If the pair is unique, place into wordpairFreq_map and increase its frequency
  // If the pair is not unique, increase the frequency



}

// Transcribes each string in stringVector to lowercase and stores them in lowerCaseStrings, leaving stringVector unchanged.
void toLowerCase(std::vector<std::string>& stringVector, std::vector<std::string>& lowerCaseStrings) {
  std::string tempSentence;
  std::string lowerCaseSentence;
  for (const std::string& sentence : stringVector) {
    tempSentence = sentence;
    std::transform(tempSentence.begin(), tempSentence.end(), tempSentence.begin(), [](unsigned char c) {return std::tolower(c); });
    lowerCaseStrings.push_back(tempSentence);
  }

}
