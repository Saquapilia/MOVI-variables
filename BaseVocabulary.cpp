/**
 * @file BaseVocabulary.cpp
 * @author Christina Palm 
 * @brief Base class for all vocabulary classes
 * @version 0.1
 * @date 2019-02-20
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include "BaseVocabulary.h"

namespace MOVIVariables{
  BaseVocabulary::BaseVocabulary(){
  }

  BaseVocabulary::BaseVocabulary(MOVI* t_recognizer, 
                                 bool t_wordGroupVocabulary, 
                                 bool t_train): 
                                    recognizer{t_recognizer}, 
                                    wordGroupVocabulary{t_wordGroupVocabulary}, 
                                    train{t_train}, 
                                    id_count{1}{}

  WordList BaseVocabulary::getWordList(){
    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN BaseVocabulary::getWordList()");
      delay(100);
    } 
    #endif

    return wordList;
  }
}