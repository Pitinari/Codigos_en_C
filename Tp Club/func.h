struct Habitaciones{
	char nombre [24];
	struct Jugadores * ocupado;
	struct Habitaciones *iz, *de, *diag;
};

struct Jugadores{
	char nombre [20];
	char **cartas;
	int cant;
	struct Habitaciones *pos;
};
typedef struct Jugadores Jugadores;
typedef struct Habitaciones Habitaciones;




