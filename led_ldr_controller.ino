// Realizar una aplicación que realice las siguientes tareas a través de una página web sencilla:
// 1. Controle el brillo de los led 9, 10 y 11 del Arduino UNO utilizando el conversor Digital a Analógico del mismo. El brillo de estos leds debe controlarse de forma independiente para cada led.
// 2. Encienda y apague el led 13 del Arduino UNO. Deberá utilizar dicho pin como salida digital.
// 3. Muestre la intensidad luminosa captada por el LDR (conectado al pin A3 del Arduino UNO). Deberá utilizar el conversor Analógico a Digital.
// 4. El control del brillo de los led 9, 10 y 11, el pin 13 y el valor de la intensidad luminosa sensado por el LDR deberá realizarse y mostrarse a través de una página web que deberá poder accederse desde otras computadoras conectadas en la misma red LAN o Internet.
// 5. La página web debe mostrar el valor actual del brillo de los leds, el estado del pin 13 y el valor leído por el LDR.

int l1 = 0, l2 = 0, l3 = 0;
bool d13 = false;

void setup() {
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  // Read LDR
  int a3 = analogRead(A3);

  // Check for serial commands
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    int colon = cmd.indexOf(':');
    if (colon != -1) {
      String key = cmd.substring(0, colon);
      int val = cmd.substring(colon + 1).toInt();

      if (key == "L1") {
        l1 = val;
        analogWrite(9, l1);
      } else if (key == "L2") {
        l2 = val;
        analogWrite(10, l2);
      } else if (key == "L3") {
        l3 = val;
        analogWrite(11, l3);
      } else if (key == "D13") {
        d13 = val;
        digitalWrite(13, d13);
      }
    }
  }

  // Send current state
  Serial.print("L1:"); Serial.print(l1);
  Serial.print(";L2:"); Serial.print(l2);
  Serial.print(";L3:"); Serial.print(l3);
  Serial.print(";D13:"); Serial.print(d13);
  Serial.print(";A3:"); Serial.print(a3);
  Serial.println(";");
  delay(200);
}