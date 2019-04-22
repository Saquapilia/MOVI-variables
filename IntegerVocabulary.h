/**
 * @file IntegerVocabulary.h
 * @author Christina Palm 
 * @brief Vocabulary containing IntegerSentences, used for matching with cosine
 *        similarity
 * @version 0.1
 * @date 2018-12-20
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#ifndef MOVIVARS_INTEGER_VOCABULARY_H
#define MOVIVARS_INTEGER_VOCABULARY_H

#include <ArduinoSTL.h>
#include "IntegerSentence.h"
#include "WordList.h"
#include "BaseVocabulary.h"
#include "debug.h"

namespace MOVIVariables{
  class IntegerVocabulary : public BaseVocabulary {
  public:

    /**
     * @brief Construct a new Integer Vocabulary object
     * 
     */
    IntegerVocabulary();

    /**
     * @brief Construct a new Integer Vocabulary object
     * 
     * @param t_recognizer 
     */
    IntegerVocabulary(MOVI* t_recognizer, 
                      bool t_wordGroupVocabulary, 
                      bool t_train);

    /**
     * @brief Get the sentences
     * 
     * @return std::vector<IntegerSentence> 
     */
    std::vector<IntegerSentence> getSentences();

    /**
     * @brief Add a sentence
     * 
     * @param t_sentence a sentence containing wildcards
     * @param t_values the values in order of the corresponding wildcards
     */
    void addSentence(String t_sentence, 
                     std::initializer_list<std::vector<String>> t_values);

    /**
     * @brief all sentences contained in the vocabulary
     * 
     * @return std::vector<String> 
     */
    std::vector<String> allSentences();

  private:

    /**
     * @brief the IntegerSentences of the vocabulary
     * 
     */
    std::vector<IntegerSentence> sentences;
  };
}
#endif // MOVIVARS_INTEGER_VOCABULARY_H
