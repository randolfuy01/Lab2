#ifndef FILEIOS_WORDPAIRS_UNITTESTS_H
#define FILEIOS_WORDPAIRS_UNITTESTS_H
#include "fileIOs_wordPairs.h"

// Standardize Unit Testing
// 2 unit tests for each function: sentenceSplitter(), wordPairMapping(), freqWordPairMmap()
// 2 end to end unit tests

bool sentenceSplitterUnitTest1() {
    std::string fileName = "../test_files/document1.txt";
    std::vector<std::string> result{};
    std::vector<std::string> expected = {
            "Hello, I am a student at San Francisco State University",
            "I am currently taking CSC-340",
            "What is your name"
    };
    sentenceSplitter(fileName, result);
    bool test = false;
    if (result.size() != expected.size()) { return test; }
    for (size_t i = 0; i < result.size(); i++) {
        if (result.at(i) != expected.at(i)) { return test; }
    }
    test = true;
    return test;
}

bool sentenceSplitterUnitTest2() {
    std::string fileName = "../test_files/document2.txt";
    std::vector<std::string> result{};
    std::vector<std::string> expected = {
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
    sentenceSplitter(fileName, result);
    bool test = false;
    if (result.size() != expected.size()) { return test; }
    for (size_t i = 0; i < result.size(); i++) {
        if (result.at(i) != expected.at(i)) { return test; }
    }
    test = true;
    return test;
}

bool wordPairMappingUnitTest1() {
    std::vector<std::string> sentences = {
            "The first story is about connecting the dots.",
            "The first story is about connecting the dots.",
            "The first story is about connecting the dots."
    };
    std::map<std::pair<std::string, std::string>, int> wordpairFreq_map;
    wordpairMapping(sentences, wordpairFreq_map);

    // Verify the wordpairFreq_map contains the expected word pairs and frequencies
    std::map<std::pair<std::string, std::string>, int> expectedWordpairFreq_map = {
            {{"about", "connecting"}, 3},{{"about", "dots."}, 3},
            {{"about", "first"}, 3},{{"about", "is"}, 3},
            {{"about", "story"}, 3},{{"about", "the"}, 3},
            {{"connecting", "dots."}, 3},{{"connecting", "first"}, 3},
            {{"connecting", "is"}, 3},{{"connecting", "story"}, 3},
            {{"connecting", "the"}, 3},{{"dots.", "first"}, 3},
            {{"dots.", "is"}, 3},{{"dots.", "story"}, 3},
            {{"dots.", "the"}, 3},{{"first", "is"}, 3},
            {{"first", "story"}, 3},{{"first", "the"}, 3}, {{"is", "story"}, 3},
            {{"is", "the"}, 3},{{"story", "the"}, 3}
    };
    bool test = false;
    for (const auto& pair : expectedWordpairFreq_map) {
        if (wordpairFreq_map[pair.first] != pair.second) {
            return test;
        }
    }
    test = true;
    return test;
}

bool wordPairMappingUnitTest2() {
    std::vector<std::string> sentences = {
            "We are going to steal the moon!",
            "He was not going to be this villain."
    };
    std::map<std::pair<std::string, std::string>, int> wordpairFreq_map;

    std::map<std::pair<std::string, std::string>, int> expectedWordpairFreq_map = {
            {{"are", "going"}, 1}, {{"are", "moon!"}, 1},{{"are", "steal"}, 1},{{"are", "the"}, 1},
            {{"are", "to"}, 1},{{"are", "we"}, 1},{{"be", "going"}, 1},{{"be", "he"}, 1},
            {{"be", "not"}, 1},{{"be", "this"}, 1},{{"be", "to"}, 1},{{"be", "villain."}, 1},
            {{"be", "was"}, 1},{{"going", "he"}, 1},{{"going", "moon!"}, 1},{{"going", "not"}, 1},
            {{"going", "steal"}, 1}, {{"going", "the"}, 1},{{"going", "this"}, 1},{{"going", "to"}, 2},{{"going", "villain."}, 1},
            {{"going", "was"}, 1},{{"going", "we"}, 1},{{"he", "not"}, 1},{{"he", "this"}, 1},{{"he", "to"}, 1},
            {{"he", "villain."}, 1},{{"he", "was"}, 1},{{"moon!", "steal"}, 1},{{"moon!", "the"}, 1},{{"moon!", "to"}, 1},
            {{"moon!", "we"}, 1},{{"not", "this"}, 1},{{"not", "to"}, 1},{{"not", "villain."}, 1},{{"not", "was"}, 1},
            {{"steal", "the"}, 1},{{"steal", "to"}, 1},{{"steal", "we"}, 1},{{"the", "to"}, 1},{{"the", "we"}, 1},
            {{"this", "to"}, 1},{{"this", "villain."}, 1},{{"this", "was"}, 1},{{"to", "villain."}, 1},{{"to", "was"}, 1},{{"to", "we"}, 1},{{"villain.", "was"}, 1}
    };

    wordpairMapping(sentences, wordpairFreq_map);

    bool test = false;

    for (const auto& pair : expectedWordpairFreq_map) {
        if (wordpairFreq_map[pair.first] != pair.second) {
            return test;
        }
    }
    test = true;
    return test;
}

bool freqWordMmapUnitTest1() {
    std::multimap<int, std::pair<std::string, std::string>> freqWordpair_multimap = {
            {3, {"about", "connecting"}},
            {3, {"about", "dots."}},
            {3, {"about", "first"}},
            {3, {"about", "is"}},
            {3, {"about", "story"}},
            {3, {"about", "the"}},
            {3, {"connecting", "dots."}},
            {3, {"connecting", "first"}},
            {3, {"connecting", "is"}},
            {3, {"connecting", "story"}},
            {3, {"connecting", "the"}},
            {3, {"dots.", "first"}},
            {3, {"dots.", "is"}},
            {3, {"dots.", "story"}},
            {3, {"dots.", "the"}},
            {3, {"first", "is"}},
            {3, {"first", "story"}},
            {3, {"first", "the"}},
            {3, {"is", "story"}},
            {3, {"is", "the"}},
            {3, {"story", "the"}}
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

bool freqWordMmapUnitTest2() {
    std::multimap<int, std::pair<std::string, std::string>> freqWordpair_multimap = {
            {1, {"are", "going"}},{1, {"are", "moon!"}},{1, {"are", "steal"}},{1, {"are", "the"}},{1, {"are", "to"}},
            {1, {"are", "we"}},{1, {"be", "going"}},{1, {"be", "he"}},{1, {"be", "not"}},{1, {"be", "this"}},
            {1, {"be", "to"}},{1, {"be", "villain."}},{1, {"be", "was"}},{1, {"going", "he"}},{1, {"going", "moon!"}},
            {1, {"going", "not"}},{1, {"going", "steal"}},{1, {"going", "the"}},{1, {"going", "this"}},{2, {"going", "to"}},
            {1, {"going", "villain."}},{1, {"going", "was"}},{1, {"going", "we"}},{1, {"he", "not"}},{1, {"he", "this"}},
            {1, {"he", "to"}},{1, {"he", "villain."}},{1, {"he", "was"}},{1, {"moon!", "steal"}},{1, {"moon!", "the"}},
            {1, {"moon!", "to"}},{1, {"moon!", "we"}},{1, {"not", "this"}},{1, {"not", "to"}},{1, {"not", "villain."}},
            {1, {"not", "was"}},{1, {"steal", "the"}},{1, {"steal", "to"}},{1, {"steal", "we"}},{1, {"the", "to"}},
            {1, {"the", "we"}},{1, {"this", "to"}},{1, {"this", "villain."}},{1, {"this", "was"}},{1, {"to", "villain."}},
            {1, {"to", "was"}},{1, {"to", "we"}},{1, {"villain.", "was"}}
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

bool endToEndUnitTest1() {
    std::string fTestName = "../test_files/EndToEndFileTest.txt";
    std::vector<std::string> sentenceSplit{};
    sentenceSplitter(fTestName, sentenceSplit);
    std::map<std::pair<std::string, std::string>, int> wordpairFreq_map{};
    wordpairMapping(sentenceSplit, wordpairFreq_map);
    int topCnt = 3;
    int botCnt = 3;
    std::string outFname = "endtoendResult.txt";
    std::multimap<int, std::pair<std::string, std::string>> freqWordpair_multimap{};
    freqWordpairMmap(wordpairFreq_map, freqWordpair_multimap);
    printWordpairs(freqWordpair_multimap, outFname, topCnt, botCnt);
    std::string result = getText(outFname);
    std::string expected = {"<am, finish>: 2\n"
                            "<am, going>: 2\n"
                            "<am, hello,>: 2\n"
                            "<lab, the>: 2\n"
                            "<lab, to>: 2\n"
                            "<the, to>: 2\n"};
    return result == expected;
}

bool endToEndUnitTest2() {
    std::string fTestName = "../test_files/EndToEndFileTest2.txt";
    std::vector<std::string> sentenceSplit{};
    sentenceSplitter(fTestName, sentenceSplit);
    std::map<std::pair<std::string, std::string>, int> wordpairFreq_map{};
    wordpairMapping(sentenceSplit, wordpairFreq_map);
    int topCnt = 5;
    int botCnt = 7;
    std::string outFname = "endtoendResult.txt";
    std::multimap<int, std::pair<std::string, std::string>> freqWordpair_multimap{};
    freqWordpairMmap(wordpairFreq_map, freqWordpair_multimap);
    printWordpairs(freqWordpair_multimap, outFname, topCnt, botCnt);
    std::string result = getText(outFname);
    std::string expected = {"<file, in>: 1\n"
                            "<file, is>: 1\n"
                            "<file, one>: 1\n"
                            "<file, only>: 1\n"
                            "<file, sentence>: 1\n"
                            "<only, this>: 1\n"
                            "<sentence, text>: 1\n"
                            "<sentence, there>: 1\n"
                            "<sentence, this>: 1\n"
                            "<text, there>: 1\n"
                            "<text, this>: 1\n"
                            "<there, this>: 1\n"};
    return result == expected;
}

bool steveJobsUnitTestEndToEnd() {
    std::string fTestName = "../unitTestFile.txt";
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

void runTests() {
    if (sentenceSplitterUnitTest1()) {
        std::cout << "Passed Sentence Splitter Test 1" << std::endl;
    } else {
        std::cout << "Failed Sentence Splitter Test 1" << std::endl;
    }
    if (sentenceSplitterUnitTest2()) {
        std::cout << "Passed Sentence Splitter Test 2" << std::endl;
    } else {
        std::cout << "Failed Sentence Splitter Test 2" << std::endl;
    }
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
    if (endToEndUnitTest1()) {
        std::cout << "Passed End-to-End Unit Test 1" << std::endl;
    } else {
        std::cout << "Failed End-to-End Unit Test 1" << std::endl;
    }
    if (endToEndUnitTest2()) {
        std::cout << "Passed End-to-End Unit Test 2" << std::endl;
    } else {
        std::cout << "Failed End-to-End Unit Test 2" << std::endl;
    }
    if (steveJobsUnitTestEndToEnd()) {
        std::cout << "Passed Steve-Jobs-Speech End to End Test" << std::endl;
    } else {
        std::cout << "Failed Steve-Jobs-Speech End to End Test";
    }
}

#endif //FILEIOS_WORDPAIRS_UNITTESTS_H
