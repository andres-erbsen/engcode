#!/bin/sh

while :; do
	dd if=/dev/urandom of=tmpfile bs=$RANDOM count=1 2>/dev/null
	c=$(cat tmpfile | ./engcode)
	py=$(cat tmpfile | ./engcode.py)
	if [[ "$py" == "$c" ]]; then
		# echo "$py"
		sleep 0
	else
		echo FAILED
		echo "$c"
		echo "$py"
		break
	fi
done

