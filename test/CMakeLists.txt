add_executable(MyProjectTests ChipControl_Unit.c) # Create a new executable for your tests.
add_test(NAME MyTest COMMAND MyProjectTests) # Define a test. 