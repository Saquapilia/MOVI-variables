
#include "Result.h"

namespace MOVIVariables{
  Result::Result() : values{""}{

    #ifdef DEBUGWHERE_RESULT
    {
      Serial.println("##### IN Result::Result()");
      delay(100);
    } 
    #endif

  }

  Result::Result(String t_words, 
                 std::vector<String> t_values, 
                 double t_score, 
                 String t_sentence, 
                 unsigned int t_id): 
                    words{t_words}, 
                    values{t_values}, 
                    score{t_score}, 
                    sentence{t_sentence}, 
                    id{t_id}{

    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN Result::Result(...)");
      delay(100);
    } 
    #endif
      
  }

  String Result::getSentence(){

    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN Result::getSentence()");
      delay(100);
    } 
    #endif

    return sentence;
  }

  std::vector<String> Result::getValues(){

    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN Result::getValues()");
      delay(100);
    } 
    #endif
    return values;
  }

  String Result::getWords(){

    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN Result::getWords()");
      delay(100);
    } 
    #endif
    return words;
  }

  double Result::getScore(){

    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN Result::getScore()");
      delay(100);
    } 
    #endif
    
    return score;
  }

  unsigned int Result::getID(){

    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN Result::getID()");
      delay(100);
    } 
    #endif
    return id;
  }
}