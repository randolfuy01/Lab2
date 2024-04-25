#ifndef FILEIOS_WORDPAIRS_UNITTESTS_H
#define FILEIOS_WORDPAIRS_UNITTESTS_H
#include "fileIOs_wordPairs.h"

bool fileInputTest1() {
    std::string fileName = "document1.txt";
    std::string result = getText(fileName);
    std::string expected = "hello, this is the first input test.\n";
    return result == expected;
}

bool fileInputTest2() {
    std::string fileName = "document2.txt";
    std::string result = getText(fileName);
    std::string expected = "The first story is about connecting the dots.\n"
                           "\n"
                           "I dropped out of Reed College after the first 6 months, but then stayed around as a drop-in for another 18 months or so before I really quit. So why did I drop out?\n"
                           "\n"
                           "It started before I was born. My biological mother was a young, unwed college graduate student, and she decided to put me up for adoption. She felt very strongly that I should be adopted by college graduates, so everything was all set for me to be adopted at birth by a lawyer and his wife. Except that when I popped out they decided at the last minute that they really wanted a girl. So my parents, who were on a waiting list, got a call in the middle of the night asking: \"We have an unexpected baby boy; do you want him?\" They said: \"Of course.\" My biological mother later found out that my mother had never graduated from college and that my father had never graduated from high school. She refused to sign the final adoption papers. She only relented a few months later when my parents promised that I would someday go to college.\n";
    return result == expected;
}

void sentenceSplitterTest() {
    std::string fileName = "document2.txt";
    std::vector<std::string> sentencesVector;
    sentenceSplitter(fileName, sentencesVector);

    for (const auto& sentence : sentencesVector) {
        std::cout << sentence << std::endl;
    }
}

bool wordpairMappingTest() {
    std::vector<std::string> sentences = {
        "The first story is about connecting the dots.",
        "The first story is about connecting the dots.",
        "The first story is about connecting the dots."
    };

    std::map<std::pair<std::string, std::string>, int> wordpairFreq_map;
    wordpairMapping(sentences, wordpairFreq_map);

    // Verify the wordpairFreq_map contains the expected word pairs and frequencies
    std::map<std::pair<std::string, std::string>, int> expectedWordpairFreq_map = {
        {{"about", "connecting"}, 3},
        {{"about", "dots."}, 3},
        {{"about", "first"}, 3},
        {{"about", "is"}, 3},
        {{"about", "story"}, 3},
        {{"about", "the"}, 3},
        {{"connecting", "dots."}, 3},
        {{"connecting", "first"}, 3},
        {{"connecting", "is"}, 3},
        {{"connecting", "story"}, 3},
        {{"connecting", "the"}, 3},
        {{"dots.", "first"}, 3},
        {{"dots.", "is"}, 3},
        {{"dots.", "story"}, 3},
        {{"dots.", "the"}, 3},
        {{"first", "is"}, 3},
        {{"first", "story"}, 3},
        {{"first", "the"}, 3},
        {{"is", "story"}, 3},
        {{"is", "the"}, 3},
        {{"story", "the"}, 3}
    };
    
    bool passed = true;
    for (const auto& pair : expectedWordpairFreq_map) {
        if (wordpairFreq_map[pair.first] != pair.second) {
            passed = false;
            break;
        }
    }

    return passed;
}


void runTests() {
    if (fileInputTest1()) {
        std::cout << "Passed File Input Test 1" << std::endl;
    } else {
        std::cout << "Failed File Input Test 1" << std::endl;
    }
    if (fileInputTest2()) {
        std::cout << "Passed File Input Test 2" << std::endl;
    } else {
        std::cout << "Failed File Input Test 2" << std::endl;
    }
    if (wordpairMappingTest()) {
        std::cout << "Passed Wordpair Mapping Test" << std::endl;
    } else {
        std::cout << "Failed Wordpair Mapping Test" << std::endl;
    }

    sentenceSplitterTest();
}
#endif //FILEIOS_WORDPAIRS_UNITTESTS_H
