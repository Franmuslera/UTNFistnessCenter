#ifndef RESERVADECANCHA_H_INCLUDED
#define RESERVADECANCHA_H_INCLUDED

const char *FILE_RESERVAS = "reservas.dat";


class Reserva {
  private:
           int nroCancha, nroSocio,duracion;
           Fecha horaReserva;
           Fecha fecha_actual;
           bool estado = true;
  public:
           int getNroCancha();
           int getNroSocio();
           int getDuracion();
           Fecha getHoraReserva();
           bool getEstado();
           void setNroCancha(int);
           void setNroSocio(int);
           void setDuracion(int);
           void setHoraReserva(Fecha);
           void setEstado(bool);
          // Reserva(int,int,int,Fecha);
           void cargarReserva();
           void mostrarReserva();
           bool grabarEnDisco();
           int leerDeDisco(int);
           bool buscarReserva(int,int,int,int);
           void modificar_en_disco(int);
           void mostrar_todas_las_reservas();
           void mostrar_reservas_x_horario();
           void mostrarHoraReserva();
           bool buscar_reserva_x_cancha(int);

};

    int Reserva::getNroCancha(){
     return nroCancha;
     }
     int Reserva::getNroSocio(){
     return nroSocio;
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
     nroCancha=nC;
     }
     void Reserva::setNroSocio(int nS){
     nroSocio = nS;
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
     /*Reserva::Reserva(int nroCancha_const,int nroSocio_const,int duracion_const,Fecha horaReserva_const){
     nroCancha = nroCancha_const;
     nroSocio = nroSocio_const;
     duracion = duracion_const;
     horaReserva = horaReserva_const;

     }*/




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

bool buscarReserva(int pos,int dia,int mes,int hora){
    Reserva reg;
    FILE *p;
    p = fopen(FILE_RESERVAS, "rb");
    if(p==NULL)return false;
    int suma;
    suma = reg.getDuracion();
    while(fread(&reg, sizeof(Reserva), 1, p)){
        if(reg.getNroCancha()==pos && reg.getHoraReserva().dia==dia &&reg.getHoraReserva().mes == mes && reg.getHoraReserva().hora == hora){
                cout << "LA CANCHA YA HA SIDO RESERVADA DE "<< reg.getHoraReserva().hora << " HASTA " << reg.getHoraReserva().hora+suma;
        system("pause");
            return true;
        }
    }
    fclose(p);
    return false;
}

void buscar_reserva_x_nroSocio(int nro){
    FILE *p;
    p = fopen(FILE_RESERVAS, "rb");
    if(p==NULL){
        system("cls");
        cout << "NO SE PUDO ABRIR EL ARCHIVO";
        system("pause");
        exit(1);
    }
    Reserva reg;
    while(fread(&reg, sizeof(Reserva), 1, p)){
        if(reg.getNroSocio()==nro){
            reg.mostrarReserva();
            cout << "presione una tecla para continuar";
            system("pause");
            fclose(p);
            return;
        }
    }
    cout << "NO SE ENCONTRO LA RESERVA BUSCADA" << endl;
    fclose(p);
    cout << "presione una tecla para continuar";
    system("pause>nul");
}

 void Reserva::cargarReserva(){

      time_t t = time(NULL);
        struct tm today = *localtime(&t);
        fecha_actual.mes = today.tm_mon + 1;
        fecha_actual.dia = today.tm_mday;
        fecha_actual.anio = (today.tm_year + 1900);

    cout << "INGRESE EL NUMERO DE CANCHA QUE DESEA RESERVAR(1-5 FUTBOL 6-10 TENNIS):";
    cin >> nroCancha;
    while (nroCancha < 1 && nroCancha >10){
        cout << "INGRESE UN NUMERO DE CANCHA VALIDO(1-10)"<< endl;
        cin >> nroCancha;
    }
    cout << "IGRESE NUMERO DE SOCIO: ";
    cin >> nroSocio;

    cout << "INGRESE FECHA Y HORA DE RESERVA: "<< endl;
    cout << "DIA: ";
    cin >> horaReserva.dia;
     while(horaReserva.dia < 1 && horaReserva.dia > 31){
            cout << "INGRESE UN DIA VALIDO (1-31): ";
            cin >> horaReserva.dia;
        }
        cout << "MES: ";
    cin >> horaReserva.mes;
     while(horaReserva.mes < 1 && horaReserva.mes > 12){
            cout << "INGRESE UN MES VALIDO (1-12): ";
            cin >> horaReserva.mes;
        }
        cout << "ANIO: ";
    cin >> horaReserva.anio;
     while(horaReserva.anio < 1 && horaReserva.anio > fecha_actual.anio){
            cout << "INGRESE UN ANIO VALIDO (1900-" << fecha_actual.anio <<"): ";
            cin >> horaReserva.anio;
        }
        cout << "HORA: ";
    cin >> horaReserva.hora;
     while(horaReserva.hora < 9 && horaReserva.hora > 24){
            cout << "INGRESE UNA HORA VALIDA (9-24): ";
            cin >> horaReserva.hora;
        }
      while(buscarReserva(nroCancha,horaReserva.dia,horaReserva.mes,horaReserva.hora)){
            cout << "INGRESE OTRA HORA DE RESERVA: ";
            cin >> horaReserva.hora;
        }
        cout << "INGRESE DURACION DE RESERVA: ";
        cin >> duracion;
        if(grabarEnDisco()){
            system("cls");
            cout << endl << "RESERVA GRABADA CON EXITO EN EL DISCO" << endl;
        } else {
            system("cls");
            cout << endl << "NO SE PUDO GUARDAR CORRECTAMENTE LA RESERVA EN EL DISCO, INTENTELO NUEVAMENTE" << endl;
        }


 }
  void Reserva::mostrarReserva(){
     cout << "- - - - - - - - - - - - - - - - - - - - - - -" << endl;
    cout << "NUMERO DE CANCHA: " << nroCancha << endl;
    cout << "NUMERO DE SOCIO: " << nroSocio << endl;
    cout << "HORA DE RESERVA: " ;
    mostrarHoraReserva() ;
    cout << "DURACION: " << duracion;
    cout << endl << "- - - - - - - - - - - - - - - - - - - - - - -" << endl;
    }
   void mostrar_todas_las_reservas(){
        FILE *p;
        p = fopen(FILE_RESERVAS, "rb");
        if(p==NULL){
            cout << endl << "NO SE PUDO ABRIR EL ARCHIVO, INTENTALO NUEVAMENTE." << endl;
            return;
        }
        Reserva reg;
        fseek(p, 0, 0);
        while(fread(&reg, sizeof(Reserva), 1, p)){
            reg.mostrarReserva();
            cout << endl;
        }

        fclose(p);
    }






#endif // RESERVADECANCHA_H_INCLUDED
