#set -x
BUILDDIR=build
TESTDIR=tests
TEMPFILE=output.tmp

if [ -f ${BUILDDIR}/count ]; then
    for FILE in $(ls tests/ | grep "^test"); do
        ${TESTDIR}/${FILE}/test.sh ${BUILDDIR} ${TESTDIR} ${TEMPFILE} &>/dev/null
        if ! diff ${TEMPFILE} ${TESTDIR}/${FILE}/out &>/dev/null; then
            echo "Failed test in ${FILE}"
        else
            echo "Passed test in ${FILE}"
        fi;
    done;
    rm ${TEMPFILE}
else
    echo "Check that build/count exists"
fi
