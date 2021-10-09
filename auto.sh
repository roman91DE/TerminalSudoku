#!/bin/sh

# automate src formatting and git 

git pull
clang-format -style='webkit' -i src/*.*
git add *
git commit -m "auto commit"
git push

