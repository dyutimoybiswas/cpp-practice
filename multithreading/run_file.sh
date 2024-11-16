
# Provide file name as argument while running this script.
g++ -std=c++20 -O1 -pthread -o output $1.cpp
./output
