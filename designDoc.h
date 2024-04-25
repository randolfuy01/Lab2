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
 

*/