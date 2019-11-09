#ifndef RESERVADECANCHA_H_INCLUDED
#define RESERVADECANCHA_H_INCLUDED

const char *FILE_RESERVAS = "reservas.dat";


void modificar_fecha_reserva();
void modificar_cancha_reserva();
void modificar_duracion_reserva();
void mostrar_todas_las_reservas_x_nro_reserva();
void mostrar_todas_las_reservas();
void buscar_reservas_x_nroSocio(int);
bool buscar_reserva_x_nroReserva(int);
bool existe_reserva(int);
int cantidad_de_reservas();
void buscar_reserva_x_cancha(int);
bool buscarReserva(int,int,int,int,int);
Fecha dia_actual();
void alta_reserva();
void baja_reserva();

class Reserva {
  private:
        int numero_cancha, numero_socio,duracion, numero_reserva;
        Fecha horaReserva;
        Fecha fecha_actual;
        bool estado;
  public:
        int getNroCancha();
        int getNroSocio();
        int getDuracion();
        Fecha getHoraReserva();
        bool getEstado();
        int getNumeroReserva();
        void setNumeroReserva(int);
        void setNroCancha(int);
        void setNroSocio(int);
        void setDuracion(int);
        void setHoraReserva(Fecha);
        void setEstado(bool);
        void cargarReserva();
        void mostrarReserva();
        bool grabarEnDisco();
        int leerDeDisco(int);
        void modificar_en_disco(int);
        void mostrarHoraReserva();
};


    int Reserva::getNumeroReserva(){
        return numero_reserva;
    }

    int Reserva::getNroCancha(){
        return numero_cancha;
    }

    int Reserva::getNroSocio(){
        return numero_socio;
    }

    int Reserva::getDuracion(){
        return duracion;
    }

    Fecha Reserva::getHoraReserva(){
        return horaReserva;
    }

    bool Reserva::getEstado(){
        return estado;
    }

    void Reserva::setNroCancha(int nC){
        numero_cancha=nC;
    }

    void Reserva::setNroSocio(int nS){
        numero_socio = nS;
    }

    void Reserva::setNumeroReserva(int nReserva){
        numero_reserva = nReserva;
    }

    void Reserva::setDuracion(int d){
        duracion = d;
    }

    void Reserva::setHoraReserva(Fecha h){
        horaReserva = h;
    }

    void Reserva::setEstado(bool estado_nuevo){
        estado=estado_nuevo;
    }

    void Reserva::mostrarHoraReserva(){
         cout << horaReserva.dia << "/" << horaReserva.mes << "/" << horaReserva.anio << " " << horaReserva.hora << "hs.";
    }


int Reserva::leerDeDisco(int pos){
    int x;
	FILE *p;
	p=fopen(FILE_RESERVAS,"rb");
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

void Reserva::modificar_en_disco(int pos)
	{
	FILE *p;
	p=fopen(FILE_RESERVAS,"rb+");
	if(p==NULL){cout<<"ERROR DE ARCHIVO";exit(1);}
	fseek(p,pos*sizeof *this,0);
	fwrite(this,sizeof *this,1,p);
	fclose(p);
	}

bool Reserva::grabarEnDisco(){
    FILE *p;
    p = fopen(FILE_RESERVAS, "ab");
    if(p==NULL)return false;
    fwrite(this, sizeof *this, 1, p);
    fclose(p);
    return true;
}

void Reserva::mostrarReserva(){
    cout << endl << "- - - - - - - - - - - - - - - - - - - - - - -" << endl;
    cout << "NUMERO DE RESERVA: " << numero_reserva << endl;
    cout << "NUMERO DE CANCHA: " << numero_cancha << endl;
    cout << "NUMERO DE SOCIO: " << numero_socio << endl;
    cout << "HORA DE RESERVA: " ;
    mostrarHoraReserva() ;
    cout << endl << "DURACION: " << duracion << " hs";
    cout << endl << "- - - - - - - - - - - - - - - - - - - - - - -" << endl;
}

bool buscarReserva(int pos,int anio, int dia,int mes,int hora){
    Reserva reg;
    FILE *p;
    p = fopen(FILE_RESERVAS, "rb");
    if(p==NULL)return false;
    long suma_reserva, suma_reserva_activa;
    suma_reserva = hora + (dia*100) + (mes*10000) + (anio*1000000);
    while(fread(&reg, sizeof(Reserva), 1, p)){
        suma_reserva_activa = reg.getHoraReserva().hora + (reg.getHoraReserva().dia*100) + (reg.getHoraReserva().mes*10000) + (reg.getHoraReserva().anio*1000000);
        if(suma_reserva == suma_reserva_activa && reg.getNroCancha() == pos && reg.getEstado()==true){
            cout << "LA CANCHA " << pos << " YA HA SIDO RESERVADA DE "<< reg.getHoraReserva().hora << "HS HASTA " << reg.getHoraReserva().hora+reg.getDuracion() << " HS" << endl;
            return true;
        }
    }
    fclose(p);
    return false;
}

void buscar_reservas_x_nroSocio(int nro){
    FILE *p;
    p = fopen(FILE_RESERVAS, "rb");
    if(p==NULL){
        system("cls");
        cout << "NO SE PUDO ABRIR EL ARCHIVO";
        cout<<"Presione una tecla para continuar";
        system("pause<null");
        return;
    }
    Reserva reg;
    int reservas = 0;
    while(fread(&reg, sizeof(Reserva), 1, p)){
        if(reg.getNroSocio()==nro && reg.getEstado()==true && es_mayor_o_igual_a_la_fecha_actual(reg.getHoraReserva())){
            reg.mostrarReserva();
            reservas++;
        }
    }

    if(reservas!=0){
        cout<<"Presione una tecla para continuar";
        system("pause<null");
        fclose(p);
        return;
    }

    cout << "EL SOCIO NO TIENE RESERVAS ACTIVAS" << endl;
    fclose(p);
    cout << "presione una tecla para continuar";
    system("pause>nul");
}

void Reserva::cargarReserva(){

    int cant_reservas;
    long fecha_hoy, fecha_ingresada;

    time_t t = time(NULL);
    struct tm today = *localtime(&t);
    fecha_actual.mes = today.tm_mon + 1;
    fecha_actual.dia = today.tm_mday;
    fecha_actual.anio = (today.tm_year + 1900);
    fecha_actual.hora = today.tm_hour;

    fecha_hoy = (fecha_actual.anio*1000000) + (fecha_actual.mes*10000) + (fecha_actual.dia*100) + fecha_actual.hora;

    cout << "INGRESE EL NUMERO DE CANCHA QUE DESEA RESERVAR(1-5 FUTBOL 6-10 TENNIS):";
    cin >> numero_cancha;
    while (numero_cancha < 1 && numero_cancha >10){
        cout << "INGRESE UN NUMERO DE CANCHA VALIDO(1-10)"<< endl;
        cin >> numero_cancha;
    }
    cout << "IGRESE NUMERO DE SOCIO: ";
    cin >> numero_socio;
    if(!buscarSocioXNro(numero_socio)){
        cout << endl << "EL SOCIO QUE DESEA BUSCAR NO EXISTE EN EL SISTEMA" << endl;
        return;
    }

    cout << "INGRESE FECHA Y HORA DE RESERVA: "<< endl;
    cout << "DIA: ";
    cin >> horaReserva.dia;
    while(horaReserva.dia < 1 || horaReserva.dia > 31){
        cout << "INGRESE UN DIA VALIDO (1-31): ";
        cin >> horaReserva.dia;
    }
    cout << "MES: ";
    cin >> horaReserva.mes;
    while(horaReserva.mes < 1 || horaReserva.mes > 12){
        cout << "INGRESE UN MES VALIDO (1-12): ";
        cin >> horaReserva.mes;
    }
    cout << "ANIO: ";
    cin >> horaReserva.anio;

    while(horaReserva.anio < fecha_actual.anio){
        cout << "INGRESE UN ANIO VALIDO MAYOR O IGUAL A " << fecha_actual.anio <<" : ";
        cin >> horaReserva.anio;
    }
        cout << "HORA: ";
    cin >> horaReserva.hora;
    while(horaReserva.hora < 9 || horaReserva.hora > 21){
        cout << "INGRESE UNA HORA VALIDA (9-21): ";
        cin >> horaReserva.hora;
    }

    while(!es_mayor_o_igual_a_la_fecha_actual(horaReserva)){

        cout << endl << "LA FECHA INGRESADA ES MENOR QUE LA DEL SISTEMA; INGRESE UNA FECHA VALIDA PARA LA RESERVA: " << endl;

        cout << "INGRESE FECHA Y HORA DE RESERVA: "<< endl;

        cout << "DIA: ";
        cin >> horaReserva.dia;
        while(horaReserva.dia < 1 || horaReserva.dia > 31){
            cout << "INGRESE UN DIA VALIDO (1-31): ";
            cin >> horaReserva.dia;
        }

        cout << "MES: ";
        cin >> horaReserva.mes;
        while(horaReserva.mes < 1 || horaReserva.mes > 12){
            cout << "INGRESE UN MES VALIDO (1-12): ";
            cin >> horaReserva.mes;
        }

        cout << "ANIO: ";
        cin >> horaReserva.anio;

        while(horaReserva.anio < fecha_actual.anio){
            cout << "INGRESE UN ANIO VALIDO MAYOR O IGUAL A " << fecha_actual.anio <<" : ";
            cin >> horaReserva.anio;
        }

            cout << "HORA: ";
        cin >> horaReserva.hora;
        while(horaReserva.hora < 9 || horaReserva.hora > 21){
            cout << "INGRESE UNA HORA VALIDA (9-21): ";
            cin >> horaReserva.hora;
        }
    }

    while(buscarReserva(numero_cancha,horaReserva.anio,horaReserva.dia,horaReserva.mes,horaReserva.hora)){
        return;
    }

    cout << "INGRESE DURACION DE RESERVA EN HORAS: ";
    cin >> duracion;

    while((duracion + horaReserva.hora)>21){
        cout << "LA DURACION DE LA RESERVA EXCEDE EL HORARIO DE CIERRE" << endl;
        cout << "INGRESE UNA DURACION EN HORAS VALIDA: ";
        cin >> duracion;
    }

    estado = true;

    cant_reservas = cantidad_de_reservas();
    numero_reserva = cant_reservas + 1;

    if(grabarEnDisco()){
        system("cls");
        cout << endl << "SU NUMERO DE RESERVA ES " << numero_reserva;
        cout << endl << "RESERVA GRABADA CON EXITO EN EL DISCO" << endl;
    } else {
        system("cls");
        cout << endl << "NO SE PUDO GUARDAR CORRECTAMENTE LA RESERVA EN EL DISCO, INTENTELO NUEVAMENTE" << endl;
    }

}


void mostrar_todas_las_reservas_x_nro_reserva(){
    FILE *p;
    p = fopen(FILE_RESERVAS, "rb");
    if(p==NULL){
        cout << endl << "NO SE PUDO ABRIR EL ARCHIVO, INTENTALO NUEVAMENTE." << endl;
        return;
    }
    Reserva reg;
    fseek(p, 0, 0);

    long fecha_reserva, fecha_sistema;

    fecha_sistema = (dia_actual().anio*10000) + (dia_actual().mes*100) + dia_actual().dia;

    while(fread(&reg, sizeof(Reserva), 1, p)){
        fecha_reserva = (reg.getHoraReserva().anio*10000) + (reg.getHoraReserva().mes*100) + reg.getHoraReserva().dia;
        if(reg.getEstado()==true && fecha_sistema <= fecha_reserva){
            reg.mostrarReserva();
            cout << endl;
        }
    }
    fclose(p);
}

Fecha dia_actual(){

    time_t t = time(NULL);
    struct tm today = *localtime(&t);

    Fecha fActual;

    fActual.mes = today.tm_mon + 1;
    fActual.dia = today.tm_mday;
    fActual.anio = (today.tm_year + 1900);
    fActual.hora = today.tm_hour;

    return fActual;
}

void buscar_reserva_x_cancha(int nCancha){
    FILE *p;
    p = fopen(FILE_RESERVAS, "rb");
    if(p==NULL){
        cout << endl << "NO SE PUDO ABRIR EL ARCHIVO, INTENTALO NUEVAMENTE." << endl;
        return;
    }
    Reserva reg;

    long dia_sistema, dia_reserva;
    int lista_horarios[12]={0};
    int hora_reserva;
    dia_sistema = (dia_actual().anio*10000) + (dia_actual().mes*100) + dia_actual().dia;

    cout << endl << "CANCHA NUMERO " << nCancha << ": " << endl;
    while(fread(&reg, sizeof(Reserva),1, p)){
        dia_reserva = (reg.getHoraReserva().anio*10000) + (reg.getHoraReserva().mes*100) + reg.getHoraReserva().dia;
        if(dia_reserva == dia_sistema && reg.getEstado()==true && reg.getNroCancha()==nCancha){
            hora_reserva = reg.getHoraReserva().hora;
            for(int i = 0; i < reg.getDuracion(); i++){
                lista_horarios[(hora_reserva-9)+i]=1;
            }
        }
   }

    for(int t = 0; t < 13; t++){
        cout << (t+9) << ":00 ESTADO: ";
        if(lista_horarios[t]==1){
            cout << "RESERVADO" << endl;
        } else {
            cout << "DISPONIBLE" << endl;
        }
    }

    cout << endl;
    fclose(p);

}

void mostrar_todas_las_reservas(){

    cout << "RESERVAS DEL DIA " << dia_actual().dia << "/" << dia_actual().mes << "/" << dia_actual().anio << " : " << endl;

    for(int j = 1; j <= 10; j++){
        buscar_reserva_x_cancha(j);
    }
    cout << "presione una tecla para continuar";
    system("pause>nul");
}

void alta_reserva(){
    Reserva reg;
    reg.cargarReserva();
    cout << "presione una tecla para continuar";
    system("pause>nul");
}

int cantidad_de_reservas(){
    FILE *p;
    int cant_reservas;
    p = fopen(FILE_RESERVAS, "rb");
    if(p==NULL){
        p = fopen(FILE_RESERVAS, "wb");
        fclose(p);
        p = fopen(FILE_RESERVAS, "rb");
    }
    fseek(p, 0, 2);
    long cantBytes = ftell(p);
    fclose(p);
    cant_reservas = (int ) cantBytes / sizeof(struct Reserva);
    return cant_reservas;

}

bool buscar_reserva_x_nroReserva(int nReserva){
    FILE *p;
    p = fopen(FILE_RESERVAS, "rb");
    if(p==NULL){cout << "NO SE PUDO ABRIR EL ARCHIVO" << endl; return false;};
    Reserva reg;
    long fecha_actual, fecha_reserva;
    fecha_actual = dia_actual().hora + (dia_actual().dia*100) + (dia_actual().mes*10000) + (dia_actual().anio*1000000);
    while(fread(&reg, sizeof(Reserva), 1, p)){
        fecha_reserva = reg.getHoraReserva().hora + (reg.getHoraReserva().dia*100) + (reg.getHoraReserva().mes*10000) + (reg.getHoraReserva().anio*1000000);
        if(reg.getNumeroReserva()==nReserva && reg.getEstado()==true && fecha_actual <= fecha_reserva){
            reg.mostrarReserva();
            fclose(p);
            return true;
        }
    }
    fclose(p);
    cout << endl << "NO HAY NINGUNA RESERVA CON ESE NUMERO" << endl;
    return false;
}

void baja_reserva(){

    int nReserva;
    char opcion;
    Reserva reg;

    cout << "INGRESE EL NUMERO DE RESERVA QUE DESEA ELIMINAR: ";
    cin >> nReserva;

    if(buscar_reserva_x_nroReserva(nReserva)){
        reg.leerDeDisco(nReserva -1);
        cout << "SEGURO QUE DESEA ELIMINAR LA RESERVA (S/N): ";
        cin >> opcion;
        switch(opcion){
            case 'S':
            case 's':
                reg.setEstado(false);
                reg.modificar_en_disco(nReserva -1);
                cout << "RESERVA DADA DE BAJA CORRECTAMENTE" << endl;
                break;
            case 'N':
            case 'n':
                cout << endl << "LA BAJA DE RESERVA ABORTADA" << endl;
                break;
            default:
                break;
        }
    }

    cout << "presione una tecla para continuar";
    system("pause>nul");
}


void modificar_fecha_reserva(){
    int nReserva;
    Fecha fNueva;
    char opcion;
    Reserva reg;

    cout << "INGRESE EL NUMERO DE LA RESERVA QUE DESEA MODIFICAR: ";
    cin >> nReserva;
    if(buscar_reserva_x_nroReserva(nReserva)){
        reg.leerDeDisco(nReserva -1);
        cout << endl << "SEGURO QUE DESEA MODIFICARLA (S/N): ";
        cin >> opcion;
        switch(opcion){
            case 'S':
            case 's':
                cout << endl << "INGRESE LOS DATOS DE SU FECHA DE RESERVA: ";
                cout << "DIA: ";
                cin >> fNueva.dia;
                while(fNueva.dia < 1 || fNueva.dia > 31){
                    cout << "INGRESE UN DIA VALIDO (1-31): ";
                    cin >> fNueva.dia;
                }

                cout << "MES: ";
                cin >> fNueva.mes;
                while(fNueva.mes < 1 || fNueva.mes > 12){
                    cout << "INGRESE UN MES VALIDO (1-12): ";
                    cin >> fNueva.mes;
                }

                cout << "ANIO: ";
                cin >> fNueva.anio;

                while(fNueva.anio < dia_actual().anio){
                    cout << "INGRESE UN ANIO VALIDO MAYOR O IGUAL A "; cout << dia_actual().anio; cout <<" : ";
                    cin >> fNueva.anio;
                }

                    cout << "HORA: ";
                cin >> fNueva.hora;
                while(fNueva.hora < 9 || fNueva.hora > 21){
                    cout << "INGRESE UNA HORA VALIDA (9-21): ";
                    cin >> fNueva.hora;
                }

                while(!es_mayor_o_igual_a_la_fecha_actual(fNueva)){

                    cout << endl << "LA FECHA INGRESADA ES MENOR QUE LA DEL SISTEMA; INGRESE UNA FECHA VALIDA PARA LA RESERVA: " << endl;

                    cout << "INGRESE FECHA Y HORA DE RESERVA: "<< endl;

                    cout << "DIA: ";
                    cin >> fNueva.dia;
                    while(fNueva.dia < 1 || fNueva.dia > 31){
                        cout << "INGRESE UN DIA VALIDO (1-31): ";
                        cin >> fNueva.dia;
                    }

                    cout << "MES: ";
                    cin >> fNueva.mes;
                    while(fNueva.mes < 1 || fNueva.mes > 12){
                        cout << "INGRESE UN MES VALIDO (1-12): ";
                        cin >> fNueva.mes;
                    }

                    cout << "ANIO: ";
                    cin >> fNueva.anio;

                    while(fNueva.anio < dia_actual().anio){
                        cout << "INGRESE UN ANIO VALIDO MAYOR O IGUAL A "; cout << dia_actual().anio; cout <<" : ";
                        cin >> fNueva.anio;
                    }

                        cout << "HORA: ";
                    cin >> fNueva.hora;
                    while(fNueva.hora < 9 || fNueva.hora > 21){
                        cout << "INGRESE UNA HORA VALIDA (9-21): ";
                        cin >> fNueva.hora;
                    }
                }

                while(buscarReserva(reg.getNroCancha(),fNueva.anio,fNueva.dia,fNueva.mes,fNueva.hora)){
                    return;
                }

                reg.setHoraReserva(fNueva);
                reg.modificar_en_disco(nReserva -1);
                cout << endl << "LA RESERVA SE MODIFICO CORRECTAMENTE" << endl;
                break;
            case 'N':
            case 'n':
                cout << endl << "EDICION DE RESERVA ABORTADA" << endl;
                break;
            default:
                break;
        }
    } else {
        cout << "NO EXISTE UNA RESERVA CON ESE NUMERO" << endl;
    }

    cout << "presione una tecla para continuar";
    system("pause>nul");
}

void modificar_cancha_reserva(){
    int nReserva;
    int nCancha;
    char opcion;
    Reserva reg;

    cout << "INGRESE EL NUMERO DE RESERVA QUE DESEA MODIFICAR: ";
    cin >> nReserva;

    if(buscar_reserva_x_nroReserva(nReserva)){
        reg.leerDeDisco(nReserva -1);

        cout << endl << "INGRESE EL NUEVO NUMERO DE CANCHA: ";
        cin >> nCancha;
        while(nCancha < 1 || nCancha > 10){
            cout << "NUMERO DE CANCHA INVALIDO (1-5 FUTBOL 6-10 TENNIS): ";
            cout << endl << "INGRESE EL NUEVO NUMERO DE CANCHA: ";
            cin >> nCancha;
        }

        if(buscarReserva(nCancha, reg.getHoraReserva().anio, reg.getHoraReserva().dia, reg.getHoraReserva().mes, reg.getHoraReserva().hora)){
            return;
        }

        cout << "SEGURO QUE DESEA EDITAR LA RESERVA (S/N): ";
        cin >> opcion;
        switch(opcion){
            case 'S':
            case 's':
                reg.setNroCancha(nCancha);
                reg.modificar_en_disco(nReserva -1);
                cout << "RESERVA MODIFICADA CORRECTAMENTE" << endl;
                break;
            case 'N':
            case 'n':
                cout << endl << "EDICION DE RESERVA ABORTADA" << endl;
                break;
            default:
                break;
        }
    }

    cout << "presione una tecla para continuar";
    system("pause>nul");
}

void modificar_duracion_reserva(){
    int nReserva;
    int duracion;
    char opcion;
    Reserva reg;

    cout << "INGRESE EL NUMERO DE RESERVA QUE DESEA MODIFICAR: ";
    cin >> nReserva;

    if(buscar_reserva_x_nroReserva(nReserva)){
        reg.leerDeDisco(nReserva -1);

        cout << endl << "INGRESE LA NUEVA DURACION EN HORAS DE LA RESERVA: ";
        cin >> duracion;
        while((duracion + reg.getHoraReserva().hora)>21){
            cout << "LA DURACION DE LA RESERVA EXCEDE EL HORARIO DE CIERRE" << endl;
            cout << "INGRESE UNA DURACION EN HORAS VALIDA: ";
            cin >> duracion;
        }

        cout << "SEGURO QUE DESEA EDITAR LA RESERVA (S/N): ";
        cin >> opcion;
        switch(opcion){
            case 'S':
            case 's':
                reg.setDuracion(duracion);
                reg.modificar_en_disco(nReserva -1);
                cout << "RESERVA MODIFICADA CORRECTAMENTE" << endl;
                break;
            case 'N':
            case 'n':
                cout << endl << "EDICION DE RESERVA ABORTADA" << endl;
                break;
            default:
                break;
        }
    }

    cout << "presione una tecla para continuar";
    system("pause>nul");
}

#endif // RESERVADECANCHA_H_INCLUDED
