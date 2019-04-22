/**
 * @file StringVocabulary.h
 * @author Christina Palm 
 * @brief Vocabulary for StringSentences
 * @version 0.1
 * @date 2019-02-20
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef MOVIVARS_STRING_VOCABULARY_H
#define MOVIVARS_STRING_VOCABULARY_H

#include <MOVIShield.h>
#include <ArduinoSTL.h>
#include "BaseVocabulary.h"
#include "StringSentence.h"

namespace MOVIVariables{
  class StringVocabulary : public BaseVocabulary {
  public:
    /**
     * @brief Construct a new String Vocabulary object
     * 
     */
    StringVocabulary();

    /**
     * @brief Construct a new String Vocabulary object
     * 
     * @param t_recognizer 
     * @param t_wordGroupVocabulary 
     * @param t_train 
     */
    StringVocabulary(MOVI* t_recognizer, 
                     bool t_wordGroupVocabulary, 
                     bool t_train);
    
    /**
     * @brief Get the Sentences
     *  
     * @return std::vector<StringSentence> 
     */
    std::vector<StringSentence> getSentences();

    /**
     * @brief add a sentence
     * 
     * @param t_sentence sentence with wildcards
     * @param t_values 
     */
    void addSentence(String t_sentence, 
                     std::initializer_list<std::vector<String>> t_values);
    
    /**
     * @brief all Sentences as string
     * 
     * @return std::vector<String> 
     */
    std::vector<String> allSentences();
  private:
    std::vector<StringSentence> sentences;
  };
}

#endif // MOVIVARS_STRING_VOCABULARY_H
