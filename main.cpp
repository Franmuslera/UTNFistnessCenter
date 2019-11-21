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
Socio socio_actual;
#include "empleado.h"
Empleado empleado_actual;
#include "rutina.h"
#include "rutina_por_cliente.h"
#include "cancha.h"
#include "reservaDeCancha.h"
#include "actividad.h"
#include "actividad_por_cliente.h"

#include "noticia.h"
#include "menus.h"

int main(){
    menu_login();
    return 0;
}

