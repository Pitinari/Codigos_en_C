Integrantes:
Tomas Pitinari
Sebasti�n I. Rodr�guez

Con respecto a los barcos:
La configuraci�n es 6 barcos en total: 2 barcos de 2 casilleros de largo, 3 de 3 casilleros de largo y 1 de 4 casilleros de largo, sin embargo esto puede modificarse cambiando las constantes definidas al principio de main.c.
Al inicio del juego cada jugador ubica sus barcos, verificando siempre que la posici�n que elige este permitida.

L�gica del desarrollo:
Para este programa usamos 2 arrays bidimensionales, 2 listas unidimensionales y 2 listas bidimensionales.
Los arrays bidimensionales se usan para ubicar los barcos al inicio del juego, decidimos usarlos porque facilita much�simo la verificaci�n de las posiciones permitidas.
Una vez colocados los barcos, transformamos este tablero representados por el array en una lista bidimensional. Esta lista est� formada por 2 estructuras, fila y casillero, la cantidad de filas es fija, ya que depende del tama�o del tablero. La cantidad de casilleros var�a, inicialmente es igual a la cantidad de barcos, a medida que el jugador dispara, cambiamos el valor de la variable disparo en el casillero donde se dispar� y,en el caso de que haya impactado un barco, reducimos el largo del nodo_barco al que apunta. Si disparo a un lugar donde hab�a agua, a�adimos un casillero cuya variable barco apunta a NULL, simbolizando agua.
La lista de barcos tiene tantos nodos como cantidad de barcos haya.Cuando creamos el tablero hecho con una lista bidimensional, hacemos que cada casillero apunte al nodo_barco que representa y que a�ada uno a la variable largo del mismo. De esta forma queda una lista con el largo de cada barco. Por otra parte, cuando se dispara a un casillero con barco, se resta 1 a la variable largo del nodo barco. Cuando largo = 0, significa que el barco se hundi�. Por lo tanto, la funci�n �check_victory� se fija si el largo de todos los barcos en la lista es 0, en caso afirmativo, significa que el jugador gan� la partida. Tenemos 1 de cada una de estas estructuras para cada jugador.


Aclaracion:La id de cada barco esta dada por su posici�n en la lista.
