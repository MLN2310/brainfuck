g++ main.cpp
cat test.txt | ./a.out | llc > assembly.s
clang assembly.s -o test.out
./test.out
echo ''