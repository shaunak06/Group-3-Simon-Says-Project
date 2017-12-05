const int buttonPinR = 4; //button for the red led on pin 4
const int ledPinR =  13; //red led on pin 13
const int buttonPinG = 3; //button for the red led on pin 3
const int ledPinG =  12; //green led on pin 12
const int buttonPinB = 2; //button for the red led on pin 2
const int ledPinB =  11; //blue led on pin 11
const int buzzer = 9; //buzzer on pin 9
int rnd = -1;
int i, j;
const int max = 20; //the max dificulty for the simon says game

int buttonStateR = 0;
int buttonStateG = 0;
int buttonStateB = 0;

void setup() {
  pinMode(ledPinR, OUTPUT);
  pinMode(buttonPinR, INPUT);
  pinMode(ledPinG, OUTPUT);
  pinMode(buttonPinG, INPUT);
  pinMode(ledPinB, OUTPUT);
  pinMode(buttonPinB, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600); //in case we wanted to debug with serial output which we did use
  randomSeed(analogRead(0)); //initialize the random number generator
}

void loop() {
  for (i = 0; i < max; i++) { //outer loop for simon says dificulty
    int rngArr[i];
    for (j = 0; j < i; j++) { //show the user the sequence they need to follow
      rnd = random(3);
      if (rnd == 0)
        red();
      if (rnd == 1)
        green();
      if (rnd == 2)
        blue();
      rngArr[j] = rnd; //keep the sequence in an array for reference
      //Serial.println(rnd);
    }

    for (j = 0; j < i; j++) {
      //Code below is for user input

      int currInput = -1;

      buttonStateR = digitalRead(buttonPinR);
      buttonStateG = digitalRead(buttonPinG);
      buttonStateB = digitalRead(buttonPinB);

      while ( digitalRead(buttonPinR) == LOW && digitalRead(buttonPinG) == LOW
              && digitalRead(buttonPinB) == LOW )//while we wait for the user to input something
        delay(20);//debounce

      while (digitalRead(buttonPinR) == HIGH) {
        digitalWrite(ledPinR, HIGH);
        tone(buzzer, 100);
        currInput = 0;
      }
      digitalWrite(ledPinR, LOW);
      noTone(buzzer);

      while (digitalRead(buttonPinG) == HIGH) {
        digitalWrite(ledPinG, HIGH);
        tone(buzzer, 250);
        currInput = 1;
      }
      digitalWrite(ledPinG, LOW);
      noTone(buzzer);

      while (digitalRead(buttonPinB) == HIGH) {
        digitalWrite(ledPinB, HIGH);
        tone(buzzer, 500);
        currInput = 2;
      }
      digitalWrite(ledPinB, LOW);
      noTone(buzzer);

      if (currInput != rngArr[j]) { //if the user enters an incorrect input it goes into a fail sequence
        fail();
      }
    }// inner for
    delay(500); //wait in between trials
  } // outer for
}//loop

/*Simple functions that make the leds and corresponding sounds go off
they are only used for showing the user the sequence 
*/
int red() {
  digitalWrite(ledPinR, HIGH);
  tone(buzzer, 100); // Send 100Hz sound signal...
  delay(750);        // ...for .75 sec
  noTone(buzzer);     // Stop sound
  digitalWrite(ledPinR, LOW);
  delay(750);        // wait
  return 0;
}

int green() {
  digitalWrite(ledPinG, HIGH);
  tone(buzzer, 250); // Send 250Hz sound signal...
  delay(750);        // ...for .75 sec
  noTone(buzzer);     // Stop sound
  digitalWrite(ledPinG, LOW);
  delay(750);        // wait
  return 1;
}

int blue() {
  digitalWrite(ledPinB, HIGH);
  tone(buzzer, 500); // Send 500Hz sound signal...
  delay(750);        // ...for .75 sec
  noTone(buzzer);     // Stop sound
  digitalWrite(ledPinB, LOW);
  delay(750);        // wait
  return 2;
}

//function that is called when the user enters an incorrect input
void fail() {
  digitalWrite(ledPinB, HIGH);
  digitalWrite(ledPinG, HIGH);
  digitalWrite(ledPinR, HIGH);
  tone(buzzer, 1500); // Send 1.5KHz sound signal
  delay(350);
  digitalWrite(ledPinB, LOW);
  digitalWrite(ledPinG, LOW);
  digitalWrite(ledPinR, LOW);
  delay(350);
  digitalWrite(ledPinB, HIGH);
  digitalWrite(ledPinG, HIGH);
  digitalWrite(ledPinR, HIGH);
  delay(350);
  digitalWrite(ledPinB, LOW);
  digitalWrite(ledPinG, LOW);
  digitalWrite(ledPinR, LOW);
  delay(350);
  digitalWrite(ledPinB, HIGH);
  digitalWrite(ledPinG, HIGH);
  digitalWrite(ledPinR, HIGH);
  delay(350);
  digitalWrite(ledPinB, LOW);
  digitalWrite(ledPinG, LOW);
  digitalWrite(ledPinR, LOW);
  noTone(buzzer);
  delay(350);
  exit(0);

}
