#ifndef RUTINA_H_INCLUDED
#define RUTINA_H_INCLUDED

const char *FILE_RUTINAS = "rutinas.dat";
const char *NIVEL_1 = "PRINCIPIANTE";
const char *NIVEL_2 = "INTERMEDIO";
const char *NIVEL_3 = "AVANZADO";
const char *TIPO_RESISTENCIA = "RESISTENCIA";
const char *TIPO_HIPERTROFIA = "HIPERFROFIA";
const char *TIPO_FUERZA_MAXIMA = "FUERZA_MAXIMA";


//Prototipo de funciones externas
int cantidad_de_rutinas();
bool buscarRutina(int);
void baja_logica_rutina();
void buscar_rutina_x_codigo(int);
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
        void setTipoRutina(char* tipo){strcpy(tipo_rutina, tipo);};
        void setNivelRutina(char* nivel){strcpy(nivel_rutina, nivel);};
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

    cout << endl << "DURACION EN MINUTOS DE RUTINA: ";
    cin >> duracion_minutos;

    cout << "TIPO DE RUTINA: ";
    cargarCadena(tipo_rutina, 30);
    while(strcmp(tipo_rutina, TIPO_RESISTENCIA) && strcmp(tipo_rutina, TIPO_HIPERTROFIA) && strcmp(tipo_rutina, TIPO_FUERZA_MAXIMA)){
        cout << "POR FAVOR INGRESE UN TIPO DE RUTINA VALIDA, LOS DISTINTOS TIPOS SON: ";
        cout << "RESISTENCIA - HIPERTROFIA - FUERZA_MAXIMA" << endl;
        cout << "TIPO DE RUTINA: ";
        cargarCadena(tipo_rutina, 30);
    }

    cout << "NIVEL DE RUTINA (PRINCIPIANTE - INTERMEDIO - AVANZADO): ";
    cargarCadena(nivel_rutina, 30);
    while(strcmp(nivel_rutina, NIVEL_1) && strcmp(nivel_rutina, NIVEL_2) && strcmp(nivel_rutina, NIVEL_3)){
        cout << "INGRESE UN NIVEL DE RUTINA VALIDO (PRINCIPIANTE - INTERMEDIO - AVANZADO)" << endl;
        cout << "NIVEL DE RUTINA: ";
        cargarCadena(nivel_rutina, 30);
    }

    codigo_rutina = (cantidad_de_rutinas() + 1);
    estado = true;

    system("cls");
    if(grabarEnDisco()){
        cout << "CODIGO DE RUTINA: " << codigo_rutina << endl;
        cout << "RUTINA CARGADA CORRECTAMENTE" << endl;
    } else {
        cout << "NO SE PUDO CARGAR LA RUTINA EN LA BASE DE DATOS" << endl;
    }
}


//Funciones externas


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

void buscar_rutina_x_codigo(int codigo){
    FILE *p;
    p = fopen(FILE_RUTINAS, "rb");
    if(p==NULL){
        system("cls");
        cout << "NO SE PUDO ABRIR EL ARCHIVO";
        system("pause");
        exit(1);
    }
    Rutina reg;
    while(fread(&reg, sizeof(Rutina), 1, p)){
        if(reg.getCodigoRutina()==codigo){
            reg.mostrarRutina();
            cout << "presione una tecla para continuar";
            system("pause>nul");
            fclose(p);
            return;
        }
    }
    cout << "NO SE ENCONTRO LA RUTINA BUSCADA" << endl;
    fclose(p);
    cout << "presione una tecla para continuar";
    system("pause>nul");
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
        if(reg.getEstado() && strcmp(reg.getNivelRutina(), NIVEL_1)==0){
            reg.mostrarRutina();
        }
    }

    fseek(p, 0, 0);
    cout << "________________________________________________________________" << endl;
    cout << "                  NIVEL 2 : INTERMEDIO" << endl;
    while(fread(&reg, sizeof(Rutina), 1, p)){
        if(reg.getEstado() && strcmp(reg.getNivelRutina(), NIVEL_2)==0){
            reg.mostrarRutina();
        }
    }

    fseek(p, 0, 0);
    cout << "________________________________________________________________" << endl;
    cout << "                  NIVEL 3 : AVANZADO" << endl;
    while(fread(&reg, sizeof(Rutina), 1, p)){
        if(reg.getEstado() && strcmp(reg.getNivelRutina(), NIVEL_3)==0){
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
        if(reg.getEstado() && strcmp(reg.getTipoRutina(), TIPO_RESISTENCIA)==0){
            reg.mostrarRutina();
        }
    }

    fseek(p, 0, 0);
    cout << "________________________________________________________________" << endl;
    cout << "                TIPO DE RUTINA : HIPERTROFIA" << endl;
    while(fread(&reg, sizeof(Rutina), 1, p)){
        if(reg.getEstado() && strcmp(reg.getTipoRutina(), TIPO_HIPERTROFIA)==0){
            reg.mostrarRutina();
        }
    }

    fseek(p, 0, 0);
    cout << "________________________________________________________________" << endl;
    cout << "                TIPO DE RUTINA : FUERZA MAXIMA" << endl;
    while(fread(&reg, sizeof(Rutina), 1, p)){
        if(reg.getEstado() && strcmp(reg.getTipoRutina(), TIPO_FUERZA_MAXIMA)==0){
            reg.mostrarRutina();
        }
    }
    fclose(p);
}

void alta_rutina(){
    Rutina reg;
    system("cls");
    reg.cargarRutina();
}

#endif // RUTINA_H_INCLUDED
