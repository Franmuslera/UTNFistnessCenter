#include <iostream>
using namespace std;
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <conio.h>
#include <cstring>
#include <stdio.h>
#include <cstdio>
#include "persona.h"
#include "socio.h"
#include "empleado.h"
#include "rutina.h"
#include "rutina_por_cliente.h"
#include "cancha.h"
#include "reservaDeCancha.h"
#include "actividad.h"
#include "actividad_por_cliente.h"
#include "noticia.h"
#include "menus.h"

const char *FUTBOL = "futbol";
const char *TENIS = "tenis";


int main(){

    bool estado = true;
    int opcion;

 //   Cancha cancha1(1, FUTBOL);
 //   Cancha cancha2(2, FUTBOL);
 //   Cancha cancha3(3, FUTBOL);
 //   Cancha cancha4(4, FUTBOL);
 //   Cancha cancha5(5, FUTBOL);

 //   Cancha cancha6(6, TENIS);
 //   Cancha cancha7(7, TENIS);
 //   Cancha cancha8(8, TENIS);
 //   Cancha cancha9(9, TENIS);
 //   Cancha cancha10(10, TENIS);

     while(estado){

            cout << "- - - - - - - MENU PRINCIPAL - - - - - - - -" << endl;
            cout << "1) GESTION SOCIOS Y EMPLEADOS" << endl;
            cout << "2) GESTION DE RUTINAS" << endl;
            cout << "3) GESTION DE RESERVAS" << endl;
            cout << "4) GESTION DE ACTIVIDADES" << endl;
            cout << "5) GESTION DE NOTICIAS" << endl;
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
                    menu_reservas();
                    break;

                case 4:
                    system("cls");
                    menu_actividades();
                    break;

                case 5:
                    system("cls");
                    menu_noticias();
                    break;

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
