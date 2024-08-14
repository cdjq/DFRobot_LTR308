# DFRobot_LTR308
- [中文版](./README_CN.md)

The LTR-308ALS-SYM is an integrated low voltage I2C ambient light sensor (ALS) in a single 2x2mm miniature chipled lead-free surface mount package. The ALS provides a linear response over a wide dynamic range, which is well suited to applications under very low 
or bright ambient brightness. The sensor has a programmable interrupt with hysteresis to response to events and that removes the need to poll the sensor for a reading which improves system efficiency. This CMOS design and factory-set one time trimming capability ensure minimal sensor-to-sensor variations for ease of manufacturability to the end customers.

## Table of Contents

* [Summary](#Summary)
* [Installation](#Installation)
* [Methods](#Methods)
* [Compatibility](#Compatibility)
* [History](#History)
* [Credits](#Credits)


## Summary

Obtain ambient light source data, which can be converted to lux according to the raw data obtained.
To set the interrupt, you can set the upper and lower limit of the light source, and set the upper and lower value boundary to trigger several times, the interrupt is triggered.

## Installation

First download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in that folder.

## Methods

```C++

/**
 * @fn begin
 * @brief Initialize the function.
 * @return bool ,Indicates the initialization state.
 */
bool begin(void);

/**
 * @fn setPowerUp
 * @brief Set the Power Up LTR308.
 */
void setPowerUp(void);

/**
 * @fn setPowerDown
 * @brief Set the Power Down LTR308
 */
void setPowerDown(void);

/**
 * @fn getPower
 * @brief Get the Power value
 * @return uint8_t: content of LTR308_CONTR control register
 */
uint8_t getPower(void);

/**
 * @fn setGain
 * @brief Set the Gain of LTR308
 * @param gain: the gain
 * @n If gain = 0, device is set to 1X gain
 * @n If gain = 1, device is set to 3X gain (Sensor default)
 * @n If gain = 2, device is set to 6X gain
 * @n If gain = 3, device is set to 9X gain
 * @n If gain = 4, device is set to 18X gain
 */
void setGain(uint8_t gain);

/**
 * @fn getGain
 * @brief Get the Gain of LTR308
 * @return uint8_t: the control register values
 * @retval If gain = 0, device is set to 1X gain
 * @retval If gain = 1, device is set to 3X gain (Sensor default)
 * @retval If gain = 2, device is set to 6X gain
 * @retval If gain = 3, device is set to 9X gain
 * @retval If gain = 4, device is set to 18X gain
 */
uint8_t getGain(void);

/**
 * @fn setMeasurementRate
 * @brief Set the Measurement Rate and resolution
 * @param measRate: Measurement Rate and resolution
 * @n If measRate.resolution = 0,  20 Bit result, Conversion time = 400ms.
 * @n If measRate.resolution = 1,  19 Bit result, Conversion time = 200ms.
 * @n If measRate.resolution = 2,  18 Bit result, Conversion time = 100ms.(Sensor default)
 * @n If measRate.resolution = 3,  17 Bit result, Conversion time = 50ms.
 * @n If measRate.resolution = 4,  16 Bit result, Conversion time = 25ms.
 * @n -------------------------------------------------------------------------------------------
 * @n If measRate.measurementRate = 0, Measurement Rate will be 25ms.
 * @n If measRate.measurementRate = 1, Measurement Rate will be 50ms.
 * @n If measRate.measurementRate = 2, Measurement Rate will be 100ms.(Sensor default)
 * @n If measRate.measurementRate = 3, Measurement Rate will be 500ms.
 * @n If measRate.measurementRate = 5, Measurement Rate will be 1000ms.
 * @n If measRate.measurementRate = 6, Measurement Rate will be 2000ms.
 * @n If measRate.measurementRate = 7, Measurement Rate will be 2000ms.
 */
void setMeasurementRate(sMeasRate_t measRate);

/**
 * @fn setMeasurementRate
 * @brief Set the Measurement Rate and resolution
 * @param resolution: The measurement time for each ALs cycle
 * @n If resolution = 0,  20 Bit result, Conversion time = 400ms.
 * @n If resolution = 1,  19 Bit result, Conversion time = 200ms.
 * @n If resolution = 2,  18 Bit result, Conversion time = 100ms.(Sensor default)
 * @n If resolution = 3,  17 Bit result, Conversion time = 50ms.
 * @n If resolution = 4,  16 Bit result, Conversion time = 25ms.
 * @param measurementRate: The interval between DATA_REGISTERS update
 * @n If measurementRate = 0, Measurement Rate will be 25ms.
 * @n If measurementRate = 1, Measurement Rate will be 50ms.
 * @n If measurementRate = 2, Measurement Rate will be 100ms.(Sensor default)
 * @n If measurementRate = 3, Measurement Rate will be 500ms.
 * @n If measurementRate = 5, Measurement Rate will be 1000ms.
 * @n If measurementRate = 6, Measurement Rate will be 2000ms.
 * @n If measurementRate = 7, Measurement Rate will be 2000ms.
 */
void setMeasurementRate(uint8_t resolution, uint8_t measurementRate);

/**
 * @fn getMeasurementRate
 * @brief Get the Measurement Rate and resolution
 * @return sMeasRate_t: Measurement Rate and resolution
 * @retval If measRate.resolution = 0,  20 Bit result, Conversion time = 400ms.
 * @retval If measRate.resolution = 1,  19 Bit result, Conversion time = 200ms.
 * @retval If measRate.resolution = 2,  18 Bit result, Conversion time = 100ms.(Sensor default)
 * @retval If measRate.resolution = 3,  17 Bit result, Conversion time = 50ms.
 * @retval If measRate.resolution = 4,  16 Bit result, Conversion time = 25ms.
 * @retval -------------------------------------------------------------------------------------------
 * @retval If measRate.measurementRate = 0, Measurement Rate will be 25ms.
 * @retval If measRate.measurementRate = 1, Measurement Rate will be 50ms.
 * @retval If measRate.measurementRate = 2, Measurement Rate will be 100ms.(Sensor default)
 * @retval If measRate.measurementRate = 3, Measurement Rate will be 500ms.
 * @retval If measRate.measurementRate = 5, Measurement Rate will be 1000ms.
 * @retval If measRate.measurementRate = 6, Measurement Rate will be 2000ms.
 * @retval If measRate.measurementRate = 7, Measurement Rate will be 2000ms.
 */
sMeasRate_t getMeasurementRate(void);

/**
 * @fn getPartID
 * @brief Gets the part number ID and revision ID of the chip
 * @return uint8_t: Default value is 0xB1, part number ID = 0xB, revision ID = 0x1.
 */
uint8_t getPartID(void);

/**
 * @fn getStatus
 * @brief Get the Status of LTR308
 * @return sMainStatus_t: The status information of LTR308.
 * @retval If sMainStatus_t.ponStatus = false(0), power on event (default)
 * @retval If sMainStatus_t.ponStatus = true(1), not specified in datasheet
 * @retval -------------------------------------------------------------------------------------------
 * @retval If sMainStatus_t.intrStatus = false(0), Interrupt is NOT triggered (default)
 * @retval If sMainStatus_t.intrStatus = true(1), Interrupt is triggered and will be cleared after read
 * @retval -------------------------------------------------------------------------------------------
 * @retval If sMainStatus_t.dataStatus = false(0), ALS data is old (Data has been read)
 * @retval If sMainStatus_t.dataStatus = true(1), ALS data is new data (Data has not been read and will be cleared after read)
 */
sMainStatus_t getStatus(void);

/**
 * @fn getData
 * @brief Get the ALS channel data
 * @return uint32_t: ALS data, Default value is 0
 */
uint32_t getData(void);

/**
 * @fn setInterruptControl
 * @brief Set the Interrupt Control of LTR308
 * @param mode: interrupt mode
 * @n If mode = false(0), ALS interrupt disabled (default)
 * @n If mdoe = true(1), ALS interrupt enabled
 */
void setInterruptControl(bool mode);

/**
 * @fn getInterruptControl
 * @brief Get the Interrupt Control of LTR308
 * @return bool: interrupt mode
 * @retval true: ALS interrupt enabled
 * @retval false: ALS interrupt disabled
 */
bool getInterruptControl(void);

/**
 * @fn setIntrPersist
 * @brief Set the Intr Persist of LTR308
 * @param persist: controls the N number of times the measurement data is outside the range defined by upper and lower threshold
 * @n If persist = 0, Every ALS value out of threshold range asserts an interrupt (default)
 * @n If persist = 1, 2 consecutive ALS values out of threshold range assert an interrupt
 * @n If persist = 2, 3 consecutive ALS values out of threshold range assert an interrupt
 * @n If persist = 3, 4 consecutive ALS values out of threshold range assert an interrupt
 * @n If persist = 4, 5 consecutive ALS values out of threshold range assert an interrupt
 * @n If persist = 5, 6 consecutive ALS values out of threshold range assert an interrupt
 * @n If persist = 6, 7 consecutive ALS values out of threshold range assert an interrupt
 * @n If persist = 7, 8 consecutive ALS values out of threshold range assert an interrupt
 * @n If persist = 8, 9 consecutive ALS values out of threshold range assert an interrupt
 * @n If persist = 9, 10 consecutive ALS values out of threshold range assert an interrupt
 * @n If persist = 10, 11 consecutive ALS values out of threshold range assert an interrupt
 * @n If persist = 11, 12 consecutive ALS values out of threshold range assert an interrupt
 * @n If persist = 12, 13 consecutive ALS values out of threshold range assert an interrupt
 * @n If persist = 13, 14 consecutive ALS values out of threshold range assert an interrupt
 * @n If persist = 14, 15 consecutive ALS values out of threshold range assert an interrupt
 * @n If persist = 15, 16 consecutive ALS values out of threshold range assert an interrupt
 */
void setIntrPersist(uint8_t persist);

/**
 * @fn getIntrPersist
 * @brief Get the Intr Persist of LTR308
 * @return uint8_t: controls the N number of times the measurement data is outside the range defined by upper and lower threshold
 * @retval If persist = 0, Every ALS value out of threshold range asserts an interrupt (default)
 * @retval If persist = 1, 2 consecutive ALS values out of threshold range assert an interrupt
 * @retval If persist = 2, 3 consecutive ALS values out of threshold range assert an interrupt
 * @retval If persist = 3, 4 consecutive ALS values out of threshold range assert an interrupt
 * @retval If persist = 4, 5 consecutive ALS values out of threshold range assert an interrupt
 * @retval If persist = 5, 6 consecutive ALS values out of threshold range assert an interrupt
 * @retval If persist = 6, 7 consecutive ALS values out of threshold range assert an interrupt
 * @retval If persist = 7, 8 consecutive ALS values out of threshold range assert an interrupt
 * @retval If persist = 8, 9 consecutive ALS values out of threshold range assert an interrupt
 * @retval If persist = 9, 10 consecutive ALS values out of threshold range assert an interrupt
 * @retval If persist = 10, 11 consecutive ALS values out of threshold range assert an interrupt
 * @retval If persist = 11, 12 consecutive ALS values out of threshold range assert an interrupt
 * @retval If persist = 12, 13 consecutive ALS values out of threshold range assert an interrupt
 * @retval If persist = 13, 14 consecutive ALS values out of threshold range assert an interrupt
 * @retval If persist = 14, 15 consecutive ALS values out of threshold range assert an interrupt
 * @retval If persist = 15, 16 consecutive ALS values out of threshold range assert an interrupt
 */
uint8_t getIntrPersist(void);

/**
 * @fn setThreshold
 * @brief Sets the upper limit and lower limit of the threshold
 * @param thres: upperLimit and lowerLimit
 * @n thres.upperLimit (up to 20-bits) (default 0x0FFFFF)
 * @n thres.lowerLimit (up to 20-bits) (default 0x000000)
 */
void setThreshold(sThres_t thres);

/**
 * @fn setThreshold
 * @brief Sets the upper limit and lower limit of the threshold
 * @param upperLimit: (up to 20-bits) (default 0x0FFFFF)
 * @param lowerLimit: (up to 20-bits) (default 0x000000)
 */
void setThreshold(uint32_t upperLimit, uint32_t lowerLimit);

/**
 * @fn getThreshold
 * @brief Gets the upper limit and lower limit of the threshold
 * @return sThres_t: upperLimit and lowerLimit
 * @retval sThres_t.upperLimit (up to 20-bits) (default 0x0FFFFF)
 * @retval sThres_t.lowerLimit (up to 20-bits) (default 0x000000)
 */
sThres_t getThreshold();

/**
 * @fn getLux
 * @brief Convert raw data to lux  (Lux = (0.6 * ALSDATA) / (GAIN * INT))
 * @param gain: The gain of this sensor
 * @param resolution: The resolution of this sensor
 * @param alsData: The ALS Data of this sensor
 * @return double: The converted lux value
 */
double getLux(uint8_t gain, uint8_t resolution, uint32_t alsData);

/**
 * @fn getLux
 * @brief Convert raw data to lux   (Lux = (0.6 * ALSDATA) / (GAIN * INT))
 * @param alsData: The ALS Data of this sensor
 * @return double: The converted lux value
 */
double getLux(uint32_t alsData);

```

## Compatibility

MCU                | Work Well    |   Work Wrong    | Untested    | Remarks
------------------ | :----------: | :-------------: | :---------: | :----:
Arduino Uno        |              |                 |      √      |
Arduino MEGA2560   |              |                 |      √      |
Arduino Leonardo   |              |                 |      √      |
ESP8266            |              |                 |      √      |
ESP32              |      √       |                 |             |
FireBeetle-M0      |              |                 |      √      |
Micro:bit          |              |                 |      √      |

## History

- 2024/07/30 - V0.1 version

## Credits

Written by thdyyl(yuanlong.yu@dfrobot.com), 2024. (Welcome to our website)