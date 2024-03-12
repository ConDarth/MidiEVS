# Waveshape Formatter
#
# Takes in specified CSV and outputs the data in an arduino readable array
#
# Connor Lindsay

import csv

print("")
fileName = input("Please input file name: ").strip()

data = []
with open(fileName + ".csv", 'r', newline='') as file:
    header = next(file)
    csvfile = csv.reader(file)
    for row in csvfile:
        data.append(row[2])

varName = input("Please input variable name: ").strip()


with open("waveshapeArray.txt", 'w') as out:
    out.write("float " + varName + "[" + str(len(data)) + "]" + " = { \n\t")

    for dataNum, data in enumerate(data):
        out.write(data + ",\t")

        if (dataNum%8 == 0):
            out.write("\n\t")

    out.write("\n} ;")

print("Array Complete. Please Remember to remove the comma in ths last line.")
