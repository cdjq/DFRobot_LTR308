/**
 * @file DFRobot_LTR308.cpp
 * @brief Defines the basic structure of the class DFRobot_LTR308, basic implementation
 * @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author [thdyyl](yuanlong.yu@dfrobot.com)
 * @version V0.1
 * @date 2024-07-25
 * @url https://github.com/DFRobot/DFRobot_LTR308
 */

#include "DFRobot_LTR308.h"



DFRobot_LTR308::DFRobot_LTR308(TwoWire *pWire)
{
  _deviceAddr = LTR308_ADDR;
  _pWire = pWire;
  _gain = 0x01;
  _resolution = 0x02;
  _measurementRate = 0x02;
}

DFRobot_LTR308::~DFRobot_LTR308()
{
}

bool DFRobot_LTR308::begin(void)
{
  _pWire->begin();
  _pWire->setClock(400000);
  uint8_t id = 0x00;
  delay(50);
  if (!readReg(LTR308_REG_PART_ID, &id, 1)){
    DBG("bus data access error");
    return false;
  }
  if (id != LTR308_PART_V_ID){
    DBG("real sensor id=");
    DBG(id);
    return false;
  }
  DBG("real sensor id=0x");
  DBG(id);
  
  setPowerUp();
  delay(10);
  setGain(_gain);
  setMeasurementRate(_resolution, _measurementRate);

  return true;
}

void DFRobot_LTR308::setPowerUp(void)
{
  uint8_t data = 0x02;
  writeReg(LTR308_REG_CONTR, &data, 1);
}

void DFRobot_LTR308::setPowerDown(void)
{
  uint8_t data = 0x00;
  writeReg(LTR308_REG_CONTR, &data, 1);
}

uint8_t DFRobot_LTR308::getPower(void)
{
  uint8_t data = 0x00;
  readReg(LTR308_REG_CONTR, &data, 1);
  return data;
}

void DFRobot_LTR308::setGain(uint8_t gain)
{
  if(gain > 4){
    gain = 0x01;
  }
  writeReg(LTR308_REG_ALS_GAIN, &gain, 1);
  _gain = gain;
}

uint8_t DFRobot_LTR308::getGain(void)
{
  uint8_t gain = 0x00;
  readReg(LTR308_REG_ALS_GAIN, &gain, 1);
  return gain;
}

void DFRobot_LTR308::setMeasurementRate(sMeasRate_t measRate)
{
  uint8_t data = 0x00;
  if (measRate.resolution >= 5){
    measRate.resolution = 4;
  }
  if (measRate.measurementRate >= 8 || measRate.measurementRate == 4){
    measRate.measurementRate = 7;
  }
  data = (measRate.resolution << 4) | measRate.measurementRate;
  writeReg(LTR308_REG_MEAS_RATE, &data, 1);
  _resolution = measRate.resolution;
  _measurementRate = measRate.resolution;
}

void DFRobot_LTR308::setMeasurementRate(uint8_t resolution, uint8_t measurementRate){
  sMeasRate_t measRate = {resolution, measurementRate};
  setMeasurementRate(measRate);
}

DFRobot_LTR308::sMeasRate_t DFRobot_LTR308::getMeasurementRate(void)
{
  uint8_t data = 0x00;
  sMeasRate_t measRate;
  readReg(LTR308_REG_MEAS_RATE, &data, 1);
  measRate.resolution = (data & 0x70) >> 4;
  measRate.measurementRate = data & 0x07;
  return measRate;
}


uint8_t DFRobot_LTR308::getPartID(void)
{
  uint8_t partID;
  readReg(LTR308_REG_PART_ID, &partID, 1);
  return partID;
}

DFRobot_LTR308::sMainStatus_t DFRobot_LTR308::getStatus(void)
{
  uint8_t data = 0x00;
  readReg(LTR308_REG_STATUS, &data, 1);
  sMainStatus_t mainStatus;
  mainStatus.ponStatus = (data & 0x20) ? true : false;
  mainStatus.intrStatus = (data & 0x10) ? true : false;
  mainStatus.dataStatus = (data & 0x08) ? true : false;
  return mainStatus;
}

uint32_t DFRobot_LTR308::getData(void)
{
  uint8_t data[3] = {0x00};
  readReg(LTR308_REG_DATA_0, data, 3);
  return ((uint32_t)(data[2] & 0x0F) << 16) | ((uint32_t)data[1] << 8) | (uint32_t)data[0];
}

void DFRobot_LTR308::setInterruptControl(bool mode)
{
  uint8_t data = 0x00;
  data = 0x10 | (mode << 2);
  writeReg(LTR308_REG_INTERRUPT, &data, 1);
}

bool DFRobot_LTR308::getInterruptControl(void)
{
  uint8_t data = 0x00;
  readReg(LTR308_REG_INTERRUPT, &data, 1);
  return (data & 0x04) ? true : false;
}

void DFRobot_LTR308::setIntrPersist(uint8_t persist)
{
  uint8_t data = 0x00;
  if (persist >= 16){
    persist = 15;
  }
  data = persist << 4;
  writeReg(LTR308_REG_INTR_PERS, &data, 1);
}

uint8_t DFRobot_LTR308::getIntrPersist(void)
{
  uint8_t data = 0x00;
  readReg(LTR308_REG_INTR_PERS, &data, 1);
  return data >> 4;
}

void DFRobot_LTR308::setThreshold(sThres_t thres)
{
  uint8_t data[6] = {0x00};
  data[0] = thres.upperLimit & 0xFF;
  data[1] = (thres.upperLimit >> 8) & 0xFF;
  data[2] = (thres.upperLimit >> 16) & 0x0F;

  data[3] = thres.lowerLimit & 0xFF;
  data[4] = (thres.lowerLimit >> 8) & 0xFF;
  data[5] = (thres.lowerLimit >> 16) & 0x0F;
  writeReg(LTR308_REG_THRES_UP_0, data, 6);
}

void DFRobot_LTR308::setThreshold(uint32_t upperLimit, uint32_t lowerLimit){
  sThres_t thres = {upperLimit, lowerLimit};
  setThreshold(thres);
}

DFRobot_LTR308::sThres_t DFRobot_LTR308::getThreshold(void)
{
  uint8_t data[6] = {0x00};
  sThres_t thres;
  readReg(LTR308_REG_THRES_UP_0, data, 6);
  thres.upperLimit = ((uint32_t)(data[2] & 0x0F) << 16) | ((uint32_t)data[1] << 8) | (uint32_t)data[0];
  thres.lowerLimit = ((uint32_t)(data[5] & 0x0F) << 16) | ((uint32_t)data[4] << 8) | (uint32_t)data[3];
  return thres;
}

double DFRobot_LTR308::getLux(uint8_t gain, uint8_t resolution, uint32_t alsData)
{
  double lux = 0.0;
  lux = alsData * 0.6;
  switch (gain){
  case 0:
    lux = lux;
    break;
  case 0x01:
    lux = lux / 3;
    break;
  case 0x02:
    lux = lux / 6;
    break;
  case 0x03:
    lux = lux / 9;
    break;
  case 0x04:
    lux = lux / 18;
    break;
  default:
    lux = 0.0;
    break;
  }

  switch (resolution){
  case 0x00:
    lux = lux / 4;
    break;
  case 0x01:
    lux = lux / 2;
    break;
  case 0x02:
    lux = lux;
    break;
  case 0x03:
    lux = lux * 2;
    break;
  case 0x04:
    lux = lux * 4;
    break;
  default:
    lux = 0.0;
    break;
  }
   return lux;
}

double DFRobot_LTR308::getLux(uint32_t alsData){
  return getLux(_gain, _resolution, alsData);
}

bool DFRobot_LTR308::readReg(uint8_t reg, void *pBuf, size_t size)
{
  if (pBuf == NULL){
    DBG("pBuf ERROR!! : null pointer");
    return false;
  }
  uint8_t *_pBuf = (uint8_t *)pBuf;
  _pWire->beginTransmission(_deviceAddr);
  _pWire->write(reg);
  if (_pWire->endTransmission() != 0){
    return false;
  }
  _pWire->requestFrom(_deviceAddr, (uint8_t)size);
  size_t i = 0;
  while (_pWire->available()){
    _pBuf[i++] = _pWire->read();
  }
  return true;
}

bool DFRobot_LTR308::writeReg(uint8_t reg, void *pBuf, size_t size)
{
  if (pBuf == NULL){
    DBG("pBuf ERROR!! : null pointer");
    return false;
  }
  uint8_t *_pBuf = (uint8_t *)pBuf;

  _pWire->beginTransmission(_deviceAddr);
  _pWire->write(reg);
  for (size_t i = 0; i < size; ++i){
    _pWire->write(_pBuf[i]);
  }
  _pWire->endTransmission();
  return true;
}