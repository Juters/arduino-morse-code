/*
400 milisegundos para un punto
800 milisegundos para una raya
*/

#define letterSpace 1200
#define endOfLetter 2500
#define endOfWord 4500
#define LDR A0

unsigned long beginOfLight = 0;  // Guarda cuánto tiempo el LDR estuvo recibiendo luz

int letter[] = {};  // 0 = punto, 1 = raya
bool reset = false;
char wordToPrint[] = {};  // Cada letra de la palabra, para luego recorrerlo y unirlas para poder imprimir la palabra completa
unsigned long timeOfSilence = 0;

void setup() {
  pinMode(LDR, INPUT);
  Serial.begin(9600);
}

void loop() {
  int light = analogRead(LDR);
  static int arrayIndex = 0;
  if (light > 30) {
    
    initializeTimeOfLight();
    unsigned long difference = millis() - beginOfLight;

    if (difference < letterSpace) {

      Serial.println(1);
      delay(250);
    } else if (difference > letterSpace && difference < endOfLetter) {
      
      Serial.println(2);
      // Debe empezar nuevo sonido de letra (punto o guión)
    } else if (difference > endOfLetter && difference < endOfWord) {
      Serial.println(3);
      // Termina la letra y empieza una nueva (se guarda en wordToPrint)
    } else {
      Serial.println(4);
      // Imprimir palabra en el LCD
      String palabra;
      for (int i = 0; i <= arrayIndex; i++) {
        palabra += letter[i];
      }
      Serial.print(palabra);
    }
  } else {
    if (reset) {
      int timeOfLight = millis() - beginOfLight;
      Serial.print("Time of light: ");
      Serial.println(timeOfLight);
      letter[arrayIndex++] = (timeOfLight <= 600 && timeOfLight >= 400)? 0 : 1;
      reset = false;
    }
  }
}

void initializeTimeOfLight() {
  if (!reset) {
    beginOfLight = millis();
    reset = true;
  }
}
