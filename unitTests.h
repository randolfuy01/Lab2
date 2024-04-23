#ifndef FILEIOS_WORDPAIRS_UNITTESTS_H
#define FILEIOS_WORDPAIRS_UNITTESTS_H

#include "fileIOs_wordPairs.h"

bool fileInputTest1() {
    std::string fileName = "../test_files/document1.txt";
    std::string result = getText(fileName);
    std::string expected = "hello, this is the first input test.\n";
    return result == expected;
}

bool fileInputTest2() {
    std::string fileName = "../test_files/document2.txt";
    std::string result = getText(fileName);
    std::string expected = "The first story is about connecting the dots.\n"
                           "\n"
                           "I dropped out of Reed College after the first 6 months, but then stayed around as a drop-in for another 18 months or so before I really quit. So why did I drop out?\n"
                           "\n"
                           "It started before I was born. My biological mother was a young, unwed college graduate student, and she decided to put me up for adoption. She felt very strongly that I should be adopted by college graduates, so everything was all set for me to be adopted at birth by a lawyer and his wife. Except that when I popped out they decided at the last minute that they really wanted a girl. So my parents, who were on a waiting list, got a call in the middle of the night asking: \"We have an unexpected baby boy; do you want him?\" They said: \"Of course.\" My biological mother later found out that my mother had never graduated from college and that my father had never graduated from high school. She refused to sign the final adoption papers. She only relented a few months later when my parents promised that I would someday go to college.\n";
    return result == expected;
}

bool sentenceSplitterTest() {
    std::string fileName = "../test_files/document2.txt";
    std::vector<std::string> expectedSentencesVector = {
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

    std::vector<std::string> sentencesVector;
    sentenceSplitter(fileName, sentencesVector);

    return sentencesVector == expectedSentencesVector;
}

bool toLowerCaseTest() {
    std::vector<std::string> input = {"Hello There My Friend", "WORLD", "tESt"};
    std::vector<std::string> expectedOutput = {"hello there my friend", "world", "test"};
    std::vector<std::string> actualOutput;

    toLowerCase(input, actualOutput);

    return expectedOutput == actualOutput;
}

bool tokenizeTest() {
    std::vector<std::string> sentences = {"Hello there", "How are you", "Nice to meet you"};
    std::vector<std::vector<std::string>> expectedTokens = {{"Hello", "there"},
                                                            {"How",   "are", "you"},
                                                            {"Nice",  "to",  "meet", "you"}};
    std::vector<std::vector<std::string>> actualTokens;

    tokenize(sentences, actualTokens);

    return expectedTokens == actualTokens;
}

bool sortAndRemoveDuplicatesTest() {
    std::vector<std::vector<std::string>> tokenGroupList = {
            {"third", "second", "first", "second", "third"},
            {"apple", "banana", "apple", "banana", "apple"},
            {"zebra", "ant",    "zebra", "ant",    "zebra"}
    };

    std::vector<std::vector<std::string>> expectedOutput = {
            {"first", "second", "third"},
            {"apple", "banana"},
            {"ant",   "zebra"}
    };

    sortAndRemoveDuplicates(tokenGroupList);

    return expectedOutput == tokenGroupList;
}

bool wordpairMappingTest() {
    std::string fileName = "../test_files/document3.txt";
    std::map<std::pair<std::string, std::string>, int> expectedWordPairFreqMap = {
            {{"about",      "connecting"}, 3},
            {{"about",      "dots"},       3},
            {{"about",      "first"},      3},
            {{"about",      "is"},         3},
            {{"about",      "story"},      3},
            {{"about",      "the"},        3},
            {{"connecting", "dots"},       3},
            {{"connecting", "first"},      3},
            {{"connecting", "is"},         3},
            {{"connecting", "story"},      3},
            {{"connecting", "the"},        3},
            {{"dots",       "first"},      3},
            {{"dots",       "is"},         3},
            {{"dots",       "story"},      3},
            {{"dots",       "the"},        3},
            {{"first",      "is"},         3},
            {{"first",      "story"},      3},
            {{"first",      "the"},        3},
            {{"is",         "story"},      3},
            {{"is",         "the"},        3},
            {{"story",      "the"},        3}
    };
    std::vector<std::string> sentencesVector;
    sentenceSplitter(fileName, sentencesVector);
    std::map<std::pair<std::string, std::string>, int> actualWordPairFreqMap;
    wordpairMapping(sentencesVector, actualWordPairFreqMap);

    return actualWordPairFreqMap == expectedWordPairFreqMap;
}

void runTests() {

    std::cout << "Begin testing..." << std::endl;

    bool allTestPassing = true;

    if (!fileInputTest1()) {
        allTestPassing = false;
        std::cout << "- Failed File Input Test 1" << std::endl;
    }
    if (!fileInputTest2()) {
        allTestPassing = false;
        std::cout << "- Failed File Input Test 2" << std::endl;
    }

    if (!sentenceSplitterTest()) {
        allTestPassing = false;
        std::cout << "- Failed sentenceSplitter() Test" << std::endl;
    }

    if (!toLowerCaseTest()) {
        allTestPassing = false;
        std::cout << "- Failed toLowerCase() Test" << std::endl;
    }

    if (!tokenizeTest()) {
        allTestPassing = false;
        std::cout << "- Failed tokenize() Test" << std::endl;
    }

    if (!sortAndRemoveDuplicatesTest()) {
        allTestPassing = false;
        std::cout << "- Failed sortAndRemoveDuplicates() Test" << std::endl;
    }

    if (!wordpairMappingTest()) {
        allTestPassing = false;
        std::cout << "- Failed wordpairMapping() Test" << std::endl;
    }

    if (allTestPassing) {
        std::cout << "All tests passed. ";
    }
    std::cout << "End of testing." << std::endl;

}

#endif //FILEIOS_WORDPAIRS_UNITTESTS_H
