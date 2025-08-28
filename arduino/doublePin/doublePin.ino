// Arduino Multi-Channel Controller
// Commands: 0=off, 1=both on, 6=channel 6 on, 7=channel 7 on
// Auto-timeout functionality included

const int CHANNEL_6_PIN = 6;
const int CHANNEL_7_PIN = 7;

bool channel6State = false;
bool channel7State = false;
unsigned long timeoutDuration = 0; // in milliseconds
unsigned long startTime = 0;
bool timeoutActive = false;

void setup() {
  Serial.begin(9600);
  pinMode(CHANNEL_6_PIN, OUTPUT);
  pinMode(CHANNEL_7_PIN, OUTPUT);
  
  // Initialize channels to OFF
  digitalWrite(CHANNEL_6_PIN, LOW);
  digitalWrite(CHANNEL_7_PIN, LOW);
  
  // Use F() macro to store string literals on the flash memory instead
  Serial.println(F("Arduino Multi-Channel Controller Ready"));
  Serial.println(F("Commands:"));
  Serial.println(F("OFF = Turn OFF all channels"));
  Serial.println(F("BOTH = Turn ON both channels"));
  Serial.println(F("CH6 = Turn ON channel 6"));
  Serial.println(F("CH7 = Turn ON channel 7"));
  Serial.println(F("STATUS = Print current status"));
  Serial.println(F("Enter number for timeout in seconds (0 to disable):"));

  printStatus();
}

void loop() {
  // Check for serial input
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    input.toUpperCase(); // Convert to uppercase for easier matching
    
    // Check if input is a number (timeout)
    if (isNumeric(input)) {
      float seconds = input.toFloat();
      setTimeout(seconds);
    } else {
      // Process string command
      processCommand(input);
    }
  }
  
  // Check timeout
  checkTimeout();
  
  delay(100); // Small delay to prevent excessive processing
}

void setTimeout(float seconds) {
  if (seconds > 0) {
    timeoutDuration = seconds * 1000; // Convert seconds to milliseconds
    Serial.print(F("Timeout set to "));
    Serial.print(seconds);
    Serial.println(F(" seconds"));
    
    // If channels are currently on, start the timeout
    if (channel6State || channel7State) {
      startTimeout();
    }
    else {
      timeoutActive = false;
      Serial.print(F("Current timeout setting in seconds "));
      Serial.println(timeoutDuration / 1000.);
      Serial.println(F("Timeout disabled because both channels are off."));
    }
  }
}

void startTimeout() {
  if (timeoutDuration > 0) {
    startTime = millis();
    timeoutActive = true;
    Serial.print(F("Timeout started - will turn off in "));
    Serial.print(timeoutDuration / 1000.0);
    Serial.println(F(" seconds"));
    printStatus();
  }
}

void checkTimeout() {
  if (timeoutActive && (millis() - startTime >= timeoutDuration)) {
    Serial.println("TIMEOUT: Turning off all channels");
    turnOffAllChannels();
    printStatus();
  }
}


void printStatus() {
  Serial.println("--- Status ---");
  Serial.print("Channel 6: ");
  Serial.println(channel6State ? "ON" : "OFF");
  Serial.print("Channel 7: ");
  Serial.println(channel7State ? "ON" : "OFF");
  
  if (timeoutDuration > 0) {
    Serial.print("Timeout: ");
    Serial.print(timeoutDuration / 1000.0);
    Serial.print(" seconds");
    
    if (timeoutActive) {
      unsigned long remaining = timeoutDuration - (millis() - startTime);
      Serial.print(" (");
      Serial.print(remaining / 1000.0);
      Serial.print(" seconds remaining)");
    }
    Serial.println();
  } else {
    Serial.println("Timeout: Disabled");
  }
  
  Serial.println("--- End Status ---");
  Serial.println();
}

void processCommand(String command) {
  bool anyChannelOn = channel6State || channel7State;
  
  if (command == "OFF") {
    // Turn OFF - always allowed
    turnOffAllChannels();
    Serial.println("Command: Turn OFF all channels");
  }
  else if (command == "BOTH") {
    // Turn both ON - only if both are currently OFF
    if (!anyChannelOn) {
      turnOnChannel(6);
      turnOnChannel(7);
      Serial.println("Command: Turn ON both channels");
      startTimeout();
    } else {
      Serial.println("Command ignored: One or both channels already ON");
    }
  }
  else if (command == "CH6") {
    // Turn ON channel 6 - only if no channels are ON
    if (!channel6State) {
      turnOnChannel(6);
      Serial.println("Command: Turn ON channel 6");
      startTimeout();
    } else {
      Serial.println("Command ignored: Channel already ON");
    }
  }
  else if (command == "CH7") {
    // Turn ON channel 7 - only if no channels are ON
    if (!channel7State) {
      turnOnChannel(7);
      Serial.println("Command: Turn ON channel 7");
      startTimeout();
    } else {
      Serial.println("Command ignored: Channel(s) already ON");
    }
  }
  else if (command == "STATUS") {
    // Print status - always allowed
    Serial.println("Command: Print status");
  }
  else {
    Serial.println("Invalid command. Use: OFF, BOTH, CH6, CH7, STATUS, or number for timeout");
    return;
  }
  
  printStatus();
}

void turnOnChannel(int channel) {
  if (channel == 6) {
    digitalWrite(CHANNEL_6_PIN, HIGH);
    channel6State = true;
  } else if (channel == 7) {
    digitalWrite(CHANNEL_7_PIN, HIGH);
    channel7State = true;
  }
}

void turnOffAllChannels() {
  digitalWrite(CHANNEL_6_PIN, LOW);
  digitalWrite(CHANNEL_7_PIN, LOW);
  channel6State = false;
  channel7State = false;
  timeoutActive = false;
}

bool isNumeric(String str) {
  // Check if string contains only digits, decimal point, or is empty
  if (str.length() == 0) return false;
  
  bool hasDecimal = false;
  for (unsigned int i = 0; i < str.length(); i++) {
    char c = str.charAt(i);
    if (c == '.') {
      if (hasDecimal) return false; // Multiple decimals
      hasDecimal = true;
    } else if (!isDigit(c)) {
      return false; // Non-digit, non-decimal character
    }
  }
  return true;
}



