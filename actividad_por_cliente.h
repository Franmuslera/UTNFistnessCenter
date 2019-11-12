#ifndef ACTIVIDAD_POR_CLIENTE_H_INCLUDED
#define ACTIVIDAD_POR_CLIENTE_H_INCLUDED

static char *FILE_ACTIVIDADES_POR_CLIENTES = "ActividadesXClientes.dat";


void cargarActividadXCliente();
void bajaActividadXCliente();
int buscarPosActividadXCliente(int, int);
void abrirArchivoAct();


class Actividad_x_cliente{
    private:
        int idActividad, nroCliente;
        bool estado;
    public:
        int getIdActividad();
        int getNroCliente();
        bool getEstado();
        void setIdActividad(int);
        void setNroCliente(int);
        void setEstado(bool);
        bool grabarEnDisco();
        int leerDisco(int);
        void modificar_en_disco(int pos);
        void cargarActividadACliente();
        void buscarPosActividadXCliente(int,int);

};

   int Actividad_x_cliente :: getIdActividad(){
   return idActividad;
   }
   int Actividad_x_cliente :: getNroCliente(){
   return nroCliente;
   }
    bool Actividad_x_cliente :: getEstado(){
   return estado;
   }
   void Actividad_x_cliente :: setIdActividad(int id){
       idActividad = id;
   }
   void Actividad_x_cliente :: setNroCliente(int nro){
    nroCliente = nro;
    }
    void Actividad_x_cliente :: setEstado(bool e_nuevo){
    estado = e_nuevo;
    }

    int Actividad_x_cliente::leerDisco(int pos){
    int x = 0;
    FILE *p;
    p = fopen(FILE_ACTIVIDADES_POR_CLIENTES, "rb");
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

void Actividad_x_cliente::modificar_en_disco(int pos)
	{
	FILE *p;
	p=fopen(FILE_ACTIVIDADES_POR_CLIENTES,"rb+");
	if(p==NULL){cout<<"ERROR DE ARCHIVO";exit(1);}
	fseek(p,pos*sizeof *this,0);
	fwrite(this,sizeof *this,1,p);
	fclose(p);
	}

bool Actividad_x_cliente::grabarEnDisco(){
    FILE *p;
    p = fopen(FILE_ACTIVIDADES_POR_CLIENTES, "ab");
    if(p==NULL)return false;
    fwrite(this, sizeof *this, 1, p);
    fclose(p);
    return true;
}

void Actividad_x_cliente::cargarActividadACliente(){



    cout << "INGRESE EL NUMERO DE SOCIO: ";
    cin >> nroCliente;
    if(!buscarSocioXNro(nroCliente)){
        cout << "EL NUMERO DE SOCIO NO EXISTE" << endl;
        return;
    }

    cout << "INGRESE EL ID ACTIVIDAD: ";
    cin >> idActividad;
    if(!buscarActividadXNro(idActividad)){
        cout << "EL ID DE ACTIVIDAD ES INVALIDO" << endl;
        return;
    }

    estado = true;

    abrirArchivoAct();

    if(buscarPosRutinaXCliente(nroCliente,idActividad)!=-1){
        cout << "EL CLIENTE YA TIENE ESTA ASIGNADO A ESTA ACTIVIDAD" << endl;
        return;
    }

    if(grabarEnDisco()){
        cout << "SE GUARDO LA ACTIVIDAD CORRECTAMENTE" << endl;
    } else {
        cout << "NO SE PUDO GUARDAR LA ACTIVIDAD, VUELVA A INTENTARLO" << endl;
    }
}


int buscarPosActividadXCliente(int nSocio, int idActividad){
    int x = 0;
    FILE *p;
    p = fopen(FILE_ACTIVIDADES_POR_CLIENTES, "rb");
    if(p==NULL)return -1;
    Actividad_x_cliente reg;
    while(fread(&reg, sizeof(Actividad_x_cliente), 1,p)){
        x++;
        if(reg.getNroCliente()==nSocio && reg.getIdActividad()==idActividad){
            return x;
        }
    }
    return -1;
}

void abrirArchivoAct(){
    FILE *p;
    p = fopen(FILE_ACTIVIDADES_POR_CLIENTES, "rb");
    if(p==NULL){
        p = fopen(FILE_ACTIVIDADES_POR_CLIENTES, "wb");
        fclose(p);
        p = fopen(FILE_ACTIVIDADES_POR_CLIENTES, "rb");
    }
    fclose(p);
}


void cargarActividadXCliente(){
    Actividad_x_cliente reg;
    reg.cargarActividadACliente();
    cout << endl << "presione una tecla para continuar";
    system("pause>nul");
}

void bajaActividadXCliente(){
    Actividad_x_cliente reg;
    int nSocio, idActividad, pos;
    char opcion;
    cout << "INGRESE EL NUMERO DE CLIENTE: ";
    cin >> nSocio;
    cout << "INGRESE EL CODIGO DE RUTINA: ";
    cin >> idActividad;
    pos = buscarPosActividadXCliente(nSocio, idActividad);
    if(pos!=-1){
        reg.leerDisco(pos);
        cout << "CONFIRMAR BAJA (S/N): ";
        cin >> opcion;
        switch(opcion){
            case 'S':
            case 's':
                reg.setEstado(false);
                reg.modificar_en_disco(pos);
                cout << "BAJA DE ACTIVIDAD REALIZADA" << endl;
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
        cout << "NO EXISTE LA ACTIVIDAD ASIGNADA QUE DESEA ELIMINAR" << endl;
    }
    cout << "presione una tecla para continuar";
    system("pause>nul");
}

#endif // ACTIVIDAD_POR_CLIENTE_H_INCLUDED
