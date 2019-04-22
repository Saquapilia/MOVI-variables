/**
 * @file StringSentence.h
 * @author Christina Palm 
 * @brief Sentence used for matchin with Levenshtein Distance
 * @version 0.1
 * @date 2019-02-20
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef MOVIVARS_STRING_SENTENTCE_H
#define MOVIVARS_STRING_SENTENTCE_H 

#include <MOVIShield.h>
#include <ArduinoSTL.h>
#include <SoftwareSerial.h>
#include "BaseSentence.h"
#include "debug.h"
#include "Util.h"

namespace MOVIVariables{
  class StringSentence : public BaseSentence{
    public:

      /**
       * @brief Construct a new String Sentence object
       * 
       */
      StringSentence();

      /**
       * @brief Construct a new String Sentence object
       * 
       * @param t_sentence 
       * @param t_values 
       * @param t_id 
       */
      StringSentence(String t_sentence, 
                     std::initializer_list<std::vector<String>> t_values, 
                     unsigned int t_id);

      /**
       * @brief Get the Core Sentence
       * 
       * @return String 
       */
      String getCoreSentence();

      /**
       * @brief The sentence as string
       * 
       * @return String 
       */
      String sentenceString();

      /**
       * @brief The sentence id in the vocabulary
       * 
       * @return unsigned int 
       */
      unsigned int sentenceID();

      /**
       * @brief Get the Values
       * 
       * @return std::vector<std::vector<String>> 
       */
      std::vector<std::vector<String>> getValues();

    private:
      String sentence;
      unsigned int id;
      std::vector<std::vector<String>> values;
      String extractCore(String t_sentence, char t_wildcard);
      std::vector<String> combine(std::vector<String> t_left, std::vector<String> t_right);
  };
}
#endif //MOVIVARS_STRING_SENTENTCE_H
