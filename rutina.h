#ifndef RUTINA_H_INCLUDED
#define RUTINA_H_INCLUDED

const char *FILE_RUTINAS = "rutinas.dat";
const char *NIVEL_1 = "PRINCIPIANTE";
const char *NIVEL_2 = "INTERMEDIO";
const char *NIVEL_3 = "AVANZADO";
const char *TIPO_RESISTENCIA = "RESISTENCIA";
const char *TIPO_HIPERTROFIA = "HIPERFROFIA";
const char *TIPO_FUERZA_MAXIMA = "FUERZA MAXIMA";


///Prototipo de funciones externas
int cantidad_de_rutinas();
bool buscarRutina(int);
void modificar_duracion_rutina();
void modificar_tipo_de_rutina();
void modificar_nivel_de_rutina();
void baja_logica_rutina();
bool buscar_rutina_x_codigo(int);
bool existe_la_rutina(int, char*,char*);
void mostrar_rutinas_x_codigo();
void mostrar_rutinas_x_niveles();
void mostrar_rutinas_x_tipos();
void alta_rutina();




class Rutina {
    protected:
        int codigo_rutina, duracion_minutos;
        char tipo_rutina[30], nivel_rutina[30];
        bool estado;
    public:
        int getCodigoRutina(){return codigo_rutina;};
        int getDuracionMinutos(){return duracion_minutos;};
        char* getTipoRutina(){return tipo_rutina;};
        char* getNivelRutina(){return nivel_rutina;};
        bool getEstado(){return estado;};
        void setDuracionMinutos(int duracion){duracion_minutos = duracion;};
        void setCodigoRutina(int codigo){codigo_rutina = codigo;};
        void setTipoRutina(const char* tipo){strcpy(tipo_rutina, tipo);};
        void setNivelRutina(const char* nivel){strcpy(nivel_rutina, nivel);};
        void setEstado(bool estado_actual){estado = estado_actual;};
        void mostrarRutina();
        int leer_disco(int);
        void modificar_en_disco(int pos);
        void cargarRutina();
        bool grabarEnDisco();
};

void Rutina::mostrarRutina(){
    cout << "- - - - - - - - - - - - - - - - - - - - - - -" << endl;
    cout << "CODIGO DE RUTINA: " << codigo_rutina << endl;
    cout << "DURACION EN MINUTOS DE RUTINA: " << duracion_minutos << endl;
    cout << "TIPO DE RUTINA: " << tipo_rutina << endl;
    cout << "NIVEL DE RUTINA: " << nivel_rutina;
    cout << endl << "- - - - - - - - - - - - - - - - - - - - - - -" << endl;
}

int Rutina::leer_disco(int pos){
    int x;
	FILE *p;
	p=fopen(FILE_RUTINAS,"rb");
	if(p==NULL)
		{
		cout<<"No existe el archivo";
		cout<<"Presione una tecla para continuar";
        system("pause<null");
		return 0;
		}
	fseek(p,pos*sizeof *this,0);
	x=fread(this,sizeof *this,1,p);
	fclose(p);
	return x;
}

void Rutina::modificar_en_disco(int pos)
	{
	FILE *p;
	p=fopen(FILE_RUTINAS,"rb+");
	if(p==NULL){cout<<"ERROR DE ARCHIVO";exit(1);}
	fseek(p,pos*sizeof *this,0);
	fwrite(this,sizeof *this,1,p);
	fclose(p);
	}

bool Rutina::grabarEnDisco(){
    FILE *p;
    p = fopen(FILE_RUTINAS, "ab");
    if(p==NULL)return false;
    fwrite(this, sizeof *this, 1, p);
    fclose(p);
    return true;
}

void Rutina::cargarRutina(){

    int opc_tipo_rutina, opc_nivel;
    bool tRutina = true, nRutina = true;

    cout << endl << "DURACION EN MINUTOS DE RUTINA: ";
    cin >> duracion_minutos;


    cout << endl << "1) RESISTENCIA";
    cout << endl << "2) HIPERTROFIA";
    cout << endl << "3) FUERZA_MAXIMA";

    while(tRutina){

        cout << endl << "OPCION DE TIPO DE RUTINA: ";
        cin >> opc_tipo_rutina;

        switch(opc_tipo_rutina){
        case 1:
            strcpy(tipo_rutina, TIPO_RESISTENCIA);
            tRutina = false;
            break;
        case 2:
            strcpy(tipo_rutina, TIPO_HIPERTROFIA);
            tRutina = false;
            break;
        case 3:
            strcpy(tipo_rutina, TIPO_FUERZA_MAXIMA);
            tRutina = false;
            break;
        default:
            cout << "INGRESE UNA OPCION VALIDA" << endl;
            break;
        }
    }

    cout << endl << "1) NIVEL PRINCIPIANTE";
    cout << endl << "2) NIVEL INTERMEDIO";
    cout << endl << "3) NIVEL AVANZADO";

    while(nRutina){
        cout << endl << "OPCION DE NIVEL DE RUTINA: ";
        cin >> opc_nivel;

        switch(opc_nivel){
            case 1:
            strcpy(nivel_rutina, NIVEL_1);
            nRutina = false;
            break;
        case 2:
            strcpy(nivel_rutina, NIVEL_2);
            nRutina = false;
            break;
        case 3:
            strcpy(nivel_rutina, NIVEL_3);
            nRutina = false;
            break;
        default:
            cout << "INGRESE UNA OPCION VALIDA" << endl;
            break;
        }
    }

    codigo_rutina = (cantidad_de_rutinas() + 1);
    estado = true;

    if(existe_la_rutina(duracion_minutos, tipo_rutina, nivel_rutina)){
        cout << endl << "LA RUTINA YA EXISTE" << endl;
        return;
    }

    system("cls");
    if(grabarEnDisco()){
        cout << "CODIGO DE RUTINA: " << codigo_rutina << endl;
        cout << "RUTINA CARGADA CORRECTAMENTE" << endl;
    } else {
        cout << "NO SE PUDO CARGAR LA RUTINA EN LA BASE DE DATOS" << endl;
    }
}


///- - - FUNCIONES GLOBALES - - -

bool existe_la_rutina(int dRutina, char *tipoRutina, char *nivelRutina){
    FILE *p;
    p = fopen(FILE_RUTINAS, "rb");
    if(p==NULL)return false;
    Rutina reg;
    while(fread(&reg, sizeof(Rutina), 1, p)){
        if(reg.getEstado()==true && reg.getDuracionMinutos()==dRutina && strcmp(reg.getTipoRutina(), tipoRutina)==0 && strcmp(reg.getNivelRutina(),nivelRutina)==0){
            return true;
        }
    }
    return false;
}


int cantidad_de_rutinas(){
    FILE *p;
    int cant_rutinas;
    p = fopen(FILE_RUTINAS, "rb");
    if(p==NULL){
        p = fopen(FILE_RUTINAS, "wb");
        fclose(p);
        p = fopen(FILE_RUTINAS, "rb");
    }
    fseek(p, 0, 2);
    long cantBytes = ftell(p);
    fclose(p);
    cant_rutinas = (int ) cantBytes / sizeof(struct Rutina);
    return cant_rutinas;
}

bool buscarRutina(int pos){
    FILE *p;
    p = fopen(FILE_RUTINAS, "rb");
    if(p==NULL)return false;
    Rutina reg;
    while(fread(&reg, sizeof(Rutina), 1, p)){
        if(reg.getCodigoRutina()==pos){
            fclose(p);
            return true;
        }
    }
    fclose(p);
    return false;
}


void baja_logica_rutina(){
    int pos_rutina;
    Rutina reg;
    cout << "INGRESE EL CODIGO DE RUTINA QUE DESEA ELIMINAR: ";
    cin >> pos_rutina;
    if(buscarRutina(pos_rutina)){
        reg.leer_disco(pos_rutina);
        reg.setEstado(false);
        reg.modificar_en_disco(pos_rutina);
        cout << "RUTINA DADA DE BAJA CORRECTAMENTE" << endl;
    } else {
        cout << "NO EXISTE LA RUTINA QUE DESEA ELIMINAR" << endl;
    }
    cout << "presione una tecla para continuar";
    system("pause>nul");
}

bool buscar_rutina_x_codigo(int codigo){
    FILE *p;
    p = fopen(FILE_RUTINAS, "rb");
    if(p==NULL){
        system("cls");
        cout << "NO SE PUDO ABRIR EL ARCHIVO";
        system("pause");
        return false;
    }
    Rutina reg;
    while(fread(&reg, sizeof(Rutina), 1, p)){
        if(reg.getCodigoRutina()==codigo){
            reg.mostrarRutina();
            cout << "presione una tecla para continuar";
            system("pause>nul");
            fclose(p);
            return true;
        }
    }
    cout << "NO SE ENCONTRO LA RUTINA BUSCADA" << endl;
    fclose(p);
    cout << "presione una tecla para continuar";
    system("pause>nul");
    return false;
}

void mostrar_rutinas_x_codigo(){
    FILE *p;
    p = fopen(FILE_RUTINAS, "rb");
    if(p==NULL){cout << "ERROR EN APERTURA DE ARCHIVO" <<endl; return;};
    Rutina reg;
    while(fread(&reg, sizeof(Rutina), 1, p)){
        if(reg.getEstado()){
            reg.mostrarRutina();
        }
    }
    fclose(p);
}

void mostrar_rutinas_x_niveles(){

    FILE *p;
    p = fopen(FILE_RUTINAS, "rb");
    if(p==NULL){cout << "ERROR EN APERTURA DE ARCHIVO" <<endl; return;};
    Rutina reg;

    fseek(p, 0, 0);
    cout << "________________________________________________________________" << endl;
    cout << "                  NIVEL 1 : PRINCIPIANTES" << endl;
    while(fread(&reg, sizeof(Rutina), 1, p)){
        if(reg.getEstado()==true && strcmp(reg.getNivelRutina(), NIVEL_1)==0){
            reg.mostrarRutina();
        }
    }

    fseek(p, 0, 0);
    cout << "________________________________________________________________" << endl;
    cout << "                  NIVEL 2 : INTERMEDIO" << endl;
    while(fread(&reg, sizeof(Rutina), 1, p)){
        if(reg.getEstado()==true && strcmp(reg.getNivelRutina(), NIVEL_2)==0){
            reg.mostrarRutina();
        }
    }

    fseek(p, 0, 0);
    cout << "________________________________________________________________" << endl;
    cout << "                  NIVEL 3 : AVANZADO" << endl;
    while(fread(&reg, sizeof(Rutina), 1, p)){
        if(reg.getEstado()==true && strcmp(reg.getNivelRutina(), NIVEL_3)==0){
            reg.mostrarRutina();
        }
    }
    fclose(p);
}

void mostrar_rutinas_x_tipos(){

    FILE *p;
    p = fopen(FILE_RUTINAS, "rb");
    if(p==NULL){cout << "ERROR EN APERTURA DE ARCHIVO" <<endl; return;};
    Rutina reg;

    fseek(p, 0, 0);
    cout << "________________________________________________________________" << endl;
    cout << "                TIPO DE RUTINA : RESISTENCIA" << endl;
    while(fread(&reg, sizeof(Rutina), 1, p)){
        if(reg.getEstado()==true && strcmp(reg.getTipoRutina(), TIPO_RESISTENCIA)==0){
            reg.mostrarRutina();
        }
    }

    fseek(p, 0, 0);
    cout << "________________________________________________________________" << endl;
    cout << "                TIPO DE RUTINA : HIPERTROFIA" << endl;
    while(fread(&reg, sizeof(Rutina), 1, p)){
        if(reg.getEstado()==true && strcmp(reg.getTipoRutina(), TIPO_HIPERTROFIA)==0){
            reg.mostrarRutina();
        }
    }

    fseek(p, 0, 0);
    cout << "________________________________________________________________" << endl;
    cout << "                TIPO DE RUTINA : FUERZA MAXIMA" << endl;
    while(fread(&reg, sizeof(Rutina), 1, p)){
        if(reg.getEstado()==true && strcmp(reg.getTipoRutina(), TIPO_FUERZA_MAXIMA)==0){
            reg.mostrarRutina();
        }
    }
    fclose(p);
}

void alta_rutina(){
    Rutina reg;
    system("cls");
    reg.cargarRutina();
    cout << "presione una tecla para continuar";
    system("pause>nul");
}

void modificar_duracion_rutina(){
    int nRutina;
    int duracion;
    char opcion;
    Rutina reg;

    cout << "INGRESE EL NUMERO DE RUTINA QUE DESEA MODIFICAR: ";
    cin >> nRutina;

    if(buscar_rutina_x_codigo(nRutina)){
        reg.leer_disco(nRutina -1);

        cout << endl << "INGRESE LA NUEVA DURACION DE LA RUTINA: ";
        cin >> duracion;
        while(existe_la_rutina(duracion, reg.getTipoRutina(), reg.getNivelRutina())){
            cout << endl << "YA HAY UNA MISMA RUTINA CON ESTA DURACION, INGRESE UNA NUEVA DURACION: ";
            cin >> duracion;
        }

        cout << "SEGURO QUE DESEA EDITAR LA RUTINA (S/N): ";
        cin >> opcion;
        switch(opcion){
            case 'S':
            case 's':
                reg.setDuracionMinutos(duracion);
                reg.modificar_en_disco(nRutina -1);
                cout << "RUTINA MODIFICADA CORRECTAMENTE" << endl;
                break;
            case 'N':
            case 'n':
                cout << endl << "EDICION DE RUTINA ABORTADA" << endl;
                break;
            default:
                break;
        }
    }

    cout << "presione una tecla para continuar";
    system("pause>nul");
}

void modificar_tipo_de_rutina(){
    int nRutina;
    int opc_tipo_rutina;
    char opcion;
    Rutina reg;
    bool tRutina = true;

    cout << "INGRESE EL NUMERO DE RUTINA QUE DESEA MODIFICAR: ";
    cin >> nRutina;

    if(buscar_rutina_x_codigo(nRutina)){
        reg.leer_disco(nRutina -1);

        cout << endl << "1) RESISTENCIA";
        cout << endl << "2) HIPERTROFIA";
        cout << endl << "3) FUERZA_MAXIMA";

        while(tRutina){

            cout << endl << "INGRESE EL NUEVO TIPO DE RUTINA: ";
            cin >> opc_tipo_rutina;

            switch(opc_tipo_rutina){
            case 1:
                reg.setTipoRutina(TIPO_RESISTENCIA);
                tRutina = false;
                break;
            case 2:
                reg.setTipoRutina(TIPO_HIPERTROFIA);
                tRutina = false;
                break;
            case 3:
                reg.setTipoRutina(TIPO_FUERZA_MAXIMA);
                tRutina = false;
                break;
            default:
                cout << "INGRESE UNA OPCION VALIDA" << endl;
                break;
            }
        }
        while(existe_la_rutina(reg.getDuracionMinutos(), reg.getTipoRutina(), reg.getNivelRutina())){
            cout << endl << "YA HAY UNA MISMA RUTINA CON ESTE TIPO" << endl;
            cout << "presione una tecla para continuar";
            system("pause>nul");
            return;
        }

        cout << "SEGURO QUE DESEA EDITAR LA RUTINA (S/N): ";
        cin >> opcion;
        switch(opcion){
            case 'S':
            case 's':
                reg.modificar_en_disco(nRutina -1);
                cout << "RUTINA MODIFICADA CORRECTAMENTE" << endl;
                break;
            case 'N':
            case 'n':
                cout << endl << "EDICION DE RUTINA ABORTADA" << endl;
                break;
            default:
                break;
        }
    }

    cout << "presione una tecla para continuar";
    system("pause>nul");
}

void modificar_nivel_de_rutina(){
    int nRutina;
    int opc_nivel_rutina;
    char opcion;
    Rutina reg;
    bool tRutina = true;

    cout << "INGRESE EL NUMERO DE RUTINA QUE DESEA MODIFICAR: ";
    cin >> nRutina;

    if(buscar_rutina_x_codigo(nRutina)){
        reg.leer_disco(nRutina -1);

        cout << endl << "1) NIVEL PRINCIPIANTE";
        cout << endl << "2) NIVEL INTERMEDIO";
        cout << endl << "3) NIVEL AVANZADO";


        while(tRutina){

            cout << endl << "INGRESE EL NUEVO NIVEL DE RUTINA: ";
            cin >> opc_nivel_rutina;

            switch(opc_nivel_rutina){
            case 1:
                reg.setNivelRutina(NIVEL_1);
                tRutina = false;
                break;
            case 2:
                reg.setNivelRutina(NIVEL_2);
                tRutina = false;
                break;
            case 3:
                reg.setNivelRutina(NIVEL_3);
                tRutina = false;
                break;
            default:
                cout << "INGRESE UNA OPCION VALIDA" << endl;
                break;
            }
        }
        while(existe_la_rutina(reg.getDuracionMinutos(), reg.getTipoRutina(), reg.getNivelRutina())){
            cout << endl << "YA HAY UNA MISMA RUTINA CON ESTE NIVEL" << endl;
            cout << "presione una tecla para continuar";
            system("pause>nul");
            return;
        }

        cout << "SEGURO QUE DESEA EDITAR LA RUTINA (S/N): ";
        cin >> opcion;
        switch(opcion){
            case 'S':
            case 's':
                reg.modificar_en_disco(nRutina -1);
                cout << "RUTINA MODIFICADA CORRECTAMENTE" << endl;
                break;
            case 'N':
            case 'n':
                cout << endl << "EDICION DE RUTINA ABORTADA" << endl;
                break;
            default:
                break;
        }
    }

    cout << "presione una tecla para continuar";
    system("pause>nul");
}
#endif // RUTINA_H_INCLUDED
