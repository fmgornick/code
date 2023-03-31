#!/bin/bash
#
# testcase.sh - simple script to run each of the 3 test cases for scullbuffer
# CSCI 5103 Spring 2023 - Anand Tripathi 
case $1 in
	1) ./producer 50 case1_red & ./consumer 50 case1;;
	2) ./producer 50 case2_red & ./consumer 10 case2;;
	3) ./producer 50 case3_red & ./consumer 100 case3;;
esac
