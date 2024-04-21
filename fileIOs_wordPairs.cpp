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

// Splits file text into sentences
void sentenceSplitter(std::string& fname, std::vector<std::string>& sentences) {
    std::string currentSentence;
    std::string text = getText(fname);

    for (char character : text) {
        // Skip if leading character is a whitespace or quotations
        if ((isspace(character) || character == '"') && currentSentence.empty()) {
            continue;
        }

        // End of sentence detected (period, question mark, or newline)
        if (character == '.' || character == '?' || character == '\n') {
            addSentence(sentences, currentSentence);
            continue;
        }

        // Handling newlines or colons following newlines
        if (character == '\n' || (character == ':' && currentSentence.back() == '\n')) {
            addSentence(sentences, currentSentence);
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

}
