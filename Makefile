etapa1: lex.yy.c main.c hash.c
	gcc -o etapa1 lex.yy.c
lex.yy.c: scanner.l
	lex scanner.l
clean:
	rm lex.yy.c etapa1
run:
	./etapa1 test_cases
test:
	./test.sh