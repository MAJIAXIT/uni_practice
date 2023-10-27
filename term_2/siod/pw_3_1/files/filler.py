import random

numbers = [int(_) for _ in open("./test_numbers.txt", "r").read().split()]
repeated_10 = open("./repeated_10.txt", "w")
repeated_100 = open("./repeated_100.txt", "w")
repeated_500 = open("./repeated_500.txt", "w")
repeated_1000 = open("./repeated_1000.txt", "w")


temp = []
for i in numbers[:6000]:
    for j in range(10):
        temp.append(i)

random.shuffle(temp)
count = 0
for i in temp:
    count += 1
    repeated_10.write(str(i) + ' ')
    if (count % 10 == 0):
        repeated_10.write('\n')


temp = []
for i in numbers[:600]:
    for j in range(100):
        temp.append(i)

random.shuffle(temp)
count = 0
for i in temp:
    count += 1
    repeated_100.write(str(i) + ' ')
    if (count % 10 == 0):
        repeated_100.write('\n')


temp = []
for i in numbers[:120]:
    for j in range(500):
        temp.append(i)

random.shuffle(temp)
count = 0
for i in temp:
    count += 1
    repeated_500.write(str(i) + ' ')
    if (count % 10 == 0):
        repeated_500.write('\n')

temp = []
for i in numbers[:60]:
    for j in range(1000):
        temp.append(i)

random.shuffle(temp)
count = 0
for i in temp:
    count += 1
    repeated_1000.write(str(i) + ' ')
    if (count % 10 == 0):
        repeated_1000.write('\n')
