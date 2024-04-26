//This file is for documentation purposes only. It will be ignored by the compiler.
//Our Teaching Assistant will manually grade this file.

//Please make sure that you include the entire content of this file as comments.

/* Design Doc: communicate your thought process in English.
 
0. List of members who contributed to the implementation of this project:
   Cesar Herrera
   Matt Stoffel
   Randolf Uy
   Avinh Huynh

 * Assisted by AI.

1. Describe your algorithm for the sentenceSplitter( ) function in pseudocode.
Input:
   a string of text
Output:
   a list of sentences
Code:
    Start with an empty collection to hold sentences
    Read the entire text from the file
        Begin compiling a sentence from the text:
            Ignore adding starting spaces or quotation marks
            Add characters to the sentence untile we reach an end of sentence delimiter (period, question mark, new line)
            Then, save the sentence to our collection of sentences.
            Repeat until reading the whole file.

    Return the collection of sentences.

Time complexity: O(n)) where (n) is the number of characters in the text.


2. Describe your algorithm for the wordpairMapping( ) function in pseudocode.
Input:
   a list of sentences,
   
Output:
   a mapping of word pairs to their number of occurrences
   
Code:
    Process each sentence individually:
       Normalize each word in the sentence by converting it to lowercase.
       Store all unique words from the sentence, avoiding duplicates.

    Generate all possible pairs from the unique words in alphabetical order:
       Ensure that for any pair (word1, word2), word1 alphabetically precedes word2.
       For each pair of unique words:
         If this is the first occurrence of this alphabetized pair, record the pair with a count of one.
         If this pair has been seen before, increment the existing count for this pair.

    Continue processing until all sentences have been handled.

    Return the mapping of alphabetized word pairs with their respective counts of occurrences.

 Time complexity: O(n * u^2 * w) where n is the number of sentences, u is the average number of unique words per sentence, and w is the average length of the words.


3. Describe your algorithm for the freqWordpairMmap( ) function in pseudocode.
Input:
    a map of word pairs and their frequencies with wird pair as key and frequency as value

Output:
    a multimap of word pairs and their frequencies with frequency as key and word pair as value

Code:
    Prepare a container to sort word pairs by their frequency

    Go through each word pair and their associated frequency:
        For each pair, organize them so that their frequencies come first, followed by the word pairs.

    Add each reordered pair into the prepared container, ensuring they are sorted by frequency.

    Return the container that now holds word pairs neatly organized by how often they appear.

Time complexity: O(m log(m)) where m is the number of word pairs.


4. Describe your algorithm for the printWordpairs( ) function in pseudocode.
Input:
    a multimap of word pairs and their frequencies with frequency as key and word pair as value
    a string for the output file name
    an integer for the number of top pairs to print, topCnt
    an integer for the number of bottom pairs to print, botCnt

Output:
    a file with the top and bottom pairs and their frequencies

Code:
    Begin by preparing to save the word pairs into a file named according to the specified filename

    If the file opens successfully:
       Start by recording the most frequently occurring word pairs:
            Select and write down ('topCnt') of the most common word pairs from the beginning of the collection.

       Then record the least frequently occurring word pairs:
         Move to the position that represents the less common word pairs.
         Select and write down ('botCnt') of the least common word pairs from this position.

       Close the file once all selected word pairs have been written.

    If unable to write to the file, indicate an error concerning file access.

Time complexity: (O(topCnt + botCnt))


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