#ifndef CHIPCONTROL_H
#define CHIPCONTROL_H

#include <stdint.h>

enum ChipControl_Status_Codes {
    CC_STATUS_OK,
    CC_STATUS_ERROR,
    CC_STATUS_ERROR_PARAMS
};

uint8_t ChipControl_Get_ADC_Mode();
uint8_t ChipControl_Set_ADC_Mode();
uint8_t ChipControl_Get_Temp_Status();
uint8_t ChipControl_Set_Charge_Thresholds();
uint8_t ChipControl_Get_Charge_Status();




#endif // CHIPCONTROL_H