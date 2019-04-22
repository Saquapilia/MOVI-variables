/**
 * @file Util.cpp
 * @author Christina Palm 
 * @brief Utility functions for the MOVIVariables library
 * @version 0.1
 * @date 2019-02-20
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "Util.h"

namespace MOVIVariables{
  std::vector<String> Util::extractGroups(String t_string){

    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN Util::extractGroups()");
      delay(100);
    } 
    #endif

    extractWords(t_string, SEPARATOR);
  }

  std::vector<String> Util::extractWords(String t_string, char t_separator){

    #ifdef DEBUGWHERE
    {
      Serial.println("##### Util::extractWords()");
      delay(100);
    } 
    #endif

    std::vector<String> result{};

    if(t_string == ""){
      return result;
    } else {

      int foundAt{0};
      unsigned int maxi{t_string.length() - 1};
      for(unsigned int i{0}; i <= maxi; i++){
        if(t_string.charAt(i) == t_separator || i == maxi){
        String word{""};
          if (i == maxi){
            word = t_string.substring(foundAt, i+1);
          } else{
            word = t_string.substring(foundAt, i);
          }
          if (!containsOnlyWhiteSpaces(word)){
            word.trim();
            result.push_back(word);
          }
          foundAt = i+1;

        }
      }
    }
      return result;
  }

  String Util::cleanString(String t_string, char t_character){

    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN Util::cleanString()");
      delay(100);
    } 
    #endif

    String result{t_string};
    int foundAt{result.indexOf(t_character)};
    while(foundAt >= 0){
      result.remove(foundAt, 1);
      foundAt = result.indexOf(t_character);
    }
    return result;  
  }

  String Util::replaceCharWithString(String t_string, 
                                     unsigned int index, 
                                     String t_content){

    #ifdef DEBUGWHERE
    {
      Serial.println("##### Util::replaceCharsWithString()");
      delay(100);
    } 
    #endif

    String temp{t_string};
    String result{temp.substring(0, index)};
    temp.remove(0, index+1);
    result.concat(t_content);
    result.concat(temp);
    return result;
  }

  // "Turn the ? in the ? ?" -> {"Turn the", "in the", "", ""}
  std::vector<String> Util::splitString(String t_string, char t_character){

    #ifdef DEBUGWHERE
    {
      Serial.println("##### Util::splitString()");
      delay(100);
    } 
    #endif

    String temp{t_string};
    int foundAt{temp.indexOf(t_character)};
    std::vector<String> result;
    while(foundAt >= 0){
      {
        String tempSub{temp.substring(0, foundAt)};
        if(Util::containsOnlyWhiteSpaces(tempSub)){
          result.push_back("");
        }else{
          tempSub.trim();
          result.push_back(tempSub);
        }
      }
      // if string ends with wildcard
      if (foundAt == temp.length() - 1){
        result.push_back("");
      }
      temp.remove(0, foundAt+1);

      foundAt = temp.indexOf(t_character);
    }

    // if string ends with text
    if (temp.length() > 0 && !containsOnlyWhiteSpaces(temp)){
      result.push_back(temp);
    }

    return result;
  }

  bool Util::containsOnlyWhiteSpaces(String s){

    #ifdef DEBUGWHERE
    {
      Serial.println("##### Util::containsOnlyWhiteSpaces()");
      delay(100);
    } 
    #endif

    for(unsigned int i{0}; i < s.length(); i++){
      if (isGraph(s[i])){
        return false;
      }
    }
    return true;
  }
}
