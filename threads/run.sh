#!/bin/bash

TESTS=("2" "4" "8")

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
NC='\033[0m'

run_test_on_question1() {
    echo -e "${YELLOW}***************** Starting running test cases 2, 4 and 8 on question 1 *****************${NC}"
    for test in "${TESTS[@]}"; do
        echo -e "${GREEN}Running test case for $test :${NC}"
        ./question1 "$test"
        echo ""
    done
}

run_test_on_question2() {
    echo -e "${YELLOW}***************** Starting running test cases 2, 4 and 8 on question 2 *****************${NC}"
    for test in "${TESTS[@]}"; do
        echo -e "${GREEN}Running test case for $test :${NC}"
        ./question2 "$test"
        echo ""
    done
}


echo -e "${RED}Compiling......................................................................................${NC}"
make

echo -e "${RED}Executing ......................................................................................${NC}"
run_test_on_question1
run_test_on_question2
echo -e "${RED}Cleaning up ....................................................................................${NC}"
make clean