//Prateek
//www.justdoelectronics.com

#define RELAYPIN 2
#define WARNLEDPIN 3
char tag[] = "4000350ABAC5";

char input[12];
int count = 0;
boolean flag = 0;
void setup() {
  Serial.begin(9600);
  pinMode(RELAYPIN, OUTPUT);
  pinMode(WARNLEDPIN, OUTPUT);
}
void loop() {
  if (Serial.available()) {
    count = 0;

    while (Serial.available() && count < 12) {
      input[count] = Serial.read();
      count++;
      delay(5);
    }

    if (count == 12) {
      count = 0;
      flag = 1;

      while (count < 12 && flag != 0) {
        if (input[count] == tag[count])
          flag = 1;
        else
          flag = 0;

        count++;
      }
    }
    if (flag == 1) {
      Serial.println("Access Allowed!");
      digitalWrite(RELAYPIN, HIGH);
      delay(5000);
      digitalWrite(RELAYPIN, LOW);
    } else {
      Serial.println("Access Denied");
      digitalWrite(WARNLEDPIN, HIGH);
      delay(5000);
      digitalWrite(WARNLEDPIN, LOW);
    }

    for (count = 0; count < 12; count++) {
      input[count] = 'F';
    }
    count = 0;
  }
}
