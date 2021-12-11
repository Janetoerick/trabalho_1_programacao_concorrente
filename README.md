# trabalho-1---programa-o-concorrente

Esse trabalho tem como objetivo analisar o quanto um programa concorrente é mais efetivo do que um programa sequencial em questão de tempo de
execução. Para esse experimento foi feita a construção de duas classes, na qual as duas fazem multiplicação de matrizes, porém uma trabalha
de forma sequencial e a outra de forma concorrente. As matrizes usadas para os calculos estão localizadas na pasta "matrizes", tendo matrizes
com dimensões quadraticas, sempre em conjunto de A e B.

Para fazer o calculo da matriz basta escrever:

" $ <<programa>> 4 S "

* O número dado na linha de comando representa a quantidade de dimensões que as matrizes deverão ter (o programa irá pegar automaticamente 
no exemplo acima as matrizes dos arquivos A4x4.txt e B4x4txt localizados na pasta "matrizes").
* A letra localizada após o número diz ao algoritmo de qual forma deseja utiliza-lo, de forma sequencial (S) ou de forma concorrente (C).


Após a execução será salvo a matriz resultante da multiplicação na pasta "matrizes_resultado". Enquanto que o tempo de execução gasto
estará registrado na pasta "tempos", apresentando a lista de tempo de 20 execuções e também o maior tempo registrado, menor tempo registrado,
a média de todos os tempos e o desvio padrão.
