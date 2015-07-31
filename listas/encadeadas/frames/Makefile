#   Autor: Lucas de Almeida Carotta

#	para compilar as listas encadeadas junto com o programa de testes
all: compile
	@gcc -o executable main.c list.o frames.o -Wall

#	para compilar apenas as listas encadeadas
compile:
	@gcc -o list.o -c list.c -Wall
	@gcc -o frames.o -c frames.c -Wall

#	para rodar o programa de testes
run:
	@./executable

#	para limpar o diretório do arquivo que contém as listas encadeadas
clean:
	@rm -r *.o

.PHONY:
	clean
