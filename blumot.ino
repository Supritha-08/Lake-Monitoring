
char inputByte;


int motor1Pin1 = 27;
int motor1Pin2 = 26;


int enable1Pin = 14;

int motor2Pin1 = 23;

int motor2Pin2 = 19;
int enable2Pin = 18;


void setup() {
  Serial.print("Testing DC Motor...");
  
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  analogWrite(enable1Pin, 250);


  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enable2Pin, OUTPUT);
  analogWrite(enable2Pin, 250);


  
  Serial.begin(9600);

  
  Serial.print("Testing DC Motor...");


  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);



  delay(2000);
  Serial.print("1..");
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  delay(2000);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  Serial.print("12..");
  Serial2.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {

 
  while (Serial2.available() > 0) {
    inputByte = Serial2.read();
    Serial.println(inputByte);

    if (inputByte == 'f') {
      Serial.println("forward");
      Serial.println("Moving Forward");
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);


      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, HIGH);
      
    }

    else if (inputByte == 's') {
      Serial.println("stop");
      Serial.println("Motor stopped");
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, LOW);

      
    }

    else if (inputByte == 'b') {
      Serial.println("backward");
      // Move DC motor backwards at maximum speed
      Serial.println("Moving Backwards");
      digitalWrite(motor1Pin1, HIGH);
      digitalWrite(motor1Pin2, LOW);


      digitalWrite(motor2Pin1, HIGH);
      digitalWrite(motor2Pin2, LOW);
    }

    else if (inputByte == 'l') {
      Serial.println("left");
     
      Serial.println("Moving Backwards");
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      digitalWrite(motor2Pin1, HIGH);
      digitalWrite(motor2Pin2, LOW);

      delay(2000);

      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, LOW);
    }

    else if (inputByte == 'r') {
      Serial.println("right");
      
      Serial.println("Moving Backwards");
      digitalWrite(motor1Pin1, HIGH);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, HIGH);

      delay(2000);

      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, LOW);
    }

    delay(200);
  }
}
