#include<stdio.h>  // Algoritmo feito para uma representação de grafos por matriz de adjacencia.
#include<stdlib.h> // A matriz de Adj possui limitacoes para representar multiplas aresta paralelas
                   
typedef struct{
    int vertice;
    int **matriz;
} grafo;

typedef struct{
    int **directed;

} direcao;

direcao *criarDirecao(int n){
    direcao *direc = new direcao;
    direc -> directed = (int **)malloc(n * sizeof(int*));

    for(int i = 0; i< n; i++){
        direc ->directed[i] = (int *) calloc(n, sizeof(int));
    }

    return direc;

}

grafo *criarGrafo(int n){
    grafo *g = new grafo;


    g->vertice = n;

    g->matriz = (int **)malloc(n * sizeof(int*));


    for (int i = 0; i < n; i++) {

        g->matriz[i] = (int *)calloc(n, sizeof(int));
    }

    return g;
}

void mostrarGrafo(grafo *g){
    printf("O Grafo:\n");

    for(int i=0; i < g->vertice; i++){

        for (int j = 0; j < g ->vertice; j++) { 
            printf(" %d ", g->matriz[i][j]); 
        }
        printf("\n");
    }
}

void liberarGrafo(grafo *g, direcao *direc){
    for(int i=0;i<g->vertice;i++){
        free(g->matriz[i]);
        free(direc -> directed[i]);
    }

    free( direc -> directed);
    free( direc);
    free(g->matriz);
    free(g);
}

void adicionarAresta(grafo *g, int origem, int destino,int direcionado, direcao *direc){
    g ->matriz[origem][destino] = 1;

    direc -> directed[origem][destino] = direcionado;


    if(direcionado == 0){

        g->matriz[destino][origem] = 1;
    }
}

void removerAresta(grafo *g,int origem, int destino, direcao *direc){

    if (g->matriz[origem][destino] == 0) {
        printf("ESSA ARESTA NAO EXISTE!\n");
        return;
    }

    g->matriz[origem][destino] = 0;

    if ( direc -> directed[origem][destino] == 0) {

        g -> matriz[destino][origem] = 0;
    }
    
}

void consultarAresta(grafo *g, int origem, int destino){

    if(g->matriz[origem][destino] == 1){
        printf("EXISTE UMA ARESTA ENTRE Os VÉRTICEs %d E %d!\n",origem+1,destino+1);
    }
    else{
        printf("NÃO EXISTE NENHUMA ARESTA ENTRE Os VÉRTICEs %d E %d!\n",origem+1,destino+1);
    }
    
}

void grauVertice(grafo *g, int vertice){

    int conSaida = 0;
    int conEntrada = 0;
    for( int i = 0; i < g -> vertice; i++){
        conSaida+= g->matriz[vertice][i];
        conEntrada += g -> matriz [i][vertice];
    }

    printf("\nGRAU DE ENTRADA E SAIDA DO VERTICE %d:\n", vertice + 1);

    printf("Grau Saida: %d\nGrau Entrada: %d\n", conSaida, conEntrada);
    
}

int main(){
    system("cls");
    int numVertices;
    int origem, destino, direcionado;
    int opcao;
    grafo *g;
    direcao *direc;

    printf("DIGITE A QUANTIDADE DE VERTICES DO GRAFO: ");
    scanf("%d",&numVertices);

    g = criarGrafo(numVertices);
    direc = criarDirecao(numVertices);

    do {
        system("cls");

        printf("\n==============================\n");
        printf("          MENU GRAFO\n");
        printf("==============================\n");
        printf("1 - Adicionar aresta\n2 - Remover aresta\n3 - Mostrar grafo\n4 - Consultar aresta\n5 - Consultar Grau do Vertice\n0 - Sair\n");
        printf("==============================\n");
        printf("NUMERO DE VÉRTICES: %d\n",numVertices);

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);


        switch (opcao) {

            case 1:

                printf("\n --- ADICIONAR ARESTA ---\n");

                printf("VERTICE DE ORIGEM: ");
                scanf("%d", &origem);

                printf("VERTICE DE DESTINO: ");
                scanf("%d", &destino);

                printf("A ARESTA É DIRECIONADA? (1 - SIM | 0 - NAO): ");
                scanf("%d", &direcionado);

                adicionarAresta(g , origem - 1,destino - 1,direcionado, direc);
                printf("\nARESTA ADICIONADA!\n");
                break;


            case 2:

                printf("\n--- REMOVER ARESTA ---\n");

                printf("VERTICE DE ORIGEM: ");
                scanf("%d", &origem);

                printf("VERTICE DE DESTINO: ");
                scanf("%d", &destino);

                removerAresta(g, origem - 1, destino - 1, direc);
                printf("\nAresta removida!\n");
                break;


            case 3:
                mostrarGrafo(g);
                break;

            case 4:

                printf("\n--- CONSULTAR ARESTA ---\n");

                printf("VERTICE DE ORIGEM: ");
                scanf("%d", &origem);

                printf("VERTICE DE DESTINO: ");
                scanf("%d", &destino);

                consultarAresta( g,origem - 1,destino - 1);

                break;

            case 5:
            printf("Digite o vertice a ser escolhido: ");
            scanf("%d", &origem);
            grauVertice(g, origem-1);
            break;


            case 0:
                printf("\nSaindo...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");

        }

        system("Pause");

    } while (opcao != 0);

    liberarGrafo(g, direc);

    return 0;

}
