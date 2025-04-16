import platform
import sys
import os

taskId = 0
testId = 0
if len(sys.argv) == 3:
    taskId = sys.argv[1]
    testId = sys.argv[2]
else:
    exit("2 args required: taskId and testId")

print("Real")
os_name = platform.system()
os.system("gcc task"+taskId+"/task.c -o task")
if os_name == "Windows":
    os.system("task.exe < task"+taskId+"\\test"+testId+".txt")
elif os_name == "Linux":
    os.system("./task < task"+taskId+"/test"+testId+".txt")
print("\nExpected")
if os_name == "Windows":
    os.system("more task"+taskId+"\\exp"+testId+".txt")
elif os_name == "Linux":
    os.system("cat task"+taskId+"/exp"+testId+".txt")
    print("")