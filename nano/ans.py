#!/usr/bin/python
# -*- coding: utf-8 -*-

import serial
import time

port = None

lines = []

def game0(line):
	if line == 'Nano$ enter your answer:':
		# enter you answer here
		port.write('%s\n' % 'HITCONNANOGAMEMORSE')
		# port.write('%s\n' % 'ANSWER')
		port.flush()

def game1(line):
	if line == 'Nano$ show map':
		global lines
		lines = lines[-3:]
		# for line in lines:
		# 	print line
		# write you rules here
		port.write('d\n')
		port.flush()
	else:
		lines.append(line)

def game2(line):
	if line == 'Nano$ enter your answer:':
		# write you rules here
		port.write('%d\n' % 10)
		port.flush()

def game3(line):
	pass	

def main():
	# enter your choice here
	choice = '0'
	# enter your team token here
	team_token = '12345678'
	while True:
		line = port.readline()[:-1]
		print line
		if line == 'Nano$ enter your team token:':
			port.write('%s\n' % team_token)
			port.flush()
		if line == 'Nano$ enter your choice:':
			port.write('%s\n' % choice)
			port.flush()
		if line == 'Nano$ finish':
			port.close()
			break
		if choice == '0':
			game0(line)
		if choice == '1':
			game1(line)
		if choice == '2':
			game2(line)
		if choice == '3':
			game3(line)

if __name__ == '__main__':
	port = serial.Serial(port=3, baudrate=115200, bytesize=serial.EIGHTBITS, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE)
	main()
