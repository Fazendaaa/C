#   Autor: Lucas de Almeida Carotta

#	nome do arquivo: Makefile

#	para compilar as listas encadeadas junto com o programa de testes
all: compile
	@gcc -o executable main.c clist.o -Wall

#	para compilar apenas as listas encadeadas
compile:
	@gcc -o clist.o -c clist.c -Wall

#	para rodar o programa de testes
run:
	@./executable

#	para limpar o diretório do arquivo que contém as estruturas
clean:
	@rm -r *.o

.PHONY:
	clean
