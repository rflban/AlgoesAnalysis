#!/usr/bin/env python3

import sys
import argparse

from random import randint


def main():
    parser = createArgParser()
    namespace = parser.parse_args(sys.argv[1:])

    for item in wordsGenerator(namespace.first, namespace.last,
                               namespace.step):
        print(*item, sep='\n')


def createArgParser():
    parser = argparse.ArgumentParser()

    parser.add_argument('first', type=int, default=1, nargs='?')
    parser.add_argument('last', type=int, default=None, nargs='?')
    parser.add_argument('step', type=int, default=1, nargs='?')

    return parser


def wordsGenerator(first=1, last=None, step=1):
    if last == None:
        first, last = 1, first

    current = first
    while current <= last:

        word1 = ''.join([chr(randint(97, 109)) for i in range(current)])
        word2 = ''.join([chr(randint(110, 122)) for i in range(current)])

        yield word1, word2

        current += step


if __name__ == '__main__':
    main()

