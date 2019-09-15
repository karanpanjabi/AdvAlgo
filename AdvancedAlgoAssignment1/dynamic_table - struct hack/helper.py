#!/usr/bin/python3

lines = []

try:
    while True:
        l = input()
        lines.append(l)
except EOFError as e:
    pass

times = [int(x) for x in lines[:len(lines)-1]]
print(times)
print("Total: %d" % (sum(times)))
print("Average: %f" % (sum(times)/len(times)))
print(lines[-1])