/**
   @file interrupt.ino
   @brief Description When the threshold was exceeded for n consecutive times, the interruption was triggered.
   @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
   @license The MIT License (MIT)
   @author [thdyyl](yuanlong.yu@dfrobot.com)
   @version V0.1
   @date 2024-07-25
   @url https://github.com/DFRobot/DFRobot_LTR308
*/

#include <DFRobot_LTR308.h>

DFRobot_LTR308 light;
// DFRobot_LTR308 light(&Wire);

void setup()
{
  Serial.begin(115200);
  while (!light.begin())
  {
    Serial.println("初始化失败!");
    delay(1000);
  }
  Serial.println("初始化成功!");

  Serial.print("PART_ID:0X");
  Serial.println(light.getPartID(), HEX);

  Serial.print("控制: 0X");
  Serial.println(light.getPower(), HEX);

  Serial.println("设置增益...");
  light.setGain(0);
  Serial.print("增益设置为0X");
  Serial.println(light.getGain(), HEX);

  Serial.println("设置测量速率...");
  // DFRobot_LTR308::sMeasRate_t measRateData = {0, 5};
  // light.setMeasurementRate(measRateData);

  light.setMeasurementRate(0, 5);
  DFRobot_LTR308::sMeasRate_t measRate;
  measRate = light.getMeasurementRate();
  Serial.print("转化时间设置为0X");
  Serial.println(measRate.resolution, HEX);
  Serial.print("测量速率设置为0X");
  Serial.println(measRate.measurementRate, HEX);

  Serial.println("设置阈值的上下限...");
  // DFRobot_LTR308::sThres_t thresHold = {1000, 50};
  // light.setThreshold(thresHold);

  light.setThreshold(1000, 50);
  DFRobot_LTR308::sThres_t thres = light.getThreshold();
  Serial.print("设置的上限: ");
  Serial.println(thres.upperLimit);
  Serial.print("设置的下限: ");
  Serial.println(thres.lowerLimit);

  Serial.println("设置中断持久化...");
  light.setIntrPersist(5);
  Serial.print("中断化持久化设置为0X");
  Serial.println(light.getIntrPersist());

  Serial.println("开启中断...");
  light.setInterruptControl(true);
  Serial.print("中断是否开启: ");
  Serial.println(light.getInterruptControl());
}

void loop()
{
  DFRobot_LTR308::sMainStatus_t mainStatus = light.getStatus();
  if (mainStatus.intrStatus){
    Serial.println("中断触发...");
    light.setPowerDown();
  }
  uint32_t data = light.getData();
  if (mainStatus.dataStatus){
    Serial.print("Original Data: ");
    Serial.println(data);
    Serial.print("Lux Data: ");
    Serial.println(light.getLux(data));
  }
  delay(1000);
}