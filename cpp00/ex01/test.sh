#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Compile the program
echo -e "${YELLOW}Compiling phonebook...${NC}"
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
    echo -e "${YELLOW}========================================${NC}"
    echo -e "${YELLOW}Test $test_num: $1${NC}"
    echo -e "${YELLOW}========================================${NC}"
    echo "$2" | ./phonebook
    echo -e "\n"
}

# Test 1: EXIT immediately
run_test "EXIT immediately" "EXIT"

# Test 2: Invalid command
run_test "Invalid commands" "INVALID
HELP
ADD
EXIT"

# Test 3: Add one contact and search
run_test "Add one contact and search" "ADD
John
Doe
Johnny
1234567890
Secret1
SEARCH
0
EXIT"

# Test 4: Add contact with empty fields (should reject)
run_test "Add contact with empty fields" "ADD


Johnny
1234567890
Secret1
EXIT"

# Test 5: Add multiple contacts
run_test "Add 3 contacts and search all" "ADD
Alice
Smith
Ali
1111111111
Loves cats
ADD
Bob
Johnson
Bobby
2222222222
Afraid of dogs
ADD
Charlie
Brown
Chuck
3333333333
Hates Mondays
SEARCH
0
SEARCH
1
SEARCH
2
EXIT"

# Test 6: Add more than 8 contacts (test replacement)
run_test "Add 9 contacts (test oldest replacement)" "ADD
Contact1
Last1
Nick1
1111111111
Secret1
ADD
Contact2
Last2
Nick2
2222222222
Secret2
ADD
Contact3
Last3
Nick3
3333333333
Secret3
ADD
Contact4
Last4
Nick4
4444444444
Secret4
ADD
Contact5
Last5
Nick5
5555555555
Secret5
ADD
Contact6
Last6
Nick6
6666666666
Secret6
ADD
Contact7
Last7
Nick7
7777777777
Secret7
ADD
Contact8
Last8
Nick8
8888888888
Secret8
ADD
Contact9
Last9
Nick9
9999999999
Secret9
SEARCH
EXIT"

# Test 7: Search with invalid index
run_test "Search with invalid index" "ADD
John
Doe
Johnny
1234567890
Secret
SEARCH
10
SEARCH
-1
SEARCH
abc
EXIT"

# Test 8: Long names (test truncation)
run_test "Long names (test truncation)" "ADD
VeryLongFirstName
VeryLongLastName
VeryLongNickname
1234567890123456
VeryLongDarkestSecret
SEARCH
0
EXIT"

# Test 9: Test column formatting
run_test "Test column formatting with multiple contacts" "ADD
Short
Name
Nick
123
Secret
ADD
VeryLongFirstNameHere
VeryLongLastNameHere
VeryLongNicknameHere
9876543210
Another long secret here
ADD
A
B
C
1
S
SEARCH
EXIT"

# Test 10: Empty phonebook search
run_test "Search in empty phonebook" "SEARCH
EXIT"

# Test 11: Mixed valid and invalid commands
run_test "Mixed commands" "INVALID
ADD
Test
User
Tester
5555555555
TestSecret
RANDOM
SEARCH
0
NONSENSE
EXIT"

echo -e "${GREEN}========================================${NC}"
echo -e "${GREEN}All tests completed!${NC}"
echo -e "${GREEN}========================================${NC}"
