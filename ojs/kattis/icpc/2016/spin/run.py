import os

path = "testdata/secret/"
for x in filter(lambda x : x.endswith(".in"), os.listdir(path)):
    print(x)
    os.system("./a.out < " + path + x[:-3] + ".in")
    os.system("cat " + path + x[:-3] + ".ans")
    a = input()
