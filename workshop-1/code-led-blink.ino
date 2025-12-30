// =====================================
// Workshop 1: Simple LED Blink
// Your very first Arduino sketch!
// =====================================

void setup() {
  // setup() runs ONCE when board powers on
  Serial.begin(9600);
  pinMode(2, OUTPUT);  // Set pin 2 to output mode
  Serial.println("LED Blink starting...");
}

void loop() {
  // loop() runs forever, over and over
  digitalWrite(2, HIGH);  // Turn LED on (5V)
  Serial.println("LED ON");
  delay(1000);            // Wait 1 second (1000 milliseconds)
  
  digitalWrite(2, LOW);   // Turn LED off (0V)
  Serial.println("LED OFF");
  delay(1000);            // Wait 1 second
}

