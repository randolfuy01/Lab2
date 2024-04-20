#include "fileIOs_wordPairs.h"

void sentenceSplitter( std::string& fname, std::vector<std::string>& sentences) {
    std::string currentSentence;
    std::string text = getText(fname);
    for (char character : text) {
        currentSentence += character;
        if (character == '.' || character == '?') {
            if ((character == '.' && currentSentence.size() >= 2 && currentSentence[currentSentence.size() - 2] == '"') ||
                (character == '?' && currentSentence.size() >= 2 && currentSentence[currentSentence.size() - 2] == '"')) {
                continue;
            }
            sentences.push_back(currentSentence);
            currentSentence.clear(); // Reset current sentence
        } else if (character == '\n' || (character == ':' && currentSentence.back() == '\n')) {
            if (!currentSentence.empty()) {
                sentences.push_back(currentSentence);
            }
            currentSentence.clear();
        }
    }
    if (!currentSentence.empty()) {
        sentences.push_back(currentSentence);
    }
}

// Read a file from input
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