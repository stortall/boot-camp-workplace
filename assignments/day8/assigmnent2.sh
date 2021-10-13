#!/bin/bash
git pull
cd ~/projects/boot-camp-workplace/mini-project/
g++ suduko.cpp -o suduko
./suduko suduko_easy.csv
