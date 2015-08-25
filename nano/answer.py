#!/usr/bin/python
# -*- coding: utf-8 -*-

import re
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
		global lines
		lines = lines[-1:]
		# write you rules here
		line = lines[0].replace(' ', '').replace('Nano$', '').replace('=?', '')
		while True:
			match_line = re.search(r'(\d+\*\d+)', line)
			if match_line:
				for group in match_line.groups():
					print group
					match_prod = re.search(r'(?P<num1>\d+)\*(?P<num2>\d+)', group)
					num1 = int(match_prod.group('num1'))
					num2 = int(match_prod.group('num2'))
					line = line.replace(group, str(num1 * num2))
			else:
				break
		total = 0
		line = line.replace('+', ' +')
		line = line.replace('-', ' -')
		items = line.split(' ')
		for item in items:
			total += int(item)
		port.write('%d\n' % total)
		port.flush()
	else:
		lines.append(line)

def main():
	# enter your choice here
	choice = '0'
	while True:
		line = port.readline()[:-1]
		print line
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
