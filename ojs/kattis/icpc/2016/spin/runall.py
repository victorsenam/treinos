import os
import re

regex = re.compile(r'.*\.in')
files = filter(regex.match, os.listdir('./secret/'))

for file in files:
	print("Running " + file)
	outname = file.replace('.in', '.ans')
	os.system('./a.out < secret/' + file + ' > res && diff res secret/' + outname)
