flex ./lexicale.l
bison -d -v ./synta.y
gcc -o test.exe lex.yy.c synta.tab.c -lfl -ly 