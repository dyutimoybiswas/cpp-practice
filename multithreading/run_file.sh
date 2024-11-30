
# Provide <file_name.cpp> as argument while running this script.
g++ -std=c++20 -O1 -pthread -o output $1

# If command line values passed, run manually.
if [[ $# -gt 1 && $2 != "manual" ]] || [[ $# -eq 1 ]]; then
    ./output
fi
