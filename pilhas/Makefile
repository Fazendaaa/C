#   Autor: Lucas de Almeida Carotta

#	nome do arquivo: Makefile

#	para compilar as listas encadeadas junto com o programa de testes
all: compile
	@gcc -o executable main.c stack.o -Wall

#	para compilar as estruturas necessárias
compile: list stack_tmp stack

#	para compilar apenas as listas encadeadas
list:
	@gcc -o list.o -c list.c -Wall

#	para compilar apenas as pilhas
stack_tmp:
	@gcc -o stack_tmp.o -c stack.c -Wall

#	irá linkar as duas bibliotecas previamente compiladas em um arquivo só
stack:
	@ar cr stack.o list.o stack_tmp.o

#	para rodar o programa de testes
run:
	@./executable

#	para limpar o diretório do arquivo que contém as estruturas
clean:
	@rm -r *.o

.PHONY:
	clean
