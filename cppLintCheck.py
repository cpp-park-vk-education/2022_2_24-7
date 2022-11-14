import subprocess
import os
for root, dirs, files in os.walk("./l1"):
    for file in files:
        if file.endswith(".cpp"):
             subprocess.run(['cpplint', os.path.join(root, file)])

for root, dirs, files in os.walk("./l1"):
    for file in files:
        if file.endswith(".cpp"):
             subprocess.run(['cppcheck', os.path.join(root, file)])
