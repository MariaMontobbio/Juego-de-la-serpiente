#include <iostream>
#include <windows.h>
#include <conio.h>
#include "colors.h"
#include <stdlib.h>
#include<time.h>
using namespace std;

// declaració de tecles
#define DALT 119
#define ESQUERRA 97
#define DRETA 100
#define BAIX 115
#define ESC 27

int serp[1596][2]; // array del cos de la serp
int n = 1;
int tam = 3; //llargada del cos de la serp
int x = 10, y = 12;
int dir = 3;
char teclas;
int xc = 30, yc = 15; //coordenadas del menjar
int velocitat = 200, h = 1;
int score = 0;
int b=0;
int numero_fruites=0;


void gotoxy (int x, int y){
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y= y;
    SetConsoleCursorPosition(hcon,dwPos);
}

void camp() { // funció que imprimeix el camp de joc
	for(int i = 2; i < 78; i++) { //linea de dalt i abaix
		gotoxy(i, 3); cout << YELLOW <<char(205);
		gotoxy(i, 23); cout <<char(205);
	}

	for(int i = 4; i < 23; i++) { //linea de la derecha y izquierda
		gotoxy(2, i); cout << char(186);
		gotoxy(77, i); cout <<char(186);
	}

	//imprimeix les cantonades del camp de joc
	gotoxy(2, 3); cout <<char(201);
	gotoxy(2, 23); cout <<char(200);
	gotoxy(77, 3); cout <<char(187);
	gotoxy(77, 23); cout <<char(188);
}

void guardar_posicio() { // guarda la posició on esta el cos de la serp

	serp[n][0] = x;
	serp[n][1] = y;
	n++;
	if (n == tam) {
		n = 1;
	}
}

void pintar_serp() { // Imprimeix els nous * perque la serp es mogui visualment
	for (int i = 1; i < tam; i++) {
		gotoxy(serp[i][0] , serp[i][1]);
		cout << GREEN "*";
	}
}

void borrar_serp() { // borra els * que ja no es necessiten en el cos de la serp
	gotoxy(serp[n][0] , serp[n][1]);
	cout << " ";

}

void tecla() { // segun la flecha que se presione cambia el valor de dir (variable direcció)
	if (kbhit()) {
		teclas = getch();
		switch (teclas) {
			case DALT:
				if (dir != 2) {
					dir = 1;
				    break;
				}
			case BAIX:
				if (dir != 1) {
					dir = 2;
				    break;
				}
			case DRETA:
				if (dir != 4) {
					dir = 3;
					break;
				}
			case ESQUERRA:
				if (dir != 3) {
					dir = 4;
					break;
				}
		}
	}
}

void canviar_velocitat() { //cada 2 puntos conseguidos se resta 10 milisegundos al Sleep, en otra palabras se sube la velocidad
	if (score == h*2) {
		velocitat -= 10;
		h++;
	}
}

void fruita() {
	if (x == xc && y == yc) {
		srand(time(NULL)); 
		xc = (rand()%73)+4; // coordenada en el eje x aleatorio entre 0-73 que se suma 4 para que la comida no choque con las paredes del campo
		yc = (rand()%19)+4; // coordenada en el eje y aleatorio entre 0-19 que se suma 4 para que la comida no choque con las paredes del campo
	
	 	 b= 1+rand()%9;

		tam += b; // se suma un numero aleatorio entre 1-9 a tam cada vez que comes
		score += b+1; //suma el nª random de la fruita
		cout << RED " ";
		gotoxy(xc, yc); cout << RED" "<<b;
		
		numero_fruites += 10-9;
		canviar_velocitat();
		
		gotoxy(17,1); cout<< YELLOW "Numero de fruites consumides: "<<GREEN" "<< numero_fruites;
		gotoxy(3, 1); cout << YELLOW "Score: " <<GREEN" "<< score;
	}
}


bool game_over() {
	if (y == 3 || y == 23 || x == 2 || x == 77) { // si la cabeza de la serpiente coenzide con las coordenadas de las paredes del campo sale verdad
		return true;
	}
	for (int j = tam-1; j > 0; j--) { // si la cabeza de la serpiente coenzide con las coodenadas donde esta su cuerpo sale verdad
		if (serp[j][0] == x && serp[j][1] == y) {
			return true;
		}
	}
	return false; // si no se comple nada de eso sale verdad
}



void main_title(){

cout << RED"     * *         " << endl;
cout << RED"      *            " << endl;
cout << RED"      *                  " << endl;
cout << GREEN"    *****             " << endl;
cout << GREEN"   *"; cout<<WHITE"*";cout<<GREEN"***";cout<<WHITE"*";cout<<GREEN"*" << endl;
cout << GREEN"  *********        					     " << endl;
cout << GREEN"  *********          								 " << endl;
cout << GREEN"   *******           *************            *   " << endl;
cout << GREEN"   *******          ***************          ***    " << endl;
cout << GREEN"    *******        *****************        *****     " << endl;
cout << GREEN"     *******      ******      *******      ******		" << endl;
cout << GREEN"      *******    ******        *******    ****** " << endl;
cout << GREEN"       ***************          *************** " << endl;
cout << GREEN"        *************            *************" << endl;
cout << GREEN"          *********                **********     " << endl<<endl<<endl;
    cout << "------------------------------------" << endl<<endl;
    cout << "             SNAKE GAME     " << endl<< endl;
    cout << "      Presiona ENTER per jugar     " << endl<<endl;
    cout << "------------------------------------" << endl;
    cout << endl;
system("pause>null");
system("cls");

cout << YELLOW "      INSTRUCCIONS:" << "\n" << "\n";
cout << "  Mou-te per la pantalla menjant-te els numeros amb la serp." << "\n";
cout << "  Aquesta anira creixent. Si colisiones amb les parets o amb" << "\n";
cout << "  tu mateix, s'acaba la partida." << "\n" << "\n";
cout << "  TECLES DE MOVIMENT" << "\n" << "\n";
cout << "  D DRETA" << "\n" << "  A ESQUERRA" << "\n" << "  S AVALL" << "\n" << "  W AMUNT" << "\n";

cout<<endl<<"Pesiona cualsevol tecla per jugar "<<endl;
system("pause>null");
system("cls");
}


void game_over_letters(){
int repeticions=0;
while (repeticions<6){

	gotoxy(1,1);
	system ("color 47");
	cout<<endl<<endl<<endl<<endl<<endl;
	cout<<"\t\t* * * * *    * * * *    *        *    * * * * *    "<<endl;
	cout<<"\t\t*            *     *    * *    * *    *            "<<endl;
	cout<<"\t\t*            *     *    *  *  *  *    *            "<<endl;
	cout<<"\t\t*   * * *    * * * *    *   *    *    * * * *      "<<endl;
	cout<<"\t\t*       *    *     *    *        *    *            "<<endl;
	cout<<"\t\t*       *    *     *    *        *    *            "<<endl;
	cout<<"\t\t* * * * *    *     *    *        *    * * * * *    "<<endl<<endl<<endl;

	cout<<"\t\t* * * * *    *     *    * * * * *     * * * *      "<<endl;
	cout<<"\t\t*       *    *     *    *             *       *    "<<endl;
	cout<<"\t\t*       *    *     *    *             *       *    "<<endl;
	cout<<"\t\t*       *    *     *    * * * *       * * * *      "<<endl;
	cout<<"\t\t*       *    *     *    *             *    *       "<<endl;
	cout<<"\t\t*       *     *   *     *             *     *      "<<endl;
	cout<<"\t\t* * * * *      * *      * * * * *     *      *     "<<endl;

	Sleep (250);

	system("cls");
	system("color 07");
	Sleep(200);

	repeticions ++;
}

}

int main() {

	Sleep(1000);
	int b= 1+rand()%9;
	main_title();
	camp();
	gotoxy(xc, yc); cout <<RED" "<< b; // imprime la comida en las coordenadas indicadas	

	
	gotoxy(17,1); cout<< YELLOW "Numero de fruites consumides: "<<GREEN" "<< numero_fruites;
	gotoxy(3, 1); cout << YELLOW "Score: " << GREEN" "<<score;
	
	
	while (teclas != ESC && !game_over()) { // mientras no se presione ESC o game_over sea falso el while continuara
	
	    // se llaman las funciones
		borrar_serp();
		guardar_posicio();
		pintar_serp();
		fruita();
		gotoxy(80, 1);
		tecla();
		tecla();
		b=0;
		if (dir == 1) { // si dir = 1 la serpiente sube
		   y--;
		}
		if (dir == 2) { // si dir = 2 la serpiente baja
			y++;
				Sleep(5);
		}
		if (dir == 3) { // si dir = 3 la serpiente se mueve acia la derecha
			x++;
		}
		if (dir == 4) { // si dir = 4 la serpiente se mueve acia la izquierda
			x--;
		}


		if (dir==1|| dir==2){
			int vel_vertical=velocitat+30;
			Sleep(vel_vertical);

		}
		else if (dir==3||dir==4){
			int vel_x = velocitat -30;
			Sleep(vel_x);
		}				// espera el valor de velocidad en milisegundos antes de volver a empezar el while

}


	if (game_over()==true){
		system("color 4f");
		Sleep (100);
		system ("color 0f");
		Beep(523, 500); //Do
		Sleep (100);
		system("color 4f");
		Beep(523, 500); //Do
		Sleep (100);
		system ("color 0f");
		Beep(523, 500); //Do
		Sleep (100);
		system("color 4f");
		Beep(523, 500); //Do
		Sleep (100);
		system("color 0f");
		Beep(523, 500); //Do
        system("cls");
		game_over_letters();
	}
	system("cls");


	return 0;

}
	/*
	camp();
	system("pause>null");
	*/
	





