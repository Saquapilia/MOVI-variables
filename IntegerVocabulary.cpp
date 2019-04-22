/**
 * @file IntegerVocabulary.cpp
 * @author Christina Palm 
 * @brief 
 * @version 0.1
 * @date 2018-12-27
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#include "IntegerVocabulary.h"

namespace MOVIVariables{
  IntegerVocabulary::IntegerVocabulary() : BaseVocabulary(){

  }

  IntegerVocabulary::IntegerVocabulary(MOVI* t_recognizer, 
                                       bool t_wordGroupVocabulary, 
                                       bool t_train):
                                           BaseVocabulary(t_recognizer, 
                                                          t_wordGroupVocabulary, 
                                                          t_train){}

  std::vector<IntegerSentence> IntegerVocabulary::getSentences(){
    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN IntegerVocabulary::getSentences()");
      delay(500);
    }
    #endif

    return sentences;
  }
    
  void IntegerVocabulary::addSentence(String t_sentence, 
                                      std::initializer_list<std::vector<String>> t_values){

    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN IntegerVocabulary::addSentence()");
    }
    #endif

    #ifdef DEBUG
    {
      Serial.println("");
      Serial.print("t_sentence: ");
      Serial.println(t_sentence);
    }
    #endif

    if(wordGroupVocabulary){
      std::vector<String> coreGroups{Util::splitString(t_sentence, BaseSentence::WILDCARD)};
      std::vector<std::vector<String>>::iterator it;
      std::vector<String>::iterator valueIt;
      unsigned int count = 0;

      for (it = t_values.begin(); it < t_values.end(); it++){
        for (valueIt = it->begin(); valueIt < it->end(); valueIt++){
          String combined = coreGroups[count] + " " + *valueIt;
          combined.trim();
          if(train) {recognizer->addSentence(combined);}
        }
        count += 1;
      }
    }
    String cleanSentence{Util::cleanString(t_sentence)};

    std::vector<String> words {Util::extractWords(cleanSentence, ' ')};
    std::vector<String>::iterator it;

    for (it = words.begin(); it < words.end(); it++){
      if (!wordList.contains(*it)){
        wordList.addWord(*it);
        if(!wordGroupVocabulary){
          if(train) {recognizer->addSentence(*it);}
        }
      }
    }

    std::vector<std::vector<String>>::iterator valueSetIt;
    std::vector<String>::iterator valueIt;

    for (valueSetIt = t_values.begin(); valueSetIt < t_values.end(); valueSetIt++){
      for (valueIt = valueSetIt->begin(); valueIt < valueSetIt->end(); valueIt++){
        if (!wordList.contains(*valueIt)){
          wordList.addWord(*valueIt);
          if(!wordGroupVocabulary){
            if(train) {recognizer->addSentence(*valueIt);}
          }
        }
      }
    }
    IntegerSentence sentence{t_sentence, t_values, &wordList, id_count};
    sentences.push_back(sentence);
    id_count += 1;
  }

  std::vector<String> IntegerVocabulary::allSentences(){
    std::vector<String> result;
    std::vector<IntegerSentence>::iterator it;
    for(it = sentences.begin(); it < sentences.end(); it++){
      result.push_back(it->sentenceString());
    }

    return result;
  }
}