#!/bin/bash
file=$1
commit=$2
git add $file
git commit -m "$2"
git push -u origin master
