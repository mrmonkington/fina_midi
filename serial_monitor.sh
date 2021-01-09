#!/bin/bash

stty 115200 -F /dev/ttyACM0 raw -echo
cat /dev/ttyACM0
