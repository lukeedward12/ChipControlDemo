#include "fake_LTC2943.h"
#include "ChipControl.h"

uint8_t status_register;
uint8_t control_register;

bool LTC2943_Initialise() { return LTC_STATUS_OK; }
bool LTC2943_Read(uint8_t address, uint8_t *dest, uint8_t dataSize) {

  if (address = register_map.Control) {
    *dest = control_register;
  }

  return LTC_STATUS_OK;
}
bool LTC2943_Write(uint8_t address, uint8_t *src, uint8_t dataSize) {
  return LTC_STATUS_OK;
}