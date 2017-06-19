import os
import subprocess

files = map(lambda name : name.strip('.in'), filter(lambda name : name.endswith('.in'), os.listdir('tests')))

for test in files:
    subprocess.call('./a.out < tests/' + test + '.in > out', shell=True)
    fl = subprocess.call('diff out tests/' + test + '.ans', shell=True)

    if fl :
        print "Fail file " + test
