/**
 * @file WordList.h
 * @author Christina Palm 
 * @brief Class for word list containing all words of the vocabulary in a vector
 * @version 0.1
 * @date 2019-02-20
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef MOVIVARS_WORDLIST_H
#define MOVIVARS_WORDLIST_H

#include <MOVIShield.h>
#include <ArduinoSTL.h>
#include <SoftwareSerial.h>
#include "debug.h"

namespace MOVIVariables{
  class WordList {
  public:

  /**
   * @brief add a word to the list
   * 
   * @param t_word 
   */
  void addWord(String t_word);

  /**
   * @brief the word at id
   * 
   * @param t_id 
   * @return String 
   */
  String wordAt(unsigned int t_id);

  /**
   * @brief Get the Words object
   * 
   * @return std::vector<String> 
   */
  std::vector<String> getWords();

  /**
   * @brief the id of the word
   * 
   * @param t_word 
   * @return unsigned int 
   */
  unsigned int wordID(String t_word);

  /**
   * @brief whether the word is in the list
   * 
   * @param word 
   * @return true 
   * @return false 
   */
  bool contains(String word);

  /**
   * @brief the id vector for the string
   * 
   * @param t_words 
   * @return std::vector<int> 
   */
  std::vector<int> wordsToVec(std::vector<String> t_words);

  /**
   * @brief the vector for the words list with the given ids (number of
   *        occurances for each word in the list)
   * 
   * @param t_ints 
   * @return std::vector<int> 
   */
  std::vector<int> intsToVec(std::vector<int> t_ints); 
  
  /**
   * @brief find the corresponding words for all given ids
   * 
   * @param t_ints 
   * @return std::vector<String> 
   */
  std::vector<String> mapStrings(std::vector<int> t_ints);
    
  private:
    std::vector<String> words;
  };
}

#endif // MOVIVARS_WORDLIST_H
