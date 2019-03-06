
#define BUTTON_1  A0
#define BUTTON_2  A1
#define BUTTON_3  A2

bool oldState = HIGH;
int counter = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_3, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  bool newState = digitalRead(BUTTON_3);
  if (newState == LOW && oldState == HIGH){
    delay(20);
    newState = digitalRead(BUTTON_3);
    if (newState == LOW) {
      counter++;
      Serial.println(counter);
    }
  }
  oldState = newState;
}
