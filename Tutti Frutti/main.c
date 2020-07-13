#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
int const CANT_CATEGORIAS = 7, CANT_LETRAS = 26;

typedef struct {
    char nombre[50];
    int puntaje;
}Jugador;

typedef struct _BTNodo {
  char dato[100];
  int altura;
  struct _BTNodo *left;
  struct _BTNodo *right;
} BTNodo;

typedef BTNodo *BTree;

BTree agregar_dato(BTree arbol, char dato[]){
    if(arbol == NULL){
        arbol = malloc(sizeof(BTNodo));
        strcpy(arbol->dato,dato);
        arbol->altura = 0;
        arbol->right = NULL;
        arbol->left = NULL;
    }
    else{
        if(strcmp(dato,arbol->dato) > 0){
            arbol->right = agregar_dato(arbol->right,dato);
        }
        if(strcmp(dato,arbol->dato) < 0){
            arbol->left = agregar_dato(arbol->left,dato);
        }
    }
    return arbol;
}

BTree crear_arbol(BTree arbol,FILE* archivo){
        char aux[100];
        while(!feof(archivo)){
            fscanf(archivo,"%s",aux);
            arbol = agregar_dato(arbol,aux);
        }
        calcular_altura(arbol);
        int i=1;
        while(i){
            i=balanceo(arbol);
            calcular_altura(arbol);
        }
        return arbol;
}

void print_arbol(BTree arbol){
    if(arbol != NULL){
        printf("%s",arbol->dato);
        printf("%d\n",arbol->altura);
        print_arbol(arbol->left);
        print_arbol(arbol->right);
    }
}

int max(int a, int b){
    if(a == b) return a;
    else if(a > b) return a;
    else return b;
}

int calcular_altura(BTree arbol){
    if(arbol == NULL) return 0;
    arbol->altura = max(calcular_altura(arbol->left),calcular_altura(arbol->right)) + 1;
    return arbol->altura;
}

void case_LL(BTree arbol){
    BTree aux = malloc(sizeof(BTNodo));
    aux = arbol->left;
    char aux_dato[100];
    strcpy(aux_dato,arbol->dato);
    strcpy(arbol->dato,aux->dato);
    arbol->left=arbol->left->left;
    aux->left=aux->right;
    strcpy(aux->dato,aux_dato);
    aux->right=arbol->right;
    arbol->right=aux;

}

void case_LR(BTree arbol){
    BTree aux = malloc(sizeof(BTNodo));
    aux = arbol->left->right;
    arbol->left->right=arbol->left->right->left;
    aux->left=arbol->left;
    arbol->left=aux;
    case_LL(arbol);
}

void case_RR (BTree arbol){
    BTree aux = malloc(sizeof(BTNodo));
    aux = arbol->right;
    char aux_dato[100];
    strcpy(aux_dato,arbol->dato);
    strcpy(arbol->dato,aux->dato);
    arbol->right=arbol->right->right;
    aux->right=aux->left;
    strcpy(aux->dato,aux_dato);
    aux->left=arbol->left;
    arbol->left=aux;
}

void case_RL(BTree arbol){
    BTree aux = malloc(sizeof(BTNodo));
    aux = arbol->right->left;
    arbol->right->left=arbol->right->left->right;
    aux->right=arbol->right;
    arbol->right=aux;
    case_RR(arbol);
}

int balanceo (BTree arbol){///Esta función esta para que el árbol sea balanceado, arriba de esta función estan las distintas rotaciones
    if(arbol!=NULL){
        if(((arbol->left==NULL ? 0 : arbol->left->altura)-(arbol->right==NULL ? 0 : arbol->right->altura))>1){
            if(arbol->left->right==NULL || (arbol->left->right->left==NULL && arbol->left->right->right==NULL)){
                case_LL(arbol);
                return 1;}
            else{
                case_LR(arbol);
                return 1;}
        }
        if(((arbol->left==NULL ? 0 : arbol->left->altura)-(arbol->right==NULL ? 0 : arbol->right->altura))<-1){
            if(arbol->right->left==NULL || (arbol->right->left->right==NULL && arbol->right->left->left==NULL)){
                case_RR(arbol);
                return 1;}
            else{
                case_RL(arbol);
                return 1;}
        }
        balanceo(arbol->left);
        balanceo(arbol->right);
        return 0;
    }
    return 2;
}

int ingresar_cant_jug(){
    int cant_jugadores = 0;
    while(1){
        printf("Ingrese la cantidad de jugadores:\n");
        scanf("%d%*c",&cant_jugadores);
        if(cant_jugadores > 5 || cant_jugadores < 2){
            printf("Cantidad no admitida de jugadores\n");
        }
        else break;
    }
    return cant_jugadores;
}

int suma5(int pos_palabra,char lista_palabras[][100],int cant_jug){

    for(int i = 0;i < cant_jug; i++){
        if(strcmp(lista_palabras[i],lista_palabras[pos_palabra]) == 0 && i != pos_palabra){
            return 1;
        }
    }
    return 0;
}
int suma10(int pos_palabra,char lista_palabras[][100],int cant_jug){


    for(int i = 0;i < cant_jug; i++){
        if(strcmp(lista_palabras[i],lista_palabras[pos_palabra]) == 0 && i != pos_palabra){
            return 0;
        }
    }
    return 1;
}
int suma20(int pos_palabra,char lista_palabras[][100],int cant_jug){
    for(int i = 0;i < cant_jug; i++){
        if(strcmp(lista_palabras[i],"") != 0 && i != pos_palabra){
            return 0;
        }
    }
    return 1;
}

//Buscar en arbol
int palabra_valida(char palabra[100],BTree arbol){
    if(arbol == NULL) return 0;
    if(strcmp(palabra,arbol->dato) == 0) return 1;
    else if(strcmp(palabra,arbol->dato) < 0) return palabra_valida(palabra,arbol->left);
    else return palabra_valida(palabra,arbol->right);
}

void calcular_puntaje(Jugador *jug,int cant_jug, char resultados[][100],BTree lista_palabras_validas[],char letra){
    //for cada categoria
    for(int i = 0; i < CANT_CATEGORIAS; i++){

        char result_campo[cant_jug][100];

        for(int x = 0; x < cant_jug; x++){//for cada jugador
            strcpy(result_campo[x],resultados[x*7 + i]);
        }
        asignar_valores(result_campo,jug,cant_jug,lista_palabras_validas[i],letra);
    }
}

void asignar_valores(char result_campo[][100],Jugador* jug, int cant_jug, BTree palabras_validas,char letra){

    for(int i = 0; i<cant_jug ;i++){//checkear si es valida
        if(palabra_valida(result_campo[i],palabras_validas) == 0 || result_campo[i][0] != letra){
            strcpy(result_campo[i],"");
        }
    }
    for(int i = 0; i<cant_jug ;i++){
        if(strcmp(result_campo[i],"") != 0){//si la palabra es valida

            if(suma20(i,result_campo,cant_jug) == 1){
                jug[i].puntaje += 20;
            }
            else if(suma5(i,result_campo,cant_jug) == 1){
                jug[i].puntaje += 5;
            }
            else if(suma10(i,result_campo,cant_jug) == 1){
                jug[i].puntaje += 10;
            }
        }
    }
}

int check_victoria(Jugador* jug,int cant_jug){
    int cuantos_ganaron = 0;
    for(int i = 0; i < cant_jug; i++){
        if(jug[i].puntaje >= 200) return i;
    }
    return -1;
}

char letra_al_azar(){
    return  (rand()%26) + 65;
}

elegir_letra(char letras_elegidas[],int cant_letras_elegidas){
    char letra;
    if(cant_letras_elegidas == CANT_LETRAS-1){
        memset(letras_elegidas,-1,26*sizeof(char));
        cant_letras_elegidas = 0;
    }
    while(1){
        int aux = 0;
        letra = letra_al_azar();
        for(int i = 0;i<cant_letras_elegidas;i++){
            if(letra == letras_elegidas[i])aux = 1;
        }
        if(aux == 0){
            break;
        }
    }
    letras_elegidas[cant_letras_elegidas++] = letra;
    return cant_letras_elegidas;
 }

int main(){

    FILE* lista_archivos_palabras[CANT_CATEGORIAS];

    lista_archivos_palabras[0] = fopen("nombres.txt","r");
    lista_archivos_palabras[1] = fopen("colores.txt","r");
    lista_archivos_palabras[2] = fopen("animales.txt","r");
    lista_archivos_palabras[3] = fopen("comidas.txt","r");
    lista_archivos_palabras[4] = fopen("flores y plantas.txt","r");
    lista_archivos_palabras[5] = fopen("frutas.txt","r");
    lista_archivos_palabras[6] = fopen("paises.txt","r");

    BTree lista_palabras_validas[CANT_CATEGORIAS];

    for(int i = 0; i < CANT_CATEGORIAS;i++){
        lista_palabras_validas[i] = NULL;
        lista_palabras_validas[i] = crear_arbol(lista_palabras_validas[i],lista_archivos_palabras[i]);
    }

    //Cerrar archivos
    for(int i = 0; i < CANT_CATEGORIAS;i++){
        fclose(lista_archivos_palabras[i]);
    }

    ///con esta función imprimís cualquier arbol in order
    ///print_arbol(lista_palabras_validas[0]);

    //Ingresar cantidad de jugadores
    int cant_jugadores = ingresar_cant_jug();

    //Ingresar datos de Jugadores
    Jugador *jugadores = malloc(cant_jugadores*sizeof(Jugador));
    char nombre_jug[50];
    for(int i = 0; i<cant_jugadores; i++){
        printf("Ingrese el nombre del Jugador %d:\n",i+1);
        scanf("%s%*c",nombre_jug);
        strcpy(jugadores[i].nombre,nombre_jug);
        jugadores[i].puntaje = 0;
    }

    ///-------------------------------------------
    char letras_elegidas[26];
    memset(letras_elegidas,-1,26*sizeof(char));
    int cant_letras_elegidas = 0;
    srand(time(NULL));
    ///------------------------------------------


    //Comienzo del juego
    int numero_ronda = 0;
    while(1){
        system("cls");
        printf("Ronda %d\n\n",numero_ronda++);

        for(int i=0; i<cant_jugadores;i++){
            printf("El puntaje de %s es %d\n",jugadores[i].nombre,jugadores[i].puntaje);
        }
        printf("Letras que ya salieron:");
        for(int i = 0; i < cant_letras_elegidas;i++){
            printf("%c ",letras_elegidas[i]);
        }
        cant_letras_elegidas = elegir_letra(letras_elegidas,cant_letras_elegidas);
        printf("\nLetra seleccionada al azar: %c\n",letras_elegidas[cant_letras_elegidas - 1]);
        printf("Presiona enter una vez finalizada la ronda...\n");
        scanf("%*c");

        int pos = 0;
        char resultados[7*cant_jugadores] [100];

        for(int i = 0; i <cant_jugadores;i++){
            printf("%s ingresa tus resultados:\n",jugadores[i].nombre);

            printf("Ingresa el nombre:\n");
            scanf("%s%*c",resultados[pos++]);

            printf("Ingresa la comida:\n");
            scanf("%s%*c",resultados[pos++]);

            printf("Ingresa el pais/capital:\n");
            scanf("%s%*c",resultados[pos++]);

            printf("Ingresa la flor/planta:\n");
            scanf("%s%*c",resultados[pos++]);

            printf("Ingresa la fruta/semilla:\n");
            scanf("%s%*c",resultados[pos++]);

            printf("Ingresa el animal:\n");
            scanf("%s%*c",resultados[pos++]);

            printf("Ingresa el color:\n");
            scanf("%s%*c",resultados[pos++]);

        }
        calcular_puntaje(jugadores,cant_jugadores,resultados,lista_palabras_validas,letras_elegidas[cant_letras_elegidas-1]);

        //checkear si alguien gano
        int victoria = check_victoria(jugadores, cant_jugadores);
        if(victoria != -1){
            printf("El jugador %s ha ganado!!!",jugadores[victoria].nombre);
            break;
        }
    }
    return 0;
}


