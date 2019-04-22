/**
 * @file BaseSentence.cpp
 * @author Christina Palm 
 * @brief Base class for all Sentence classes
 * @version 0.1
 * @date 2019-02-20
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include "BaseSentence.h"

namespace MOVIVariables{
  BaseSentence::BaseSentence(String t_sentence, 
                             std::initializer_list<std::vector<String>> t_values, 
                             unsigned int t_id){

    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN BaseSentence::BaseSentence()");
      delay(100);
    } 
    #endif

  }

  String BaseSentence::sentenceString(){
    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN BaseSentence::getSentence()");
      delay(100);
    } 
    #endif
      return "";
  }

  unsigned int BaseSentence::sentenceID(){

      #ifdef DEBUGWHERE
    {
      Serial.println("##### IN BaseSentence::getID()");
      delay(100);
    } 
    #endif

      return 0;
  }
}
