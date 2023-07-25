#include "LTC2943.h"

bool LTC2943_Initialise() { return LTC_STATUS_OK; }
bool LTC2943_Read(uint8_t address, uint8_t *dest, uint8_t dataSize) {
	(void)address;
	(void)dest;
	(void)dataSize;
	return LTC_STATUS_OK;
}
bool LTC2943_Write(uint8_t address, uint8_t *src, uint8_t dataSize) {
	(void)address;
	(void)src;
	(void)dataSize;
	return LTC_STATUS_OK;
}