#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int enA = 9;
const int in1 = 4;
const int in2 = 5;

const int enB = 10;
const int in3 = 6;
const int in4 = 7;

const int enGripper = 3;
const int gripperIn1 = 8;
const int gripperIn2 = 11;

const int enLifter = 2;
const int lifterIn1 = 12;
const int lifterIn2 = 13;

String input = "";

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Ketik Perintah");
  lcd.setCursor(5, 1);
  lcd.print("Anda");

  pinMode(enA, OUTPUT);  pinMode(in1, OUTPUT);  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);  pinMode(in3, OUTPUT);  pinMode(in4, OUTPUT);

  pinMode(enGripper, OUTPUT);  pinMode(gripperIn1, OUTPUT);  pinMode(gripperIn2, OUTPUT);
  pinMode(enLifter, OUTPUT);   pinMode(lifterIn1, OUTPUT);   pinMode(lifterIn2, OUTPUT);

  stopMotor();
  stopGripper();
  stopLifter();
}

void loop() {
  if (Serial.available()) {
    input = Serial.readStringUntil('\n');
    input.trim();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Perintah: " + input);

    if (input == "maju") {
      maju(); lcd.setCursor(0, 1); lcd.print("Gerak Maju");
    } 
    else if (input == "mundur") {
      mundur(); lcd.setCursor(0, 1); lcd.print("Gerak Mundur");
    } 
    else if (input == "kiri") {
      belokKiri(); lcd.setCursor(0, 1); lcd.print("Belok Kiri");
    }
    else if (input == "kanan") {
      belokKanan(); lcd.setCursor(0, 1); lcd.print("Belok Kanan");
    }
    else if (input == "berhenti") {
      stopMotor(); lcd.setCursor(0, 1); lcd.print("Berhenti");
    }
    else if (input == "capit") {
      gripperCapit(); lcd.setCursor(0, 1); lcd.print("Gripper Capit");
    }
    else if (input == "stopgripper") {
      stopGripper(); lcd.setCursor(0, 1); lcd.print("Gripper Stop");
    }
    else if (input == "naik") {
      lifterNaik(); lcd.setCursor(0, 1); lcd.print("Lifter Naik");
    }
    else if (input == "stoplifter") {
      stopLifter(); lcd.setCursor(0, 1); lcd.print("Lifter Stop");
    }
    else {
      lcd.setCursor(0, 1);
      lcd.print("Salah Input");
    }
  }
}

void maju() {
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
  analogWrite(enA, 200); analogWrite(enB, 200);
}

void mundur() {
  digitalWrite(in1, LOW); digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW); digitalWrite(in4, HIGH);
  analogWrite(enA, 200); analogWrite(enB, 200);
}

void belokKiri() {
  digitalWrite(in1, LOW); digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
  analogWrite(enA, 200); analogWrite(enB, 200);
}

void belokKanan() {
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
  digitalWrite(in3, LOW); digitalWrite(in4, HIGH);
  analogWrite(enA, 200); analogWrite(enB, 200);
}

void stopMotor() {
  digitalWrite(in1, LOW); digitalWrite(in2, LOW);
  digitalWrite(in3, LOW); digitalWrite(in4, LOW);
  analogWrite(enA, 0); analogWrite(enB, 0);
}

void gripperCapit() {
  digitalWrite(gripperIn1, HIGH);
  digitalWrite(gripperIn2, LOW);
  analogWrite(enGripper, 180);
}

void stopGripper() {
  digitalWrite(gripperIn1, LOW);
  digitalWrite(gripperIn2, LOW);
  analogWrite(enGripper, 0);
}

void lifterNaik() {
  digitalWrite(lifterIn1, HIGH);
  digitalWrite(lifterIn2, LOW);
  analogWrite(enLifter, 180);
}

void stopLifter() {
  digitalWrite(lifterIn1, LOW);
  digitalWrite(lifterIn2, LOW);
  analogWrite(enLifter, 0);
}
