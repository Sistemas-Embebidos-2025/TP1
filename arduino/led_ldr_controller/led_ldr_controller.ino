// Variables to store the state of LEDs and digital pin 13
int l1 = 0, l2 = 0, l3 = 0;
bool d13 = false;

void setup() {
  // Initialize serial communication at a baud rate of 9600
  Serial.begin(9600);
  
  // Set pin modes for LEDs and digital pin 13
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  // Read the value from the LDR (Light Dependent Resistor) connected to analog pin A3
  int a3 = analogRead(A3);

  // Check if there are any serial commands available
  if (Serial.available() > 0) {
    // Read the incoming serial command until a newline character is encountered
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();  // Remove any leading or trailing whitespace
    int colon = cmd.indexOf(':');  // Find the position of the colon character

    // If a colon is found, parse the command
    if (colon != -1) {
      String key = cmd.substring(0, colon);  // Extract the key part of the command
      int val = cmd.substring(colon + 1).toInt();  // Extract the value part of the command and convert to integer

      // Update the corresponding LED or digital pin based on the key
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

  // Send the current state of LEDs, digital pin 13, and LDR value to the serial port
  Serial.print("L1:"); Serial.print(l1);
  Serial.print(";L2:"); Serial.print(l2);
  Serial.print(";L3:"); Serial.print(l3);
  Serial.print(";D13:"); Serial.print(d13);
  Serial.print(";A3:"); Serial.print(a3);
  Serial.println(";");
  
  // Delay for 500 milliseconds before the next loop iteration
  delay(500);
}