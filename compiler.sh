#!/bin/bash
echo "Loading the Betty test"
betty *.h *.c
echo "the code is betty approuved"
gcc *.c -o simple-shell
echo "The basic gcc command working"
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o shell
echo "The alx gcc command launched"
