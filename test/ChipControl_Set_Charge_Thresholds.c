#include "ChipControl.h"
#include "fake_LTC2943.h"
#include <stdio.h>

enum ctest_return_status { SUCCESS = 0, FAILURE = 1 } ctest_return_status;

#define VALID_MAX 2000
#define VALID_MIN 100
#define INVALID_MAX 5000
#define INVALID_MIN 3000

bool within_one_percent(uint32_t a, uint32_t b);
bool within_one_percent(uint32_t a, uint32_t b) {
	uint32_t diff = a > b ? a - b : b - a;
	uint32_t one_percent = (uint32_t)((a > b ? a : b) * 0.01);
	return diff <= one_percent;
}

uint8_t Set_Charge_Thresholds_VALID();
uint8_t Set_Charge_Thresholds_VALID() {

	SetChargeThresholdInput input = {.max_threshold = VALID_MAX,
					 .min_threshold = VALID_MIN};

	// Unit Under Test
	uint8_t api_status = ChipControl_Set_Charge_Thresholds(&input);

	// Reconstruct Registers into Engineering Units
	uint16_t max_threshold =
	    q_LSb * (float)((register_map_values.charge_threshold_high_msb
			     << MSB_16BIT_POSITION) |
			    register_map_values.charge_threshold_high_lsb);

	if (within_one_percent(max_threshold, VALID_MAX) &&
	    api_status == CC_STATUS_OK) {
		return SUCCESS;
	}

	return FAILURE;
}

uint8_t Set_Charge_Thresholds_INVALID();
uint8_t Set_Charge_Thresholds_INVALID() {

	SetChargeThresholdInput input = {.max_threshold = INVALID_MAX,
					 .min_threshold = INVALID_MIN};

	// Unit Under Test
	uint8_t api_status = ChipControl_Set_Charge_Thresholds(&input);

	if (api_status == CC_STATUS_ERROR_PARAMS) {
		return SUCCESS;
	}

	return FAILURE;
}

int main() {
	uint8_t status_valid = Set_Charge_Thresholds_VALID();

	uint8_t status_invalid = Set_Charge_Thresholds_INVALID();

	uint8_t status = status_valid | status_invalid;
	return 0;
}