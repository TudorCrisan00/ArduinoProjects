const int buttonPin = 2;
const int ledPins[] = {3, 4, 5, 6};
const int numLeds = sizeof(ledPins) / sizeof(ledPins[0]);

int sequence[] = {0, 1, 2, 3};
int sequenceLength = sizeof(sequence) / sizeof(sequence[0]);

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
}

void loop() {
  for (int i = 0; i < sequenceLength; i++) {
    digitalWrite(ledPins[sequence[i]], HIGH);
    delay(500);
    digitalWrite(ledPins[sequence[i]], LOW);
    delay(300);
  }

  int playerSequence[sequenceLength];
  for (int i = 0; i < sequenceLength; i++) {
    while (digitalRead(buttonPin) == HIGH) {} 
    playerSequence[i] = getButtonPressed();
    delay(300);
  }

  bool correct = true;
  for (int i = 0; i < sequenceLength; i++) {
    if (playerSequence[i] != sequence[i]) {
      correct = false;
      break;
    }
  }

  if (correct) {
    flashLeds(3, 200);
    delay(1000);
  } else {
    flashLeds(2, 400);
    delay(1000);
  }
}

int getButtonPressed() {
  for (int i = 0; i < numLeds; i++) {
    if (digitalRead(ledPins[i]) == HIGH) {
      return i;
    }
  }
  return -1;
}

void flashLeds(int times, int delayTime) {
  for (int i = 0; i < times; i++) {
    for (int j = 0; j < numLeds; j++) {
      digitalWrite(ledPins[j], HIGH);
    }
    delay(delayTime);
    for (int j = 0; j < numLeds; j++) {
      digitalWrite(ledPins[j], LOW);
    }
    delay(delayTime);
  }
}
