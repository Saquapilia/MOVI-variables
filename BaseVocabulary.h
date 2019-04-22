/**
 * @file BaseVocabulary.h
 * @author Christina Palm 
 * @brief Base class for all vocabulary classes
 * @version 0.1
 * @date 2019-02-20
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef MOVIVARS_BASE_VOCABULARY_H
#define MOVIVARS_BASE_VOCABULARY_H

#include <MOVIShield.h>
#include <ArduinoSTL.h>
#include "BaseSentence.h"
#include "Util.h"
#include "WordList.h"
#include "debug.h"

namespace MOVIVariables{
  class BaseVocabulary {
  public:

    /**
     * @brief Construct a new Base Vocabulary object
     * 
     * @param t_recognizer the MOVI object
     * @param t_wordGroupVocabulary whether one vocabulary entry should contain 
     *        word groups instead of single words
     * @param t_train whether sentences will be trained on MOVI
     */
    BaseVocabulary(MOVI* t_recognizer, bool t_wordGroupVocabulary, bool t_train);
    
    /**
     * @brief Construct a new Base Vocabulary object
     * 
     */
    BaseVocabulary();

    /**
     * @brief Add a sentence to the Vocabulary
     * 
     * @param t_sentence a sentence with wildcards
     * @param t_values  the values in the order of corresponding wildcards
     */
    virtual void addSentence(String t_sentence, std::initializer_list<std::vector<String>> t_values) = 0;

    /**
     * @brief Get the word list
     * 
     * @return wordList 
     */
    WordList getWordList();

    /**
     * @brief All sentences as strings
     * 
     * @return std::vector<String> 
     */
    virtual std::vector<String> allSentences() = 0;

  private:
  protected:
    MOVI* recognizer;
    WordList wordList;
    bool wordGroupVocabulary;
    bool train;
    unsigned int id_count;
  };
}
#endif // MOVIVARS_BASE_VOCABULARY_H
