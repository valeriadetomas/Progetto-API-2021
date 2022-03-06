# Prova Finale di Algoritmi e Strutture Dati a.a. 2020-2021
The objective of the project is the management of a classification between weighted direct graphs.
Moreover the goal is to keep track of the k 'best' graphs through a ranking by optimizing running time and memory usage.

# Input commands
The program can receive in input the following commands:
• AggiungiGrafo [adjacency matrix] 
• TopK

The first line of the file must be composed by two parameters separated by a space:
the parameter d that indicates the number of nodes of the graphs in the file and k which specify the length of the ranking.

The **AggiungiGrafo[]** command adds a graph to those considered to draw up the ranking. It is followed by the adjacency matrix of the graph itself, printed one line for each line, with the elements separated by commas.

The **TopK** command prints the integer indices of k graphs having the smallest k values. The value of a graph is calculated by the sum of the shortest paths between node 0 and all the other nodes of the graph.
The top k graphs in the ranking must be printed as follows: the k integer indices are printed, on a single line, separated by a space, in any order.

#Test cases
The implementation has been tested with several test, in order to evaluate the efficiency in terms of running time and memory usage. The tests used for debugging are available on this repository. The project has been then evaluated through private tests by a special platform capable of determining the memory occupied and the execution time of the program.
