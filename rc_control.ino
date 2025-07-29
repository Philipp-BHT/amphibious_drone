#define CH1 2  // Channel corresponds to pin number on board
#define CH2 4  


class ChannelReader {
  public:
    ChannelReader() {}
    float readChannel(int channelInput, float minLimit = -1.0, float maxLimit = 1.0, float defaultValue = 0.0) {
      int ch = pulseIn(channelInput, HIGH, 30000);
      if (ch < 100) return defaultValue; 
      return map(ch, 1000, 2000, minLimit * 100, maxLimit * 100) / 100.0; 
    }

    bool readSwitch(int channelInput, bool defaultValue = false) {
      int intDefaultValue = (defaultValue) ? 100 : 0;
      float ch = readChannel(channelInput, 0, 100, intDefaultValue);
      return (ch > 50); 
    }
};

float calculate_motor_1_value(float ch1Value, float ch2Value) {
  // ch2Value is y, ch1Value is x
  float m_r = ch2Value - ch1Value;
  return max(-1.0, min(1.0, m_r));
}

float calculate_motor_2_value(float ch1Value, float ch2Value) {
  // ch2Value is y, ch1Value is x
  float m_l = ch2Value + ch1Value;
  return max(-1.0, min(1.0, m_l));
}

void printStatus(float ch1Value, float ch2Value, float m_r, float m_l) {
  Serial.print("Channel 1: ");
  Serial.print(ch1Value);
  Serial.print(", Channel 2: ");
  Serial.print(ch2Value);
  
  Serial.print(", M_r: ");
  Serial.print(m_r);
  Serial.print(", M_l: ");
  Serial.println(m_l);
}


ChannelReader channelReader;

void setup() {
  Serial.begin(115200);
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
}

float ch1Value, ch2Value;
float m_r, m_l;

void loop() {
  ch1Value = channelReader.readChannel(CH1, -1.0, 1.0, 0.0);
  ch2Value = channelReader.readChannel(CH2, -1.0, 1.0, 0.0);
  
  m_r = calculate_motor_1_value(ch1Value, ch2Value);
  m_l = calculate_motor_2_value(ch1Value, ch2Value);

  printStatus(ch1Value, ch2Value, m_r, m_l);
  
  delay(500);
}
