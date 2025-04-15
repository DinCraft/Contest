import platform
import sys
import os

os_name = platform.system()
if os_name == "Windows":
    os.system("gcc task2/task.c -o task")
    os.system("task.exe < task2\\test1.txt")
    print("\n")
    os.system("more task2\\exp1.txt")

if len(sys.argv) == 2:
    print(sys.argv[1], end="")