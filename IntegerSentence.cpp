/**
 * @file IntegerSentence.cpp
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

#include "IntegerSentence.h"

namespace MOVIVariables{
  IntegerSentence::IntegerSentence():BaseSentence("", {{""}}, 0){

    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN IntegerSentence::IntegerSentence()");
      delay(100);
    } 
    #endif

  }

  // t_sentence: "Turn the ? in the ? ?", t_values: {{radio, tv},{kitchen, living room},{on,off}}
  IntegerSentence::IntegerSentence(String t_sentence, 
                                   std::initializer_list<std::vector<String>> t_values, 
                                   WordList* t_wordList, 
                                   unsigned int t_id):
                                      BaseSentence(t_sentence, t_values, t_id), 
                                      wordList{t_wordList}{
    
    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN IntegerSentence::IntegerSentence(...)");
      delay(100);
    } 
    #endif


      id = t_id;

      #ifdef DEBUG
      {
        Serial.println("sentence in IntegerSentence(): ");
        Serial.println(t_sentence);
      }
      #endif

      std::vector<String> coreString{Util::splitString(t_sentence, BaseSentence::WILDCARD)};

      #ifdef DEBUG
      {
        Serial.println("CORE STRING: ");
        std::vector<String>::iterator it;
        for(it=coreString.begin(); it < coreString.end(); it++){
          Serial.println(*it);
        }
      }  
      #endif

      // Add core
      // {"Turn the", "in the", "", ""}
      std::vector<String>::iterator partsIt;
      for(partsIt = coreString.begin(); partsIt < coreString.end(); partsIt++){
        std::vector<int> temp;
        if(*partsIt == ""){
          temp.push_back(-1);
        } else {
          std::vector<String> words{Util::extractWords(*partsIt)};
          std::vector<String>::iterator wordsIt;
          for(wordsIt = words.begin(); wordsIt < words.end(); wordsIt++){
            temp.push_back(wordList->wordID(*wordsIt));
          }
        }
        core.push_back(temp);
      }

      #ifdef DEBUG
      { 
        Serial.print("core: [");
        std::vector<std::vector<int>>::iterator partsIt;
        for(partsIt = core.begin(); partsIt < core.end(); partsIt++){
          Serial.print("[");
          std::vector<int>::iterator i;
          for(i = partsIt->begin(); i < partsIt->end(); i++){
            Serial.print(*i);
            if(!(i == partsIt->end() - 1)){
              Serial.print(", ");
            }
          }
          Serial.print("]");
        }
        Serial.println("]");
      }
      #endif

      // Add values
      // {"light", "radio"}{"on", "off"}
      for(auto valueSet : t_values){
        std::vector<int> temp;
        for(auto value : valueSet){
          temp.push_back(wordList->wordID(value));
        }
        values.push_back(temp);
      }

      #ifdef DEBUG
      {
        Serial.print("values: [");
        for(auto part : values){
          Serial.print("[");
          std::vector<int>::iterator i;
          for(i = part.begin(); i < part.end(); i++){
            Serial.print(*i);
            if(!(i == part.end() - 1)){
              Serial.print(", ");
            }
          }
          Serial.print("]");
        }
        Serial.println("]");
      }
      #endif

    }
      
  std::vector<int> IntegerSentence::getCore(){

    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN IntegerSentence::getCore()");
      delay(100);
    } 
    #endif

    std::vector<int> clean{cleanCore()};

    #ifdef DEBUG
    { 
      Serial.print("clean: [");
      std::vector<int>::iterator i;
      for(i = clean.begin(); i < clean.end(); i++){
        Serial.print(*i);
        if(!(i == clean.end() - 1)){
          Serial.print(", ");
        }
      }
      Serial.println("]");
    }
    #endif

    return clean;
  }

  std::vector<int> IntegerSentence::cleanCore(){

    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN IntegerSentence::cleanCore()");
      delay(100);
    } 
    #endif

    #ifdef DEBUG
    { 
      Serial.print("core: [");
      std::vector<std::vector<int>>::iterator partsIt;
      for(partsIt = core.begin(); partsIt < core.end(); partsIt++){
        Serial.print("[");
        std::vector<int>::iterator i;
        for(i = partsIt->begin(); i < partsIt->end(); i++){
          Serial.print(*i);
          if(!(i == partsIt->end() - 1)){
            Serial.print(", ");
          }
        }
        Serial.print("]");
      }
      Serial.println("]");
    }
    #endif


    std::vector<int> result;
    std::vector<std::vector<int>>::iterator part;
    for (part = core.begin(); part < core.end(); part++){
      std::vector<int>::iterator i;
      for (i = part->begin(); i < part->end(); i++){
        if(*i >= 0){result.push_back(*i);} // -1 stands for value and can be left out here
      }

    }

    #ifdef DEBUG
    { 
      Serial.print("result of cleanCore(): [");
      std::vector<int>::iterator i;
      for(i = result.begin(); i < result.end(); i++){
        Serial.print(*i);
        if(!(i == result.end() - 1)){
          Serial.print(", ");
        }
      }
      Serial.println("]");
    }
    #endif

    return result;
  }

  std::vector<std::vector<int>> IntegerSentence::getValues(){

    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN IntegerSentence::getValues()");
      delay(100);
    } 
    #endif

    return values;
  }

  std::vector<int> IntegerSentence::fillInValues(std::vector<int> t_values){

    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN IntegerSentence::fillInValues(");
      delay(100);
    } 
    #endif

    std::vector<int> result;
    std::vector<std::vector<int>>::iterator part;
    unsigned int i{0}; // Loop counter to find value
    for(part = core.begin(); part < core.end(); part++){

      #ifdef DEBUG
      {
        Serial.print("i is: ");
        Serial.print(i);
        Serial.print("\t part.size() is: ");
        Serial.println(part->size());
      }
      #endif //DEBUG


      std::vector<int>::iterator word;
      for(word = part->begin(); word < part->end(); word++){
        if(*word >= 0){ // -1 is place holder for value at the end or series of values
          result.push_back(*word);
        }
      }
      
      if(i < t_values.size()){
        result.push_back(t_values.at(i));
      }

      i++;
    }
  
    #ifdef DEBUG
    {
      Serial.print("result: ");
      for(auto i : result){
        Serial.print(i);
        Serial.print(' ');
      }
      Serial.println("");
    }
    #endif //DEBUG

    return result;
  }

  String IntegerSentence::sentenceString(){

    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN IntegerSentence::getSentence()");
      delay(100);
    } 
    #endif

    String result{""};

    std::vector<std::vector<int>>::iterator part;
    for(part = core.begin(); part < core.end(); part++){
      std::vector<int>::iterator word;
      for(word = part->begin(); word < part->end(); word++){
        if(*word >= 0){ // -1 is place holder for value at the end or series of values
          result += wordList->wordAt(*word);
          if(part < core.end() - 1){
            result += ' ';
          }
        }
      }
      if(part < core.end() - 1){
        result += '?';
        if(part < core.end() -2){
          result += ' ';
        }
      }
    }

    return result;
  }

  unsigned int IntegerSentence::sentenceID(){

    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN IntegerSentence::getID()");
      delay(100);
    } 
    #endif

    return id;
  }
}