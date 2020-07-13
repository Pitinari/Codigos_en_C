#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "func.h"


void mezclar (char cartas [18][24]){
	int i=0,k;
	char aux[24];
	for(;i<18;i++){
		k=rand()%18;
		strcpy(aux,cartas[i]);
		strcpy(cartas[i],cartas[k]);
		strcpy(cartas[k],aux);
	}
}

void repartir (char cartas [18][24], Jugadores *jug, int k){
	int i,j=0,o=0;
	for(i=0;i<k;i++){
		jug[i].cartas=malloc(sizeof(char *)*(18/k+1));
		jug[i].cant=0;
	}
	while (o<18){
		for(i=0;i<k;i++){
			if(o<18){
				jug[i].cartas[j]=cartas[o++];
				jug[i].cant++;
			}
			else
				break;
		}
		j++;
	}
}
int hacer_acusacion(char acusacion[3][24],char solucion[3][24]){
    if(strcmp(acusacion[0],solucion[0])==0 && strcmp(acusacion[1],solucion[1])==0 && strcmp(acusacion[2],solucion[2])==0)
        return 1;
    return 0;
}

void posicion_inicial(Jugadores jug[],int k,Habitaciones habit[9]){
    int i=0,aux,m,p[9]={0,1,2,3,4,5,6,7,8};
    for(;i<k;i++){
        m=(rand()%(9-i))+i;
        aux=p[i];
        p[i]=p[m];
        p[m]=aux;
        jug[i].pos=(habit+p[i]);
        habit[p[i]].ocupado=&jug[i];
    }
}

int revisar_esquina(Jugadores jug){
    if(jug.pos->diag != NULL)
        return 1;
    return 0;
}

void mover_esquina(Jugadores *jug){

    if(!jug->pos->diag->ocupado){
        jug->pos->diag->ocupado = jug;
        jug->pos=jug->pos->diag;
        jug->pos->diag->ocupado = NULL;
        return;
    }
    else{
        printf("La esquina esta ocupada");
        return;
    }
}

void mapa(){
    char c;
    FILE *f = fopen("mapa.txt","r");
    while(!feof(f)){
        fscanf(f,"%c",&c);
        printf("%c",c);
    }
    fclose(f);
    }

int dado(){
    printf("Tirando dado");
    Sleep(500);
    printf(".");
    Sleep(500);
    printf(".");
    Sleep(500);
    printf(".");
    printf("\r ");
 return rand()%6+1;
}



int main(){
    int k,i,j,d,casillas[12],cant_pos;
    while(1){
        printf("Ingrese la cantidad de jugadores (3-6): ");
		scanf("%d",&k);
		if(k<=6 && k>=3)
			break;
		printf("Solo se puede jugar de 3 a 6 jugadores\n");
		system("pause");
		system("cls");
    }
	Jugadores *jug;
	jug = malloc(sizeof(Jugadores)*k);
	for(i=0;i<k;i++){
		printf("Ingrese el nombre del jugador %d: ",i+1);
		scanf("%s",jug[i].nombre);
	}
	system("cls");
	char *armas[6];
	for(i=0;i<6;i++)
		armas[i]=malloc(sizeof(char)*20);
	strcpy(armas[0],"Revolver");
	strcpy(armas[1],"Cuchillo");
	strcpy(armas[2],"Lazo");
	strcpy(armas[3],"Candelabro");
	strcpy(armas[4],"Llave Inglesa");
	strcpy(armas[5],"Tubo de Plomo");
	char *sospechosos[6];
	for(i=0;i<6;i++)
		sospechosos[i]=malloc(sizeof(char)*20);
	strcpy(sospechosos[0],"Coronel Moztaza");
	strcpy(sospechosos[1],"Senora Azulino");
	strcpy(sospechosos[2],"Senora Blanco");
	strcpy(sospechosos[3],"Senorita Escarlata");
	strcpy(sospechosos[4],"Profesor Moradillo");
	strcpy(sospechosos[5],"Senor Verdi");
	Habitaciones habit[9];
	strcpy(habit[0].nombre,"Cocina");
	strcpy(habit[1].nombre,"Patio");
	strcpy(habit[2].nombre,"Spa");
	strcpy(habit[3].nombre,"Teatro");
	strcpy(habit[4].nombre,"Salon");
	strcpy(habit[5].nombre,"Observatorio");
	strcpy(habit[6].nombre,"Vestibulo");
	strcpy(habit[7].nombre,"Habitacion de Huespedes");
	strcpy(habit[8].nombre,"Comedor");
    for(i=0;i<9;i++){
        habit[i].iz = (habit+(i==0 ? 8 : i-1));
        habit[i].de = (habit+(i==8 ? 0 : i+1));
        habit[i].ocupado=NULL;
        switch (i){
        case 0:
            habit[i].diag=(habit+5);
            break;
        case 2:
            habit[i].diag=(habit+7);
            break;
        case 5:
            habit[i].diag=habit;
            break;
        case 7:
            habit[i].diag=(habit+2);
            break;
        default:
            habit[i].diag=NULL;
            break;
        }
    }
    srand(time(NULL));

    char cartas [18][24],solucion[3][24];

    strcpy(solucion[0],armas[rand()%6]);

    for(i=0,j=0;i<6;i++){
        if(strcmp(solucion[0],armas[i])!=0){
            strcpy(cartas[j++],armas[i]);
        }
    }
    strcpy(solucion[1],sospechosos[rand()%6]);

    for(i=0;i<6;i++){
        if(strcmp(solucion[1],sospechosos[i])!=0){
            strcpy(cartas[j++],sospechosos[i]);
        }
    }
    strcpy(solucion[2],habit[rand()%9].nombre);

    for(i=0;i<9;i++){
        if(strcmp(solucion[2],habit[i].nombre)!=0){
            strcpy(cartas[j++],habit[i].nombre);
        }
    }
    mezclar(cartas);
    repartir(cartas,jug,k);
    char acusacion[3][24];
    printf("%s   %s   %s\n",solucion[0],solucion[1],solucion[2]);
    posicion_inicial(jug,k,habit);
    getchar();
    while(1){       ///turnos
        for(i=0;i<k;i++){
            mapa();
            printf("TURNO DE %s\n\n",jug[i].nombre);
            printf("Usted esta en la habitacion: %s\n\n",jug[i].pos->nombre);
            printf("Sus cartas son: \n");
            for(j=0;j<jug[i].cant;j++){
                printf("%s\n",jug[i].cartas[j]);
            }
            printf("\n\nJugador %s, desea hacer una acusacion? si(1) - no(0) : ",jug[i].nombre);
            scanf("%d",&j);
            getchar();
            if(j){
                printf("Ingrese el arma homicida: ");
                scanf("%[^\n]",acusacion[0]);
                getchar();
                printf("Ingrese el nombre del criminal: ");
                scanf("%[^\n]",acusacion[1]);
                getchar();
                printf("Ingrese la escena del crimen: ");
                scanf("%[^\n]",acusacion[2]);
                getchar();
                if(hacer_acusacion(acusacion,solucion)){
                    printf("El Jugador %s ha ganado el juego !!\n\n",jug[i].nombre);
                    system("pause");
                    return 0;
                }
            }
            j=0;
            if(revisar_esquina(jug[i])){
                printf("\nDesea moverse a la esquina opuesta? si(1) - no(0) : ");
                scanf("%d",&j);
                getchar();
                if(j){
                    mover_esquina(&jug[i]);
                }
            }
            if(j==0){
                d=dado();
                printf("Usted Saco %d\n",d);
                iz(jug[i]->pos ,casillas,d,&cant_pos);
                system("pause");
            }
         system("cls");
        }

    }
	return 0;
}
