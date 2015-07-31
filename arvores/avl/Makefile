#   Autor: Lucas de Almeida Carotta

#	nome do arquivo: Makefile

#	para compilar as listas encadeadas junto com o programa de testes
all: compile
	@gcc -o executable main.c tree.o -Wall

#	compila todos os arquivos necessários para criar a biblioteca
compile: bitree bistree tree

#	para compilar apenas a árvore de busca binária
bistree:
	@gcc -o bistree.o -c bistree.c -Wall

#	para compilar apenas a árvore binária
bitree:
	@gcc -o bitree.o -c bitree.c -Wall

#	irá linkar as duas bibliotecas previamente compiladas em um arquivo só
tree:
	@ar cr tree.o bitree.o bistree.o

#	para rodar o programa de testes
run:
	@./executable

#	para limpar o diretório do arquivo que contém as estruturas
clean:
	@rm -r *.o

.PHONY:
	clean
