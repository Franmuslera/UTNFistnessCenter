#ifndef RUTINA_POR_CLIENTE_H_INCLUDED
#define RUTINA_POR_CLIENTE_H_INCLUDED

static char *FILE_RUTINAS_POR_CLIENTES = "RutinasXClientes.dat";


void cargarRutinaXCliente();
void bajaRutinaXCliente();
int buscarPosRutinaXCliente(int, int);
void abrirArchivo();
void mostrar_rutinas_x_cliente(int);
void baja_de_rutina_por_cliente_menu_cliente(int,int);


class Rutina_x_cliente {
    private:
        int numero_socio, codigo_rutina;
        Fecha fecha_inicio;
        bool estado;
    public:
        int getNumeroSocio(){return numero_socio;};
        int getCodigoRutina(){return codigo_rutina;};
        Fecha getFechaInicio(){return fecha_inicio;};
        bool getEstado(){return estado;};
        void setNumeroSocio(int nroSocio){numero_socio = nroSocio;};
        void setCodigoRutina(int codRutina){codigo_rutina = codRutina;};
        void setFechaInicio(Fecha fInicio){fecha_inicio = fInicio;};
        void setEstado(bool estado_nuevo){estado = estado_nuevo;};
        void cargarRutinaACliente();
        bool grabarEnDisco();
        int leerDisco(int);
        void modificar_en_disco(int pos);
        void mostrar();

};

void Rutina_x_cliente::mostrar(){
    cout << "_______________________________________" << endl;
    buscar_rutina_x_codigo(codigo_rutina);
    cout << "_______________________________________" << endl;

}

int Rutina_x_cliente::leerDisco(int pos){
    int x = 0;
    FILE *p;
    p = fopen(FILE_RUTINAS_POR_CLIENTES, "rb");
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

void Rutina_x_cliente::modificar_en_disco(int pos)
	{
	FILE *p;
	p=fopen(FILE_RUTINAS_POR_CLIENTES,"rb+");
	if(p==NULL){cout<<"ERROR DE ARCHIVO";exit(1);}
	fseek(p,pos*sizeof *this,0);
	fwrite(this,sizeof *this,1,p);
	fclose(p);
	}

bool Rutina_x_cliente::grabarEnDisco(){
    FILE *p;
    p = fopen(FILE_RUTINAS_POR_CLIENTES, "ab");
    if(p==NULL)return false;
    fwrite(this, sizeof *this, 1, p);
    fclose(p);
    return true;
}

void Rutina_x_cliente::cargarRutinaACliente(){

    time_t t = time(NULL);
    struct tm today = *localtime(&t);
    fecha_inicio.mes = today.tm_mon + 1;
    fecha_inicio.dia = today.tm_mday;
    fecha_inicio.anio = (today.tm_year + 1900);
    fecha_inicio.hora = today.tm_hour;

    cout << "INGRESE EL NUMERO DE SOCIO: ";
    cin >> numero_socio;
    if(!buscarSocioXNro(numero_socio)){
        cout << "EL NUMERO DE SOCIO NO EXISTE" << endl;
        return;
    }

    cout << "INGRESE EL CODIGO DE RUTINA: ";
    cin >> codigo_rutina;
    if(!buscarRutina(codigo_rutina)){
        cout << "EL CODIGO DE RUTINA ES INVALIDO" << endl;
        return;
    }

    estado = true;

    abrirArchivo();

    if(buscarPosRutinaXCliente(numero_socio,codigo_rutina)!=-1){
        cout << "EL CLIENTE YA TIENE ESTA RUTINA ASIGNADA" << endl;
        return;
    }

    if(grabarEnDisco()){
        cout << "SE GUARDO LA RUTINA CORRECTAMENTE" << endl;
    } else {
        cout << "NO SE PUDO GUARDAR LA RUTINA, VUELVA A INTENTARLO" << endl;
    }
}


int buscarPosRutinaXCliente(int nSocio, int cRutina){
    int x = 0;
    FILE *p;
    p = fopen(FILE_RUTINAS_POR_CLIENTES, "rb");
    if(p==NULL)return -1;
    Rutina_x_cliente reg;
    while(fread(&reg, sizeof(Rutina_x_cliente), 1,p)){
        x++;
        if(reg.getNumeroSocio()==nSocio && reg.getCodigoRutina()==cRutina && reg.getEstado()==true){
            return x;
        }
    }
    return -1;
}

void abrirArchivo(){
    FILE *p;
    p = fopen(FILE_RUTINAS_POR_CLIENTES, "rb");
    if(p==NULL){
        p = fopen(FILE_RUTINAS_POR_CLIENTES, "wb");
        fclose(p);
        p = fopen(FILE_RUTINAS_POR_CLIENTES, "rb");
    }
    fclose(p);
}


void cargarRutinaXCliente(){
    Rutina_x_cliente reg;
    reg.cargarRutinaACliente();
    cout << endl << "presione una tecla para continuar";
    system("pause>nul");
}

void bajaRutinaXCliente(){
    Rutina_x_cliente reg;
    int nSocio, cRutina, pos;
    char opcion;
    cout << "INGRESE EL NUMERO DE CLIENTE: ";
    cin >> nSocio;
    cout << "INGRESE EL CODIGO DE RUTINA: ";
    cin >> cRutina;
    pos = buscarPosRutinaXCliente(nSocio, cRutina);
    if(pos!=-1){
        reg.leerDisco(pos);
        cout << "CONFIRMAR BAJA (S/N): ";
        cin >> opcion;
        switch(opcion){
            case 'S':
            case 's':
                reg.setEstado(false);
                reg.modificar_en_disco(pos);
                cout << "BAJA DE RUTINA REALIZADA" << endl;
                break;
            case 'N':
            case 'n':
                system("cls");
                cout << "LA BAJA SE CANCELO" << endl;
                break;
            default:
                cout << "LA BAJA SE CANCELO" << endl;
                break;
        }
    } else {
        cout << "NO EXISTE LA RUTINA ASIGNADA QUE DESEA ELIMINAR" << endl;
    }
    cout << "presione una tecla para continuar";
    system("pause>nul");
}


void baja_de_rutina_por_cliente_menu_cliente(int cRutina, int nCliente){
    Rutina_x_cliente reg;
    int pos;
    char opcion;
    pos = buscarPosRutinaXCliente(nCliente, cRutina);
    if(pos!=-1){
        reg.leerDisco(pos);
        cout << "CONFIRMAR BAJA (S/N): ";
        cin >> opcion;
        switch(opcion){
            case 'S':
            case 's':
                reg.setEstado(false);
                reg.modificar_en_disco(pos);
                cout << "BAJA DE RUTINA REALIZADA" << endl;
                break;
            case 'N':
            case 'n':
                system("cls");
                cout << "LA BAJA SE CANCELO" << endl;
                break;
            default:
                cout << "LA BAJA SE CANCELO" << endl;
                break;
        }
    } else {
        cout << "NO EXISTE LA RUTINA ASIGNADA QUE DESEA ELIMINAR" << endl;
    }
    cout << endl << "presione una tecla para continuar";
    system("pause>nul");
}

void mostrar_rutinas_x_cliente(int nCliente){
    FILE *p;
    p = fopen(FILE_RUTINAS_POR_CLIENTES, "rb");
    if(p==NULL){
        cout << "NO SE PUDO ABRIR EL ARCHIVO";
        return;
    }
    Rutina_x_cliente reg;
    while(fread(&reg, sizeof(Rutina_x_cliente), 1, p)){
        if(reg.getNumeroSocio()==nCliente && reg.getEstado()==true){
            reg.mostrar();
        }
    }
}


#endif // RUTINA_POR_CLIENTE_H_INCLUDED
