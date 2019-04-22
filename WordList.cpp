/**
 * @file WordList.cpp
 * @author Christina Palm 
 * @brief 
 * @version 0.1
 * @date 2019-02-20
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "WordList.h"
using namespace MOVIVariables;

namespace MOVIVariables{
  void WordList::addWord(String t_word){
    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN WordList::addWord()");
      delay(500);
    } 
    #endif
      t_word.toUpperCase();
      words.push_back(t_word);
  }

  String WordList::wordAt(unsigned int t_id){

    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN WordList::getWord()");
      delay(100);
    } 
    #endif

    return words.at(t_id);
  }

  std::vector<String> WordList::getWords(){

    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN WordList::getWords()");
      delay(100);
    } 
    #endif

    return words;
  }

  unsigned int WordList::wordID(String t_word){
    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN WordList::getID()");
      delay(100);
    } 
    #endif
    String temp{t_word};
    temp.toUpperCase();
    temp.trim();
    return std::distance(words.begin(), 
                         std::find(words.begin(), words.end(), temp));
  }

  bool WordList::contains(String t_word){

    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN WordList::contains()");
      delay(100);
    } 
    #endif

    t_word.toUpperCase();
    return (std::find(words.begin(), words.end(), t_word) != words.end());
  }

  std::vector<int> WordList::wordsToVec(std::vector<String> t_words){
    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN WordList::wordsToVec()");
      delay(100);
    } 
    #endif

    std::vector<int> result(words.size(), 0);

    std::vector<String>::iterator wordsIt;
    for(wordsIt = t_words.begin(); wordsIt < t_words.end(); wordsIt++){
      result.at(wordID(*wordsIt)) += 1;
    }
    return result;
  }

  std::vector<int> WordList::intsToVec(std::vector<int> t_ints){
    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN WordList::intsToVec()");
      delay(100);
    }
    #endif

    #ifdef DEBUG
    {
      Serial.print("Integers: [");
      std::vector<int>::iterator it;
      for(it = t_ints.begin(); it < t_ints.end(); it++){
        Serial.print(*it);
        if(!(it==t_ints.end()-1)){Serial.print(", ");}
      }
      Serial.println("]");
      delay(500);
    }
    #endif

    std::vector<int> Result(words.size(), 0);
    std::vector<int>::iterator intsIt;
    for(intsIt = t_ints.begin(); intsIt < t_ints.end(); intsIt++){
      if(!(*intsIt < 0)){
        Result.at(*intsIt) += 1;
      }
    }
    return Result;
  }

  std::vector<String> WordList::mapStrings(std::vector<int> t_ints){

    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN WordList::mapStrings()");
      delay(100);
    } 
    #endif

    std::vector<String> Result;
    std::vector<int>::iterator i;
    for(i=t_ints.begin(); i < t_ints.end(); i++){
      Result.push_back(wordAt(*i));
    }
    return Result;
  }
}