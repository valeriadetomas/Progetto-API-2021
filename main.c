#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 15
#define MAX_LINE_LENGTH 2500
#define MAX_COST 4294967295

/**********************************************************
                        DATA TYPES
**********************************************************/

typedef enum {false, true} boolean;

typedef struct node{
    int index;
    long int shortest_path;
}node;

/**********************************************************
                        GLOBAL VARIABLES
**********************************************************/

int d, k, current_index = -1;
char buffer[MAX_LINE_LENGTH];
long int **matrix;
char command[MAX_COMMAND_LENGTH];
node* array;

/**********************************************************
                        MAX-HEAP FUNCTIONS
**********************************************************/

//returns the index of the get_left_index child of the node with index=node_index
int get_left_index(int node_index){
    return 2*node_index + 1;
}

//returns the index of the get_right_index child of the node with index=node_index
int get_right_index(int node_index){
    return 2*node_index + 2;
}

void swap (node* n1, node* n2){
    node tmp = *n1;
    *n1 = *n2;
    *n2 = tmp;
}

void max_heapify(int i){
    int left, right, max;

    left = get_left_index(i);
    right = get_right_index(i);

    //check on the left child
    if (left < k && array[left].shortest_path > array[i].shortest_path){
        max = left;
    } else {
        max = i;
    }

    //check on the right child
    if (right < k && array[right].shortest_path > array[max].shortest_path)
        max = right;

    if (max != i){
        swap(&array[max], &array[i]);
        max_heapify(max);
    }
}

void build_max_heap(){
    int i;
    for (i = k/2; i >= 0; i--){
        max_heapify(i);
    }
}

/********************************************************
                        GENERIC FUNCTIONS
*********************************************************/
long int shortest_path(long int **graph, int start){
    int i, j, cont, next = 0;
    long int paths_sum = 0, min, distance[d];
    int visited[d];
    for (i=0; i<d; i++){
        visited[i] = 0;
        for (j = 0; j < d; j++) {
            if (graph[i][j] == 0)
                graph[i][j] = MAX_COST*d;
        }
        distance[i] = graph[start][i];
    }
    visited[start] = 1;
    distance[start] = 0;    //non considero la distanza del nodo di partenza

    for (cont = 1; cont < d-1; cont ++){
        min = MAX_COST*d;
        //CASO 1: nodo direttamente connesso al nodo che sto considerando
        for (i=0; i<d; i++){
            if (distance[i]<min && visited[i]!=1){
                min = distance[i];
                next = i;
            }

        }
        visited[next] = 1; //marco il nodo come visitato
        //CASO 2: nodo non direttamente connesso al nodo che sto considerando
        for (i=0; i<d; i++){
            if (visited[i]!=1){
                if (graph[next][i] != MAX_COST*d && distance[i] > (graph[next][i] + min)){
                    distance[i] = graph[next][i] + min;
                }
            }
        }
    }
    for (i = 0; i<d; i++){
        paths_sum += distance[i] == MAX_COST*d ? 0 : distance[i];
    }
    return paths_sum;
}
long int read_graph() {
    long int min_distance;
    boolean allzero=true;
    int i, j;
    char* end;
    //Incremento l'indice del grafo che sto leggendo
    current_index++;
    for (i = 0; i < d; i++) {
        if (fgets(buffer, MAX_LINE_LENGTH, stdin) == NULL)
            return 0;
        matrix[i][0] = strtol(buffer, &end, 10);
        for (j = 1; j < d; j++){
            matrix[i][j] = strtol(end+1, &end, 10);
            if (i==0 && matrix[i][j]!=0)
                allzero = false;
        }
    }

    if (allzero) min_distance = 0;
    else min_distance = shortest_path(matrix, 0);

    return min_distance;
}


void handle_add_graph(){
    long int shortest_path = read_graph();
    if (current_index == 0)
        array = (node*) malloc(sizeof (node) * k);
    //CASO 1: aggiungo l'elemento all'array, ma il numero di grafi forniti in input è ancora minore di k
    if (current_index < k-1) {
        array[current_index].shortest_path = shortest_path;
        array[current_index].index = current_index;
        return;
    }

    //CASO 2: mi è apppena stato fornito il k-esimo grafo: lo aggiungo all'array e dall'array costruisco il max-heap. Poi distruggo l'array
    if (current_index == k-1){
        array[current_index].shortest_path = shortest_path;
        array[current_index].index = current_index;
        build_max_heap();
        return;
    }

    //CASO 3: mi sono già stati forniti più di k grafi in precedenza. Verifico se il nuovo grafo rientra nei topk
    if (current_index >= k){
        if (array[0].shortest_path > shortest_path){
            array[0].index = current_index;
            array[0].shortest_path = shortest_path;
            max_heapify(0);
        }
    }
}

void print(){
    int i;
    for (i = 0; i < k && i <= current_index; i++){
        if (i!= k-1 && i != current_index)
            printf("%d ", array[i].index);
        else
            printf("%d\n", array[i].index);
    }

}

void handle_top_k() {
    if (current_index == -1) {
        printf("\n");
        return;
    }
    print();
}

boolean parse_command(){
    if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
        return false;

    if (command[0] == 'A'){
        handle_add_graph();
        return true;
    }
    else if (command[0] == 'T'){
        handle_top_k();
        return true;
    }
    else
        return false;
}

/**********************************************************
                           MAIN
**********************************************************/

int main() {
    int i;
    boolean read;
    boolean ok = scanf("%d %d\n", &d, &k);
    matrix = (long int **) malloc(d * sizeof(long int *));
    for (i = 0; i < d; i++) {
        matrix[i] = (long int *) malloc(d * sizeof(long int));
    }
    do {
        read = parse_command();
    } while (read && ok);

    for (i = 0; i < d; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(array);
    return 0;
}