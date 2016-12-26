#!/bin/python3

import subprocess

for i in range(4,47):
    nm = "buffet/secret/buffet-"
    if (i < 10):
        nm = nm + "0"
    nm = nm + str(i)

    print(nm)
    subprocess.call("./a.out < " + nm + ".in > " + nm + ".out", shell=True);
    subprocess.call("diff " + nm + ".ans " + nm + ".out", shell=True);
