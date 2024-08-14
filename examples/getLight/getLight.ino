/**
 * @file getLight.ino
 * @brief Get the light source value and lux value of the LTR308
 * @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author [thdyyl](yuanlong.yu@dfrobot.com)
 * @version V0.1
 * @date 2024-07-25
 * @url https://github.com/DFRobot/DFRobot_LTR308
 */

#include <DFRobot_LTR308.h>

DFRobot_LTR308 light;
// DFRobot_LTR308 light(&Wire);
void setup(){
  Serial.begin(115200);
  while(!light.begin()){
    Serial.println("初始化失败!");
    delay(1000);
  }
  Serial.println("初始化成功!");
  
  // Serial.println("设置增益...");
  // light.setGain(0);
  // Serial.print("增益设置为0X");
  // Serial.println(light.getGain(), HEX);

  // Serial.println("设置测量速率...");
  // light.setMeasurementRate(0, 3);
  // DFRobot_LTR308::sMeasRate_t measRate;
  // measRate = light.getMeasurementRate();
  // Serial.print("转化时间设置为0X");
  // Serial.println(measRate.resolution, HEX);
  // Serial.print("测量速率设置为0X");
  // Serial.println(measRate.measurementRate, HEX);
}

void loop(){
  uint32_t data = light.getData();
  Serial.println();
  Serial.print("Original Data: ");
  Serial.println(data);
  Serial.print("Lux Data: ");
  Serial.println(light.getLux(data));

  delay(500);
}