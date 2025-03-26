import os

while True:
    os.system("python3 gen.py && ./run2 < testcase.in > control.out && ./run < testcase.in > test.out")
    os.system("diff control.out test.out | wc -l > result.txt")

    f = open("result.txt").read()

    if f != '0\n':
        print("FOUND A CASE")
        break
