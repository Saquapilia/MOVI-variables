/**
 * @file BaseSentence.h
 * @author Christina Palm 
 * @brief Base class for all Sentence classes
 * @version 0.1
 * @date 2019-02-20
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef MOVIVARS_BASE_SENTENTCE_H
#define MOVIVARS_BASE_SENTENTCE_H

#include <MOVIShield.h>
#include <ArduinoSTL.h>
#include <SoftwareSerial.h>
#include "debug.h"

namespace MOVIVariables{
  class BaseSentence {
    public:
      /**
       * @brief The wildcard used in sentences
       * 
      */
      static const char WILDCARD{'?'};
      /**
       * @brief Construct a new Base Sentence:: Base Sentence object
       * 
       * @param t_sentence a sentence, can contain wildcards
       * @param t_values  values, given in order of the corresponding wildcards
       */
      BaseSentence(String t_sentence, 
                   std::initializer_list<std::vector<String>> t_values, 
                   unsigned int t_id);

      /**
       * @brief The core sentence of the sentence object
       * 
       * @return String 
       */
      virtual String sentenceString();

      /**
       * @brief The ID of the sentence object
       * 
       * @return unsigned int 
       */
      virtual unsigned int sentenceID();
    private:
  };
}
#endif //MOVIVARS_Base_SENTENTCE_H
