#ifndef NOTICIA_H_INCLUDED
#define NOTICIA_H_INCLUDED


const char *FILE_NOTICIAS = "noticias.dat";

///- - - - - - - - - - - - - - - - - - - - - -

int cantidad_de_noticias();
int obtenerPosicion(char*,int,int);
int cantidadCaracteres(char*,int);
void desdeHasta(char*,int,int);
void mostrarDescripcion(char*);
void alta_noticia();
void mostrar_todas_las_noticias();
bool buscarNoticiaXNro(int);
void baja_noticia();
void modificar_titulo();
void modificar_descripcion();
void modificar_fecha_de_noticia();

///- - - - - - - - - - - - - - - - - - - - - -

class Noticia{
    private:
        char titulo[200], descripcion[200];
        Fecha fecha_de_noticia;
        int id_noticia;
        bool estado;
    public:
        char* getTitulo(){return titulo;};
        char* getDescripcion(){return descripcion;};
        Fecha getFechaNoticia(){return fecha_de_noticia;};
        int getIdNoticia(){return id_noticia;};
        bool getEstado(){return estado;};
        void setTitulo(char*t){strcpy(titulo, t);};
        void setDescripcion(char *d){strcpy(descripcion, d);};
        void setFecha(Fecha f){fecha_de_noticia = f;};
        void setEstado(bool e){estado = e;};
        void setIdNoticia(int id_nuevo){id_noticia = id_nuevo;};
        void cargar_noticia();
        void mostrar();
        bool grabarEnDisco();
        bool leerDeDisco(int);
        void modificar_de_disco(int);
};
bool Noticia::grabarEnDisco(){
    FILE *p;
    p = fopen(FILE_NOTICIAS, "ab");
    if(p==NULL)return false;
    fwrite(this, sizeof *this, 1, p);
    fclose(p);
    return true;
}

bool Noticia::leerDeDisco(int pos){
    FILE *p;
    p = fopen(FILE_NOTICIAS, "rb");
    if(p==NULL) return false;
    if(pos==-1)return false;
    int x;
    fseek(p, pos*sizeof*this,0);
    x = fread(this, sizeof(Noticia), 1, p);
    fclose(p);
    if(x){
        return true;
    } else return false;
}

void Noticia::modificar_de_disco(int pos){
    FILE *p;
    p = fopen(FILE_NOTICIAS, "rb+");
    if(p==NULL){cout<<"ERROR DE ARCHIVO";exit(1);}
    fseek(p,pos*sizeof *this,0);
    fwrite(this,sizeof *this,1,p);
    fclose(p);
}

void Noticia::mostrar(){
    cout << "-------------------------------------------------------------------------" << endl;
    cout << "TITULO:  " << titulo << endl << endl << "DESCRIPCION: ";
    mostrarDescripcion(descripcion);
    cout << endl;
    cout << "FECHA DE CADUCIDAD: ";
    mostrar_fecha_con_barras(fecha_de_noticia);
    cout << endl;
    cout << "-------------------------------------------------------------------------" << endl;
}

void Noticia::cargar_noticia(){
    Fecha fecha_actual;
    fecha_actual = fecha_sistema();

    cout << "INGRESE EL TITULO DE LA NOTICIA: ";
    cargarCadena(titulo,200);

    cout << "INGRESE LA DESCRIPCION (HASTA 200 CARACTERES): " << endl;
    cargarCadena(descripcion,200);

    cout << "FECHA NOTICIA: " << endl;
    cout << "DIA: ";
    cin >> fecha_de_noticia.dia;
    while(fecha_de_noticia.dia < 1 || fecha_de_noticia.dia > 31){
        cout << "INGRESE UN DIA VALIDO (1-31): ";
        cin >> fecha_de_noticia.dia;
    }
    cout << "MES: ";
    cin >> fecha_de_noticia.mes;
    while(fecha_de_noticia.mes < 1 || fecha_de_noticia.mes > 12){
        cout << "INGRESE UN MES VALIDO (1-12): ";
        cin >> fecha_de_noticia.mes;
    }
    cout << "ANIO: ";
    cin >> fecha_de_noticia.anio;
    fecha_de_noticia.hora = fecha_actual.hora;
    while(fecha_de_noticia.anio < 1900 && fecha_de_noticia.anio >  fecha_actual.anio){
        cout << "INGRESE UN ANIO VALIDO (1900-" << fecha_actual.anio <<"): ";
        cin >> fecha_de_noticia.anio;
    }
    id_noticia = (cantidad_de_noticias()+1);
    estado = true;
    if(grabarEnDisco()){
        system("cls");
        cout << endl << "NUMERO DE NOTICIA: " << id_noticia;
        cout << endl << "NOTICIA GRABADA CON EXITO." << endl;
    } else {
        system("cls");
        cout << endl << "NO SE PUDO GUARDAR CORRECTAMENTE LA NOTICIA EN EL DISCO, INTENTELO NUEVAMENTE" << endl;
    }
}

int cantidad_de_noticias(){
    FILE *p;
    int cant_noticias;
    p = fopen(FILE_NOTICIAS, "rb");
    if(p==NULL){
        p = fopen(FILE_NOTICIAS, "wb");
        fclose(p);
        p = fopen(FILE_NOTICIAS, "rb");
    }
    fseek(p, 0, 2);
    long cantBytes = ftell(p);
    fclose(p);
    cant_noticias = (int ) cantBytes / sizeof(struct Noticia);
    return cant_noticias;
}

int obtenerPosicion(char *cadena,int d, int h){
    int pos;
    for (d; d < h; d++){
        if (cadena[d]== ' '){
            pos =  d;
            return pos;
        }
    }
}

int cantidadCaracteres(char *cadena,int tam){
    int pos;
    int i;
    for (i=0 ; i < tam; i++){
        if (cadena[i]== '\0'){
            pos =  i;
            return pos;
        }
    }
}

void desdeHasta(char *desc, int desde, int hasta){
    for (desde ; desde <= hasta ; desde++){
        cout << desc[desde];
    }
    cout << endl;
}

void mostrarDescripcion(char *desc){
    int d=0,cantTotal;
    cantTotal = cantidadCaracteres(desc,200);

    if(cantTotal <= 50){
        desdeHasta(desc,d,cantTotal);
        return;
    }else if (cantTotal <= 100){
        int e;
        e= obtenerPosicion(desc,50,60);
        desdeHasta(desc,d,e);
        desdeHasta(desc,(e+1),cantTotal);
        return;
    }else if (cantTotal <=150){
        int e1,e2;
        e1=obtenerPosicion(desc,50,60);
        e2=obtenerPosicion(desc,100,110);
        desdeHasta(desc,d,e1);
        desdeHasta(desc,(e1+1),e2);
        desdeHasta(desc,(e2+1),cantTotal);
        return;
    }
}

void alta_noticia(){
    Noticia reg;
    system("cls");
    reg.cargar_noticia();
}

void mostrar_todas_las_noticias(){
    FILE *p;
    int contador = 0;
    p = fopen(FILE_NOTICIAS, "rb");
    if(p==NULL){
        cout << endl << "NO SE PUDO ABRIR EL ARCHIVO, INTENTALO NUEVAMENTE." << endl;
        return;
    }
    Noticia reg;
    fseek(p, 0, 0);
    while(fread(&reg, sizeof(Noticia), 1, p)){
        if(reg.getEstado()==true && es_mayor_o_igual_a_la_fecha_actual(reg.getFechaNoticia())){
            reg.mostrar();
            contador++;
            cout << endl;
        }
    }
    fclose(p);
    if(contador==0){
        cout << "NO HAY NOTICIAS PARA MOSTRAR, INTENTELO MAS TARDE" << endl;
    }
    cout << "presione una tecla para continuar";
    system("pause>nul");
}

bool buscarNoticiaXNro(int nro){
    FILE *p;
    p = fopen(FILE_NOTICIAS, "rb");
    if(p==NULL)return false;
    Noticia reg;
    while(fread(&reg, sizeof(Noticia),1 ,p)){
        if(reg.getIdNoticia()==nro && reg.getEstado()==true){
            fclose(p);
            return true;
        }
    }
    fclose(p);
    return false;
}

void mostrar_noticia_x_nro_noticia(int nNoticia){
    FILE *p;
    p = fopen(FILE_NOTICIAS, "rb");
    if(p==NULL){
        cout << endl << "NO SE PUDO ABRIR EL ARCHIVO" << endl;
        return;
    }
    Noticia reg;
    while(fread(&reg, sizeof(Noticia),1 ,p)){
        if(reg.getIdNoticia()==nNoticia && reg.getEstado()==true){
            reg.mostrar();
            fclose(p);
            return;
        }
    }
    fclose(p);
    cout << endl << "NO SE ENCONTRO LA NOTICIA BUSCADA" << endl;
}

void baja_noticia(){
    int nNoticia;
    char opcion;
    Noticia reg;

    system("cls");
    cout << "INGRESE EL NUMERO DEL NOTICIA QUE DESEA ELIMINAR: ";
    cin >> nNoticia;
    if(buscarNoticiaXNro(nNoticia)){
        reg.leerDeDisco(nNoticia -1);
        reg.mostrar();
        cout << endl << "SEGURO QUE DESEA ELIMINARLA (S/N): ";
        cin >> opcion;
        switch(opcion){
            case 'S':
            case 's':
                reg.setEstado(false);
                reg.modificar_de_disco(nNoticia -1);
                cout << endl << "SE ELIMINO CORRECTAMENTE" << endl;
                break;
            case 'N':
            case 'n':
                cout << endl << "ABORTO ELIMINACION DE NOTICIA" << endl;
                break;
            default:
                break;
        }
    } else {
        cout << "NO EXISTE UNA NOTICIA CON ESE NUMERO" << endl;
    }
}

void modificar_fecha_de_noticia(){
    int nNoticia;
    Fecha fNueva;
    char opcion;
    Noticia reg;

    cout << "INGRESE EL NUMERO DE LA NOTICIA QUE DESEA MODIFICAR: ";
    cin >> nNoticia;
    if(buscarNoticiaXNro(nNoticia)){
        reg.leerDeDisco(nNoticia -1);
        reg.mostrar();
        cout << endl << "SEGURO QUE DESEA MODIFICARLO (S/N): ";
        cin >> opcion;
        switch(opcion){
            case 'S':
            case 's':
                cout << endl << "INGRESE LOS DATOS DE LA NUEVA FECHA: ";
                cout << "FECHA DE CADUCIDAD: " << endl;

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
                fNueva.hora = 0;
                while(fNueva.anio < 1900 || fNueva.anio >  fNueva.anio){
                    cout << "INGRESE UN ANIO VALIDO (1900-" << fNueva.anio <<"): ";
                    cin >> fNueva.anio;
                }

                reg.setFecha(fNueva);
                reg.modificar_de_disco(nNoticia -1);
                break;
            case 'N':
            case 'n':
                cout << endl << "ABORTO EDICION DE NOTICIA" << endl;
                break;
            default:
                break;
        }
    } else {
        cout << "NO EXISTE UNA NOTICIA CON ESE NUMERO" << endl;
    }

    cout << "presione una tecla para continuar";
    system("pause>nul");
}

void modificar_titulo(){
    char titulo_nuevo[200];
    int nNoticia;
    char opcion;
    Noticia reg;

    cout << "INGRESE EL NUMERO DE LA NOTICIA QUE DESEA MODIFICAR: ";
    cin >> nNoticia;
    if(buscarNoticiaXNro(nNoticia)){
        reg.leerDeDisco(nNoticia -1);
        reg.mostrar();
        cout << endl << "SEGURO QUE DESEA MODIFICARLO (S/N): ";
        cin >> opcion;
        switch(opcion){
            case 'S':
            case 's':
                cout << endl << "INGRESE EL TITULO NUEVO: ";
                cargarCadena(titulo_nuevo, 200);
                reg.setTitulo(titulo_nuevo);
                reg.modificar_de_disco(nNoticia -1);
                break;
            case 'N':
            case 'n':
                cout << endl << "ABORTO EDICION DE NOTICIA" << endl;
                break;
            default:
                break;
        }
    } else {
        cout << "NO EXISTE UNA NOTICIA CON ESE NUMERO" << endl;
    }

    cout << "presione una tecla para continuar";
    system("pause>nul");
}

void modificar_descripcion(){
    char descripcion_nueva[200];
    int nNoticia;
    char opcion;
    Noticia reg;

    cout << "INGRESE EL NUMERO DE LA NOTICIA QUE DESEA MODIFICAR: ";
    cin >> nNoticia;
    if(buscarNoticiaXNro(nNoticia)){
        reg.leerDeDisco(nNoticia -1);
        reg.mostrar();
        cout << endl << "SEGURO QUE DESEA MODIFICARLO (S/N): ";
        cin >> opcion;
        switch(opcion){
            case 'S':
            case 's':
                cout << endl << "INGRESE EL TITULO NUEVO: ";
                cargarCadena(descripcion_nueva, 200);
                reg.setDescripcion(descripcion_nueva);
                reg.modificar_de_disco(nNoticia -1);
                break;
            case 'N':
            case 'n':
                cout << endl << "ABORTO EDICION DE NOTICIA" << endl;
                break;
            default:
                break;
        }
    } else {
        cout << "NO EXISTE UNA NOTICIA CON ESE NUMERO" << endl;
    }

    cout << "presione una tecla para continuar";
    system("pause>nul");
}
#endif // NOTICIA_H_INCLUDED
