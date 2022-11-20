import subprocess
import os
for root, dirs, files in os.walk("."):
    for file in files:
        if not root.startswith("./build"):
            if file.endswith(".cpp"):
                subprocess.run(['cpplint', os.path.join(root, file)])

for root, dirs, files in os.walk("."):
    for file in files:
        if not root.startswith("./build"):
            if file.endswith(".cpp"):
                subprocess.run(['cppcheck', os.path.join(root, file)])

for root, dirs, files in os.walk("."):
    for file in files:
        if not root.startswith("./build"):
            if file.endswith(".cpp"):
                subprocess.run(['clang-tidy', os.path.join(root, file)])
