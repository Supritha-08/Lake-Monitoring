
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);  

#include "ThingSpeak.h"
#include <WiFi.h>
WiFiClient client;
const char* ssid = "Royal";         // Enter SSID here
const char* password = "8431868663";  //Enter Password here
// WiFiClient  client;
int turbidity = 36;
int turbidity_val ;
unsigned long myChannelNumber = 2524550;
const char* myWriteAPIKey = "5ESB90ZXDP29OKOE";
String myStatus = "";
char inputByte;


int motor1Pin1 = 27;
int motor1Pin2 = 26;


int enable1Pin = 14;

int motor2Pin1 = 23;

// int motor2Pin2 = 22;
// int enable2Pin = 21;

int motor2Pin2 = 19;
int enable2Pin = 18;

TaskHandle_t Task1;
TaskHandle_t Task2;

void setup() {
    lcd.init();
    lcd.clear();                 
  lcd.backlight();
    lcd.setCursor(0, 0);
lcd.print("Lake Cleaning System Using IOT");

  delay(1000);
  Serial.print("Testing DC Motor...");
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());
  ThingSpeak.begin(client);

  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  analogWrite(enable1Pin, 250);


  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enable2Pin, OUTPUT);
  analogWrite(enable2Pin, 250);



  Serial.begin(9600);

pinMode(turbidity,INPUT);
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

  xTaskCreatePinnedToCore(
    upload,  /* Task function. */
    "Task1", /* name of task. */
    10000,   /* Stack size of task */
    NULL,    /* parameter of the task */
    1,       /* priority of the task */
    &Task1,  /* Task handle to keep track of created task */
    0);      /* pin task to core 0 */
  delay(500);

  //create a task that will be executed in the Task2code() function, with priority 1 and executed on core 1
  xTaskCreatePinnedToCore(
    control, /* Task function. */
    "Task2", /* name of task. */
    10000,   /* Stack size of task */
    NULL,    /* parameter of the task */
    1,       /* priority of the task */
    &Task2,  /* Task handle to keep track of created task */
    1);      /* pin task to core 1 */
  delay(500);
}
void upload(void* pvParameters) {
  for (;;) {
    int turbidity_val=analogRead(turbidity);
    Serial.println(turbidity_val);
  ThingSpeak.setField(1, turbidity_val);
  ThingSpeak.setStatus(myStatus);

  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if (x == 200) {
    Serial.println("Channel update successful.");
  } else {
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  delay(1000);
  }

}
void control(void* pvParameters) {
  for (;;) {
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

      delay(100);
    }
  }
}

void loop() {
  lcd.scrollDisplayLeft();
  delay(500);

}
