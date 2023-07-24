#include "ChipControl.h"
#include "fake_LTC2943.h"
#include <stdio.h>

enum ctest_return_status { SUCCESS = 0, FAILURE = 1 } ctest_return_status;

uint8_t Get_ADC_Mode_AUTO();
uint8_t Get_ADC_Mode_AUTO() {

  control_register = 0xC0;

  GetADCModeResponse get_adc_response;
  ChipControl_Get_ADC_Mode(&get_adc_response);

  if (get_adc_response.mode == AUTO) {
    return 0;
  } else {
    return 1;
  }
}

int main() {

  uint8_t status = Get_ADC_Mode_AUTO();

  return status;
}
