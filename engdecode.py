#!/usr/bin/env python2
from sys import stdin, stdout

def main():
    words = open('words.txt').read().split()
    inwords = stdin.read().split()
    builder = []
    for word in inwords:
        n = words.index(word)
        group = bin(n)[2:]
        builder.append( group.rjust(18,'0') )
    bits = ''.join(builder)
    for i in range(0, len(bits), 8):
        byte = bits[i:i+8].rjust(8,'0')
        stdout.write( chr(int(byte, 2)) )

if __name__ == "__main__":
    main()
