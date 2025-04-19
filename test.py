import platform
import sys
import os

taskId = 0
if len(sys.argv) == 2:
    taskId = sys.argv[1]
else:
    exit("1 arg required: taskId")

os_name = platform.system()
os.system("gcc task"+taskId+"/test.c -o test")
if os_name == "Windows":
    os.system("test.exe")
elif os_name == "Linux":
    os.system("./task")