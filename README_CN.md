# DFRobot_LTR308
- [English Version](./README.md)

LTR-308ALS-SYM是一款集成的低压I2C环境光传感器(ALS)，封装在一个2x2mm的微型无铅表面贴装封装中。ALS在宽动态范围内提供线性响应，非常适合非常低或明亮的环境亮度下的应用。传感器具有可编程中断，具有响应事件的滞后，从而消除了轮询传感器读取的需要，从而提高了系统效率。这种CMOS设计和工厂设置的一次性修剪能力确保最小的传感器到传感器的变化，便于最终客户的可制造性。

## 目录

* [概述](#概述)
* [库安装](#库安装)
* [方法](#方法)
* [兼容性](#兼容性)
* [历史](#历史)
* [创作者](#创作者)

## 概述

获取环境光源数据，可根据获取的原始数据转为lux。
设置中断，可以设置光源的上下限值，设置触发几次上下值边界时，中断触发。

## 库安装

首先下载库文件，将其粘贴到\Arduino\libraries目录中，然后打开examples文件夹并在该文件夹中运行演示。

## 方法
```C++

/**
 * @fn begin
 * @brief 初始化传感器
 * @return bool ,返回初始化状态
 */
bool begin(void);

/**
 * @fn setPowerUp
 * @brief 设置LTR308上电
 */
void setPowerUp(void);

/**
 * @fn setPowerDown
 * @brief 设置LTR308下电
 */
void setPowerDown(void);

/**
 * @fn getPower
 * @brief 获取LTR308的操作模式
 * @return uint8_t: 获取控制寄存器的值
 */
uint8_t getPower(void);

/**
 * @fn setGain
 * @brief 设置LTR308的增益
 * @param gain: the gain
 * @n 如果 gain = 0, 则设备的增益效果为1X增益
 * @n 如果 gain = 1, 则设备的增益效果为3X增益 (传感器默认值)
 * @n 如果 gain = 2, 则设备的增益效果为6X增益
 * @n 如果 gain = 3, 则设备的增益效果为9X增益
 * @n 如果 gain = 4, 则设备的增益效果为18X增益
 */
void setGain(uint8_t gain);

/**
 * @fn getGain
 * @brief 获取LTR308的增益
 * @return uint8_t: 增益值
 * @retval 如果 gain = 0, 则设备的增益效果为1X增益
 * @retval 如果 gain = 1, 则设备的增益效果为3X增益 (传感器默认值)
 * @retval 如果 gain = 2, 则设备的增益效果为6X增益
 * @retval 如果 gain = 3, 则设备的增益效果为9X增益
 * @retval 如果 gain = 4, 则设备的增益效果为18X增益
 */
uint8_t getGain(void);

/**
 * @fn setMeasurementRate
 * @brief 设置测量速率和转化时间
 * @param measRate: 测量速率和转化时间
 * @n 如果 measRate.resolution = 0,  20位的结果, 转化时间 400ms.
 * @n 如果 measRate.resolution = 1,  19位的结果, 转化时间 200ms.
 * @n 如果 measRate.resolution = 2,  18位的结果, 转化时间 100ms.(传感器默认值)
 * @n 如果 measRate.resolution = 3,  17位的结果, 转化时间 50ms.
 * @n 如果 measRate.resolution = 4,  16位的结果, 转化时间 25ms.
 * @n -------------------------------------------------------------------------------------------
 * @n 如果 measRate.measurementRate = 0, 测量速率为 25ms.
 * @n 如果 measRate.measurementRate = 1, 测量速率为 50ms.
 * @n 如果 measRate.measurementRate = 2, 测量速率为 100ms.(传感器默认值)
 * @n 如果 measRate.measurementRate = 3, 测量速率为 500ms.
 * @n 如果 measRate.measurementRate = 5, 测量速率为 1000ms.
 * @n 如果 measRate.measurementRate = 6, 测量速率为 2000ms.
 * @n 如果 measRate.measurementRate = 7, 测量速率为 2000ms.
 */
void setMeasurementRate(sMeasRate_t measRate);

/**
 * @fn setMeasurementRate
 * @brief 设置测量速率和转化时间
 * @param resolution: 每个ALs周期的测量时间
 * @n 如果 resolution = 0,  20位的结果, 转化时间 400ms.
 * @n 如果 resolution = 1,  19位的结果, 转化时间 200ms.
 * @n 如果 resolution = 2,  18位的结果, 转化时间 100ms.(传感器默认值)
 * @n 如果 resolution = 3,  17位的结果, 转化时间 50ms.
 * @n 如果 resolution = 4,  16位的结果, 转化时间 25ms.
 * @param measurementRate: DATA_REGISTERS更新之间的间隔
 * @n 如果 measurementRate = 0, 测量速率为 25ms.
 * @n 如果 measurementRate = 1, 测量速率为 50ms.
 * @n 如果 measurementRate = 2, 测量速率为 100ms.(传感器默认值)
 * @n 如果 measurementRate = 3, 测量速率为 500ms.
 * @n 如果 measurementRate = 5, 测量速率为 1000ms.
 * @n 如果 measurementRate = 6, 测量速率为 2000ms.
 * @n 如果 measurementRate = 7, 测量速率为 2000ms.
 */
void setMeasurementRate(uint8_t resolution, uint8_t measurementRate);

/**
 * @fn getMeasurementRate
 * @brief 获取测量速率和转化时间
 * @return sMeasRate_t: 测量速率和转化时间
 * @retval 如果 resolution = 0,  20位的结果, 转化时间 400ms.
 * @retval 如果 resolution = 1,  19位的结果, 转化时间 200ms.
 * @retval 如果 resolution = 2,  18位的结果, 转化时间 100ms.(传感器默认值)
 * @retval 如果 resolution = 3,  17位的结果, 转化时间 50ms.
 * @retval 如果 resolution = 4,  16位的结果, 转化时间 25ms.
 * @retval -------------------------------------------------------------------------------------------
 * @retval 如果 measRate.measurementRate = 0, 测量速率为 25ms.
 * @retval 如果 measRate.measurementRate = 1, 测量速率为 50ms.
 * @retval 如果 measRate.measurementRate = 2, 测量速率为 100ms.(传感器默认值)
 * @retval 如果 measRate.measurementRate = 3, 测量速率为 500ms.
 * @retval 如果 measRate.measurementRate = 5, 测量速率为 1000ms.
 * @retval 如果 measRate.measurementRate = 6, 测量速率为 2000ms.
 * @retval 如果 measRate.measurementRate = 7, 测量速率为 2000ms.
 */
sMeasRate_t getMeasurementRate(void);

/**
 * @fn getPartID
 * @brief 获取芯片的部件号ID和版本ID
 * @return uint8_t: 默认值为0xB1，部件号ID = 0xB，版本号ID = 0x1。
 */
uint8_t getPartID(void);

/**
 * @fn getStatus
 * @brief 获取LTR308的状态
 * @return sMainStatus_t: 返回LTR308的状态信息
 * @retval 如果sMainStatus_t.ponStatus = false(0)，上电事件(默认)
 * @retval 如果sMainStatus_t.ponStatus = true(1)，未在数据表中指定
 * @retval -------------------------------------------------------------------------------------------
 * @retval 如果sMainStatus_t.intrStatus = false(0)，则不触发中断(默认)。
 * @retval 如果sMainStatus_t.intrStatus = true(1)，则触发Interrupt，读取后清除
 * @retval -------------------------------------------------------------------------------------------
 * @retval 如果sMainStatus_t。dataStatus = false(0)， ALS数据是旧的(数据已被读取)
 * @retval 如果sMainStatus_t。dataStatus = true(1)， ALS数据为新数据(数据未被读取，读取后将被清除)
 */
sMainStatus_t getStatus(void);

/**
 * @fn getData
 * @brief 获取ALS通道数据
 * @return uint32_t: ALS数据，默认值为0
 */
uint32_t getData(void);

/**
 * @fn setInterruptControl
 * @brief 设置LTR308的中断控制
 * @param mode: 中断模式
 * @n 如果mode = false(0)， ALS中断被禁用(默认)
 * @n 如果mdoe = true(1)， ALS中断启用
 */
void setInterruptControl(bool mode);

/**
 * @fn getInterruptControl
 * @brief 获得LTR308的中断控制
 * @return bool: 中断模式
 * @retval true: ALS中断启用
 * @retval false: ALS中断禁用
 */
bool getInterruptControl(void);

/**
 * @fn setIntrPersist
 * @brief 设置LTR308的中断持久化
 * @param persist: 控制测量数据超出上下阈值范围的N次
 * @n 如果persist = 0，每个超出阈值范围的ALS值断言一个中断(默认)
 * @n 如果persist = 1，则连续2个超出阈值范围的ALS值断言中断
 * @n 如果persist = 2，则连续3个超出阈值范围的ALS值断言中断
 * @n 如果persist = 3，则连续4个超出阈值范围的ALS值断言中断
 * @n 如果persist = 4，则连续5个超出阈值范围的ALS值断言中断
 * @n 如果persist = 5，则连续6个超出阈值范围的ALS值断言中断
 * @n 如果persist = 6，则连续7个超出阈值范围的ALS值断言中断
 * @n 如果persist = 7，则连续8个超出阈值范围的ALS值断言中断
 * @n 如果persist = 8，则连续9个超出阈值范围的ALS值断言中断
 * @n 如果persist = 9，则连续10个超出阈值范围的ALS值断言中断
 * @n 如果persist = 10，则连续11个超出阈值范围的ALS值断言中断
 * @n 如果persist = 11，则连续12个超出阈值范围的ALS值断言中断
 * @n 如果persist = 12，则连续13个超出阈值范围的ALS值断言中断
 * @n 如果persist = 13，则连续14个超出阈值范围的ALS值断言中断
 * @n 如果persist = 14，则连续15个超出阈值范围的ALS值断言中断
 * @n 如果persist = 15，则连续16个超出阈值范围的ALS值断言中断
 */
void setIntrPersist(uint8_t persist);

/**
 * @fn getIntrPersist
 * @brief 获取LTR308的中断持久化
 * @return uint8_t: 控制测量数据超出上下阈值范围的N次
 * @retval 如果persist = 0，每个超出阈值范围的ALS值断言一个中断(默认)
 * @retval 如果persist = 1，则连续2个超出阈值范围的ALS值断言中断
 * @retval 如果persist = 2，则连续3个超出阈值范围的ALS值断言中断
 * @retval 如果persist = 3，则连续4个超出阈值范围的ALS值断言中断
 * @retval 如果persist = 4，则连续5个超出阈值范围的ALS值断言中断
 * @retval 如果persist = 5，则连续6个超出阈值范围的ALS值断言中断
 * @retval 如果persist = 6，则连续7个超出阈值范围的ALS值断言中断
 * @retval 如果persist = 7，则连续8个超出阈值范围的ALS值断言中断
 * @retval 如果persist = 8，则连续9个超出阈值范围的ALS值断言中断
 * @retval 如果persist = 9，则连续10个超出阈值范围的ALS值断言中断
 * @retval 如果persist = 10，则连续11个超出阈值范围的ALS值断言中断
 * @retval 如果persist = 11，则连续12个超出阈值范围的ALS值断言中断
 * @retval 如果persist = 12，则连续13个超出阈值范围的ALS值断言中断
 * @retval 如果persist = 13，则连续14个超出阈值范围的ALS值断言中断
 * @retval 如果persist = 14，则连续15个超出阈值范围的ALS值断言中断
 * @retval 如果persist = 15，则连续16个超出阈值范围的ALS值断言中断
 */
uint8_t getIntrPersist(void);

/**
 * @fn setThreshold
 * @brief 设置阈值的上下限
 * @param thres: 上限和下限
 * @n thres.upperLimit (最高20位) (默认值 0x0FFFFF)
 * @n thres.lowerLimit (最高20位) (默认值 0x000000)
 */
void setThreshold(sThres_t thres);

/**
 * @fn setThreshold
 * @brief 设置阈值的上下限
 * @param upperLimit: (最高20位) (默认值 0x0FFFFF)
 * @param lowerLimit: (最高20位) (默认值 0x000000)
 */
void setThreshold(uint32_t upperLimit, uint32_t lowerLimit);

/**
 * @fn getThreshold
 * @brief 获取阈值的上下限
 * @return sThres_t: 上限和下限
 * @retval sThres_t.upperLimit (最高20位) (默认值 0x0FFFFF)
 * @retval sThres_t.lowerLimit (最高20位) (默认值 0x000000)
 */
sThres_t getThreshold();

/**
 * @fn getLux
 * @brief 原始数据转化为lux  (Lux = (0.6 * ALSDATA) / (GAIN * INT))
 * @param gain: 传感器的增益
 * @param resolution: 该传感器的分辨率
 * @param alsData: 该传感器的ALS数据
 * @return double: 转化后的lux值
 */
double getLux(uint8_t gain, uint8_t resolution, uint32_t alsData);

/**
 * @fn getLux
 * @brief 原始数据转化为lux   (Lux = (0.6 * ALSDATA) / (GAIN * INT))
 * @param alsData: 该传感器的ALS数据
 * @return double: 转化后的lux值
 */
double getLux(uint32_t alsData);

```

## 兼容性

MCU                | Work Well    |   Work Wrong    | Untested    | Remarks
------------------ | :----------: | :-------------: | :---------: | :----:
Arduino Uno        |              |                 |      √      |
Arduino MEGA2560   |              |                 |      √      |
Arduino Leonardo   |              |                 |      √      |
ESP8266            |              |                 |      √      |
ESP32              |      √       |                 |             |
FireBeetle-M0      |              |                 |      √      |
Micro:bit          |              |                 |      √      |

## 历史

- 2024/07/30 - V0.1 版本

## 创作者

Written by thdyyl(yuanlong.yu@dfrobot.com), 2024. (Welcome to our website)
