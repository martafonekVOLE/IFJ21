# Author: Martin Pech <xpechm00@stud.fit.vutbr.cz>
PROJECT = ifj21

CC = gcc
CFLAGS = -std=c99 -Werror -Wall -Wextra -pedantic
.PHONY: scanner default help

# Cíl default zkompiluje všechny jednotlivé podsekce 
#default: scanner codegen syntax

default: 
	$(CC) -o ifj21_compiler scanner.c charAppender.c symtable.c tabstack.c codegen.c syntaktick.c semantika.c zasobnik.c typeZas.c

# Podsekce: Scanner
# Sestaví soubor ifj21_scanner ze spustitelných souborů .o
# K opakovanému přeložení dojde vždy, když se změní některý ze závislých souborů
scanner: scanner.o charAppender.o scanner_test.o
	$(CC) scanner.o charAppender.o scanner_test.o -o $(PROJECT)_scanner
	-rm -f *.o 

scanner.o: scanner.c
	$(CC) -c scanner.c

charAppender.o: charAppender.c
	$(CC) -c charAppender.c

scanner_test.o: scanner_test.c
	$(CC) -c scanner_test.c

.PHONY: cleanScanner
cleanScanner: 
	rm $(PROJECT)_scanner

#Podsekce: Stack tabulek 
#Sestaví ifj21_tabstack - test bench pro stack
tabstack: symtable.o tabstack.o tabstack-test.o 
	$(CC) -g symtable.o tabstack.o tabstack-test.o -o $(PROJECT)_tabstack
	-rm -f *.o

tabstack-test.o: tabstack-test.c 
	$(CC) -c tabstack-test.c 

tabstack.o: tabstack.c 
	$(CC) -c tabstack.c 

clean_tabstack:
	rm $(PROJECT)_tabstack

#Podsekce: Symtable
#Sestaví soubor ifj21_symtable - spustitelný soubor je test bench
symtable: symtable.o symtable-test.o
	$(CC) symtable.o symtable-test.o -o $(PROJECT)_symtable
	-rm -f *.o

symtable-test.o: symtable-test.c
	$(CC) -c symtable-test.c

symtable.o: symtable.c
	$(CC) -c symtable.c

clean_symtable:
	rm $(PROJECT)_symtable

# Podsekce: Codegen
# Sestaví soubor ifj21_codegen ze spustitelných souborů .o
# TODO: přidat závislosti
codegen: 
	$(CC) test.c -o $(PROJECT)_codegen

.PHONY: cleanCodegen
cleanCodegen:
	rm $(PROJECT)_codegen

codegenTest:
	./$(PROJECT)_codegen

codegenTestFile:
	./$(PROJECT)_codegen > codegenOutput.ifjcode

codegenInterpret:
	./$(PROJECT)_codegen > codegenOutput.ifjcode
	clear
	./ic21int codegenOutput.ifjcode


# Podsekce: SyntaxAnalyzer
# Sestaví soubor ifj21_syntax ze spustitelnách souborů .o
# TODO: přidat závislosti
syntax: syntaktick.o scanner.o charAppender.o semantika.o
	$(CC) syntaktick.o scanner.o charAppender.o semantika.o -o $(PROJECT)_syntax
	-rm -f *.o

syntaktick.o: syntaktick.c syntaktick.h
	$(CC) -c syntaktick.c syntaktick.h
	
semantika.o: semantika.c
	$(CC) -c semantika.c 
#	printf "\nsyntax neobsahuje žádné soubory!\n"

.PHONY: cleanSyntax
cleanSyntax: 
	rm $(PROJECT)_syntax

# Sekce: Help
# Vypíše všechny možné céle pro Make
help: 
	printf "\n\n\n\n\t Make targets: \n-----------------------------\n default:\tzkompiluje všechny jednotlivé podsekce\n scanner:\tsestaví soubor ifj21_scanner\n cleanScanner:\tuklidí soubory po 'scanner'\n codegen:\tsestaví soubor ifj21_codegen\n cleanCodegen:\tuklidí soubory po 'codegen'\n syntax:\tsestaví soubor ifj21_syntax\n cleanSyntax:\tuklidí soubory po 'syntax'\n clean:\t\tsmaže všechny spustitelné soubory\n help:\t\tvypíše nápovědu\n\n"


# Sekce: Clean
# Smaže všechny spustitelné soubory
clean:
	-rm -f $(PROJECT)_scanner
	-rm -f $(PROJECT)_codegen
	-rm -f $(PROJECT)_syntax
	-rm -f $(PROJECT)_symtable
	-rm -f $(PROJECT)_tabstack
	-rm -f $(PROJECT)_compiler
	-rm -rf *.o *h.gch