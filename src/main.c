#include "ChipControl.h"

int main() {
  ChipControl_Initialize();

  GetADCModeResponse response;
  ChipControl_Get_ADC_Mode(&response);

  SetADCModeInput input = {.mode = SCAN};
  ChipControl_Set_ADC_Mode(&input);

  return 0;
}