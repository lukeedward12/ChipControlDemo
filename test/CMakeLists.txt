set(SOURCES
    ChipControl_Get_ADC_Mode.c
    ${SOURCE_DIR}/ChipControl/ChipControl.c
    fakes/fake_LTC2943.c
    # Add more source files here
)

add_executable(ChipControl_Get_ADC_Mode ${SOURCES})
add_test(NAME ChipControl_Get_ADC_Mode COMMAND ChipControl_Get_ADC_Mode) 
target_include_directories(ChipControl_Get_ADC_Mode PRIVATE ${SOURCE_DIR}/ChipControl)
target_include_directories(ChipControl_Get_ADC_Mode PRIVATE ${SOURCE_DIR}/Drivers)
target_include_directories(ChipControl_Get_ADC_Mode PRIVATE ${TEST_DIR}/fakes)