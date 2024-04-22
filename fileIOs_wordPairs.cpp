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

void wordpairMapping(std::vector<std::string>& sentences, std::map<std::pair<std::string, std::string>, int>& wordpairFreq_map) {
    for (const auto& sentence : sentences) {
        std::set<std::string> words; // Use a set instead of a vector
        std::stringstream ss(sentence);
        std::string word;
        while (ss >> word) {
            // remove punctuation and make word lowercase
            if (std::ispunct(word.back()))
                word.pop_back();
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);

            words.insert(word);
        }

        // create word pairs
        for (auto i = words.begin(); i != words.end(); ++i) {
            for (auto j = std::next(i); j != words.end(); ++j) { // Use std::next to get the next iterator 
                std::pair<std::string, std::string> wordpair = std::make_pair(*i, *j);
                if (wordpairFreq_map.find(wordpair) == wordpairFreq_map.end()) {
                    wordpairFreq_map[wordpair] = 1;
                } else {
                    wordpairFreq_map[wordpair]++;
                }
            }
        }
    }
}

void freqWordpairMmap(std::map< std::pair<std::string,std::string>, int> &wordpairFreq_map, std::multimap<int, std::pair<std::string, std::string> > &freqWordpair_mmap ){
    for (const auto& pair : wordpairFreq_map) {
        freqWordpair_mmap.insert(std::make_pair(pair.second, pair.first));
    }
}