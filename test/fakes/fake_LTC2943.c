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

	if (address == register_map.Charge_Threshold_High_LSB) {
		register_map_values.charge_threshold_high_lsb = *src;
	}

	if (address == register_map.Charge_Threshold_High_MSB) {
		register_map_values.charge_threshold_high_msb = *src;
	}

	if (address == register_map.Charge_Threshold_Low_LSB) {
		register_map_values.charge_threshold_low_lsb = *src;
	}

	if (address == register_map.Charge_Threshold_Low_MSB) {
		register_map_values.charge_threshold_low_msb = *src;
	}
	return LTC_STATUS_OK;
}