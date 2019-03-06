/*!
 2 * @file HeartRateMonitor.ino
 3 * @brief HeartRateMonitor.ino  Sampling and ECG output 
 4 *
 5 *  Real-time sampling and ECG output
 6 * 
 7 * @author linfeng(490289303@qq.com)
 8 * @version  V1.0
 9 * @date  2016-4-5
10 */
const int heartPin = A1;
void setup() {
  Serial.begin(115200);
}
void loop() { 
  int heartValue = analogRead(heartPin);
  Serial.println(heartValue);
  delay(5);
}
