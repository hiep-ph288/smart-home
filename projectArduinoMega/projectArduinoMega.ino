#include "DHT.h"
#include "Wire.h"
#include "LiquidCrystal_I2C.h"
// #include "define.h"  //THU VIEN
// file này đuoqcj viết vào ngày 8 tháng 3
//PHONG NGU------------------------------------
#define INPUT_BUTTON_REM 3
#define INPUT_BUTTON_PWM10 2
#define INPUT_BUTTON_MH 4

#define INPUT_SENSOR_DHT11PN 40

#define INPUT_SENSOR_PIRPN 47
#define OUTPUT_LEDPN 31
#define INPUT_SENSOR_MHPN A1

// #define OUTPUT_PWM10_DHT11    11
#define OUTPUT_LED_PIR 33
#define OUTPUT_LED_MH 35


//PHONG KHACH----------------------------------
#define INPUT_BUTTON_PWM9 6
#define INPUT_BUTTON_LED 7
#define INPUT_BUTTON_PAN 5
#define INPUT_BUTTON_PANPK 42


#define INPUT_SENSOR_DHT11PK 41
#define INPUT_SENSOR_GAS A0

// #define OUTPUT_PWM9_DHT11     10
#define OUTPUT_LEDPK 37
#define OUTPUT_LEDPK1 39
#define OUTPUT_PANPK1 8
#define OUTPUT_PANTG1 10
#define OUTPUT_PANPK 44  // chân mới thêm



//WC--------------------------------------------
#define INPUT_SENSOR_DHT11WC 45
#define INPUT_SENSOR_PIRWC 49

#define OUTPUT_LEDWC 51
#define OUTPUT_PANWC 9

//Gara-Vuon--------------------------------------------
#include <Servo.h>
Servo myservo;
#define INPUT_SENSOR_DOAMDAT A2
#define OUTPUT_BOM 52

int pos = 0;  //gocquay_servogara
#define OUTPUT_SERVO_GARA 50
#define INPUT_BUTTON_GARA 48
int stateWindow = 0;  // state cửa chính
int statemaybom = 0;
int quatwcstate =0;

//---------------------------------------------------------------------
//---------------------------------------------------------------------
LiquidCrystal_I2C lcd(0x27, 16, 2);
LiquidCrystal_I2C lcd16(0x3f, 16, 2);

const int DHTTYPE = DHT11;
const int DHTTYPE1 = DHT11;
const int DHTTYPEWC = DHT11;
DHT dht(INPUT_SENSOR_DHT11PN, DHTTYPE);
DHT dht1(INPUT_SENSOR_DHT11PK, DHTTYPE1);
DHT dhtwc(INPUT_SENSOR_DHT11WC, DHTTYPEWC);
//-------------------------------------------------
#include <AccelStepper.h>
// Motor pin definitions:
#define motorPin1 23  // IN1 on the ULN2003 driver
#define motorPin2 25  // IN2 on the ULN2003 driver
#define motorPin3 27  // IN3 on the ULN2003 driver
#define motorPin4 29  // IN4 on the ULN2003 driver
#define MotorInterfaceType 8
AccelStepper stepper = AccelStepper(MotorInterfaceType, motorPin1, motorPin3, motorPin2, motorPin4);
//--------------------------------------------------

String datapn;
String datapk;
// du lieu do am dat
String datadoamdat;
String datal;
String datalpn;
String dataq;
String dataqpk;
String dataservogara;
// code khí gas
String datagas;
String datawc;



//PAR PWM---------------------------------------
int pwm9 = 0;
int pwm10 = 0;

//DIEU CHINH NHIET DO DIEU HOA VA LED+QUAT QUA WEB
float Temppn = 26;  // GIA TRI DAT
float Temppk = 26;  // GIA TRI DAT
float changeTemppn = Temppn * 2;
float changeTemppk = Temppk * 2;
float tam1 = 0.00;



uint8_t controlpan = 0;
uint8_t controlpanPK = 0;

uint8_t controlled = 0;
uint8_t controlledPN = 0;
uint8_t controlservogara = 0;

uint8_t controlHenGio = 0;
uint8_t stateQuatPN = 0;

//CAC HAM CHUC NANG VA KHOI TAO-------------------------------------------------------------------------------------

void reciveforweb(void) {
  String datare = "";
  while (Serial.available()) {
    char c = (char)Serial.read();
    if (c == 'n') {
      tam1 = (float)datare.toInt();
      if (tam1 > 0.00) {
        Temppn = (float)datare.toInt();
        lcd.setCursor(14, 0);
        lcd.print((uint8_t)Temppn);
        int nhietdo = dht.readTemperature();

        if (Temppn < nhietdo) {
          digitalWrite(OUTPUT_PANPK1, HIGH);

        } else {
          digitalWrite(OUTPUT_PANPK1, LOW);
        }
        Serial.print("\n");
        Serial.print(Temppn);
        Serial.print("---");
        Serial.print(datare);
        Serial.print("\n");
      }
      datare = "";
    } else if (c == 'k') {
      tam1 = (float)datare.toInt();
      if (tam1 > 0.00) {
        Temppk = (float)datare.toInt();
        lcd16.setCursor(11, 1);
        lcd16.print((uint8_t)Temppk);
        //TEST
        Serial.print("\n");
        Serial.print(Temppk);
        Serial.print("---");
        Serial.print(datare);
        Serial.print("\n");
        int nhietdopk = dht.readTemperature();

        if (Temppk < nhietdopk) {
          digitalWrite(OUTPUT_PANPK, HIGH);
        } else {
          digitalWrite(OUTPUT_PANPK, LOW);
        }
      }
      datare = "";
    } else if (c == 'q') {
      controlpan = (uint8_t)datare.toInt();
      lcd16.setCursor(14, 1);
      lcd16.print(controlpan);
      //TEST
      Serial.print("\n");
      Serial.print(controlpan);
      Serial.print("---");
      Serial.print(datare);
      Serial.print("\n");
      datare = "";
    } else if (c == 'v') {
      controlpanPK = (uint8_t)datare.toInt();
      lcd16.setCursor(14, 1);
      lcd16.print(controlpanPK);
      //TEST
      Serial.print("\n");
      Serial.print(controlpanPK);
      Serial.print("---");
      Serial.print(datare);
      Serial.print("\n");
      datare = "";
    } else if (c == 'i') {
      controlservogara = (uint8_t)datare.toInt();
      lcd16.setCursor(14, 1);
      lcd16.print(controlservogara);
      //TEST
      Serial.print("\n");
      Serial.print(controlservogara);
      datare = "";
    } else if (c == 'l') {
      controlled = (uint8_t)datare.toInt();
      lcd16.setCursor(15, 1);
      lcd16.print(controlled);
      //TEST
      Serial.print("\n");
      Serial.print(controlled);
      Serial.print("---");
      Serial.print(datare);
      Serial.print("\n");
      datare = "";
    }
    else if (c == 'w') {
      quatwcstate = (uint8_t)datare.toInt();
/// code quat nha ve sinh
      //TEST
      Serial.print("\n");
      Serial.print(quatwcstate);
      Serial.print("---");
      Serial.print(datare);
      Serial.print("\n");
      datare = "";
    }
     else if (c == 'z') {
      controlledPN = (uint8_t)datare.toInt();
      lcd16.setCursor(15, 1);
      lcd16.print(controlledPN);
      //TEST
      Serial.print("\n");
      Serial.print(controlledPN);
      Serial.print("---");
      Serial.print(datare);
      Serial.print("\n");
      datare = "";
    } else if (c == 's') {
      statemaybom = (uint8_t)datare.toInt();
      Serial.print("\n");
      Serial.print(statemaybom);
      Serial.print("---");
      Serial.print(datare);
      Serial.print("\n");
      datare = "";
    }

    else if (c == '*') {
      if (controlHenGio == 0) {
        controlHenGio = 1;
      }
      else if(controlHenGio==1){
        controlHenGio=0;
      }
      datare = "";
    } else {
      datare = datare + c;
    }
  }
}

void intiter(void) {
  //PHONG NGU------------------------------------------
  pinMode(INPUT_BUTTON_REM, INPUT);
  pinMode(INPUT_BUTTON_PWM10, INPUT);
  pinMode(INPUT_BUTTON_MH, INPUT);

  pinMode(INPUT_SENSOR_DHT11PN, INPUT);
  pinMode(INPUT_SENSOR_PIRPN, INPUT);
  pinMode(INPUT_SENSOR_MHPN, INPUT);
  pinMode(OUTPUT_LEDPN, OUTPUT);

  // pinMode(OUTPUT_PWM10_DHT11, OUTPUT);
  pinMode(OUTPUT_LED_PIR, OUTPUT);
  pinMode(OUTPUT_LED_MH, OUTPUT);

  //PHONG KHACH----------------------------------------
  // pinMode(INPUT_BUTTON_PWM9, INPUT);
  pinMode(INPUT_BUTTON_LED, INPUT);
  pinMode(INPUT_BUTTON_PAN, INPUT);
  pinMode(INPUT_BUTTON_PANPK, INPUT);  // nút bấm pk


  pinMode(INPUT_SENSOR_DHT11PK, INPUT);
  pinMode(INPUT_SENSOR_GAS, INPUT);

  // pinMode(OUTPUT_PWM10_DHT11, OUTPUT);
  pinMode(OUTPUT_LEDPK, OUTPUT);
  pinMode(OUTPUT_PANPK1, OUTPUT);
  pinMode(OUTPUT_PANTG1, OUTPUT);
  pinMode(OUTPUT_PANPK, OUTPUT);  // quạt pk mới


  //WC------------------------------------------------
  pinMode(INPUT_SENSOR_DHT11WC, INPUT);
  pinMode(INPUT_SENSOR_PIRWC, INPUT);

  pinMode(OUTPUT_LEDWC, OUTPUT);
  pinMode(OUTPUT_PANWC, OUTPUT);

  //--------------------------------------------------
  digitalWrite(OUTPUT_PANPK1, LOW);
  digitalWrite(OUTPUT_PANTG1, LOW);
  digitalWrite(OUTPUT_PANWC, LOW);
  digitalWrite(OUTPUT_PANPK, LOW);
  //Gara-vuon------------------------------------------------
  pinMode(OUTPUT_BOM, OUTPUT);
  pinMode(INPUT_BUTTON_GARA, INPUT);
  myservo.attach(OUTPUT_SERVO_GARA);
  pinMode(OUTPUT_SERVO_GARA, OUTPUT);
  digitalWrite(OUTPUT_SERVO_GARA, LOW);
}

void lcdintstart(void) {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("T: ");
  lcd.setCursor(5, 0);
  lcd.print("|H:");
  lcd.setCursor(11, 0);
  lcd.print("|T:");
  lcd.setCursor(14, 0);
  lcd.print("26");

  //GARA-VUON
  // Hiển thị giá trị cảm biến lên màn hình lcd
  lcd.setCursor(0, 1);
  lcd.print("DA: ");
  lcd.setCursor(5, 1);
  lcd.print("%");
  //Hiển thị giá trị biến trở lên màn hình lcd32
  lcd16.init();
  lcd16.backlight();
  lcd16.setCursor(0, 0);
  lcd16.print("T: ");
  lcd16.setCursor(7, 0);
  lcd16.print("|H: ");
  lcd16.setCursor(6, 1);
  lcd16.print("|TP: ");
  lcd16.setCursor(11, 1);
  lcd16.print("26");
}

void controlVuon() {
  //Đọc giá trị và chuyển đổi sang phần trăm của vườn
  int sensorValue = analogRead(INPUT_SENSOR_DOAMDAT);
  int sensorPercent = map(sensorValue, 0, 1023, 100, 0);
  datadoamdat = String(sensorPercent) + "b";
  Serial.print(datadoamdat);
  lcd.setCursor(3, 1);
  lcd.print(sensorPercent);
  lcd.setCursor(12, 1);
  // So sánh
  if (statemaybom == 1) {
    digitalWrite(OUTPUT_BOM, HIGH);
  } else {
    digitalWrite(OUTPUT_BOM, LOW);
  }
}


//PHÒNG NGỦ---------------------------------------------------------------------------
void PIDpn(float xi) {
  float Kp = 0.6;
  float Ki = 0.2;
  float Kd = 0.2;
  float Ei = Temppn;
  static float xPrev = Temppn;
  static float e = Temppn;
  static float sum_e = 0;
  static uint32_t dem = 0;
  static float P, I, D;

  dem++;
  e = Temppn - xi;  // calculate the error value.
  sum_e = sum_e + e;

  P = Kp * e;
  I = Ki * (sum_e / dem);
  D = Kd * (xi - xPrev);

  Ei = (P + I + D) / (Kp + Ki + Kd);  // OUTPUT OF THE PID ALGORITHM.
  xPrev = xi;
  pwm10 = pwm10 - Ei;
  if (pwm10 >= 255) {
    pwm10 = 255;
  } else if (pwm10 <= 0) {
    pwm10 = 0;
  }
}

// uint8_t t;
void readdht11pn(void) {
  uint8_t h = dht.readHumidity();
  datapn = String(h) + "h";
  Serial.print(datapn);
  uint8_t t = dht.readTemperature();
  datapn = String(t) + "t";
  Serial.print(datapn);
  lcd.setCursor(2, 0);
  lcd.print("   ");
  lcd.setCursor(8, 0);
  lcd.print("   ");
  lcd.setCursor(2, 0);
  lcd.print(t);
  lcd.setCursor(8, 0);
  lcd.print(h);
}

void cbas(void) {
  int givenValue = analogRead(INPUT_SENSOR_MHPN);
  if (givenValue > 300) {
    lcd16.setCursor(0, 1);
    lcd16.print("NIGHT");
    delay(200);
  } else {
    lcd16.setCursor(0, 1);
    lcd16.print("  DAY");
    delay(200);
  }
  if (digitalRead(INPUT_BUTTON_MH) == 0) {
    int value = digitalRead(INPUT_SENSOR_MHPN);  //lưu giá trị cảm biến vào biến value
    digitalWrite(OUTPUT_LED_MH, value);          //xuất giá trị ra đèn LED
  } else {
    digitalWrite(OUTPUT_LED_MH, LOW);
  }
}

void pirLedpn(void) {
  digitalWrite(OUTPUT_LED_PIR, digitalRead(INPUT_SENSOR_PIRPN));
}

void controlRem(void) {
  static unsigned char stt_old_webrem = 0;
  static unsigned char stt_old_gobrem = 0;
  static unsigned char stt_change_buttonR = 1;
  static unsigned char stt_rem = 0;

  if (digitalRead(INPUT_BUTTON_REM) != stt_change_buttonR) {
    stt_change_buttonR = digitalRead(INPUT_BUTTON_REM);
    if (digitalRead(INPUT_BUTTON_REM) == 1) {
      delay(20);
      if (digitalRead(INPUT_BUTTON_REM) == 1) {
        stt_rem = !stt_rem;
      }
    }
    // stt_rem = !stt_rem;
  }
  if ((controlHenGio != stt_old_webrem) || (stt_rem != stt_old_gobrem)) {
    stt_old_webrem = !stt_old_webrem;
    stt_old_gobrem = !stt_old_gobrem;
    controlHenGio = stt_old_webrem;
    stt_rem = stt_old_gobrem;
    if (stt_old_webrem == 1) {
      stepper.setCurrentPosition(0);
      while (stepper.currentPosition() != 4096) {
        stepper.setSpeed(1000);
        stepper.runSpeed();
      }
    } else {
      stepper.setCurrentPosition(4096);
      while (stepper.currentPosition() != 0) {
        stepper.setSpeed(-1000);
        stepper.runSpeed();
      }
    }
  }
}


//PHÒNG KHÁCH-------------------------------------------------------------------------
void readdht11pk(void) {
  uint8_t h1 = dht1.readHumidity();
  datapk = String(h1) + "o";
  Serial.print(datapk);
  uint8_t t1 = dht1.readTemperature();
  datapk = String(t1) + "p";
  Serial.print(datapk);
  lcd16.setCursor(2, 0);
  lcd16.print("   ");
  lcd16.setCursor(11, 0);
  lcd16.print("   ");
  lcd16.setCursor(2, 0);
  lcd16.print(t1);
  lcd16.setCursor(11, 0);
  lcd16.print(h1);
}

void PIDpk(float xi) {
  float Kp = 0.6;
  float Ki = 0.2;
  float Kd = 0.2;
  float Ei = Temppk;
  static float xPrev = Temppk;
  static float e = Temppk;
  static float sum_e = 0;
  static uint32_t dem = 0;
  static float P, I, D;

  dem++;
  e = Temppk - xi;  // calculate the error value.
  sum_e = sum_e + e;

  P = Kp * e;
  I = Ki * (sum_e / dem);
  D = Kd * (xi - xPrev);

  Ei = (P + I + D) / (Kp + Ki + Kd);  // OUTPUT OF THE PID ALGORITHM.
  xPrev = xi;
  pwm9 = pwm9 - Ei;
  if (pwm9 >= 255) {
    pwm9 = 255;
  } else if (pwm9 <= 0) {
    pwm9 = 0;
  }
}

void GasToMotor(void) {
  int gasValue;
  gasValue = analogRead(INPUT_SENSOR_GAS);
  delay(20);
  if (gasValue >= 950) {
    digitalWrite(OUTPUT_PANTG1, HIGH);
  } else {
    digitalWrite(OUTPUT_PANTG1, LOW);
  }
  // đoạn này thêm  khí gas 8/3 1h25
  datagas = String(gasValue) + "f";
  Serial.print(datagas);
}

void control_led(void) {
  static unsigned char stt_old_webled = 0;
  static unsigned char stt_old_gobled = 0;
  static unsigned char stt_change_buttonL = 1;
  static unsigned char stt_led = 0;
  static unsigned short delaysendled = 0;

  if (digitalRead(INPUT_BUTTON_LED) != stt_change_buttonL) {
    stt_change_buttonL = digitalRead(INPUT_BUTTON_LED);
    // stt_led = !stt_led;
    if (digitalRead(INPUT_BUTTON_LED) == 1) {
      delay(20);
      if (digitalRead(INPUT_BUTTON_LED) == 1) {
        stt_led = !stt_led;
      }
    }
  }

  if ((controlled != stt_old_webled) || (stt_led != stt_old_gobled)) {
    stt_old_webled = !stt_old_webled;
    stt_old_gobled = !stt_old_gobled;
    controlled = stt_old_webled;
    stt_led = stt_old_gobled;
    if (stt_old_webled == 1) {
      digitalWrite(OUTPUT_LEDPK1, HIGH);
      digitalWrite(OUTPUT_LEDPK, HIGH);
    } else {
      digitalWrite(OUTPUT_LEDPK1, LOW);
      digitalWrite(OUTPUT_LEDPK, LOW);
    }
  }

  delaysendled++;
  if (delaysendled >= 1500) {
    if (delaysendled == 1504) {
      delaysendled = 0;
    }
    datal = String(stt_old_webled) + "l";
    Serial.print(datal);
  }
}
void control_ledpn(void) {
  static unsigned char stt_old_webledPN = 0;
  static unsigned char stt_old_gobledPN = 0;
  static unsigned char stt_change_buttonLPN = 1;
  static unsigned char stt_ledPN = 0;
  static unsigned short delaysendledPN = 0;
  if (digitalRead(INPUT_BUTTON_PWM10) != stt_change_buttonLPN) {
    stt_change_buttonLPN = digitalRead(INPUT_BUTTON_PWM10);
    // stt_led = !stt_led;
    if (digitalRead(INPUT_BUTTON_PWM10) == 1) {
      delay(20);
      if (digitalRead(INPUT_BUTTON_PWM10) == 1) {
        stt_ledPN = !stt_ledPN;
      }
    }
  }

  if ((controlledPN != stt_old_webledPN) || (stt_ledPN != stt_old_gobledPN)) {
    stt_old_webledPN = !stt_old_webledPN;
    stt_old_gobledPN = !stt_old_gobledPN;
    controlledPN = stt_old_webledPN;
    stt_ledPN = stt_old_gobledPN;
    if (stt_old_webledPN == 1) {
      digitalWrite(OUTPUT_LEDPN, HIGH);
      // digitalWrite(OUTPUT_LEDPK, HIGH);
    } else {
      digitalWrite(OUTPUT_LEDPN, LOW);
      // digitalWrite(OUTPUT_LEDPK, LOW);
    }
  }

  delaysendledPN++;
  if (delaysendledPN >= 1500) {
    if (delaysendledPN == 1504) {
      delaysendledPN = 0;
    }
    datalpn = String(stt_old_webledPN) + "s";
    Serial.print(datalpn);
  }
}
/// dieu khien servo gara

void control_servoGara(void) {
  static unsigned char stt_old_webservoGara = 0;
  static unsigned char stt_old_gobservoGara = 0;
  static unsigned char stt_change_buttonPK = 1;
  static unsigned char stt_servoGara = 0;
  static unsigned short delaysendservoGara = 0;
  if (digitalRead(INPUT_BUTTON_GARA) != stt_change_buttonPK) {
    delay(20);
    if (digitalRead(INPUT_BUTTON_GARA) != stt_change_buttonPK) {
      stt_change_buttonPK = digitalRead(INPUT_BUTTON_GARA);
      if (digitalRead(INPUT_BUTTON_GARA) == 1) {
        delay(20);
        {
          if (digitalRead(INPUT_BUTTON_GARA) == 1) {
            stt_servoGara = !stt_servoGara;
          }
        }
      }
    }
  }
  if ((controlservogara != stt_old_webservoGara) || (stt_servoGara != stt_old_gobservoGara)) {
    stt_old_webservoGara = !stt_old_webservoGara;
    stt_old_gobservoGara = !stt_old_gobservoGara;
    controlservogara = stt_old_webservoGara;
    stt_servoGara = stt_old_gobservoGara;
    if (stt_old_webservoGara == 1) {
      // digitalWrite(OUTPUT_servoGara, LOW);
      myservo.write(0);

    } else {
      // digitalWrite(OUTPUT_servoGara, HIGH);
      myservo.write(90);
    }
  }

  delaysendservoGara++;
  if (delaysendservoGara >= 1200) {
    if (delaysendservoGara == 1204) {
      delaysendservoGara = 0;
    }
    dataservogara = String(stt_old_webservoGara) + "d";
    Serial.print(dataservogara);
  }
}

void control_panPK(void) {
  static unsigned char stt_old_webpanPK = 0;
  static unsigned char stt_old_gobpanPK = 0;
  static unsigned char stt_change_buttonPK = 1;
  static unsigned char stt_panPK = 0;
  static unsigned short delaysendpanPK = 0;


  if (digitalRead(INPUT_BUTTON_PANPK) != stt_change_buttonPK) {
    delay(20);
    if (digitalRead(INPUT_BUTTON_PANPK) != stt_change_buttonPK) {
      stt_change_buttonPK = digitalRead(INPUT_BUTTON_PANPK);
      if (digitalRead(INPUT_BUTTON_PANPK) == 1) {
        delay(20);
        {
          if (digitalRead(INPUT_BUTTON_PANPK) == 1) {
            stt_panPK = !stt_panPK;
          }
        }
      }
      // stt_pan = !stt_pan;
    }
  }
  if ((controlpanPK != stt_old_webpanPK) || (stt_panPK != stt_old_gobpanPK)) {
    stt_old_webpanPK = !stt_old_webpanPK;
    stt_old_gobpanPK = !stt_old_gobpanPK;
    controlpanPK = stt_old_webpanPK;
    stt_panPK = stt_old_gobpanPK;
    if (stt_old_webpanPK == 1) {
      digitalWrite(OUTPUT_PANPK, LOW);
    } else {
      digitalWrite(OUTPUT_PANPK, HIGH);
    }
  }

  delaysendpanPK++;
  if (delaysendpanPK >= 1200) {
    if (delaysendpanPK == 1204) {
      delaysendpanPK = 0;
    }
    dataqpk = String(stt_old_webpanPK) + "a";
    Serial.print(dataqpk);
  }
}

void control_pan(void) {
  static unsigned char stt_old_webpan = 0;
  static unsigned char stt_old_gobpan = 0;
  static unsigned char stt_change_buttonP = 1;
  static unsigned char stt_pan = 0;
  static unsigned short delaysendpan = 0;
  if (digitalRead(INPUT_BUTTON_PAN) != stt_change_buttonP) {
    delay(20);
    if (digitalRead(INPUT_BUTTON_PAN) != stt_change_buttonP) {
      stt_change_buttonP = digitalRead(INPUT_BUTTON_PAN);
      if (digitalRead(INPUT_BUTTON_PAN) == 1) {
        delay(20);
        {
          if (digitalRead(INPUT_BUTTON_PAN) == 1) {
            stt_pan = !stt_pan;
          }
        }
      }
    }
  }
  if ((controlpan != stt_old_webpan) || (stt_pan != stt_old_gobpan)) {
    stt_old_webpan = !stt_old_webpan;
    stt_old_gobpan = !stt_old_gobpan;
    controlpan = stt_old_webpan;
    stt_pan = stt_old_gobpan;
    if (stt_old_webpan == 1) {
      digitalWrite(OUTPUT_PANPK1, LOW);
    } else {
      digitalWrite(OUTPUT_PANPK1, HIGH);
    }
  }

  delaysendpan++;
  if (delaysendpan >= 1200) {
    if (delaysendpan == 1204) {
      delaysendpan = 0;
    }
    dataq = String(stt_old_webpan) + "q";
    Serial.print(dataq);
  }
}
//WC----------------------------------------------------------------------------------
void pirLedwc(void) {
  digitalWrite(OUTPUT_LEDWC, digitalRead(INPUT_SENSOR_PIRWC));
}

void readdht11wc(void) {
  uint8_t h2 = dhtwc.readHumidity();
  datawc = String(h2) + "y";
  Serial.print(datawc);
  uint8_t t2 = dhtwc.readTemperature();
  uint8_t temp = 0;
  datawc = String(t2) + "u";
  Serial.print(datawc);
  if ((t2 > 35)) {
    digitalWrite(OUTPUT_PANWC, HIGH);
  }
   else if(quatwcstate==0) {
    digitalWrite(OUTPUT_PANWC, LOW);
  }
  else if(quatwcstate==1){
     digitalWrite(OUTPUT_PANWC, HIGH);
  }
  else{
    digitalWrite(OUTPUT_PANWC, LOW);
  }
  
}

//-----------------------------------------------------------------------------------
void setup() {
  stepper.setMaxSpeed(1000);
  Serial.begin(115200);
  intiter();
  lcdintstart();
  dht.begin();
  dht1.begin();
  dhtwc.begin();
}

//THỰC THI CÁC CHỨC NĂNG--------------------------------------------------------
void loop() {
  reciveforweb();
  readdht11pn();
  readdht11pk();
  readdht11wc();
  GasToMotor();
  pirLedpn();
  pirLedwc();
  control_led();
  control_ledpn();
  control_servoGara();
  control_pan();
  control_panPK();
  cbas();
  controlRem();
  controlVuon();
}
