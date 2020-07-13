#include <stdio.h>
#include <stdlib.h>
#include "a.h"
#define AGUA 0
#define AVERIADO 1
#define HUNDIDO 2
#define NO_VALIDO 3
#define borrar system("cls")
#define pausa system("pause")

int verif_vacio(int x,int y,int tablero[SIZE][SIZE]){
  if(tablero[x][y] != 0){
    return 1;
    }
    //Horizontal
    if(x>0 && tablero[x-1][y] != 0){
      return 1;
    }
    if(x<9 && tablero[x+1][y] != 0){
      return 1;
    }
    //Vertical
    if(y>0 && tablero[x][y-1] != 0){
      return 1;
    }
    if(x<9 && tablero[x][y+1] != 0){
      return 1;
    }
    //Diagonal
    if(x>0 && y>0 && tablero[x-1][y-1] != 0){
      return 1;
    }
    if(x<9 && y<9 && tablero[x+1][y+1] != 0){
      return 1;
    }
    if(x<9 && y>0 && tablero[x+1][y-1] != 0){
      return 1;
    }
    if(x>0 && y<9 && tablero[x-1][y+1] != 0){
      return 1;
    }
    return 0;
  }

int anadir_barco(int id, int x_inic,int y_inic,int x_fin,int y_fin,int tablero[SIZE][SIZE],int largo){

    //Detectar barcos en diagonales
    if(x_inic != x_fin && y_inic != y_fin)
        return 1;
    //Ordenar coordenadas
    if(x_inic> x_fin){
        int aux = x_inic;
        x_inic = x_fin;
        x_fin = aux;
    }
    if(y_inic> y_fin){
        int aux = y_inic;
        y_inic = y_fin;
        y_fin = aux;
    }
    //Detectar largo incorrecto
    if(x_fin - x_inic + 1 != largo && y_fin - y_inic + 1 != largo)
        return 1;
    //Detectar si todos los casilleros que rodean al barco estan vacios
    if(y_inic == y_fin){//Caso horizontal
        for(int x = x_inic; x <= x_fin; x++){
            if(verif_vacio(x ,y_inic,tablero)){
                return 1;
            }

        }
        //Colocar barco en tablero auxiliar
        for(int x = x_inic; x <= x_fin; x++){
            tablero[x][y_inic] = id;
        }
    }
    else{//Caso vertical
        for(int y = y_inic; y <= y_fin; y++){
            if(verif_vacio( x_inic, y, tablero)){
                return 1;
            }
        }
        //Colocar barco en tablero auxiliar
        for(int y = y_inic; y <= y_fin; y++){
            tablero[x_inic][y] = id;
        }
    }
    return 0;
  }

void imprimir_tablero_bien_croto(int tablero[SIZE][SIZE]){
  printf("Tablero:\n");
  int i;

        for(i = 0;i<SIZE;i++){
           printf("\t %d \t",9-i);
           for(int q = 0;q<SIZE;q++){
             printf("%d ",tablero[q][i]);
            }
            printf("\n");
    }
      printf("\n\n\t   \t");
   for(i=0;i<SIZE;i++){
            printf("%d ",i);
        }
    printf("\n");
  }


nodo_barco* buscar_barco_por_id(nodo_barco* list_barco,int pos){
    nodo_barco* barco_buscado = list_barco;
    for(int i = 0; i < pos && barco_buscado != NULL; i++){
        barco_buscado = barco_buscado->sig;
    }
    return barco_buscado;
}

fila* crear_tablero(int tab_inic[SIZE][SIZE], nodo_barco * list_bar){

    fila*aux = malloc(sizeof(fila));
    fila*tablero = aux;
    casillero* ca_aux;

    for(int i = 0; i < SIZE; i++){

        aux->casillero = NULL;
        aux->sig = NULL;

        for(int q = 0; q < SIZE; q++){
            if(tab_inic[q][i] != 0){//Si el casillero esta ocupado
                if(aux->casillero == NULL){
                    aux->casillero = malloc(sizeof(casillero));
                    aux->casillero->barco = buscar_barco_por_id(list_bar,tab_inic[q][i]);//agrego el barco con ese id
                    aux->casillero->barco->largo++;
                    aux->casillero->disparo=0;
                    aux->casillero->x = q;
                    aux->casillero->sig = NULL;
                    ca_aux = aux->casillero;
                }
                else{
                    ca_aux->sig=malloc(sizeof(casillero));
                    ca_aux->sig->barco = buscar_barco_por_id(list_bar,tab_inic[q][i]);//agrego el barco con ese id
                    ca_aux->barco->largo++;
                    ca_aux->sig->disparo=0;
                    ca_aux->sig->x = q;
                    ca_aux->sig->sig=NULL;
                    ca_aux = ca_aux->sig;
                }
            }
        }
        if(i<SIZE - 1){//Para que ultima fila->sig = NULL
            aux->sig = malloc(sizeof(fila));
        }
        aux=aux->sig;
    }
    return tablero;
}

nodo_barco* crear_lista_barcos(nodo_barco* lista){
  nodo_barco* nuevo_barco = malloc(sizeof(nodo_barco));
  nuevo_barco->largo = 0;
  nuevo_barco->sig = NULL;
  lista = nuevo_barco;
  for(int i = 0; i < CANT_BARCOS; i++){
    nuevo_barco->sig = malloc(sizeof(nodo_barco));
    nuevo_barco->sig->largo = 0;
    nuevo_barco->sig->sig = NULL;
    nuevo_barco = nuevo_barco->sig;
  }
  return lista;
}

int disparo(int x, int y,fila* tablero,nodo_barco* list_barco){

    if(x < 0 || x > 9 || y < 0 || y > 9)
        return NO_VALIDO;

    fila* aux = tablero;
    for(int q=0;q<y;q++){
        aux = aux->sig;
    }
    casillero* ca = aux->casillero;
    for(int z=0;z<=x;z++){

        if(ca->x == x){
            if(ca->barco == NULL || ca->disparo == 1)
                return NO_VALIDO;
            ca->disparo = 1;
            if(ca->barco->largo == 1){

                return HUNDIDO;
            }
            else{
                ca->barco->largo--;
                return AVERIADO;
            }
            ca->disparo = 1;
        }
        if(ca->sig == NULL) break;
        ca = ca->sig;
    }
    ca->sig=malloc(sizeof(casillero));
    ca->sig = NULL;
    ca->barco = NULL;
    return AGUA;
}

void ingresar_barcos(int tablero[SIZE][SIZE]){
    int xi,yi,xf,yf,id = 1;

    printf("Ingrese la posicion de sus barcos mi capitán\n");

    //Ingresar largo 2
    for(int cont = id + 1; id < cont;id++){//cont = id + cant barco
        imprimir_tablero_bien_croto(tablero);
        printf("barco largo 2\n\n");

        printf("\tIngrese coordenadas de inicio\n");
        printf("\tx:");
        scanf("%d",&xi);
        printf("\ty:");
        scanf("%d",&yi);

        printf("\tIngrese coordenadas de fin\n");
        printf("\tx:");
        scanf("%d",&xf);
        printf("\ty:");
        scanf("%d",&yf);

        if(anadir_barco(id, xi,9-yi,xf,9-yf,tablero,2)){
            printf("Barco mal puesto,ingreselo de vuelta\n");
            system("pause");
            id--;
        }
borrar;
    }
    //Ingresar largo 3
    /*for(int cont = id + 3; id < cont;id++){//cont = id + cant barco
        imprimir_tablero_bien_croto(tablero);
        printf("barco largo 3\n\n",id);

        printf("\tIngrese coordenadas de inicio\n");
        printf("\tx:");
        scanf("%d",&xi);
        printf("\ty:");
        scanf("%d",&yi);

        printf("\tIngrese coordenadas de fin\n");
        printf("\tx:");
        scanf("%d",&xf);
        printf("\ty:");
        scanf("%d",&yf);

        if(anadir_barco(id,xi,9-yi,xf,9-yf,tablero,3)){
            printf("Barco mal puesto,ingreselo de vuelta\n");
            system("pause");
            id--;
        }
borrar
    }

    //Ingresar largo 4
    for(int cont = id + 2; id < cont;id++){//cont = id + cant barco
        imprimir_tablero_bien_croto(tablero);
        printf("barco largo 4\n\n",id);

        printf("\tIngrese coordenadas de inicio\n");
        printf("\tx:");
        scanf("%d",&xi);
        printf("\ty:");
        scanf("%d",&yi);

        printf("\tIngrese coordenadas de fin\n");
        printf("\tx:");
        scanf("%d",&xf);
        printf("\ty:");
        scanf("%d",&yf);

        if(anadir_barco(id,xi,9-yi,xf,9-yf,tablero,4)){
            printf("Barco mal puesto,ingreselo de vuelta\n");
            system("pause");
            id--;
        }
borrar
    }*/
}

int check_victoria(nodo_barco* list_barco){

    int bandera = 0;
    nodo_barco* aux = list_barco;
    for(int i = 0; i < CANT_BARCOS; i++){
        if(aux->largo != 0)
            bandera = 1;
        aux = aux->sig;
    }
    if(bandera == 1){
        return 0;
    }
    return 1;

}

void mostrar_tablero_enemigo(fila* tablero){
    fila* aux = tablero;
    int fila_print[SIZE];
    int i,j=9;
    for(i=0;i<SIZE;i++){
        fila_print[i]=0;
    }
    printf("TABLERO ENEMIGO\n");
    for(;aux != NULL;aux = aux->sig){
        printf("\t %d \t",j);
        j--;
        if(aux->casillero==NULL){
            for(i=0;i<SIZE;i++){
                printf("%d ",fila_print[i]);
            }
            printf("\n");
        }
        else{
            for(casillero* ca = aux->casillero;ca != NULL;ca = ca->sig){
                if(ca->barco==NULL){
                    fila_print[ca->x]=8;
                }
                else{
                    if(ca->disparo==1){
                        if(ca->barco->largo)
                            fila_print[ca->x]=1;
                        else
                            fila_print[ca->x]=2;
                    }
                }
            }
            for(i=0;i<SIZE;i++){
                printf("%d ",fila_print[i]);
                fila_print[i]=0;
            }
            printf("\n");
        }
    }
    printf("\n\n\t   \t");
    for(i=0;i<SIZE;i++){
        printf("%d ",i);
    }
    printf("\ntermine de mostrar\n0:agua\n8:impacto en agua\n1:barco dañado\n2:barco hundido\n");
}


void mostrar_tu_tablero(fila* tablero){
    fila* aux = tablero;
    int fila_print[SIZE];
    int i,j=9;
    for(i=0;i<SIZE;i++){
        fila_print[i]=0;
    }
    printf("TU TABLERO\n");
    for(;aux != NULL;aux = aux->sig){
        printf("\t %d \t",j);
        j--;
        if(aux->casillero==NULL){
            for(i=0;i<SIZE;i++){
                printf("%d ",fila_print[i]);
            }
        printf("\n");
        }
        else{
            for(casillero* ca = aux->casillero;ca != NULL;ca = ca->sig){
                if(ca->barco==NULL){
                    fila_print[ca->x]=8;
                }
                else{
                    if(ca->disparo==0){
                        fila_print[ca->x]=1;
                    }
                    else{
                        fila_print[ca->x]=2;
                    }
                }
        }
        for(i=0;i<SIZE;i++){
            printf("%d ",fila_print[i]);
            fila_print[i]=0;
        }
        printf("\n");
        }
    }
    printf("\n\n\t   \t");
    for(i=0;i<SIZE;i++){
        printf("%d ",i);
    }
    printf("\ntermine de mostrar\n0:agua\n8:impacto en agua\n1:barco\n2:barco dañado\n");
}
int main()
{
  int tablero_inic_jug1[SIZE][SIZE];
  int tablero_inic_jug2[SIZE][SIZE];
  for(int g = 0;g<SIZE;g++){
    for(int y = 0;y<SIZE;y++){
      tablero_inic_jug1[g][y] = 0;
      tablero_inic_jug2[g][y] = 0;
    }
  }

  //Ingreso de datos

  printf("Turno del Jugador 1\n");

  ingresar_barcos(tablero_inic_jug1);


  printf("Turno del Jugador 2\n");

  ingresar_barcos(tablero_inic_jug2);

  nodo_barco* lista_barcos_jug1 = NULL;

  nodo_barco* lista_barcos_jug2 = NULL;

  lista_barcos_jug1 = crear_lista_barcos(lista_barcos_jug1);

  lista_barcos_jug2 = crear_lista_barcos(lista_barcos_jug2);

  fila* tablero1 = crear_tablero(tablero_inic_jug1,lista_barcos_jug1);

  fila* tablero2 = crear_tablero(tablero_inic_jug2,lista_barcos_jug2);

  //Comienzo del Juego

  int dispx, dispy,result;

  while(1){

        //mostrar tablero enemigo
        while(1){
            mostrar_tu_tablero(tablero1);//muestra las coordenadas donde hay barcos
            mostrar_tablero_enemigo(tablero2);

            printf("Turno del Jugador 1\n");
            printf("A donde quiere disparar capitán?\n");
            printf("Ingrese coordenada x\n");
            printf("\tx:");
            scanf("%d",&dispx);
            printf("Ingrese coordenada y\n");
            printf("\ty:");
            scanf("%d",&dispy);

            result = disparo(dispx,9-dispy,tablero2,lista_barcos_jug2);

            if(result == AGUA){
                printf("Agua\n");
                break;
            }
            else if (result == AVERIADO){
                printf("Averiado\n");
                break;
            }
            else if (result == HUNDIDO){
                printf("Hundido\n");
                break;
            }
            printf("Disparo no valido\n");
            pausa;
            borrar;
        }

        if(check_victoria(lista_barcos_jug2)){
            printf("Felicidades capitan, ha ganado la batalla!\n");
            break;
        }


        while(1){

            mostrar_tu_tablero(tablero2);//muestra las coordenadas donde hay barcos
            mostrar_tablero_enemigo(tablero1);
            printf("Turno del Jugador 2\n");
            printf("A donde quiere disparar capitan?\n");
            printf("Ingrese coordenada x\n");
            printf("\tx:");
            scanf("%d",&dispx);
            printf("Ingrese coordenada y\n");
            printf("\ty:");
            scanf("%d",&dispy);

            result = disparo(dispx,9-dispy,tablero1,lista_barcos_jug1);
            if(result == AGUA){
                printf("Agua\n");
                break;
            }
            else if (result == AVERIADO){
                printf("Averiado\n");
                break;
            }
            else if (result == HUNDIDO){
                printf("Hundido\n");
                break;
            }
            printf("Disparo no valido\n");
            pausa;
            borrar;
        }
        if(check_victoria(lista_barcos_jug1)){
            printf("Felicidades capitan, ha ganado la batalla!\n");
            break;
        }

  }

  return 0;
}
