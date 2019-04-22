/**
 * @file Result.h
 * @author Christina Palm 
 * @brief Class containing the matching result
 * @version 0.1
 * @date 2019-02-20
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef MOVIVARS_RESULT_H
#define MOVIVARS_RESULT_H

#include <ArduinoSTL.h>
#include <BaseSentence.h>

namespace MOVIVariables{
  class Result {
  public:

    /**
     * @brief Construct a new Result object
     * 
     */
    Result();

    /**
     * @brief Construct a new Result object
     * 
     * @param t_words the full sentence matched
     * @param t_values the matched values
     * @param t_score the matchscore (between 0 and 1 for cosine similarity and 
     *        positive int for levenshtein distance)
     * @param sentence the sentence with wildcards
     * @param t_id the sentence id of the matched sentence 
     */
    Result(String t_words, 
           std::vector<String> t_values, 
           double t_score, 
           String sentence, 
           unsigned int t_id);

    /**
     * @brief Get the Words
     * 
     * @return String 
     */
    String getWords();

    /**
     * @brief Get the Sentence
     * 
     * @return String 
     */
    String getSentence();

    /**
     * @brief Get the Values 
     * 
     * @return std::vector<String> 
     */
    std::vector<String> getValues();

    /**
     * @brief Get the Score
     * 
     * @return double 
     */
    double getScore();

    /**
     * @brief Get the ID
     * 
     * @return unsigned int 
     */
    unsigned int getID();

  private:
    String words;
    std::vector<String> values;
    double score;
    String sentence;
    unsigned int id;
  };
}
#endif //MOVIVARS_RESULT_H
