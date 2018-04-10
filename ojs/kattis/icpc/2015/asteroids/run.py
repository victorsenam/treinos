import os

o = ""
for i in range(3,51):
    print(i)
    os.system("./a.out < tests/asteroids%02d.in"%i)
    os.system("cat tests/asteroids%02d.ans"%i)
    o = input()
