#include "fileIOs_wordPairs.h"
#include "fileIOs_wordPairs.h"

void sentenceSplitter( std::string& fname, std::vector<std::string>& sentences) {
    std::string currentSentence;
    std::string text = getText(fname);
    for (char character : text) {
        currentSentence += character;

        // Check for sentence boundaries
        if (character == '.' || character == '?') {
            // Check for special cases: period + double quotation mark or question mark + double quotation mark
            if ((character == '.' && currentSentence.size() >= 2 && currentSentence[currentSentence.size() - 2] == '"') ||
                (character == '?' && currentSentence.size() >= 2 && currentSentence[currentSentence.size() - 2] == '"')) {
                continue; // Ignore as it's not the end of a sentence
            }
            sentences.push_back(currentSentence);
            currentSentence.clear(); // Reset current sentence
        } else if (character == '\n' || (character == ':' && currentSentence.back() == '\n')) {
            // Newline character or colon followed by newline character marks the end of a paragraph,
            // treat it as a sentence delimiter
            if (!currentSentence.empty()) {
                sentences.push_back(currentSentence);
            }
            currentSentence.clear(); // Reset current sentence
        }
    }

    // Add the last sentence if it's not empty
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