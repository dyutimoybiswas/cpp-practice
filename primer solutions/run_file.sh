
if [ $# -lt 3 ]; then
    # Special case - chapter 1
    if [ $1 -eq 1 ]; then
        if [ $# -lt 2 ]; then
            echo "Too few arguments. Please specify exercise no."
        elif [ $2 = CUSTOM ]; then
            g++ -std=c++20 -o output chapter1/*.cpp -D CUSTOM -g
            ./output
        else
            EXERCISE=$2
            g++ -std=c++20 -o output chapter1/*.cpp -D "EXERCISE${EXERCISE} " -g
            ./output
        fi
    else
        echo "Too few arguments. Please specify part no, chapter no and exercise no."
    fi
else
    PART=$1
    CHAPTER=$2
    if [ $3 = CUSTOM ]; then
        g++ -std=c++20 -o output "part${PART}"/"chapter${CHAPTER}"/*.cpp -D CUSTOM -g
    else
        EXERCISE=$3
        g++ -std=c++20 -o output "part${PART}"/"chapter${CHAPTER}"/*.cpp -D "EXERCISE${EXERCISE}" -g
    fi
    ./output
fi
