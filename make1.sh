#!/bin/bash
rm *.o
rm gnl
gcc -g test1.c get_next_line.c -o gnl
