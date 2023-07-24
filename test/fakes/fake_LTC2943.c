#include "fake_LTC2943.h"
#include "ChipControl.h"

RegisterMapValues register_map_values;

bool LTC2943_Initialise() { return LTC_STATUS_OK; }
bool LTC2943_Read(uint8_t address, uint8_t *dest, uint8_t dataSize) {

	// If 0 Data was requested, error out:
	if (dataSize == 0) {
		return LTC_STATUS_ERROR_PARAMS;
	}

	if (address == register_map.Control) {
		*dest = (uint8_t)register_map_values.control_register;
	}

	if (address == register_map.Status) {
		*dest = (uint8_t)register_map_values.status_register;
	}

	return LTC_STATUS_OK;
}
bool LTC2943_Write(uint8_t address, uint8_t *src, uint8_t dataSize) {

	// If 0 Data was requested, error out:
	if (dataSize == 0) {
		return LTC_STATUS_ERROR_PARAMS;
	}

	if (address == register_map.Control) {
		register_map_values.control_register = *src;
	}
	return LTC_STATUS_OK;
}