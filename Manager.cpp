/**
 * @file Manager.cpp
 * @author Christina Palm 
 * @brief 
 * @version 0.1
 * @date 2018-12-27
 * 
 * @copyright Copyright (c) 2018
 * 
 */
#include "Manager.h"

using namespace MOVIVariables;

namespace MOVIVariables{
  Manager::Manager(MOVI* t_recognizer, 
                   Method t_method, 
                   bool t_twoStepMatch, 
                   bool t_wordGroupVocabulary, 
                   bool t_train) : 
                      recognizer{t_recognizer}, 
                      method{t_method}, 
                      twoStepMatch{t_twoStepMatch}, 
                      wordGroupVocabulary{t_wordGroupVocabulary}, 
                      train{t_train}{

    switch(method){
      case Method::levenshtein_chars :  lvocabulary = StringVocabulary(recognizer, 
                                                                       wordGroupVocabulary, 
                                                                       train); 
                                        break;
      case Method::levenshtein_words :  lvocabulary = StringVocabulary(recognizer, 
                                                                       wordGroupVocabulary, 
                                                                       train); 
                                        break;
      case Method::cosine            :  cvocabulary = IntegerVocabulary(recognizer, 
                                                                        wordGroupVocabulary, 
                                                                        train); 
                                        break;         
    }
  }

  std::vector<String> Manager::vocabulary(){

    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN Manager::getVocabulary()");
      delay(100);
    } 
    #endif


    return baseVocabulary()->allSentences();
  }
  std::vector<String> Manager::wordList(){
    return baseVocabulary()->getWordList().getWords();
  }

  BaseVocabulary* Manager::baseVocabulary(){
    BaseVocabulary* vocabulary{0};
    switch(method){
      case Method::levenshtein_chars : vocabulary = &lvocabulary; break;
      case Method::levenshtein_words : vocabulary = &lvocabulary; break;
      case Method::cosine            : vocabulary = &cvocabulary; break;
    }
    return vocabulary;
  }

  void Manager::addSentence(String t_sentence, 
                            std::initializer_list<std::vector<String>> t_values){

    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN Manager::addSentence()");
    } 
    #endif
    
    switch(method){
      case Method::levenshtein_chars : 
        lvocabulary.addSentence(t_sentence, t_values); 
        break;
      case Method::levenshtein_words : 
        lvocabulary.addSentence(t_sentence, t_values); 
        break;
      case Method::cosine            : 
        cvocabulary.addSentence(t_sentence, t_values); 
        break;
      default: 
        #ifdef DEBUGWHERE
        {
          Serial.println("##### IN case default - no valid method");
        } 
        #endif
        break;
    }
  }


  Result Manager::match(){

      #ifdef DEBUGWHERE
    {
      Serial.println("##### IN  Manager::match()");
      delay(100);
    } 
    #endif

    Result result;
        //if(DEBUG)Serial.println("RAW_WORDS");               
    String words = recognizer->getResult();
    if (words == "---"); // Ignore silence
    if (words == "?");   // Ignore unknown sentences 
    
    switch (method)
    {
      case Method::levenshtein_chars : 
        if (twoStepMatch){
          result = matchLevenshtein(words); 
          break;
        } else {
          result = matchLevenshteinOneStep(words);
          break;
        }
      case Method::levenshtein_words : 
        if (twoStepMatch){
          result = matchLevenshtein(words); 
          break;
        } else {
          result = matchLevenshteinOneStep(words);
          break;
        }
      case Method::cosine            :
        if (twoStepMatch){ 
        result = matchCosine(words); 
        break;
        } else {
          result = matchCosineOneStep(words);
          break;
        }
      default: break;
    }
    return result; 
  }

  Result Manager::matchLevenshtein(String t_words){

    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN  Manager::matchLevenshtein()");
      delay(100);
    } 
    #endif

    std::vector<StringSentence> sentences{lvocabulary.getSentences()};

    double matchScore = 30000; // unachievably high number TODO: maxint
    std::vector<StringSentence>::iterator it;
    StringSentence matchSentence;
    int i = 0; // Loop counter for getting the index of matched sentence
    for (it = sentences.begin(); it < sentences.end(); it++){
      int distance;
      if (method == Method::levenshtein_words) {
        distance = levenshteinDistanceWords(t_words, it->getCoreSentence());
      }
      else {
        distance = levenshteinDistance(t_words, it->getCoreSentence());
      }
      if (distance < matchScore){
        matchScore = distance;
        matchSentence = *it;
      }
      i++;
    }

    // https://stackoverflow.com/questions/4683539/variable-amount-of-nested-for-loops/4694438#4694438
    std::vector<std::vector<String>> values{matchSentence.getValues()};
    std::vector<unsigned int> lengths;

    for(auto value : values){
      lengths.push_back(value.size());
    }

    unsigned int n{lengths.size()};
    unsigned int indices[n]{0};

    std::vector<String> resultValues;
    String matchSentenceWithValues;
    matchScore = 30000;
    while(true){
      String tempSentence{matchSentence.sentenceString()};
      for(unsigned int i{0}; i < values.size(); i++){
        tempSentence = Util::replaceCharWithString(tempSentence, 
                                                   tempSentence.indexOf(StringSentence::WILDCARD), 
                                                   values[i][indices[i]]);
      }
      int distance;
      if (method == Method::levenshtein_words) {
        distance = levenshteinDistanceWords(t_words, tempSentence);
      }
      else {
        distance = levenshteinDistance(t_words, tempSentence);
      }
      
      if(distance < matchScore){
        matchScore = distance;
        matchSentenceWithValues = tempSentence;
      }
      

      ++indices[n - 1];
      for(unsigned int j{n}; --j >= 0 && indices[j] == lengths[j];){
        if(j == 0) goto afterWhile;
        indices[j] = 0;
        ++indices[j - 1];
      }
    }

    afterWhile: ;

    return Result(matchSentenceWithValues, 
                  resultValues, 
                  matchScore, 
                  matchSentence.sentenceString(), 
                  matchSentence.sentenceID());
  }

  /*
  * matchLevenshteinOneStep(String t_words)
  *
  *
  */
  Result Manager::matchLevenshteinOneStep(String t_words){

    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN Manager::matchLevenshteinOneStep()");
      delay(100);
    } 
    #endif

    std::vector<StringSentence> sentences{lvocabulary.getSentences()};

    int matchScore = 30000; // unachievably high number TODO: maxint
    std::vector<StringSentence>::iterator it;
    StringSentence matchSentence;
    std::vector<String> resultValues;
    String matchSentenceContent{""};
    for (it = sentences.begin(); it < sentences.end(); it++){

      std::vector<std::vector<String>> values{it->getValues()};
      std::vector<unsigned int> lengths;

      for(auto value : values){
        lengths.push_back(value.size());
      }

      unsigned int n{lengths.size()};
      unsigned int indices[n]{0};
      while(true){
        String tempSentence{it->sentenceString()};
        std::vector<String> tempResultValues;
        for(unsigned int i{0}; i < values.size(); i++){
          tempSentence = Util::replaceCharWithString(tempSentence, 
                                                     tempSentence.indexOf(StringSentence::WILDCARD), 
                                                     values[i][indices[i]]);
          tempResultValues.push_back(values[i][indices[i]]);
        }
        int distance;
        if (method == Method::levenshtein_words) {
          distance = levenshteinDistanceWords(t_words, tempSentence);
        }
        else {
          distance = levenshteinDistance(t_words, tempSentence);
        }
      
        if(distance < matchScore){
          matchScore = distance;
          matchSentence = *it;
          resultValues = tempResultValues;
          matchSentenceContent = tempSentence;
        }
      

        ++indices[n - 1];
        for(unsigned int j{n}; --j >= 0 && indices[j] == lengths[j];){
          if(j == 0) goto afterWhile;
          indices[j] = 0;
          ++indices[j - 1];
        }
      }

    afterWhile: ;
    } 

    return Result(matchSentenceContent, 
                  resultValues, 
                  matchScore, 
                  matchSentence.sentenceString(), 
                  matchSentence.sentenceID());
  }

  Result Manager::matchCosine(String t_words){
    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN Manager::matchCosine()");
    }
    #endif


    #ifdef DEBUG
    { Serial.println("");
      Serial.print("Words: ");
      Serial.println(t_words);
      Serial.println("");
    }
    #endif
    std::vector<IntegerSentence> sentences{cvocabulary.getSentences()};
    std::vector<IntegerSentence>::iterator it;

    #ifdef DEBUG
    {
      Serial.print("Number of sentences: ");
      Serial.println(sentences.size());
      delay(500);
    }
    #endif

    double matchScore{0.0};
    unsigned int i{0}; // Loop counter for getting the index of best matched sentence
    IntegerSentence matchSentence;
    WordList wordList{(cvocabulary.getWordList())};
    std::vector<int> wordsVector = wordList.wordsToVec(Util::extractWords(t_words));
    for (it = sentences.begin(); it < sentences.end(); it++){
      double csimilarity;
      
      
      std::vector<int> core =  wordList.intsToVec(it->getCore());

      #ifdef DEBUG
      {
        std::vector<int>::iterator i;
        Serial.print("Core: [");
        for(i=core.begin(); i < core.end(); i++){
          Serial.print(*i);
          if(!(i==core.end()-1)){Serial.print(", ");}
        }
        Serial.println("]");
        delay(1000);
      }
      #endif

      #ifdef DEBUG
      {
        std::vector<int>::iterator i;
        Serial.print("Words: [");
        for(i=wordsVector.begin(); i < wordsVector.end(); i++){
          Serial.print(*i);
          if(!(i==wordsVector.end()-1)){Serial.print(", ");}
        }
        Serial.println("]");
      }
      #endif
      csimilarity = cosineSimilarity(wordsVector, core);

      if(csimilarity > matchScore){
        matchScore = csimilarity;
        matchSentence = *it;
      }

      i++;
    }

    // TODO edit for cosine

    std::vector<std::vector<int>> values{matchSentence.getValues()};
    std::vector<unsigned int> lengths;

    std::vector<std::vector<int>>::iterator valueSet;
    for(valueSet = values.begin(); valueSet < values.end(); valueSet++){
  
      lengths.push_back(valueSet->size());
    }

    unsigned int n{lengths.size()};
    unsigned int indices[n]{0};

    std::vector<int> matchSentenceWithValues;
    matchScore = 0.0;
    std::vector<int> matchValues;
    while(true){

      //std::vector<int> tempSentence{matchSentence.getCore()};
      std::vector<int> tempValues;
      for(unsigned int i{0}; i < values.size(); i++){
        tempValues.push_back(values[i][indices[i]]);
        
      }

      std::vector<int> tempSentence{matchSentence.fillInValues(tempValues)};
      double cosine{cosineSimilarity(wordsVector, wordList.intsToVec(tempSentence))};
      
      if(cosine > matchScore){
        matchScore = cosine;

        matchValues = tempValues;
        matchSentenceWithValues = tempSentence;
      }

      ++indices[n - 1];
      for(unsigned int j{n}; --j >= 0 && indices[j] == lengths[j];){
        if(j == 0) goto afterWhile;
        indices[j] = 0;
        ++indices[j - 1];
      }
    }

    afterWhile: ; 

    String sentence{""};
    std::vector<int>::iterator index;

    for(index = matchSentenceWithValues.begin(); 
        index < matchSentenceWithValues.end() - 1; 
        index++)
    {

      sentence += wordList.wordAt(*index);
      sentence += ' ';
    }
    
    sentence += wordList.wordAt(*index);

    std::vector<String> resultValues;
    std::vector<int>::iterator value;
    for(value = matchValues.begin(); value < matchValues.end(); value++){
      resultValues.push_back(wordList.wordAt(*value));
    }

    return Result(sentence, 
                  resultValues, 
                  matchScore, 
                  matchSentence.sentenceString(), 
                  matchSentence.sentenceID());
  }


  Result Manager::matchCosineOneStep(String t_words){

    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN Manager::matchCosineOneStep()");
      delay(100);
    } 
    #endif

    #ifdef DEBUG
    { 
      Serial.println("");
      Serial.print("Words: ");
      Serial.println(t_words);
      Serial.println("");
    }
    #endif

    std::vector<IntegerSentence> sentences{cvocabulary.getSentences()};
    std::vector<IntegerSentence>::iterator it;

    double matchScore{0.0};
    IntegerSentence matchSentence;
    WordList wordList{(cvocabulary.getWordList())};
    std::vector<int> wordsVector = wordList.wordsToVec(Util::extractWords(t_words));
    std::vector<int> matchSentenceWithValues;
    matchScore = 0.0;
    std::vector<int> matchValues;
    for (it = sentences.begin(); it < sentences.end(); it++){

      #ifdef DEBUG
      { 
        Serial.println("#####\t1");  
        delay(100); 
      }
      #endif
      
      std::vector<std::vector<int>> values{it->getValues()};
      std::vector<unsigned int> lengths;

      std::vector<std::vector<int>>::iterator valueSet;
      for(valueSet = values.begin(); valueSet < values.end(); valueSet++){
        #ifdef DEBUG
        { 
          Serial.println("#####\t2");  
          delay(100); 
        }
        #endif
        lengths.push_back(valueSet->size());
      }

      unsigned int n{lengths.size()};
      unsigned int indices[n]{0};


      while(true){

        #ifdef DEBUG
        { 
          Serial.println("#####\t3");
          delay(100);   
        }
        #endif

        std::vector<int> tempValues;
        for(unsigned int i{0}; i < values.size(); i++){
          tempValues.push_back(values[i][indices[i]]);
          
        }

        #ifdef DEBUG
        { 
          Serial.println("#####\t4"); 
          delay(100);  
        }
        #endif
        std::vector<int> tempSentence{it->fillInValues(tempValues)};
        double cosine{cosineSimilarity(wordsVector, wordList.intsToVec(tempSentence))};

        if(cosine > matchScore){
          matchSentence = *it;
          matchScore = cosine;

          matchValues = tempValues;
          matchSentenceWithValues = tempSentence;
        }

        #ifdef DEBUG
        { 
          Serial.println("#####\t5"); 
          delay(100); 
        }
        #endif

        ++indices[n - 1];
        for(unsigned int j{n}; --j >= 0 && indices[j] == lengths[j];){
          if(j == 0) goto afterWhile;
          indices[j] = 0;
          ++indices[j - 1];
        }
      }
      afterWhile: ;
    }
  

    String sentence{""};
    std::vector<int>::iterator index;

    for(index = matchSentenceWithValues.begin(); 
        index < matchSentenceWithValues.end() - 1; 
        index++)
    {
      sentence += wordList.wordAt(*index);
      sentence += ' ';
    }
    
    sentence += wordList.wordAt(*index);

    std::vector<String> resultValues;
    std::vector<int>::iterator value;
    for(value = matchValues.begin(); value < matchValues.end(); value++){
      resultValues.push_back(wordList.wordAt(*value));
    }

    return Result(sentence, 
                  resultValues, 
                  matchScore, 
                  matchSentence.sentenceString(), 
                  matchSentence.sentenceID());
  }

  /*
  * 
  * The following function is taken from the SentenceSets example of the MOVI shield.
  * 
  * This function calculates the Levenshtein, or edit-distance, counting the number of insertions, deletions, and substitutions needed to go from string s1 to string s2.
  * More information about the function can be found here: https://en.wikipedia.org/wiki/Levenshtein_distance
  * This particular implementation is optimized to use O(min(m,n)) space instead of O(mn) as memory on the Arduino is scarce. 
  * More information on this function can be found from the original source it was adopted from: https://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance
  */
  
  #define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))

  int Manager::levenshteinDistance(String s1, String s2) {

    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN Manager::levenshteinDistance()");
      delay(100);
    } 
    #endif

      unsigned int s1len, s2len, x, y, lastdiag, olddiag;
      s1len=s1.length();
      s2len=s2.length();
      unsigned int column[s1len+1];
      for (y = 1; y <= s1len; y++)
          column[y] = y;
      for (x = 1; x <= s2len; x++) {
          column[0] = x;
          for (y = 1, lastdiag = x-1; y <= s1len; y++) {
              olddiag = column[y];
              column[y] = MIN3(column[y] + 1, 
                               column[y-1] + 1, 
                               lastdiag + (s1[y-1] == s2[x-1] ? 0 : 1));
              lastdiag = olddiag;
          }
      }
      return(column[s1len]);
  }

  /*
  * Based on levenshteinDistance function above, but uses words as tokens.
  *
  */
  int Manager::levenshteinDistanceWords(String s1, String s2) {

    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN Manager::levenshteinDistanceWords()");
      delay(100);
    } 
    #endif

      unsigned int s1len, s2len, x, y, lastdiag, olddiag;
      std::vector<String> words_s1{Util::extractWords(s1)};
      std::vector<String> words_s2{Util::extractWords(s2)};
      s1len=words_s1.size();
      s2len=words_s2.size();
      unsigned int column[s1len+1];
      for (y = 1; y <= s1len; y++)
          column[y] = y;
      for (x = 1; x <= s2len; x++) {
          column[0] = x;
          for (y = 1, lastdiag = x-1; y <= s1len; y++) {
              olddiag = column[y];
              column[y] = MIN3(column[y] + 1, 
                               column[y-1] + 1, 
                               lastdiag + (words_s1[y-1] == words_s2[x-1] ? 0 : 1));
              lastdiag = olddiag;
          }
      }

      return(column[s1len]);
  }

  double Manager::cosineSimilarity(std::vector<int> t_vec1, std::vector<int> t_vec2){
    #ifdef DEBUGWHERE
    {
      Serial.println("##### IN Manager::cosineSimilarity()");
      delay(500);
    } 
    #endif

    double innerProduct12{stdWorkaround::inner_product(t_vec1.begin(), 
                                                       t_vec1.end(), 
                                                       t_vec2.begin(), 
                                                       0.0)};
    double norm1{sqrt(stdWorkaround::inner_product(t_vec1.begin(), 
                                                   t_vec1.end(), 
                                                   t_vec1.begin(), 
                                                   0.0))};
    double norm2{sqrt(stdWorkaround::inner_product(t_vec2.begin(), 
                                                   t_vec2.end(), 
                                                   t_vec2.begin(), 
                                                   0.0))};

    double cosine = innerProduct12 / (norm1 * norm2); // Cosine Similarity

    return cosine;
  }

  std::vector<String> Manager::extractWords(String t_string){
    return Util::extractWords(t_string, SEPARATOR);
  }
}
