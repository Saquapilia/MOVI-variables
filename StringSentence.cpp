/**
 * @file StringSentence.cpp
 * @author Christina Palm 
 * @brief 
 * @version 0.1
 * @date 2018-12-27
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#include "StringSentence.h"

namespace MOVIVariables{
  StringSentence::StringSentence()
    : BaseSentence("", {{""}},0), sentence{""}, values{{""}} {

    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN StringSentence::StringSentence()");
      delay(100);
    } 
    #endif

    }

  StringSentence::StringSentence(String t_sentence, 
                                 std::initializer_list<std::vector<String>> t_values, 
                                 unsigned int t_id): 
                                    BaseSentence(t_sentence, t_values, t_id){


    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN StringSentence::StringSentence(...)");
      delay(100);
    } 
    #endif

    t_sentence.toUpperCase();
    sentence = t_sentence;
    id = t_id;

    values.assign(t_values);
    std::vector<std::vector<String>>::iterator it;
    for(it = values.begin(); it < values.end(); it++){
      std::vector<String>::iterator it2;
      for(it2 = it->begin(); it2 < it->end(); it2++){
        it2->toUpperCase();
      }
    }
  }

  String StringSentence::getCoreSentence(){

    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN StringSentence::getCoreSentence()");
      delay(100);
    } 
    #endif

    return extractCore(sentence, WILDCARD);
  }

  String StringSentence::sentenceString(){

    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN StringSentence::getSentence()");
      delay(100);
    } 
    #endif

    return sentence;
  }

  unsigned int StringSentence::sentenceID(){

    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN StringSentence::getID()");
      delay(100);
    } 
    #endif

    return id;
  }

  // Example: extractCore("Turn the ? in the ? ?", '?') == "Turn the  in the  "
  String StringSentence::extractCore(String t_sentence, char t_wildcard){

    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN StringSentence::extractCore()");
      delay(100);
    } 
    #endif

    return Util::cleanString(t_sentence, t_wildcard);
  }

  std::vector<std::vector<String>> StringSentence::getValues(){

    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN StringSentence::getValues()");
      delay(100);
    } 
    #endif

    return values;
  }

  std::vector<String> StringSentence::combine(std::vector<String> t_left, 
                                              std::vector<String> t_right){

    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN StringSentence::combine()");
      delay(100);
    } 
    #endif

    std::vector<String> result{};
      for(const auto& left : t_left){
        for(const auto& right : t_right){
          result.push_back(left + " " + right); 
        }
      }
      return result;
  }
}