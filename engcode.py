#!/usr/bin/env python2
from sys import stdin, stdout, stderr

def tobits(s):
    builder = []
    for c in s:
        byte = bin(ord(c))[2:].rjust(8,'0')
        builder.append( byte )
    return ''.join(builder)

def main():
    words = open('words.txt').read().split()
    bits = tobits( stdin.read() )
    # pad with zeros at end to blocks of 18 bits
    if len(bits) % 18:
        bits += '0' * (18 - len(bits) % 18)
    # each group of 18 bits is encoded to one word
    for i in range(0, len(bits), 18):
        group = bits[i:i+18]
        n = int( group, 2)
	# stderr.write(hex(n)[2:]+' '+str(n)+'\n')
        if i: stdout.write(' ')
        stdout.write( words[n] )
    stdout.write('\n')


if __name__ == "__main__":
    main()
