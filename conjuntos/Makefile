#   Autor: Lucas de Almeida Carotta

#	nome do arquivo: Makefile

#	para compilar as listas encadeadas junto com o programa de testes
all: compile
	@gcc -o executable main.c set.o -Wall

#	para compilar as estruturas necessárias
compile: list set_tmp set

#	para compilar apenas as listas encadeadas
list:
	@gcc -o list.o -c list.c -Wall

#	para compilar apenas os conjuntos
set_tmp:
	@gcc -o set_tmp.o -c set.c -Wall

#	irá linkar as duas bibliotecas previamente compiladas em um arquivo só
set:
	@ar cr set.o list.o set_tmp.o

#	para rodar o programa de testes
run:
	@./executable

#	para limpar o diretório do arquivo que contém as estruturas
clean:
	@rm -r *.o

.PHONY:
	clean
