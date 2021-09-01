// motor one
int enA = 6;
int in1 = 7;
int in2 = 8;
// motor two
int enB = 3;
int in3 = 2;
int in4 = 4;

const uint8_t maxspeed_A = 200;
const uint8_t maxspeed_B = 200;
const uint8_t basespeed_A = 140;
const uint8_t basespeed_B = 140;
 

float elapsedTime, current_time, timePrev;

float pid_total, err, previous_error = 0;
float pid_p = 0;
float pid_i = 0;
float pid_d = 0;

double kp = 2.5;
double ki = 5;
double kd = 1.5;

int speed_A, speed_B;

void pid (float error){
timePrev = current_time;  
current_time = millis();  
elapsedTime = (current_time - timePrev) / 1000; 

  //Serial.println(error);

pid_p = kp*error;


pid_i = pid_i + (error*elapsedTime);  
  

pid_d = kd*((error - previous_error)/elapsedTime);

pid_total = pid_p + ki*pid_i + pid_d;
  //Serial.println(pid);


speed_A = basespeed_A - pid_total;
speed_B = basespeed_B + pid_total;

if (speed_A > maxspeed_A) {
  speed_A = maxspeed_A;
}
if (speed_B > maxspeed_B) {
  speed_B = maxspeed_B;
}

if (speed_A < 0) {
  speed_A = 0;
}
if (speed_B < 0) {
  speed_B = 0;
}

previous_error = error;
}

void setup() {
  // All the arduino pins used are outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  current_time = millis();
  Serial.begin(115200);
  Serial.setTimeout(1);
}

void moveForward(int speed1, int speed2){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, speed1); // Speed Range 0-255
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  analogWrite(enB,speed2);
}

void loop() {
  while (!Serial.available());
  err = Serial.readString().toInt();
//  Serial.print(x + 1);
  pid(err);
  moveForward(speed_A, speed_B);
}
