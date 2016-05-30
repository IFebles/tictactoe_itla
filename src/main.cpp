#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

int Verify(char [][3][3]);
void GetResp(int, int, int*);

int main()
{
	const char MARKS[] = {'O', 'X'};

	cout << "\n* Bienvenido al Tick-Tack-Toe ! *" << endl;

	B:
	//Marcas de los jugadores
	char players[2];
	//Tablero de juego
	char dash[][3][3] =
	{
		{{'-'}, {'-'}, {'-'}},
		{{'-'}, {'-'}, {'-'}},
		{{'-'}, {'-'}, {'-'}}
	};

	//Respuesta de la marca seleccionada para el Jugador1
	int resp = 0;
	//Fin del juego
	bool end = false;

	cout << "\nSeleccione la marca para el Jugador1: (Salir: Ctrl+C)" << endl
		<< "  - " << MARKS[0] << " (1)" << endl
		<< "  - " << MARKS[1] << " (2)" << endl << endl;

	GetResp(1, 2, &resp);

	//Jugador1:
	players[0] = MARKS[resp - 1];
	//Jugador2:
	players[1] = MARKS[resp - 2 < 0 ? 1: 0];
	
	cout << "\nMarca del Jugador1: " << players[0] << endl
		<< "Marca del Jugador2: " << players[1] << endl;

	//reiniciar el valor de "resp"
	resp = -1;

	//Espaciado
	string esp1 = "   ";
	string esp2 = "  |  ";
	//Determinar si es el turno del Jugador2 o no
	srand(time(NULL));
	int turn2 = rand() % 2;
	

	while(!end)
	{
		//Fila y columna seleccionada por el jugador actual
		int row = -1, col = -1;

		cout << endl << " " << esp1 << esp1 << "(1)" << esp1 << "(2)" << esp1 << "(3)" << esp1 << endl;

		for(int x = 0; x < 3; x++)
		{
			cout << "(" << x + 1 << ")" << esp2;
			for(int y = 0; y < 3; y++)
				cout << dash[x][y] << esp2;
			cout << endl;
		}

		cout << endl << "Turno del " << (turn2 ? "*Jugador2*": "*Jugador1*")
			<< " (" << players[turn2] << ")" << endl << endl;

		A:
		cout << "Seleccione una fila [1 - 3]: (Salir: Ctrl+C)" << endl;
		GetResp(1, 3, &row);

		cout << "Seleccione una columna [1 - 3]: (Atras: 0 | Salir: Ctrl+C)" << endl;
		GetResp(0, 3, &col);

		if(col == 0)
		{
			row = col = -1;
			goto A;
		}

		if(*dash[row-1][col-1] == '-')
			*dash[row-1][col-1] = players[turn2];
		else
		{
			cout << "\n* Este espacio ya esta ocupado! *\n" << endl;
			row = col = -1;
			goto A;
		}

		//Resultado del "chequeo"
		int res = Verify(dash);

		if(res == 0)
			//Cambiar el turno
			turn2 = !turn2;
		else
		{
			stringstream ss;
			if(res == 1)
				ss << "\n* GANO EL " << (turn2 ? "Jugador2": "Jugador1") << " !!! *\n\n";
			else
				ss << "\n* Juego trancado *\n\n";
			cout << ss.str();

			cout << "Que desea hacer? (Salir: Ctrl+C)" << endl
				<< "  - Salir (0)" << endl
				<< "  - Volver a jugar (1)" << endl
				<< "  - Reseleccionar marcas (2)" << endl << endl;

			int resp2 = -1;

			GetResp(0, 2, &resp2);

			if(resp2 == 0)
				end = true;
			else if(resp2 == 1)
			{
				turn2 = !turn2;
				//Limpiar el tablero
				for(int x = 0; x < 3; x++)
					for(int y = 0; y < 3; y++)
						*dash[x][y] = '-';
			}
			else
				goto B;
		}
	}

	cout << "\n* Adios *\n\n";
}


//Recibe el input del usuario y lo asigna en formato "numerico"
//rangeI: inicio del rango
//rangeF: fin del rango
//val: variable a la que asignar el valor recibido
void GetResp(int rangeI, int rangeF, int* val)
{
	while(!(*val >= rangeI && *val <= rangeF))
		{
			cout << ">> ";
			string incoming;
			cin >> incoming;
			istringstream(incoming) >> *val;
		}
}

//Verifica el estado actual del juego
//tab: copia del tablero
//0 -> Continua el juego
//1 -> Alguien gano
//2 -> Juego trancado
int Verify(char tab[][3][3])
{
	//Verificando la horizontal
	for(int x = 0; x < 3; x++)
		if(*tab[x][0] == *tab[x][1] && *tab[x][1] == *tab[x][2] && *tab[x][2] != '-')
			return 1;

	//Verificando la vertical
	for(int x = 0; x < 3; x++)
		if(*tab[0][x] == *tab[1][x] && *tab[1][x] == *tab[2][x] && *tab[2][x] != '-')
			return 1;

	//Diagonal descendente
	if(*tab[0][0] == *tab[1][1] && *tab[1][1] == *tab[2][2] && *tab[2][2] != '-')
		return 1;

	//Diagonal ascendente
	if(*tab[2][0] == *tab[1][1] && *tab[1][1] == *tab[0][2] && *tab[0][2] != '-')
		return 1;

	//Saber si quedan jugadas por hacer
	for(int x = 0; x < 3; x++)
		for(int y = 0; y < 3; y++)
			if(*tab[x][y] == '-')
				return 0;

	//Si llega aqui es que se tranco el juego
	return 2;
}