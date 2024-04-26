#include "fileIOs_wordPairs.h"

// Adds a non-empty sentence to a vector and resets the working string.
void addSentence(std::vector<std::string> &sentences, std::string &currentSentence) {
    if (!currentSentence.empty()) {
        sentences.push_back(currentSentence);
        currentSentence.clear();                // Clear the current sentence for reuse
    }
}

// Reads text from a file and splits it into sentences based on punctuation.
void sentenceSplitter(std::string &fname, std::vector<std::string> &sentences) {
    std::string currentSentence;
    std::string text = getText(fname);

    for (const char &character: text) {
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
    }

    // Add any remaining sentence at the end of the file; if empty, nothing will be added to sentences list
    addSentence(sentences, currentSentence);
}

// Reads text from a specific file.
std::string getText(std::string &fname) {
    std::ifstream inFS(fname);
    std::string fileText;

    // Check for successful file opening and handle potential errors
    if (!inFS.is_open()) {
        if (inFS.fail()) {
            std::cerr << "Error opening file: " << fname << " (Permission denied)" << std::endl;
        } else {
            std::cerr << "Error opening file: " << fname << std::endl;
        }
        return "";
    }

    // Read file content line by line
    std::string line;
    while (std::getline(inFS, line)) {
        fileText += line + '\n';
    }

    inFS.close();
    return fileText;
}

// Maps and counts frequency of unique word pairs form a collection of sentences.
void wordpairMapping(std::vector<std::string> &sentences, std::map<std::pair<std::string, std::string>, int> &wordpairFreq_map) {

    for (const auto &sentence: sentences) {
        std::set<std::string> words; // Use a set to handle duplication and sorting lexicographically
        std::stringstream ss(sentence);
        std::string word;

        // Extract words from the stream, normalize, and add to the set
        while (ss >> word) {
            std::transform(word.begin(), word.end(), word.begin(), ::tolower); // lowercase the word
            words.insert(word);
        }

        // Generate all possible unique word pairs from the collected words
        for (auto i = words.begin(); i != words.end(); ++i) {
            for (auto j = std::next(i); j != words.end(); ++j) {
                wordpairFreq_map[std::make_pair(*i, *j)]++;
            }

        }
    }
}

// Transfers word pair frequencies into a multimap sorted by frequency.
void freqWordpairMmap(std::map<std::pair<std::string, std::string>, int> &wordpairFreq_map, std::multimap<int, std::pair<std::string, std::string> > &freqWordpair_mmap) {
    for (const auto &pair: wordpairFreq_map) {
        freqWordpair_mmap.insert(std::make_pair(pair.second, pair.first));
    }
}

// Outputs the most and least frequent word pairs to a specified file.
void printWordpairs(std::multimap<int, std::pair<std::string, std::string>> &freqWordpair_multimap, std::string outFname, int topCnt, int botCnt) {
    std::ofstream out(outFname);

    if (out.is_open()) {
        std::multimap<int, std::pair<std::string, std::string>>::iterator iterator = freqWordpair_multimap.begin();

        // Output the top most frequent word pairs
        for (int i = 0; i < topCnt; ++i) {
            out << "<" << (*iterator).second.first << ", " << (*iterator).second.second << ">: " << (*iterator).first
                << std::endl;
            iterator++;
        }

        iterator = freqWordpair_multimap.end();
        std::advance(iterator, -botCnt);

        // Output the least frequent word pairs
        for (int i = 0; i < botCnt; ++i) {
            out << "<" << (*iterator).second.first << ", " << (*iterator).second.second << ">: " << (*iterator).first
                << std::endl;
            iterator++;
        }
        out.close();

    } else {
        std::cerr << "Error opening file: " << outFname << std::endl;
        return;
    }
}
