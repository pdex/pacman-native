#!/bin/bash

INCLUDES="-Igoogletest/googletest/include"
CFLAGS="-std=gnu++14 -Wall -g"
GTEST_MAIN="googletest/googletest/make/gtest_main.a"
g++ $CFLAGS $INCLUDES $GTEST_MAIN Test*.cc -o main_test &&
echo "run" | lldb -s /dev/stdin ./main_test
