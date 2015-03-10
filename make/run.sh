GDB=gdb
VALGRIND=valgrind

if [ $# -eq 1 ]; then
    if [ $1 = $VALGRIND ]; then
        debug="valgrind --track-origins=yes --leak-check=full --log-file=valgrind.log"
    else if [ $1 = $GDB ]; then
        debug="gdb --args"
    fi; fi
fi

$debug ./ssp -r
