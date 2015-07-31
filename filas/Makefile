#   Autor: Lucas de Almeida Carotta

#	nome do arquivo: Makefile

#	para compilar as listas encadeadas junto com o programa de testes
all: compile
	@gcc -o executable main.c queue.o -Wall

#	para compilar as estruturas necessárias
compile: list queue_tmp queue

#	para compilar apenas as listas encadeadas
list:
	@gcc -o list.o -c list.c -Wall

#	para compilar apenas as filas
queue_tmp:
	@gcc -o queue_tmp.o -c queue.c -Wall

#	irá linkar as duas bibliotecas previamente compiladas em um arquivo só
queue:
	@ar cr queue.o list.o queue_tmp.o

#	para rodar o programa de testes
run:
	@./executable

#	para limpar o diretório do arquivo que contém as estruturas
clean:
	@rm -r *.o

.PHONY:
	clean
