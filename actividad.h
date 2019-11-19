#ifndef ACTIVIDAD_H_INCLUDED
#define ACTIVIDAD_H_INCLUDED

void baja_actividades();
const char *FILE_ACTIVIDADES = "actividades.dat";

Fecha fecha_sistema();

class Actividad {
  private:
      int idAct,nroEmp,duracion;
      Fecha fAct,fecha_actual;
      char nombreAct[50];
      bool estado;

  public:
    int getIdActividad();
    int getNroEmpleado();
    int getDuracion();
    Fecha getFechaActividad();
    char* getNombreActividad();
    bool getEstado();
    void setIdActividad(int);
    void setNroEmpleado(int);
    void setDuracion(int);
    void setFecha(Fecha);
    void setNombreActividad(char*);
    void setEstado(bool);
    void mostrarHoraActividad();
    bool grabarEnDisco();
    int leerDeDisco(int);
    void modificar_en_disco(int);
    void cargarActividad();
    void mostrarActividad();

};

     int Actividad::getIdActividad(){
     return idAct;
     }

     int Actividad::getNroEmpleado(){
     return nroEmp;
     }

     int Actividad::getDuracion(){
     return duracion;
     }

     char* Actividad::getNombreActividad(){
     return nombreAct;
     }

     Fecha Actividad::getFechaActividad(){
     return fAct;
     }

     bool Actividad::getEstado(){
     return estado;
     }

     void Actividad::setIdActividad(int id){
     idAct = id;
     }

     void Actividad::setNroEmpleado(int n){
     nroEmp = n;
     }

     void Actividad::setDuracion(int d){
     duracion = d;
     }

     void Actividad::setNombreActividad(char* nom){
     strcpy(nombreAct,nom);
     }

     void Actividad::setFecha(Fecha f){
     fAct = f;
     }

     void Actividad::setEstado(bool estado_nuevo){
     estado = estado_nuevo;
     }

      void Actividad::mostrarHoraActividad(){
         cout << fAct.hora << "hs.";
    }

     bool Actividad::grabarEnDisco(){
    FILE *p;
    p = fopen(FILE_ACTIVIDADES, "ab");
    if(p==NULL)return false;
    fwrite(this, sizeof *this, 1, p);
    fclose(p);
    return true;
}
    int Actividad::leerDeDisco(int pos){
    int x;
	FILE *p;
	p=fopen(FILE_ACTIVIDADES,"rb");
	if(p==NULL)
		{
		cout<<"No existe el archivo";
		cout<<"Presione una tecla para continuar";
    system("pause");
		return 0;
		}
	fseek(p,pos*sizeof *this,0);
	x=fread(this,sizeof *this,1,p);
	fclose(p);
	return x;
}

    void Actividad::modificar_en_disco(int pos)
	{
	FILE *p;
	p=fopen(FILE_ACTIVIDADES,"rb+");
	if(p==NULL){cout<<"ERROR DE ARCHIVO";exit(1);}
	fseek(p,pos*sizeof *this,0);
	fwrite(this,sizeof *this,1,p);
	fclose(p);
	}

	int cantidad_de_actividades(){
    FILE *p;
    int cant_actividades;
    p = fopen(FILE_ACTIVIDADES, "rb");
    if(p==NULL){
        p = fopen(FILE_ACTIVIDADES, "wb");
        fclose(p);
        p = fopen(FILE_ACTIVIDADES, "rb");
    }
    fseek(p, 0, 2);
    long cantBytes = ftell(p);
    fclose(p);
    cant_actividades = (int ) cantBytes / sizeof(struct Actividad);
    return cant_actividades;
}

     void Actividad:: cargarActividad(){

     int cant_actividades;

    time_t t = time(NULL);
    struct tm today = *localtime(&t);
    fecha_actual.mes = today.tm_mon + 1;
    fecha_actual.dia = today.tm_mday;
    fecha_actual.anio = (today.tm_year + 1900);
    fecha_actual.hora = today.tm_hour;


     fAct.dia = fecha_actual.dia;
     fAct.mes = fecha_actual.mes;
     fAct.anio = fecha_actual.anio;



     cout << "INGRESE EL NOMBRE DE LA ACTIVIDAD: ";
     cargarCadena(nombreAct, 50);

     cout << "IGRESE NRO DE ENTRENADOR: ";
     cin >> nroEmp;
     while(buscar_empleado_x_nro_y_tipo(nroEmp, ENTRENADOR)){
        cout << "EL EMPLEADO NO ES ENTRENADOR O NO EXISTE. INGRESE UN NUMERO DE EMPLEADO VALIDO: ";

        cin >> nroEmp;
     }

       cout << "IGRESE HORARIO DE ACTIVIDAD: ";
       cin >> fAct.hora;

      while (fAct.hora < fecha_actual.hora || fAct.hora > 21  ){
            cout << "INGRESE UNA HORA VALIDA (" << fecha_actual.hora << "-21): ";
            cin >> fAct.hora;


      }

     cout << "INGRESE DURACION DE ACTIVIDAD: ";
     cin >> duracion;

      while((duracion + fAct.hora)>21){
        cout << "LA DURACION DE LA RESERVA EXCEDE EL HORARIO DE CIERRE" << endl;
        cout << "INGRESE UNA DURACION EN HORAS VALIDA: ";
        cin >> duracion;
    }

     fAct.dia = fecha_actual.dia;
     fAct.mes = fecha_actual.mes;
     fAct.anio = fecha_actual.anio;


      idAct = (cantidad_de_actividades()+1);
      estado= true;
       if(grabarEnDisco()){
        system("cls");
        cout << endl << "ACTIVIDAD GRABADA CON EXITO." << endl;
    } else {
        system("cls");
        cout << endl << "NO SE PUDO GUARDAR CORRECTAMENTE LA ACTIVIDAD EN EL DISCO, INTENTELO NUEVAMENTE" << endl;
    }
     }

     bool buscarActividadXNro(int nro){
        FILE *p;
        p = fopen(FILE_ACTIVIDADES, "rb");
        if(p==NULL)return false;
        Actividad reg;
        while(fread(&reg, sizeof(Actividad),1 ,p)){
            if(reg.getIdActividad()==nro && reg.getEstado()==true && es_mayor_o_igual_a_la_fecha_actual(reg.getFechaActividad())){
                fclose(p);
                return true;
            }
        }
        fclose(p);
        return false;
    }

    void mostrar_actividad_x_nro_actividad(int nActividad){
        FILE *p;
        p = fopen(FILE_ACTIVIDADES, "rb");
        if(p==NULL)return;
        Actividad reg;
        while(fread(&reg, sizeof(Actividad),1 ,p)){
            if(reg.getIdActividad()==nActividad && reg.getEstado()==true && es_mayor_o_igual_a_la_fecha_actual(reg.getFechaActividad())){
                reg.mostrarActividad();
                fclose(p);
                return;
            }
        }
        fclose(p);
    }



   void Actividad::mostrarActividad(){
        Empleado reg;
        reg = buscar_empleado_x_nro_empleado(nroEmp);
        cout << endl << "- - - - - - - - - - - - - - - - - - - - - - -" << endl;
        cout << "ID ACTIVIDAD: " << idAct << endl;
        cout << "NOMBRE DE ACTIVIDAD: " << nombreAct << endl;
        cout << "NOMBRE ENTRENADOR: " << reg.getNombre() << " " << reg.getApellido() << endl;
        cout << "DURACION DE ACTIVIDAD: " << duracion << " HS."<< endl;
        cout << "HORA DE ACTIVIDAD: " ;
        mostrarHoraActividad();
        cout << endl << "- - - - - - - - - - - - - - - - - - - - - - -" << endl;
}


bool comparar_fechas(Fecha fecha, Fecha fechaAct){

     if (fecha.dia == fechaAct.dia && fecha.mes == fechaAct.mes && fecha.anio == fechaAct.anio){
        return true;
     }
     return false;
}

  void mostrar_todas_las_actividades(){
    Fecha fecha_act;

    fecha_act = fecha_sistema();
    int idActividad;
    FILE *p;
    Actividad reg;
    p = fopen(FILE_ACTIVIDADES, "rb");
    if(p==NULL){
        cout << endl << "NO SE PUDO ABRIR EL ARCHIVO, INTENTALO NUEVAMENTE." << endl;
        return;
    }
    cout << "ACTIVIDADES DEL DIA "<< fecha_act.dia << "/"<< fecha_act.mes << "/"<< fecha_act.anio << endl;
    while(fread(&reg, sizeof(Actividad), 1, p)){
        baja_actividades();
        if(reg.getEstado()== true ){
        reg.mostrarActividad();
        }
    }
    fclose(p);
  }


  void baja_actividades(){
      Fecha fecha_act,fechaActividad;

    fecha_act = fecha_sistema();
    int idActividad;
        FILE *p;
        Actividad reg;
        p = fopen(FILE_ACTIVIDADES, "rb");
        if(p==NULL){
            cout << endl << "NO SE PUDO ABRIR EL ARCHIVO, INTENTALO NUEVAMENTE." << endl;
            return;
        }
        while(fread(&reg, sizeof(Actividad), 1, p)){
             if(reg.getFechaActividad().dia<fecha_act.dia
                || reg.getFechaActividad().mes<fecha_act.mes
                || reg.getFechaActividad().anio<fecha_act.anio
                || reg.getFechaActividad().hora<fecha_act.hora){
                idActividad = reg.getIdActividad();
                reg.setEstado(false);
                reg.modificar_en_disco(idActividad-1);
             }
        }
        fclose(p);
        return;
  }


    void buscar_actividad_x_id(){
    FILE *p;
    int id;
    baja_actividades();
    cout << "INGRESE EL ID DE ACTIVIDAD QUE DESEA BUSCAR: ";
    cin >> id;
    p = fopen(FILE_ACTIVIDADES, "rb");
    if(p==NULL){
        system("cls");
        cout << "NO SE PUDO ABRIR EL ARCHIVO";
        system("pause");
        exit(1);
    }
    Actividad reg;
    while(fread(&reg, sizeof(Actividad), 1, p)){
        if(reg.getIdActividad()==id ){

            reg.mostrarActividad();
            fclose(p);
            return;
        }
    }
    cout << "NO SE ENCONTRO LA ACTIVIDAD BUSCADA" << endl;
    fclose(p);
}
    void alta_actividad(){
    Actividad reg;
    system("cls");
    reg.cargarActividad();
}

    Fecha fecha_sistema(){
            Fecha fecha_act;
            time_t t = time(NULL);
            struct tm today = *localtime(&t);
            fecha_act.mes = today.tm_mon + 1;
            fecha_act.dia = today.tm_mday;
            fecha_act.anio = (today.tm_year + 1900);
            fecha_act.hora = today.tm_hour;
            return fecha_act;

        }


    void modificar_nombre_actividad(){

        char nombre_nuevo[50];
        int nActividad;
        char opcion;
        Actividad reg;

        cout << "INGRESE EL NUMERO DEL ACTIVIDAD QUE DESEA MODIFICAR: ";
        cin >> nActividad;
        if(buscarActividadXNro(nActividad)){
            reg.leerDeDisco(nActividad -1);
            reg.mostrarActividad();
            cout << endl << "SEGURO QUE DESEA MODIFICARLO (S/N): ";
            cin >> opcion;
            switch(opcion){
                case 'S':
                case 's':
                    cout << endl << "INGRESE EL NOMBRE NUEVO: ";
                    cargarCadena(nombre_nuevo, 50);
                    reg.setNombreActividad(nombre_nuevo);
                    reg.modificar_en_disco(nActividad -1);
                    break;
                case 'N':
                case 'n':
                    cout << endl << "ABORTO EDICION DE ACTIVIDAD" << endl;
                    break;
                default:
                    break;
            }
        } else {
            cout << "NO EXISTE UNA ACTIVIDAD CON ESE NUMERO" << endl;
        }

        cout << "presione una tecla para continuar";
        system("pause>nul");
    }

    void modificar_entrenador(){


        int nEntrenador,nActividad;
        char opcion;
        Actividad reg;

        cout << "INGRESE EL NUMERO DEL ACTIVIDAD QUE DESEA MODIFICAR: ";
        cin >> nActividad;
        if(buscarActividadXNro(nActividad)){
            reg.leerDeDisco(nActividad -1);
            reg.mostrarActividad();
            cout << endl << "SEGURO QUE DESEA MODIFICARLO (S/N): ";
            cin >> opcion;
            switch(opcion){
                case 'S':
                case 's':
                    cout << endl << "INGRESE EL ENTRENADOR NUEVO: ";
                    cin >> nEntrenador;
                    reg.setNroEmpleado(nEntrenador);
                    reg.modificar_en_disco(nActividad -1);
                    break;
                case 'N':
                case 'n':
                    cout << endl << "ABORTO EDICION DE ACTIVIDAD" << endl;
                    break;
                default:
                    break;
            }
        } else {
            cout << "NO EXISTE UNA ACTIVIDAD CON ESE NUMERO" << endl;
        }

        cout << "presione una tecla para continuar";
        system("pause>nul");
    }

    void modificar_duracion_actividad(){

        int duracion_nueva;
        int nActividad;
        char opcion;
        Actividad reg;

        cout << "INGRESE EL NUMERO DEL ACTIVIDAD QUE DESEA MODIFICAR: ";
        cin >> nActividad;
        if(buscarActividadXNro(nActividad)){
            reg.leerDeDisco(nActividad -1);
            reg.mostrarActividad();
            cout << endl << "SEGURO QUE DESEA MODIFICARLO (S/N): ";
            cin >> opcion;
            switch(opcion){
                case 'S':
                case 's':
                    cout << endl <<"INGRESE UNA DURACION NUEVA: ";
                    cin >> duracion_nueva;
                    reg.setDuracion(duracion_nueva);
                    reg.modificar_en_disco(nActividad -1);
                    break;
                case 'N':
                case 'n':
                    cout << endl << "ABORTO EDICION DE ACTIVIDAD" << endl;
                    break;
                default:
                    break;
            }
        } else {
            cout << "NO EXISTE UNA ACTIVIDAD CON ESE NUMERO" << endl;
        }

        cout << "presione una tecla para continuar";
        system("pause>nul");
    }


    void modificar_hora_actividad(){
        int nActividad;
        Fecha fNueva, fActual;
        char opcion;
        Actividad reg;

        fActual = fecha_sistema();

        cout << "INGRESE EL NUMERO DEL ACTIVIDAD QUE DESEA MODIFICAR: ";
        cin >> nActividad;
        if(buscarActividadXNro(nActividad)){
            reg.leerDeDisco(nActividad -1);
            reg.mostrarActividad();
            cout << endl << "SEGURO QUE DESEA MODIFICARLO (S/N): ";
            cin >> opcion;
            switch(opcion){
                case 'S':
                case 's':
                    fNueva.dia = fActual.dia;
                    fNueva.mes = fActual.mes;
                    fNueva.anio = fActual.anio;
                    cout << endl << "INGRESE LOS EL NUEVO HORARIO: ";
                    cin >> fNueva.hora;
                    reg.setFecha(fNueva);
                    reg.modificar_en_disco(nActividad -1);
                    break;
                case 'N':
                case 'n':
                    cout << endl << "ABORTO EDICION DE ACTIVIDAD" << endl;
                    break;
                default:
                    break;
            }
        } else {
            cout << "NO EXISTE UNA ACTIVIDAD CON ESE NUMERO" << endl;
        }

        cout << "presione una tecla para continuar";
        system("pause>nul");
    }

    void mostrar_actividades_x_nro_entrenador(int nEntrenador){
        Fecha fecha_act;

        fecha_act = fecha_sistema();
        int idActividad;
        FILE *p;
        Actividad reg;
        p = fopen(FILE_ACTIVIDADES, "rb");
        if(p==NULL){
            cout << endl << "NO SE PUDO ABRIR EL ARCHIVO, INTENTALO NUEVAMENTE." << endl;
            cout << "presione una tecla para continuar";
            system("pause>nul");
            return;
        }
        cout << "ACTIVIDADES DEL DIA "<< fecha_act.dia << "/"<< fecha_act.mes << "/"<< fecha_act.anio << endl;
        while(fread(&reg, sizeof(Actividad), 1, p)){
            baja_actividades();
            if(reg.getEstado()== true && reg.getNroEmpleado()==nEntrenador){
            reg.mostrarActividad();
            }
        }
        fclose(p);
        cout << "presione una tecla para continuar";
        system("pause>nul");
    }



















#endif // ACTIVIDAD_H_INCLUDED
