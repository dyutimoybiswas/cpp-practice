# Provide folder name as argument eg - bash run_file part2 chapter 9 to run exercises in chapter 9.
# Additionally define exercises to run as -D EXCHNO_EXNO where CHNO - chapter no, EXNO - exercise no
# eg -D EX_3_20 to run Ex 3.20
# Part1 contains chapters 2 through 7.
# Part2 contains chapters 8 through 12.
# Part3 contains chapters 13 through 16.
# Part4 contains chapters 17 through 19.

if [ $# -lt 2 ]; then
    echo "Too few arguments. Please specify part no and chapter no."
else
    PART=$1
    CHAPTER=$2
    g++ -std=c++20 -o output $PART/$CHAPTER/*.cpp
    ./output
fi
