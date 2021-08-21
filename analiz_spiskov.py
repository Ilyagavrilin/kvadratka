import sys
from termcolor import colored, cprint


def spisok():
    mass = []
    file = open("output.txt")
    for line in file:
        line = line.split()
        mass1 = line
        mass.append(mass1)
    file.close()
    return mass


def sogl_find(mass, facultet, snils):
    mass2 = []
    for line in mass:
        if line[2] in snils:
            line[-1] = facultet
            mass2.append(line)
        else:
            continue
    return mass


itog = []
for i in range(1000):
    fac = input("напишите факультет:")
    if fac == "-1":
        break
    snilas = input('список снилсов:').split()
    if i == 0:
        itog = sogl_find(spisok(), fac, snilas)
    else:
        itog = sogl_find(itog, fac, snilas)
fil = open("output.txt", "w")
for line in itog:
    line = " ".join(line)
    fil.write(line + "\n")
    print(line)
fil.close()
file = open("output.txt", "r")
num = 0
for line in file:
    if int(line.split()[1]) > 3 or line.split()[-1] != "-":
        print(colored(line, 'red', attrs=['reverse', 'blink']))
    elif int(line.split()[0]) == 98:
        print(colored(line, 'green', attrs=['reverse', 'blink']))
        print(num)
    else:
        num += 1
        print(line)
