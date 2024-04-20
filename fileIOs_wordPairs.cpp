#include "fileIOs_wordPairs.h"

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
    for (char character : text) {
        // Skip if leading character is a whitespace or quotations
        if ((isspace(character) || character == '"') && currentSentence.empty()) {
            continue;
        }

        currentSentence += character;

        // Handling periods and question marks (end of a sentence)
        if (character == '.' || character == '?') {
            if (currentSentence.size() >= 2 && currentSentence[currentSentence.size() - 2] == '"') {
                continue;
            }
            addSentence(sentences, currentSentence);
        }

        // Handling newlines and colons
        else if (character == '\n' || (character == ':' && currentSentence.back() == '\n')) {
            addSentence(sentences, currentSentence);
        }
    }
    // Handle the last sentence
    addSentence(sentences, currentSentence);
}

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