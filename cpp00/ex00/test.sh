#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Compile the program
echo -e "${YELLOW}Compiling megaphone...${NC}"
make re
if [ $? -ne 0 ]; then
    echo -e "${RED}Compilation failed!${NC}"
    exit 1
fi
echo -e "${GREEN}Compilation successful!${NC}\n"

# Test counter
test_num=0

# Function to run a test
run_test() {
    test_num=$((test_num + 1))
    echo -e "${YELLOW}Test $test_num: $1${NC}"
    echo -e "Command: ./megaphone $2"
    echo -e "Output:"
    eval "./megaphone $2"
    echo -e "\n---\n"
}

# Test 1: No arguments
run_test "No arguments" ""

# Test 2: Single argument with lowercase
run_test "Single argument with lowercase" '"shhhhh... I think the students are asleep..."'

# Test 3: Multiple arguments
run_test "Multiple arguments" '"Damnit" "! " "Sorry students, I thought this thing was off."'

# Test 4: Mixed case
run_test "Mixed case" '"Hello World"'

# Test 5: Only lowercase
run_test "Only lowercase" '"abcdefghijklmnopqrstuvwxyz"'

# Test 6: Only uppercase (should remain uppercase)
run_test "Already uppercase" '"ALREADY LOUD"'

# Test 7: Numbers and special characters
run_test "Numbers and special characters" '"42 is the answer! #winning"'

# Test 8: Multiple words as separate arguments
run_test "Multiple separate words" '"Hello" "From" "42" "School"'

# Test 9: Empty string
run_test "Empty string" '""'

# Test 10: Special characters
run_test "Special characters" '"!@#$%^&*()"'

echo -e "${GREEN}All tests completed!${NC}"
