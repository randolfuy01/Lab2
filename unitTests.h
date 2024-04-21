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
            "I dropped out of Reed College after the first 6 months but then stayed around as a drop-in for another 18 months or so before I really quit",
            "So why did I drop out",
            "It started before I was born",
            "My biological mother was a young unwed college graduate student and she decided to put me up for adoption",
            "She felt very strongly that I should be adopted by college graduates so everything was all set for me to be adopted at birth by a lawyer and his wife",
            "Except that when I popped out they decided at the last minute that they really wanted a girl",
            "So my parents who were on a waiting list got a call in the middle of the night asking We have an unexpected baby boy do you want him",
            "They said Of course",
            "My biological mother later found out that my mother had never graduated from college and that my father had never graduated from high school",
            "She refused to sign the final adoption papers",
            "She only relented a few months later when my parents promised that I would someday go to college"
    };

    std::vector<std::string> sentencesVector;
    sentenceSplitter(fileName, sentencesVector);

    return sentencesVector == expectedSentencesVector;
}

void runTests() {

    std::cout << "Begin testing..." << std::endl;

    bool allTestPassing = true;

    if (!fileInputTest1()) {
        allTestPassing = false;
        std::cout << "Failed File Input Test 1" << std::endl;
    }
    if (!fileInputTest2()) {
        allTestPassing = false;
        std::cout << "Failed File Input Test 2" << std::endl;
    }

    if (!sentenceSplitterTest()) {
        allTestPassing = false;
        std::cout << "Failed sentenceSplitter() Test" << std::endl;
    }

    if (allTestPassing) {
        std::cout << "All test passing." << std::endl;
    }

}
#endif //FILEIOS_WORDPAIRS_UNITTESTS_H
