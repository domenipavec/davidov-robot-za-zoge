#!/usr/bin/python
# -*- coding: utf-8 -*-
#
# Writes hex file to serial port
# copyright ¢ 2013 by Domen Ipavec

serialDevice = '/dev/ttyUSB0'

import serial
import sys
import random

f = open(sys.argv[1], 'r')
fw = open(sys.argv[1] + ".bin", 'w')

output = {}

for line in f:
	if line[0] != ':':
		raise Exception("Not correct file format")
	byte_count = int(line[1:3], 16)
	address = int(line[3:7], 16)
	record_type = int(line[7:9], 16)
	if record_type == 0:
		for x in range(byte_count):
			output[address + x] = chr(int(line[(9 + 2*x):(9 + 2*x + 2)], 16))
	
i = 0
		
ser = serial.Serial(serialDevice, 9600, parity=serial.PARITY_ODD, stopbits=2)

# time for mem clear
for x in range(255):
	ser.write(chr(random.randrange(255)))

for x in range(max(output.keys()) + 128):
	i += ser.write(output.get(x, chr(random.randrange(255))))
	if (x+1)%128 == 0:
		for x in range(100):
			ser.write(chr(random.randrange(255)))
	fw.write(output.get(x, chr(0)))

print "Zapisal sem " + str(i) + " bitov"

ser.close()
