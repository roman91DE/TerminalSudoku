#!/bin/sh


# pull changes
git pull

# format implementations
clang-format -style='google' -i src/*.cpp 
# .. and header files
clang-format -style='chromium' -i src/*.h

# push and commit
git add *
git commit -m "auto commit"
git push

