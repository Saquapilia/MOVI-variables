/**
 * @file Util.h
 * @author Christina Palm 
 * @brief Utility functions for the MOVIVariables library
 * @version 0.1
 * @date 2019-02-20
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef MOVIVARS_UTIL_H
#define MOVIVARS_UTIL_H

#include <MOVIShield.h>
#include <ArduinoSTL.h>
#include "debug.h"

namespace MOVIVariables{
  class Util {
  public:
  /**
   * @brief Extract word groups from a string with wildcards
   * 
   * @param t_string 
   * @return std::vector<String> 
   */
  static std::vector<String> extractGroups(String t_string);
  
  /**
   * @brief extract words separated by separator
   * 
   * @param t_string 
   * @param t_separator 
   * @return std::vector<String> 
   */
  static std::vector<String> extractWords(String t_string, char t_separator = ' ');
  
  /**
   * @brief clean string from wildcards
   * 
   * @param t_string 
   * @param t_character 
   * @return String 
   */
  static String cleanString(String t_string, char t_character = SEPARATOR);
  
  /**
   * @brief replaces character at index in string with content
   * 
   * @param t_string 
   * @param index 
   * @param t_content 
   * @return String 
   */
  static String replaceCharWithString(String t_string, unsigned int index, String t_content);
  
  /**
   * @brief splits string at char
   * 
   * @param t_string 
   * @param t_character 
   * @return std::vector<String> 
   */
  static std::vector<String> splitString(String t_string, char t_character);

  private:
    static const char SEPARATOR{'?'};
    static bool containsOnlyWhiteSpaces(String s);
    Util() {}
  };
}
#endif // MOVIVARS_UTIL_H
