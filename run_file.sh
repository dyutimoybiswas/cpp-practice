# Run as - bash run_file part_no chapter_no exercise_no eg - bash run_file 2 9 4 to run exercise 4 in chapter 9 under part 2.
# Define CUSTOM to run examples.
# Part1 contains chapters 2 through 7.
# Part2 contains chapters 8 through 12.
# Part3 contains chapters 13 through 16.
# Part4 contains chapters 17 through 19.

if [ $# -lt 3 ]; then
    # Special case - chapter 1
    if [ $1 -eq 1 ]; then
        if [ $# -lt 2 ]; then
            echo "Too few arguments. Please specify exercise no."
        elif [ $2 = CUSTOM ]; then
            g++ -std=c++20 -o output chapter1/*.cpp -D CUSTOM
            ./output
        else
            EXERCISE=$2
            g++ -std=c++20 -o output chapter1/*.cpp -D "EXERCISE${EXERCISE} "
            ./output
        fi
    else
        echo "Too few arguments. Please specify part no, chapter no and exercise no."
    fi
else
    PART=$1
    CHAPTER=$2
    if [ $3 = CUSTOM ]; then
        g++ -std=c++20 -o output "part${PART}"/"chapter${CHAPTER}"/*.cpp -D CUSTOM
    else
        EXERCISE=$3
        g++ -std=c++20 -o output "part${PART}"/"chapter${CHAPTER}"/*.cpp -D "EXERCISE${EXERCISE}"
    fi
    ./output
fi
