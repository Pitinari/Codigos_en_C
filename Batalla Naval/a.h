#ifndef A_H_INCLUDED
#define A_H_INCLUDED
#define SIZE 10
#define CANT_BARCOS 6

typedef struct nodo_barco{
  struct nodo_barco* sig;
  //barco* bar;
  int largo;
  }nodo_barco;

typedef struct casillero{
    struct casillero* sig;
    nodo_barco * barco;
    int disparo,x;
} casillero;

typedef struct fila{
    casillero * casillero;
    struct fila* sig;
} fila;






#endif // A_H_INCLUDED
