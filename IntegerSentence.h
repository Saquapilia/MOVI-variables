/**
 * @file IntegerSentence.h
 * @author Christina Palm 
 * @brief Class for sentences represented by vectors of integer values
 *        A sentence is represented by a vector of integers, which are the
 *        indices of the corresponding words in the word list of the IntegerVocabulary
 * @version 0.1
 * @date 2019-02-20
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef MOVIVARS_INTEGER_SENTENTCE_H
#define MOVIVARS_INTEGER_SENTENTCE_H

#include <MOVIShield.h>
#include <ArduinoSTL.h>
#include <SoftwareSerial.h>
#include "BaseSentence.h"
#include "WordList.h"
#include "debug.h"
#include "Util.h"

namespace MOVIVariables{
  class IntegerSentence : public BaseSentence{
    public:

      /**
       * @brief Construct a new Integer Sentence object
       * 
       */
      IntegerSentence();

      /**
       * @brief Construct a new Integer Sentence object
       * 
       * @param t_sentence 
       * @param t_values 
       * @param t_wordList 
       * @param t_id 
       */
      IntegerSentence(String t_sentence, 
                      std::initializer_list<std::vector<String>> t_values, 
                      WordList* t_wordList, 
                      unsigned int t_id);

      /**
       * @brief Get the core (without wildcards and values)
       * 
       * @return std::vector<int> 
       */
      std::vector<int> getCore();

      /**
       * @brief Get the values
       * 
       * @return std::vector<std::vector<int>> 
       */
      std::vector<std::vector<int>> getValues();

      /**
       * @brief Get a vector of integers which represents the sentence with
       *        the given values filled in for the wildcards
       * 
       * @param t_values the values to replace the wildcards
       * @return std::vector<int> the sentence with values
       */
      std::vector<int> fillInValues(std::vector<int> t_values);

      /**
       * @brief The core sentence of the sentence object
       * 
       * @return String 
       */
      String sentenceString();

      /**
       * @brief The ID of the sentence object
       * 
       * @return unsigned int 
       */
      unsigned int sentenceID();

    private:

      /**
       * @brief clean the core sentence of wildcards
       * 
       * @return std::vector<int> 
       */
      std::vector<int> cleanCore();

      /**
       * @brief the word list of the vocabulary the sentence belongs to
       * 
       */
      WordList* wordList;

      /**
       * @brief the core of the sentence, -1 if no word, positive integer for word 
       *        in word list 
       *        Example: "Turn the ? in the ? ?" would be represented by e.g.
       *                 [[0, 1][2, 1][-1][-1]]
       * 
       */
      std::vector<std::vector<int>> core;

      /**
       * @brief the possible values for the variables (wildcards) of the sentence
       *        represented by integers
       * 
       */
      std::vector<std::vector<int>> values;

      /**
       * @brief the id of the sentence
       * 
       */
      unsigned int id;
  };
}

#endif //MOVIVARS_INTEGER_SENTENTCE_H
