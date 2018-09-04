# Biblioteca de Grafos

Repositório de códigos criados para a disciplina de Teoria dos Grafos - 2018/2.

## Resultados do Primeiro Trabalho

Nos grafos as_graph e dblp foram executadas 1000 iterações de BFS e DFS, enquanto no grafo live_journal foram executadas apenas 10.

Abaixo se encontram os resultados obtidos e a média do tempo para cada iteração dos algoritmos.

|Grafo|Vértices|Arestas|Memória|Inicialização|BFS|DFS|
|-----|--------|-------|-------|-------------|---|---|
|as_graph Matriz|32385|46823|2,25 GB|932 ms|2920 ms|3105 ms|
|as_graph Lista|32385|46823|12 MB|26 ms|12 ms|20 ms|
|dblp Lista|1397510|5450815|558 MB|5110 ms|1342 ms|3292 ms|
|live_journal Lista|3997962|34614288|2,92 GB|21862 ms|6855 ms|21369 ms|
