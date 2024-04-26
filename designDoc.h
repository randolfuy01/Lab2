//This file is for documentation purposes only. It will be ignored by the compiler.
//Our Teaching Assistant will manually grade this file.

//Please make sure that you include the entire content of this file as comments.

/* Design Doc: communicate your thought process in English.
 
0. List of members who contributed to the implementation of this project:
   Cesar Herrera
   Matt Stoffel
   Randolf Uy
   Avinh Huynh


 
1. Describe your algorithm for the sentenceSplitter( ) function in pseudocode.
Input:
   a string of text
Output:
   a list of sentences
Code:
    Initialize an empty string for the current sentence
    Read the text from the file

    For each character in the text:
        If the character is a space or quote and the current sentence is empty, skip it
        If the character is a period, question mark, or newline, add the current sentence to the list and clear it
        Otherwise, add the character to the current sentence



2. Describe your algorithm for the wordpairMapping( ) function in pseudocode.
Input:
   a list of sentences,
   
Output:
   a set of pairs with number of occurences in the supplies sentences
   
Code:
For each sentence in sentences:
    Initialize an empty set called words
    Convert sentence into a stream
    Initialize an empty string called word

    While there are words in the stream:
        Read a word from the stream
        Convert the word to lowercase
        Add the word to the set words

    For each word i in the set words:
        For each word j in the set words that comes after i:
            Create a pair of words (i, j)

            If the pair (i, j) is not in the map wordpairFreq_map:
                Add the pair (i, j) to the map wordpairFreq_map with a count of 1
            Else:
                Increment the count of the pair (i, j) in the map wordpairFreq_map by 1



3. Describe your algorithm for the freqWordpairMmap( ) function in pseudocode.
Input:
    a map of word pairs and their frequencies with wird pair as key and frequency as value

Output:
    a multimap of word pairs and their frequencies with frequency as key and word pair as value

Code:
    Initialize an empty multimap called freqWordpair_mmap

    For each pair in the map wordpairFreq_map:
        Add the pair to the multimap freqWordpair_mmap with the frequency as the key and the pair as the value

    Return the multimap freqWordpair_mmap



4. Describe your algorithm for the printWordpairs( ) function in pseudocode.
Input:
    a multimap of word pairs and their frequencies with frequency as key and word pair as value
    a string for the output file name
    an integer for the number of top pairs to print
    an integer for the number of bottom pairs to print

Output:
    a file with the top and bottom pairs and their frequencies

Code:
    Open the output file for writing

    Initialize a counter to 0

    Initialize an iterator to the beginning of the multimap freqWordpair_multimap
    
    For each from counter 0 to the number of top pairs to print:
        write the current iterator's pair and frequency to the output file
        increment counter
        increment iterator

    Initialize a counter to 0

    Initialize an iterator to the end of the multimap freqWordpair_multimap

    Advance iterator pointer back by the number of bottom pairs to print
    
    For each from counter 0 to the number of bottom pairs to print:
        write the current iterator's pair and frequency to the output file
        increment counter
        increment iterator

    Close the output file



5. What built-in and/or user-defined data types are you going to use and why?

    // Thanks copilot for writing this
    Built-in data types:
    - std::string: to store the text, sentences, and words
    - std::vector: to store the list of sentences
    - std::map: to store the word pairs and their frequencies
    - std::multimap: to store the word pairs and their frequencies sorted by frequency
    - std::set: to store the unique words in a sentence
    - std::pair: to store the word pairs
    - std::stringstream: to convert the sentence into a stream
    - std::ifstream: to read the text from a file
    - std::ofstream: to write the word pairs and their frequencies to a file

    User-defined data types:
    - Pair<string, string>: to store the word pairs
    - Map<Pair<string, string>, int>: to store the word pairs and their frequencies
    - Multimap<int, Pair<string, string>>: to store the word pairs and their frequencies sorted by frequency



*/