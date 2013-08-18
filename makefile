######################################################################
# TRABALHO PRÁTICO 1 - Stable Marriage with Incomplete Lists Problem
# Algoritmos e Estruturas de Dados III
#
# Bruno Maciel Peres
# brunomperes@dcc.ufmg.br
######################################################################


# Especifica o compilador
CC = gcc

# Especifica as opções do compilador, habilita aviso sobre erros
CFLAGS = -Wall -g

# Comando terminal para limpar sem confirmação
RM = rm -f

# Lista dos ficheiros (arquivos) objetos necessários para o programa final
OBJS = main.o lista.o grafo.o io.o heuristica1.o heuristica2.o timerlinux.o poligono.o ordena.o tempo.o

# Nome do executável
MAIN = tp2

# Compilação do programa e passos das ligações de dependências
$(MAIN): $(OBJS)
	@echo ""
	@echo " --- COMPILANDO PROGRAMA ---"
	@$(CC) $(CFLAGS) $(OBJS) -lm -o $(MAIN)
	@echo ""

%.o: %.c %.h
	@echo ""
	@echo " --- COMPILANDO OBJETO \"$@\""
	@$(CC) $(CFLAGS) $< -c 

clean:
	$(RM) $(MAIN) *.o
	clear

run: $(MAIN)
	./$(MAIN)
