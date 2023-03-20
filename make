#/bin/sh

cd build/ && make
cd ..

BINARY=rtype

# if [ $# -eq 0 ]
# then
    # ./$BINARY
# else
    # valgrind ./$BINARY
# fi