#!/bin/bash

# Define ANSI color
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
PURPLE='\033[0;35m'
RED='\033[0;31m'
BLUE='\033[0;34m'
RESET='\033[0m'

# Get script directory
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"

# Set the path to the executable
EXECUTABLE="$SCRIPT_DIR/../convert"
MAKEFILE_LOCATION="$SCRIPT_DIR/.."
OUTPUT_FILE="$SCRIPT_DIR/output"

# If an argument is provided, enable logging
SHOW_EXPECTED_ENABLED=false
if [ $# -eq 1 ] && [ "$1" == "true" ]
then
  SHOW_EXPECTED_ENABLED=$1
  echo "${GREEN}Showing expected${RESET}"
else
	echo -e "Run '$0 ${BLUE}true${RESET}' to show expected."
	echo -e "${YELLOW}Press enter to start the tests${RESET}"
	read -n 1 -s
fi

#----------------------------------------------------#
# Function to print number of characters (num, sign, color)
print_signs()
{
  local width="$1"
	local sign="$2"
	local color="$3"

	for ((i = 0; i < width; i++)); do
		echo -n -e "${color}$sign${RESET}"
	done
	echo
}

# Function to print info between a line of signs (text, sign)
print_info()
{
	print_signs "40" "$2" "$BLUE"
	echo -e "${YELLOW}$1${RESET}"
	print_signs "40" "$2" "$BLUE"
}
#----------------------------------------------------#

# Build the executable and check for relinking
RELINKING=true
print_info "make re" "-"
make re -C $MAKEFILE_LOCATION
if [ $? -ne 0 ]; then
    echo -e "${RED}Compilation failed${RESET}"
    exit 1
fi
print_info "make - relinking?" "-"
make_output=$(make -C $MAKEFILE_LOCATION)
if [ $? -ne 0 ]; then
    echo -e "${RED}Compilation failed${RESET}"
    exit 1
elif [[ $make_output == *"Nothing to be done for 'all'."* ]]; then
    echo -e "${GREEN}No relinking occurred.${RESET}"
		RELINKING=false
else
    echo -e "${RED}Relinking occurred.${RESET}"
		echo -e "$make_output"
fi

test_counter=0
passed_counter=0
process_test_case()
{
	local input="$1"
	local output_char="$2"
	local output_int="$3"
	local output_float="$4"
	local output_double="$5"

	# Increment counter
	((test_counter++))

	# Execute
	$EXECUTABLE "$input" > $OUTPUT_FILE

	# Generate expected output
	expected_output="char: $output_char\nint: $output_int\nfloat: $output_float\ndouble: $output_double"

	# Compare the output with the expected output
	diff=$(diff <(echo -e "$expected_output") $OUTPUT_FILE)
	diff_exit_code=$?

	if [ $diff_exit_code -ne 0 ]
	then
		echo -e "${RED}Diff exit code: $diff_exit_code${RESET}"
		return
	fi

	# If the output is different from the expected output
	if [ "$diff" != "" ]
	then
		echo -e "Test ${YELLOW}$test_counter${RESET} -> input: [${PURPLE}$input${RESET}] -> ${RED}FAILED${RESET}"
		echo -e "Expected output: [${GREEN}$expected_output${RESET}]"
		echo -e "Your output: [${RED}$(cat output)${RESET}]"
		# echo -e "Diff: [${RED}$diff${RESET}]"
	else
		echo -e "Test ${YELLOW}$test_counter${RESET} -> input: [${PURPLE}$input${RESET}] -> ${GREEN}PASSED${RESET}"
		((passed_counter++))

		# If logging is enabled, print the test and expected output
    if [ "$SHOW_EXPECTED_ENABLED" = true ]
    then
        echo -e "Expected output: [${GREEN}$expected_output${RESET}]"
    fi
	fi
}



#-----------------TEST CASES-----------------#
# nan
print_info "Testing nan" "-"
process_test_case nan impossible impossible nanf nan
process_test_case nanf impossible impossible nanf nan

# inf
print_info "Testing inf" "-"
process_test_case -inf impossible impossible -inff -inf
process_test_case +inf impossible impossible inff inf
process_test_case inf impossible impossible inff inf

# inff
print_info "Testing inff" "-"
process_test_case -inff impossible impossible -inff -inf
process_test_case +inff impossible impossible inff inf
process_test_case inff impossible impossible inff inf

# Non displayable char
print_info "Testing non displayable char" "-"
process_test_case -129 impossible -129 -129.0f -129.0
process_test_case -128 "Non displayable" -128 -128.0f -128.0
process_test_case 0 "Non displayable" 0 0.0f 0.0
process_test_case 127 "Non displayable" 127 127.0f 127.0
process_test_case 128 impossible 128 128.0f 128.0
process_test_case 10.6 "Non displayable" 10 10.6f 10.6

# Special cases
print_info "Testing special cases" "-"
process_test_case 0.23f "Non displayable" 0 0.23f 0.23
process_test_case -0.23f "Non displayable" 0 -0.23f -0.23
process_test_case -0.44 "Non displayable" 0 -0.44f -0.44
process_test_case 0.44 "Non displayable" 0 0.44f 0.44

# Char
print_info "Testing char" "-"
process_test_case -128.2 impossible -128 -128.2f -128.2
process_test_case 42 "'*'" 42 42.0f 42.0
process_test_case 77 "'M'" 77 77.0f 77.0
process_test_case 99 "'c'" 99 99.0f 99.0
process_test_case 56 "'8'" 56 56.0f 56.0
process_test_case "'''" "'''" 39 39.0f 39.0
process_test_case "''" impossible impossible impossible impossible
process_test_case "'" impossible impossible impossible impossible
process_test_case "" impossible impossible impossible impossible
process_test_case "'44'" impossible impossible impossible impossible

# Int
print_info "Testing int" "-"
process_test_case -2147483648 impossible -2147483648 -2147483648.0f -2147483648.0
process_test_case 2147483647 impossible 2147483647 2147483648.0f 2147483647.0
process_test_case 0 "Non displayable" 0 0.0f 0.0
process_test_case 500 impossible 500 500.0f 500.0

# Float
print_info "Testing float" "-"
process_test_case 33.33f "'!'" 33 33.33f 33.33
process_test_case -33.33f "Non displayable" -33 -33.33f -33.33
process_test_case 765456809984.0f impossible impossible 765456809984.0f 765456809984.0
FLOAT_MAX=340282346638528859811704183484516925440.0
process_test_case "${FLOAT_MAX}f" impossible impossible "${FLOAT_MAX}f" $FLOAT_MAX
process_test_case "-${FLOAT_MAX}f" impossible impossible "-${FLOAT_MAX}f" -$FLOAT_MAX
process_test_case 34.23847923874f "'\"'" 34 34.23847961426f 34.23847961426
process_test_case 34.23847f "'\"'" 34 34.23847f 34.23847

# Double
print_info "Testing double" "-"
process_test_case 33.33 "'!'" 33 33.33f 33.33
process_test_case -33.33 "Non displayable" -33 -33.33f -33.33
process_test_case 765456809984.0 impossible impossible 765456809984.0f 765456809984.0
process_test_case "${FLOAT_MAX}" impossible impossible "${FLOAT_MAX}f" $FLOAT_MAX
process_test_case "-${FLOAT_MAX}" impossible impossible "-${FLOAT_MAX}f" -$FLOAT_MAX
process_test_case 34.23847923874 "'\"'" 34 34.23847961426f 34.23847923874
process_test_case 34.23847 "'\"'" 34 34.23847f 34.23847
process_test_case 99.8765445678765 "'c'" 99 99.8765411376953f 99.8765445678765

print_info "Testing double max" "-"
DOUBLE_MAX=179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.0
process_test_case $DOUBLE_MAX impossible impossible impossible $DOUBLE_MAX
process_test_case -$DOUBLE_MAX impossible impossible impossible -$DOUBLE_MAX

# Error cases
print_info "Testing error cases" "-"
process_test_case "a" impossible impossible impossible impossible
process_test_case "1.2.3" impossible impossible impossible impossible
process_test_case "i" impossible impossible impossible impossible
process_test_case "-i" impossible impossible impossible impossible
process_test_case "-in" impossible impossible impossible impossible
process_test_case "in" impossible impossible impossible impossible
process_test_case "infff" impossible impossible impossible impossible
process_test_case "-infff" impossible impossible impossible impossible
process_test_case "-nanff" impossible impossible impossible impossible
process_test_case "-na" impossible impossible impossible impossible
process_test_case "na" impossible impossible impossible impossible
process_test_case "+" impossible impossible impossible impossible
process_test_case "-" impossible impossible impossible impossible
process_test_case "--1" impossible impossible impossible impossible
process_test_case "++1" impossible impossible impossible impossible

# No Args
print_info "Testing no args" "-"
((test_counter++))
echo -e "Test ${YELLOW}$test_counter${RESET} -> input:"
$EXECUTABLE > $OUTPUT_FILE
if [ $? -ne 0 ]
then
	echo -e "${GREEN}PASSED${RESET}"
	((passed_counter++))
else
	echo -e "${RED}FAILED${RESET}"
fi


# Print final result
print_info "Final result" "-"
echo -e "You passed $passed_counter/${YELLOW}$test_counter${RESET} tests"
if [ "$RELINKING" = true ]
then
		echo -e "${RED}Relinking occurred${RESET}"
else
		echo -e "${GREEN}No relinking occurred${RESET}"
fi

#Clean
make fclean -C $MAKEFILE_LOCATION > ${SCRIPT_DIR}/output
rm -f ${SCRIPT_DIR}/output