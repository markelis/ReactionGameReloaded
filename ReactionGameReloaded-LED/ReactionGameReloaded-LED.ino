int red = 11;
int blue = 10;
int green = 9;
int temp = A0;
int btn = 2;
int tPass = 0;
bool stop = false;
float cTemp = 0;
int start = 0;
unsigned long sumStart = 0;
boolean correct, gameStarted = false;
void setup() {
  Serial.begin(9600);  
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(btn, INPUT);
  correct = false;
}
void loop() {
  if (gameStarted == false) {
    for(int i = 0; i < 3; i++) {
      Serial.println();
    }
    Serial.println("Let's start the game!");
    analogWrite(green, 0);
    analogWrite(red, 0);
    analogWrite(blue, 0);
    gameStarted = true;
  }
  randomSeed(analogRead(A1));
  start = random(0,10);
  sumStart = millis();
  //Καθυστέρησε για start δευτρόλεπτα. Αν έχεις πιο γρήγορη αντίδραση από την αναμενώμενη...
  while((millis()-sumStart) < (start * 1000) && correct == false) 
     {
      delay(1);
      if(digitalRead(btn) != LOW)
      {
          // Code for the tone!!
        // tone(3, 640, 550);
          // tone(3, 31040, 1250);
          stop = true;
          Serial.print("False reaction!");
          delay(5000);
      }
    }
  // Άναψε το φώς ή ενεργοποίησε το buzzer
  while((stop == false) && (digitalRead(btn) != HIGH) && (tPass < start*1000))
  {
    // Code for the buzzer
    // tone(3, 440, 200);
    
    if((start % 3) == 1 && correct == false) { // Αν ισχύει κάτι...
      analogWrite(red, 255);
      analogWrite(green, 0);
      analogWrite(blue, 0);
      randomSeed(analogRead(A1));
      start = random(0,10);
      sumStart = millis();
    } else if ((start % 3) == 2 && correct == false) { // Αν ισχύει κάτι άλλο...
      analogWrite(red, 0);
      analogWrite(green, 0);
      analogWrite(blue, 255);
      tPass = 0;
      correct = true; 
    } else if ((start % 3) == 0 && correct == false){ // Διαφορετικά...
      analogWrite(red, 0);
      analogWrite(green, 255);
      analogWrite(blue, 0);
      randomSeed(analogRead(A1));
      start = random(0,10);
      sumStart = millis();
    }
    while((millis()-sumStart) < (start * 1000)) 
    {
      delay(1);
      if(digitalRead(btn) != LOW)
      {
          // Code for the tone!!
        // tone(3, 640, 550);
          // tone(3, 31040, 1250);
          stop = true;
          Serial.print("False reaction!");
          delay(5000);
      }
    }
    delay(1);
    tPass++;
    if(digitalRead(btn) != LOW && tPass <= start*1000)
    {
      // Code for the tone!!
      stop = true;
    }
  }
  // Αν αργήσεις πάνω από 3 δεύτερα εμφανίζεται μήνυμα
  if(tPass >= 3000) {
    // Code for the other tone!!!
    // tone(3, 640, 550);
    // tone(3, 31040, 1250);
    Serial.print("Slow reaction!");
    Serial.print(tPass);
    stop = true;
  }
  // Αν αντιδράσεις σωστά εμφανίζονται τα αποτελέσματα!
  else if ((tPass != 0) && (digitalRead(btn) == HIGH) && correct == true)
  {    
    // Code for the other tone!!!
    // 
    // tone(3, 31040, 1250);
    // tone(3, 640, 550);
    int tempVal = analogRead(temp);
    cTemp = (tempVal * 5.0) / 1024.0;
    cTemp = (cTemp - 0.5) * 100;
    Serial.print("Reaction time is "); 
    Serial.print(tPass);
    Serial.print(" msec at "); 
    Serial.print(cTemp);
    Serial.print(" oC"); 
    stop = true;
  }
  // Σταμάτησε το πρόγραμμα...
  while(stop == true) {
    delay(1);
    // ToDo restart...
    /*delay(100);
    Serial.println("To repeat the challenge press the button!");
    while(digitalRead(btn) == LOW) {
      delay(1);
    
    if(digitalRead(btn) == HIGH) {
      stop = false;
    }
    }*/
    
  }

}

