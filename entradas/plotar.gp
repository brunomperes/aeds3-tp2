NomeArq1 = 'gerado.txt'
NomeEixoX = "X"
NomeEixoY = "Y"
NomeArqSaida = "gerado.eps"
TituloGrafico = "Polígono tp2 generated"

set terminal postscript eps 28 enhanced color
set style fill solid 1.00 border
set encoding utf8
#Nome do arquivo de saída
set output NomeArqSaida

set style fill solid 1.00 border

#Título do gráfico no arquivo
set title TituloGrafico

#Alcance dos eixos x e y são os valores máximos lidos
set xrange[0:]
set yrange[:]

#Título dos eixos
set xlabel NomeEixoX
set ylabel NomeEixoY

#Arquivo de entrada = gerado.txt, usando a coluna 1 e 2 do arquivo
plot NomeArq1 using 1:2 notitle with linespoints pointsize 0.4 pt 7

#Para dar título às linhas plotadas: title
#Para plotar mais de uma linha
#plot 'gerado.txt' using 1:2 title 'tempo de execucao' with linespoints pointsize 2.0 pt 4, 'gerado.txt' using 3:4 title 'tempo de usuario' with linespoints pointsize 2.0 pt 8
