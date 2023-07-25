#ifndef FAKE_LTC2943_H
#define FAKE_LTC2943_H

#include "LTC2943.h"

typedef struct RegisterMapValues {
	uint16_t status_register;
	uint16_t control_register;
	uint16_t charge_threshold_high_msb;
	uint16_t charge_threshold_high_lsb;
	uint16_t charge_threshold_low_msb;
	uint16_t charge_threshold_low_lsb;
} RegisterMapValues;

/**
 * @brief Used for interacting with the fake registers inside testing or
 * the fake driver
 *
 */
extern RegisterMapValues register_map_values;

#endif // FAKE_LTC2943_H