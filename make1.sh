#!/bin/bash
cd libft; make fclean; make; make clean; cd ..;
rm gnl
gcc -g -Llibft -lft main.c get_next_line.c -o gnl
