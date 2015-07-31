#   Autor: Lucas de Almeida Carotta

#	nome do arquivo: Makefile

#	para compilar as listas encadeadas junto com o programa de testes
all: compile
	@gcc -o executable main.c hash.o -Wall

#	compila todos os arquivos necessários para criar a biblioteca
compile: list chtbl hash

#	para compilar apenas as listas encadeadas
list:
	@gcc -o list.o -c list.c -Wall

#	para compilar a tabela hashing encadeada
chtbl:
	@gcc -o chtbl.o -c chtbl.c -Wall

#	irá linkar as duas bibliotecas previamente compiladas em um arquivo só
hash:
	@ar cr hash.o list.o chtbl.o

#	para rodar o programa de testes
run:
	@./executable

#	para limpar o diretório do arquivo que contém as estruturas
clean:
	@rm -r *.o

.PHONY:
	clean
