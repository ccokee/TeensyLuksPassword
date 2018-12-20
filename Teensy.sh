#!/bin/bash
echo "Sending kill signal to teensy!"
echo 'k' > /dev/ttyACM0
echo "Sent!!!"
