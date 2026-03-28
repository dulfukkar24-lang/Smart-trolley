#define L_RPWM 25

#define L_LPWM 26

#define L_EN_R 16

#define L_EN_L 17


#define R_RPWM 27

#define R_LPWM 13

#define R_EN_R 32

#define R_EN_L 33

#define PWM_FREQ 1000

#define PWM_RES 8


#define CH_L_RPWM 0

#define CH_L_LPWM 1

#define CH_R_RPWM 2

#define CH_R_LPWM 3

float trimL = 1.0;  

float trimR = 0.92;

int offsetL = 0;

int offsetR = 0;

int targetL = 0;

int targetR = 0;


unsigned long lastCmdTime = 0;

unsigned long lastTime = 0;

void hardStop() {

  digitalWrite(L_EN_R, LOW);

  digitalWrite(L_EN_L, LOW);

  digitalWrite(R_EN_R, LOW);

  digitalWrite(R_EN_L, LOW);


  ledcWrite(CH_L_RPWM, 0);

  ledcWrite(CH_L_LPWM, 0);

  ledcWrite(CH_R_RPWM, 0);

  ledcWrite(CH_R_LPWM, 0);

}


void setMotor(int pwmL, int pwmR) {

  pwmL = pwmL * trimL + offsetL;

  pwmR = pwmR * trimR + offsetR;


  pwmL = constrain(pwmL, -255, 255);

  pwmR = constrain(pwmR, -255, 255);

  if (abs(pwmL) < 20) pwmL = 0;

  if (abs(pwmR) < 20) pwmR = 0;

  if (pwmL == 0 && pwmR == 0) {

    hardStop();

    return;

  }

  digitalWrite(L_EN_R, HIGH);

  digitalWrite(L_EN_L, HIGH);

  digitalWrite(R_EN_R, HIGH);

  digitalWrite(R_EN_L, HIGH);

  if (pwmL > 0) {

    ledcWrite(CH_L_RPWM, pwmL);

    ledcWrite(CH_L_LPWM, 0);

  } else {

    ledcWrite(CH_L_RPWM, 0);

    ledcWrite(CH_L_LPWM, -pwmL);

  }

  if (pwmR > 0) {

    ledcWrite(CH_R_RPWM, pwmR);

    ledcWrite(CH_R_LPWM, 0);

  } else {

    ledcWrite(CH_R_RPWM, 0);

    ledcWrite(CH_R_LPWM, -pwmR);

  }

}

void setup() {

  Serial.begin(115200);


  ledcSetup(CH_L_RPWM, PWM_FREQ, PWM_RES);

  ledcSetup(CH_L_LPWM, PWM_FREQ, PWM_RES);

  ledcSetup(CH_R_RPWM, PWM_FREQ, PWM_RES);

  ledcSetup(CH_R_LPWM, PWM_FREQ, PWM_RES);


  ledcAttachPin(L_RPWM, CH_L_RPWM);

  ledcAttachPin(L_LPWM, CH_L_LPWM);

  ledcAttachPin(R_RPWM, CH_R_RPWM);

  ledcAttachPin(R_LPWM, CH_R_LPWM);


  pinMode(L_EN_R, OUTPUT);

  pinMode(L_EN_L, OUTPUT);

  pinMode(R_EN_R, OUTPUT);

  pinMode(R_EN_L, OUTPUT);


  hardStop();


  lastCmdTime = millis();


  Serial.println("=== OPEN LOOP (PWM TRIM) SYSTEM READY ===");

}

void loop() {

  if (Serial.available()) {

    String cmd = Serial.readStringUntil('\n');


    lastCmdTime = millis();


    if (cmd == "STOP") {

      targetL = 0;

      targetR = 0;

    } else {

      sscanf(cmd.c_str(), "L:%d,R:%d", &targetL, &targetR);

    }

  }

  if (millis() - lastCmdTime > 300) {

    targetL = 0;

    targetR = 0;

  }

  if (millis() - lastTime >= 100) {


    setMotor(targetL, targetR);


    Serial.print("CMD L:");

    Serial.print(targetL);

    Serial.print(" R:");

    Serial.println(targetR);


    lastTime = millis();

  }

}
