#set -e
pintos -v -k --qemu $2 --filesys-size=4 --swap-size=4 -p build/tests/filesys/base/$1 -a $1  -- -q -f run $1 $3

#pintos -v -k -gdb --qemu  --filesys-size=2 -p tests/filesys/base/syn-write -a syn-write -p tests/filesys/base/child-syn-wrt -a child-syn-wrt --swap-size=4 -- -q  -f run syn-write
