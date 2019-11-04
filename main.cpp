#include <iostream>
using namespace std;
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <cstring>
#include <stdio.h>
#include <cstdio>
#include "persona.h"
#include "socio.h"
#include "empleado.h"
#include "rutina.h"
#include "reservaDeCancha.h"

#include "menus.h"

/*struct Fecha{
    int anio;
    int mes;
    int dia;
    int hora;
}; */



int main(){
    bool estado = true;
    int opcion;

     while(estado){

            cout << "- - - - - - - MENU PRINCIPAL - - - - - - - -" << endl;
            cout << "1) GESTION SOCIOS Y EMPLEADOS" << endl;
            cout << "2) GESTION DE RUTINAS" << endl;
            cout << "3) GESTION DE RESERVAS" << endl;
            cout << "0) CERRAR PROGRAMA" << endl;
            cout << "- - - - - - - - - - - - - - - - - - - - - - -" << endl;
            cout << "INGRESE UNA OPCION: ";
            cin >> opcion;

            switch(opcion){
                case 1:
                    system("cls");
                    menu_personas();
                    break;
                case 2:
                    system("cls");
                    menu_rutina();
                    break;
                case 3:
                    system("cls");
                    //menu_reservas();
                case 0:
                    estado = false;
                    break;
                default:
                    break;
            }

            system("cls");
     }

return 0;
}
