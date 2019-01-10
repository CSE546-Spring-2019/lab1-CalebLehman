#set -x
for file in $(ls tests/ | grep "^test"); do #"tests/test1"; do
    ./tests/${file}/test.sh &>/dev/null
    if ! diff temp tests/${file}/out &>/dev/null; then
        echo "Failed test in ${file}"
    else
        echo "Passed test in ${file}"
    fi;
done;
rm temp
