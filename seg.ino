int mos=A0;
int mos_val;


#include <Servo.h>

int ir=3;
int ir_val;

int servoPin = 9;
Servo servo;
int angle = 0; 
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
 servo.attach(servoPin);
 pinMode(ir,INPUT);
    servo.write(60);
    delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:


  ir_val=digitalRead(ir);
  Serial.println(ir_val);

  if(ir_val==0){
    delay(1000);
mos_val=analogRead(mos);
Serial.println(mos_val);
delay(1000);
if(mos_val<1000){
  Serial.println("wet");
  servo.write(0);
delay(2000);
servo.write(60);
delay(2000);
}
else
{
Serial.println("Dry");
servo.write(130);
delay(2000);
servo.write(60);
delay(2000);
}
  }


  else{
    Serial.print("no object found");
  }
}
