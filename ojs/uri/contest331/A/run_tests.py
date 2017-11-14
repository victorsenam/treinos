#!/usr/bin/python3

import wget
import os
import subprocess

for i in range(1,35):
	name = "A_" + str(i)
	print("==== " + name + " ====")

#	print("downloading input...")
#	wget.download("http://maratona.ime.usp.br/resultados17/A/input/" + name)
#	os.rename(name, "inp/" + name)
#
#	print("\ndownloading output...")
#	wget.download("http://maratona.ime.usp.br/resultados17/A/output/" + name)
#	os.rename(name, "ans/" + name)

	#print("\nopenning files")
	inp_file = os.open("inp/" + name, os.O_RDONLY)
	os.remove("out/" + name)
	out_file = os.open("out/" + name, os.O_WRONLY|os.O_CREAT)

	#print("running...")
	subprocess.call("./a.out", shell=True, stdin=inp_file, stdout=out_file, timeout=3)
	subprocess.call("diff out/" + name + " ans/" + name, shell=True)
	#print(" ")
