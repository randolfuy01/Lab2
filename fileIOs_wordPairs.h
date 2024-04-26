#ifndef FILEIOS_WORDPAIRS_FILEIOS_WORDPAIRS_H
#define FILEIOS_WORDPAIRS_FILEIOS_WORDPAIRS_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>
#include <set>

/**
 * @brief Adds a non-empty sentence to a vector and clears the sentence.
 *
 * This function checks if the provided `currentSentence` is non-empty. If it is, the sentence
 * is added to the `sentences` vector. After adding the sentence, it clears `currentSentence`
 * to prepare for the next sentence collection. This is useful in contexts where sentences are
 * accumulated and processed sequentially.
 *
 * @param sentences A reference to a vector of strings where the sentence will be added.
 * @param currentSentence A reference to a string that contains the current sentence to be added.
 *        This string will be cleared after adding to the vector if it is not empty.
 */
void addSentence(std::vector<std::string> &sentences, std::string &currentSentence);

/**
 * @brief Splits the contents of a file into sentences and stores them into a vector.
 *
 * This function reads the contents of a file specified by the file name. It then parses the text
 * content and divides it into sentences based on punctuation marks and newline characters. Each
 * detected sentence is added to the provided vector. Sentences are determined by the presence
 * of periods, question marks, or newline characters. Leading whitespaces and quotation marks
 * are ignored while identifying the start of a new sentence.
 *
 * @param fname A reference to a string containing the filename from which to read the text.
 * @param sentences A reference to a vector of strings where the discovered sentences will be stored.
 */
void sentenceSplitter(std::string &fname, std::vector<std::string> &sentences);

/**
 * @brief Reads the entire content of a file into a single string.
 *
 * This function attempts to open a file specified by the filename and reads its contents into a string.
 * If the file is successfully opened, it reads the file line by line, appending each line to the
 * resultant string along with a newline character. If the file cannot be opened, it logs an error message
 * to the standard error stream indicating the issue, which could be due to the file not being found or
 * permission being denied. The function will return an empty string if it fails to open the file.
 *
 * @param fname A reference to a string containing the filename to read from.
 * @return A string containing the content of the file, or an empty string if the file could not be opened.
 */
std::string getText(std::string &fname);

/**
 * @brief Maps and counts frequency of unique word pairs in sentences.
 *
 * This function processes a list of sentences, extracting and normalizing words by removing punctuation
 * and converting them to lowercase. It uses a set to collect unique words from each sentence. Then, for each
 * unique pair of words within a sentence, it creates a pair and maps it in a map with an integer that tracks
 * the frequency of each word pair's occurrence across all sentences. If a pair is encountered for the first
 * time, it is added to the map with a count of 1. If the pair already exists in the map, its count is incremented.
 *
 * @param sentences A reference to a vector of strings containing sentences.
 * @param wordpairFreq_map A reference to a map where keys are pairs of strings (word pairs) and values are integers representing the frequency of each word pair.
 */
void wordpairMapping(std::vector<std::string> &sentences,
                     std::map<std::pair<std::string, std::string>, int> &wordpairFreq_map);

/**
 * @brief Transfers word pair frequencies into a multimap sorted by frequency.
 *
 * This function takes each word pair and its associated frequency from a map and inserts them into a multimap.
 * In this multimap, the frequency of the word pairs serves as the key, which allows the entries to be sorted
 * by frequency. The word pairs then become the values. This structure is especially useful for quick lookup,
 * sorting, and iterating through word pairs based primarily on their frequency of occurrence.
 *
 * @param wordpairFreq_map A reference to a map from which word pairs and their frequencies are read.
 *        The map's keys are word pairs (pair of strings), and the values are integers representing the frequencies.
 * @param freqWordpair_mmap A reference to a multimap where the integer frequencies are the keys and
 *        the word pairs (pair of strings) are the values. This is filled by the function to allow sorting
 *        and efficient frequency-based retrieval.
 */
void freqWordpairMmap(std::map<std::pair<std::string, std::string>, int> &wordpairFreq_map,
                      std::multimap<int, std::pair<std::string, std::string> > &freqWordpair_mmap);

/**
 * @brief Outputs the most and least frequent word pairs to a specified file.
 *
 * This function writes the top and bottom 'n' frequent word pairs from a multimap to a specified output file.
 * The multimap should have frequencies as keys and word pairs as values, sorted by frequency. It first
 * writes the top `topCnt` frequent pairs from the beginning of the multimap. Then, it writes the bottom
 * `botCnt` frequent pairs starting from the end of the multimap. If there is an issue in opening the output
 * file, an error message is displayed.
 *
 * @param freqWordpair_multimap A reference to a multimap that contains word pairs sorted by their frequencies.
 * @param outFname The filename where the result will be printed.
 * @param topCnt The number of top frequent word pairs to print.
 * @param botCnt The number of least frequent word pairs to print.
 */
void
printWordpairs(std::multimap<int, std::pair<std::string, std::string> > &freqWordpair_multimap, std::string outFname,
               int topCnt,
               int botCnt);


// Standardize Unit Testing
// 2 unit tests for each function: sentenceSplitter(), wordPairMapping(), freqWordPairMmap()
// 1 end to end unit test for the file the professor provided

inline bool wordPairMappingUnitTest1() {
    std::vector<std::string> sentences = {
            "The first story is about connecting the dots.",
            "The first story is about connecting the dots.",
            "The first story is about connecting the dots."
    };
    std::map<std::pair<std::string, std::string>, int> wordpairFreq_map;
    wordpairMapping(sentences, wordpairFreq_map);

    // Verify the wordpairFreq_map contains the expected word pairs and frequencies
    std::map<std::pair<std::string, std::string>, int> expectedWordpairFreq_map = {
            {{"about",      "connecting"}, 3},
            {{"about",      "dots."},      3},
            {{"about",      "first"},      3},
            {{"about",      "is"},         3},
            {{"about",      "story"},      3},
            {{"about",      "the"},        3},
            {{"connecting", "dots."},      3},
            {{"connecting", "first"},      3},
            {{"connecting", "is"},         3},
            {{"connecting", "story"},      3},
            {{"connecting", "the"},        3},
            {{"dots.",      "first"},      3},
            {{"dots.",      "is"},         3},
            {{"dots.",      "story"},      3},
            {{"dots.",      "the"},        3},
            {{"first",      "is"},         3},
            {{"first",      "story"},      3},
            {{"first",      "the"},        3},
            {{"is",         "story"},      3},
            {{"is",         "the"},        3},
            {{"story",      "the"},        3}
    };
    bool test = false;
    for (const auto &pair: expectedWordpairFreq_map) {
        if (wordpairFreq_map[pair.first] != pair.second) {
            return test;
        }
    }
    test = true;
    return test;
}

inline bool wordPairMappingUnitTest2() {
    std::vector<std::string> sentences = {
            "We are going to steal the moon!",
            "He was not going to be this villain."
    };
    std::map<std::pair<std::string, std::string>, int> wordpairFreq_map;

    std::map<std::pair<std::string, std::string>, int> expectedWordpairFreq_map = {
            {{"are",      "going"},    1},
            {{"are",      "moon!"},    1},
            {{"are",      "steal"},    1},
            {{"are",      "the"},      1},
            {{"are",      "to"},       1},
            {{"are",      "we"},       1},
            {{"be",       "going"},    1},
            {{"be",       "he"},       1},
            {{"be",       "not"},      1},
            {{"be",       "this"},     1},
            {{"be",       "to"},       1},
            {{"be",       "villain."}, 1},
            {{"be",       "was"},      1},
            {{"going",    "he"},       1},
            {{"going",    "moon!"},    1},
            {{"going",    "not"},      1},
            {{"going",    "steal"},    1},
            {{"going",    "the"},      1},
            {{"going",    "this"},     1},
            {{"going",    "to"},       2},
            {{"going",    "villain."}, 1},
            {{"going",    "was"},      1},
            {{"going",    "we"},       1},
            {{"he",       "not"},      1},
            {{"he",       "this"},     1},
            {{"he",       "to"},       1},
            {{"he",       "villain."}, 1},
            {{"he",       "was"},      1},
            {{"moon!",    "steal"},    1},
            {{"moon!",    "the"},      1},
            {{"moon!",    "to"},       1},
            {{"moon!",    "we"},       1},
            {{"not",      "this"},     1},
            {{"not",      "to"},       1},
            {{"not",      "villain."}, 1},
            {{"not",      "was"},      1},
            {{"steal",    "the"},      1},
            {{"steal",    "to"},       1},
            {{"steal",    "we"},       1},
            {{"the",      "to"},       1},
            {{"the",      "we"},       1},
            {{"this",     "to"},       1},
            {{"this",     "villain."}, 1},
            {{"this",     "was"},      1},
            {{"to",       "villain."}, 1},
            {{"to",       "was"},      1},
            {{"to",       "we"},       1},
            {{"villain.", "was"},      1}
    };

    wordpairMapping(sentences, wordpairFreq_map);

    bool test = false;

    for (const auto &pair: expectedWordpairFreq_map) {
        if (wordpairFreq_map[pair.first] != pair.second) {
            return test;
        }
    }
    test = true;
    return test;
}

inline bool freqWordMmapUnitTest1() {
    std::multimap<int, std::pair<std::string, std::string>> freqWordpair_multimap = {
            {3, {"about",      "connecting"}},
            {3, {"about",      "dots."}},
            {3, {"about",      "first"}},
            {3, {"about",      "is"}},
            {3, {"about",      "story"}},
            {3, {"about",      "the"}},
            {3, {"connecting", "dots."}},
            {3, {"connecting", "first"}},
            {3, {"connecting", "is"}},
            {3, {"connecting", "story"}},
            {3, {"connecting", "the"}},
            {3, {"dots.",      "first"}},
            {3, {"dots.",      "is"}},
            {3, {"dots.",      "story"}},
            {3, {"dots.",      "the"}},
            {3, {"first",      "is"}},
            {3, {"first",      "story"}},
            {3, {"first",      "the"}},
            {3, {"is",         "story"}},
            {3, {"is",         "the"}},
            {3, {"story",      "the"}}
    };

    std::string outFname = "output.txt";
    int topCnt = 3;
    int botCnt = 3;
    printWordpairs(freqWordpair_multimap, outFname, topCnt, botCnt);

    std::string expected = "<about, connecting>: 3\n"
                           "<about, dots.>: 3\n"
                           "<about, first>: 3\n"
                           "<is, story>: 3\n"
                           "<is, the>: 3\n"
                           "<story, the>: 3\n";

    std::string result = getText(outFname);
    return result == expected;
}

inline bool freqWordMmapUnitTest2() {
    std::multimap<int, std::pair<std::string, std::string>> freqWordpair_multimap = {
            {1, {"are",      "going"}},
            {1, {"are",      "moon!"}},
            {1, {"are",      "steal"}},
            {1, {"are",      "the"}},
            {1, {"are",      "to"}},
            {1, {"are",      "we"}},
            {1, {"be",       "going"}},
            {1, {"be",       "he"}},
            {1, {"be",       "not"}},
            {1, {"be",       "this"}},
            {1, {"be",       "to"}},
            {1, {"be",       "villain."}},
            {1, {"be",       "was"}},
            {1, {"going",    "he"}},
            {1, {"going",    "moon!"}},
            {1, {"going",    "not"}},
            {1, {"going",    "steal"}},
            {1, {"going",    "the"}},
            {1, {"going",    "this"}},
            {2, {"going",    "to"}},
            {1, {"going",    "villain."}},
            {1, {"going",    "was"}},
            {1, {"going",    "we"}},
            {1, {"he",       "not"}},
            {1, {"he",       "this"}},
            {1, {"he",       "to"}},
            {1, {"he",       "villain."}},
            {1, {"he",       "was"}},
            {1, {"moon!",    "steal"}},
            {1, {"moon!",    "the"}},
            {1, {"moon!",    "to"}},
            {1, {"moon!",    "we"}},
            {1, {"not",      "this"}},
            {1, {"not",      "to"}},
            {1, {"not",      "villain."}},
            {1, {"not",      "was"}},
            {1, {"steal",    "the"}},
            {1, {"steal",    "to"}},
            {1, {"steal",    "we"}},
            {1, {"the",      "to"}},
            {1, {"the",      "we"}},
            {1, {"this",     "to"}},
            {1, {"this",     "villain."}},
            {1, {"this",     "was"}},
            {1, {"to",       "villain."}},
            {1, {"to",       "was"}},
            {1, {"to",       "we"}},
            {1, {"villain.", "was"}}
    };

    std::string outFname = "output.txt";
    int topCnt = 3;
    int botCnt = 3;
    printWordpairs(freqWordpair_multimap, outFname, topCnt, botCnt);

    std::string expected = "<are, going>: 1\n"
                           "<are, moon!>: 1\n"
                           "<are, steal>: 1\n"
                           "<to, we>: 1\n"
                           "<villain., was>: 1\n"
                           "<going, to>: 2\n";

    std::string result = getText(outFname);
    return result == expected;
}

inline bool steveJobsUnitTestEndToEnd() {
    std::string fTestName = "./unitTestFile.txt";
    std::vector<std::string> sentenceSplit{};
    sentenceSplitter(fTestName, sentenceSplit);
    std::map<std::pair<std::string, std::string>, int> wordpairFreq_map{};
    wordpairMapping(sentenceSplit, wordpairFreq_map);
    int topCnt = 1;
    int botCnt = 3;
    std::string outFname = "endtoendResult.txt";
    std::multimap<int, std::pair<std::string, std::string>> freqWordpair_multimap{};
    freqWordpairMmap(wordpairFreq_map, freqWordpair_multimap);
    printWordpairs(freqWordpair_multimap, outFname, topCnt, botCnt);
    std::string result = getText(outFname);
    std::string expected = {"<\"of, course>: 1\n"
                            "<a, college>: 4\n"
                            "<a, i>: 4\n"
                            "<she, to>: 4\n"
    };
    return result == expected;
}

inline bool steveJobsSentenceSplitterUnitTest() {
    std::string fTestName = "./unitTestFile.txt";
    std::vector<std::string> expected{};
    sentenceSplitter(fTestName, expected);
    std::vector<std::string> result = {
            "The first story is about connecting the dots",
            "I dropped out of Reed College after the first 6 months, but then stayed around as a drop-in for another 18 months or so before I really quit",
            "So why did I drop out",
            "It started before I was born",
            "My biological mother was a young, unwed college graduate student, and she decided to put me up for adoption",
            "She felt very strongly that I should be adopted by college graduates, so everything was all set for me to be adopted at birth by a lawyer and his wife",
            "Except that when I popped out they decided at the last minute that they really wanted a girl",
            "So my parents, who were on a waiting list, got a call in the middle of the night asking: \"We have an unexpected baby boy; do you want him",
            "They said: \"Of course",
            "My biological mother later found out that my mother had never graduated from college and that my father had never graduated from high school",
            "She refused to sign the final adoption papers",
            "She only relented a few months later when my parents promised that I would someday go to college"
    };
    bool test = false;
    if (result.size() != expected.size()) { return test; }
    for (size_t i = 0; i < result.size(); i++) {
        if (result.at(i) != expected.at(i)) { return test; }
    }
    test = true;
    return test;
}

inline void runTests() {

    if (wordPairMappingUnitTest1()) {
        std::cout << "Passed Word-pair Mapping Test 1" << std::endl;
    } else {
        std::cout << "Failed Word-pair Mapping Test 1" << std::endl;
    }
    if (wordPairMappingUnitTest2()) {
        std::cout << "Passed Word-pair Mapping Test 2" << std::endl;
    } else {
        std::cout << "Failed Word-pair Mapping Test 2" << std::endl;
    }
    if (freqWordMmapUnitTest1()) {
        std::cout << "Passed Freq-word Multi-map Test 1" << std::endl;
    } else {
        std::cout << "Failed Freq-word Multi-map Test 1" << std::endl;
    }
    if (freqWordMmapUnitTest2()) {
        std::cout << "Passed Freq-word Multi-map Test 2" << std::endl;
    } else {
        std::cout << "Failed Freq-word Multi-map Test 2" << std::endl;
    }
    if (steveJobsUnitTestEndToEnd()) {
        std::cout << "Passed Steve-Jobs-Speech End to End Test" << std::endl;
    } else {
        std::cout << "Failed Steve-Jobs-Speech End to End Test";
    }
    if (steveJobsSentenceSplitterUnitTest()) {
        std::cout << "Passed Splitter Unit Test" << std::endl;
    } else {
        std::cout << "Failed Splitter Unit Test" << std::endl;
    }
}

#endif