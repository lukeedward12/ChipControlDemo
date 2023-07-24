#ifndef FAKE_LTC2943_H
#define FAKE_LTC2943_H

#include "LTC2943.h"

typedef struct RegisterMapValues {
  uint16_t status_register;
  uint16_t control_register;
} RegisterMapValues;

/**
 * @brief Used for interacting with the fake registers inside testing or
 * the fake driver
 *
 */
extern RegisterMapValues register_map_values;

#endif // FAKE_LTC2943_H