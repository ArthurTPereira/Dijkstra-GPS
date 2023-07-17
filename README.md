# Segundo Trabalho de TBO
Programa que encontra o menor caminho em um grafo, com atualizações de velocidade das vias.

# Arquivos de entrada
O arquivo de entrada é um grafo G(V,E,ω), representando o mapa e os custos de deslocamento em **metros**, os nós de origem e destino, a velocidade média inicial das rodovias, e as atualizações das velocidades médias, em **km/h**, nos determinados instantes de tempo, em **segundos**, como o seguinte exemplo:
```
7;20    -- Número de nós e vértices
1;7     -- Origem e Destino
40      -- Velocidade inicial das vias
1;2;250 -- Vértices
2;1;250
1;3;250
3;1;250
1;4;500
4;1;500
2;4;200
3;4;300
4;5;300
4;6;200
2;5;500
5;2;500
3;6;500
6;3;500
6;7;250
7;6;250
5;7;250
7;5;250
4;7;500
7;4;500
40;6;7;10 -- Início das atualizações
```

# Utilização
Para utilizar e compilar o código, deve ser utilizado o makefile, incluso nos
arquivos. O comando ```make``` irá gerar o executável do programa, chamado ```trab2```. 

# Execução
Para executar o programa, execute o seguinte comando:

```
./trab2 <arquivo_de_entrada.csv>
```

