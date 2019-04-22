/**
 * @file Manager.h
 * @author Christina Palm 
 * @brief Class responsible for building up the vocabulary and adding sentences
 * @version 0.1
 * @date 2019-02-20
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef MOVIVARS_MANAGER_H
#define MOVIVARS_MANAGER_H

#include <MOVIShield.h>
#include <ArduinoSTL.h>
#include <SoftwareSerial.h> 
#include "BaseVocabulary.h"
#include "IntegerVocabulary.h"
#include "StringVocabulary.h"
#include "BaseSentence.h"
#include "IntegerSentence.h"
#include "StringSentence.h"
#include "Result.h"
#include "Util.h"
#include "debug.h"

namespace MOVIVariables {
  enum class Method {levenshtein_chars, levenshtein_words, cosine};
  class Manager{
  public:

  /**
    * @brief Construct a new Manager object
    * 
    * @param t_recognizer the MOVI object
    * @param t_method the matching method
    * @param t_twoStepMatch whether matching should be done in two steps
    * @param t_wordGroupVocabulary whether a word group vocabulary should be used
    * @param t_train whether training should be performed
    */
    Manager(MOVI* t_recognizer, Method t_method = Method::cosine, bool t_twoStepMatch = true, bool t_wordGroupVocabulary = true, bool t_train = false);

    /**
     * @brief The entries of the vocabulary
     * 
     * @return std::vector<String> 
     */
    std::vector<String> vocabulary();

    /**
     * @brief The list of words in the vocabulary
     * 
     * @return std::vector<String> 
     */
    std::vector<String> wordList();

    /**
     * @brief Add sentence with variable parts. 
     *        E.g. addSentence("Turn the light ?", {{"on", "off"}})
     *        Values must not contain whitespaces. Just pull the words together: 
     *        e.g. "livingroom" works well
     * @param t_sentence 
     * @param t_values 
     */
    void addSentence(String t_sentence, std::initializer_list<std::vector<String>> t_values);

    /**
     * @brief match a result from the recognizer with the method
     * 
     * @return Result 
     */
    Result match();
    
  private:
    Result matchLevenshtein(String t_words);
    Result matchCosine(String t_words);
    Result matchCosineOneStep(String t_words);
    Result matchLevenshteinOneStep(String t_words);
    int levenshteinDistance(String t_string1, String t_string2);
    int levenshteinDistanceWords(String s1, String s2);
    double cosineSimilarity(std::vector<int> t_vec1, std::vector<int> t_vec2);
    int* vectorizeString(String t_string);
    std::vector<String> extractWords(String t_string);
    BaseVocabulary* baseVocabulary();
    MOVI* recognizer;
    Method method;
    bool twoStepMatch;
    bool wordGroupVocabulary;
    bool train;
    StringVocabulary lvocabulary;
    IntegerVocabulary cvocabulary;
    const char SEPARATOR = ' ';
    
  };

  // The following was copied from the ArduinoSTL because of "error: 'inner_product' is not a member of 'std'"
  namespace stdWorkaround
  {
    template <class InputIterator1, class InputIterator2, class T> _UCXXEXPORT 
      T inner_product(InputIterator1 first1, InputIterator1 last1,
        InputIterator2 first2, T init)
    {
      while(first1 != last1){
        init = init + *first1 * *first2;
        ++first1;
        ++first2;
      }
      return init;
    }
  } // stdWorkaround

  #endif //MOVIVARS_MANAGER_H
}
