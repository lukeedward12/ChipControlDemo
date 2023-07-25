#include "ChipControl.h"

int main() {
  ChipControl_Initialize();

  GetADCModeResponse get_adc_response;
  ChipControl_Get_ADC_Mode(&get_adc_response);

  SetADCModeInput set_adc_input = {.mode = SCAN};
  ChipControl_Set_ADC_Mode(&set_adc_input);

  GetTempStatusResponse get_temp_response;
  ChipControl_Get_Temp_Status(&get_temp_response);

  SetChargeThresholdInput set_charge_input = {.max_threshold = 2000,
                                              .min_threshold = 0};
  ChipControl_Set_Charge_Thresholds(&set_charge_input);

  GetChargeStatusResponse get_charge_response;
  ChipControl_Get_Charge_Status(&get_charge_response);

  return 0;
}