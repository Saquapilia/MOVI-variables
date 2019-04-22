#include <avr/pgmspace.h>
#include <MOVIShield.h>

#include <MOVIVariables.h>
#include <ArduinoSTL.h>

#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_PIC32)
#include <SoftwareSerial.h> // This is nice and flexible but only supported on AVR and PIC32 architecture, other boards need to use Serial1 
#endif

MOVIVariables::Method method{MOVIVariables::Method::levenshtein_words};
bool twoStepMatch{false};
bool wordGroupVocabulary{true};
bool train{true};

// MOVI pins because ethernet shield uses standard pins
const auto MOVI_TX_PIN{A14} ;
const auto MOVI_RX_PIN{A15} ;

// MOVI object
MOVI recognizer(true, MOVI_TX_PIN, MOVI_RX_PIN);
MOVIVariables::Manager manager(&recognizer, method, twoStepMatch, wordGroupVocabulary, train);

// Calsign
const String CALLSIGN{"Arduino"};

void setup() {
  Serial.begin(9600);
  Serial.println("Start Training");

  recognizer.init();
  recognizer.callSign(CALLSIGN);

  std::vector<String> objects = {"light", "radio"};
  std::vector<String> places = {"kitchen", "garden"};
  std::vector<String> status = {"on", "off"};

  manager.addSentence("Turn the ? in the ? ?", {objects, places, status});
  manager.addSentence("Turn all ?", {status});

  recognizer.train();

  Serial.println("Training finished.");
}

void loop() {
    while(true){}
}
