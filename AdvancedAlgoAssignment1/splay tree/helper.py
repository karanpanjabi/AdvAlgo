#!/usr/bin/python3

lines = []

try:
    while True:
        l = input()
        lines.append(l)
except EOFError as e:
    pass

ssearches = 0

times = lines[:len(lines)-1]
for i in range(len(times)):
    arr = [int(x) for x in times[i].split(" ")]
    if(len(arr) == 2):
        if(arr[0] != -1):
            ssearches += 1
        times[i] = arr[1]
    else:
        times[i] = arr[0]

print(lines)
print("Total: %d" % (sum(times)))
print("Average: %f" % (sum(times)/len(times)))
print("Succesful searches: %d" % (ssearches))
print(lines[-1])