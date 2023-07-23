add_executable(ChipControl_Tests ChipControl_Unit.c) # Create a new executable for your tests.
add_test(NAME MyTest COMMAND ChipControl_Tests) # Define a test. 