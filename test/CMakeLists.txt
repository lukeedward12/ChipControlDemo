set(SOURCES_GET_ADC
    ChipControl_Get_ADC_Mode.c
    ${SOURCE_DIR}/ChipControl/ChipControl.c
    fakes/fake_LTC2943.c
    # Add more source files here
)
add_executable(ChipControl_Get_ADC_Mode ${SOURCES_GET_ADC})
add_test(NAME ChipControl_Get_ADC_Mode COMMAND ChipControl_Get_ADC_Mode) 
target_include_directories(ChipControl_Get_ADC_Mode PRIVATE ${SOURCE_DIR}/ChipControl)
target_include_directories(ChipControl_Get_ADC_Mode PRIVATE ${SOURCE_DIR}/Drivers)
target_include_directories(ChipControl_Get_ADC_Mode PRIVATE ${TEST_DIR}/fakes)

set(SOURCES_SET_ADC
    ChipControl_Set_ADC_Mode.c
    ${SOURCE_DIR}/ChipControl/ChipControl.c
    fakes/fake_LTC2943.c
    # Add more source files here
)
add_executable(ChipControl_Set_ADC_Mode ${SOURCES_SET_ADC})
add_test(NAME ChipControl_Set_ADC_Mode COMMAND ChipControl_Set_ADC_Mode) 
target_include_directories(ChipControl_Set_ADC_Mode PRIVATE ${SOURCE_DIR}/ChipControl)
target_include_directories(ChipControl_Set_ADC_Mode PRIVATE ${SOURCE_DIR}/Drivers)
target_include_directories(ChipControl_Set_ADC_Mode PRIVATE ${TEST_DIR}/fakes)

set(SOURCES_GET_TEMP
    ChipControl_Get_Temp_Status.c
    ${SOURCE_DIR}/ChipControl/ChipControl.c
    fakes/fake_LTC2943.c
    # Add more source files here
)
add_executable(ChipControl_Get_Temp_Status ${SOURCES_GET_TEMP})
add_test(NAME ChipControl_Get_Temp_Status COMMAND ChipControl_Get_Temp_Status) 
target_include_directories(ChipControl_Get_Temp_Status PRIVATE ${SOURCE_DIR}/ChipControl)
target_include_directories(ChipControl_Get_Temp_Status PRIVATE ${SOURCE_DIR}/Drivers)
target_include_directories(ChipControl_Get_Temp_Status PRIVATE ${TEST_DIR}/fakes)

set(SOURCES_SET_CHARGE_THESHOLDS
    ChipControl_Set_Charge_Thresholds.c
    ${SOURCE_DIR}/ChipControl/ChipControl.c
    fakes/fake_LTC2943.c
    # Add more source files here
)
add_executable(ChipControl_Set_Charge_Thresholds ${SOURCES_SET_CHARGE_THESHOLDS})
add_test(NAME ChipControl_Set_Charge_Thresholds COMMAND ChipControl_Set_Charge_Thresholds) 
target_include_directories(ChipControl_Set_Charge_Thresholds PRIVATE ${SOURCE_DIR}/ChipControl)
target_include_directories(ChipControl_Set_Charge_Thresholds PRIVATE ${SOURCE_DIR}/Drivers)
target_include_directories(ChipControl_Set_Charge_Thresholds PRIVATE ${TEST_DIR}/fakes)