#!/bin/bash

rhasher_result=$(echo "MD5 test.txt" | ./rhasher 2>/dev/null | tr -d '\n\r')
system_result="MD5 test.txt$(md5sum "test.txt" | cut -d' ' -f1)"
if [[ "$rhasher_result" == "$system_result" ]]; then
	echo "PASS MD5 TEST"
else
	echo "FAIL MD5 TEST"
fi
	
rhasher_result=$(echo "SHA1 test.txt" | ./rhasher 2>/dev/null | tr -d '\n\r')
system_result="SHA1 test.txt$(sha1sum "test.txt" | cut -d' ' -f1)"    
if [[ "$rhasher_result" == "$system_result" ]]; then
	echo "PASS SHA1 TEST"
else
	echo "FAIL SHA1 TEST"
fi	
