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
        std::set<std::string> words; // Use a set
        std::stringstream ss(sentence);
        std::string word;
        while (ss >> word) {
            // remove punctuation and make word lowercase

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

void printWordpairs(std::multimap<int, std::pair<std::string, std::string>> &freqWordpair_multimap, std::string outFname, int topCnt, int botCnt) {
    std::ofstream out(outFname);
    if (out.is_open()) {

        std::multimap<int, std::pair<std::string, std::string>>::iterator iterator = freqWordpair_multimap.begin();

        for (int i = 0; i < topCnt; ++i) {
            out << "<" << (*iterator).second.first << ", " << (*iterator).second.second << ">: " << (*iterator).first << std::endl;
            iterator++;
        }

        iterator = freqWordpair_multimap.end();
        std::advance(iterator, -botCnt);

        for (int i = 0; i < botCnt; ++i) {
            out << "<" << (*iterator).second.first << ", " << (*iterator).second.second << ">: " << (*iterator).first << std::endl;
            iterator++;
        }

        out.close();
    }
    else {
        std::cerr << "Error opening file: " << outFname << std::endl;
        return;
    }
}