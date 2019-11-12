#ifndef SOCIO_H_INCLUDED
#define SOCIO_H_INCLUDED

const char *FILE_SOCIOS = "socios.dat";

 void buscar_actividad_x_id();


/// - - - DECLARACION DE FUNCIONES GLOBALES - - -

bool es_mayor_o_igual_a_la_fecha_actual(Fecha);
void alta_socio();
void baja_socio();
void modificar_nombre_socio();
void modificar_apellido_socio();
void modificar_telefono_socio();
void modificar_direccion_socio();
void modificar_email_socio();
void modificar_dni_socio();
void modificar_fecha_nacimiento_socio();
void modificar_sexo_socio();
int cantidad_de_socios();
bool buscarDNI(long);
bool buscarSocioXNro(int);
void cargarCadena(char*, int);
void buscar_socio_por_nro(int);
void mostrar_todos_los_socios();

/// - - - DECLARACION DE CLASE - - -

class Socio: public Persona{
    private:

        int nroSocio;
        long telefono;
        char email[100], direccion[100];
    public:

        int getNroSocio();
        long getTelefono();
        char* getEmail();
        char* getDireccion();
        void setNroSocio(int);
        void setTelefono(long);
        void setEmail(char*);
        void setDireccion(char*);
        void mostrar();
        void cargar();
        bool grabarEnDisco();
        bool leerDeDisco(int);
        void modificar_de_disco(int);

};

///- - - - - - - - - - - - GETERS - - - - - - - - -

    int Socio::getNroSocio(){
        return nroSocio;
    }

    long Socio::getTelefono(){
        return telefono;
    }

    char* Socio::getEmail(){
        return email;
    }

    char* Socio::getDireccion(){
        return direccion;
    }

    ///- - - - - - - - - - - - - SETERS - - - - - - - - - -

    void Socio::setNroSocio(int n){
        nroSocio = n;
    }

    void Socio::setTelefono(long t){
        telefono = t;
    }

    void Socio::setEmail(char *e){
        strcpy(email, e);
    }

    void Socio::setDireccion(char *d){
        strcpy(direccion, d);
    }

    ///- - - - - - - - - - - - FUNCIONES PUBLICAS - - - - - - - - - - - - - -


    bool Socio::grabarEnDisco(){
        FILE *p;
        p = fopen(FILE_SOCIOS, "ab");
        if(p==NULL)return false;
        fwrite(this, sizeof *this, 1, p);
        fclose(p);
        return true;
    }

    bool Socio::leerDeDisco(int pos){
        FILE *p;
        p = fopen(FILE_SOCIOS, "rb");
        if(p==NULL) return false;
        if(pos==-1)return false;
        int x;
        fseek(p, pos*sizeof*this,0);
        x = fread(this, sizeof(Socio), 1, p);
        fclose(p);
        if(x){
            return true;
        } else return false;
    }

    void Socio::modificar_de_disco(int pos){
        FILE *p;
        p = fopen(FILE_SOCIOS, "rb+");
        if(p==NULL){cout<<"ERROR DE ARCHIVO";exit(1);}
        fseek(p,pos*sizeof *this,0);
        fwrite(this,sizeof *this,1,p);
        fclose(p);
    }


    void Socio::cargar(){

        time_t t = time(NULL);
        struct tm today = *localtime(&t);
        fecha_de_inicio.mes = today.tm_mon + 1;
        fecha_de_inicio.dia = today.tm_mday;
        fecha_de_inicio.anio = (today.tm_year + 1900);
        fecha_de_inicio.hora = 0;

        cout << endl << "CARGA DE SOCIO: " << endl;

        //VALIDAR NOMBRE Y APELLIDO

        cout << endl << "INGRESE EL NOMBRE: ";
        cargarCadena(nombre, 50);
        while(nombre[0]=='\0'){
            cout << endl << "INGRESE UN NOMBRE VALIDO: ";
            cargarCadena(nombre, 50);
        }
        cout << "INGRESE EL APELLIDO: ";
        cargarCadena(apellido, 50);
        while(apellido[0]=='\0'){
            cout << endl << "INGRESE UN APELLIDO VALIDO: ";
            cargarCadena(apellido, 50);
        }

        //VALIDAR DNI

        cout << "DNI: ";
        cin >> dni;
        if(buscarDNI(dni)){
            system("cls");
            cout << "ESTE DNI YA ESTA REGISTRADO CON OTRA PERSONA, INTENTE NUEVAMENTE CON OTRO" << endl;
            return;
        }

        //VALIDAR FECHA DE NACIMIENTO

        cout << "FECHA DE NACIMIENTO: " << endl;
        cout << "DIA: ";
        cin >> fecha_de_nacimiento.dia;
        while(fecha_de_nacimiento.dia < 1 || fecha_de_nacimiento.dia > 31){
            cout << "INGRESE UN DIA VALIDO (1-31): ";
            cin >> fecha_de_nacimiento.dia;
        }
        cout << "MES: ";
        cin >> fecha_de_nacimiento.mes;
        while(fecha_de_nacimiento.mes < 1 || fecha_de_nacimiento.mes > 12){
            cout << "INGRESE UN MES VALIDO (1-12): ";
            cin >> fecha_de_nacimiento.mes;
        }
        cout << "ANIO: ";
        cin >> fecha_de_nacimiento.anio;
        fecha_de_nacimiento.hora = 0;
        while(fecha_de_nacimiento.dia < 1900 && fecha_de_nacimiento.dia >  fecha_de_inicio.anio){
            cout << "INGRESE UN ANIO VALIDO (1900-" << fecha_de_inicio.anio <<"): ";
            cin >> fecha_de_nacimiento.dia;
        }

        //VALIDAR GENERO

        cout << "GENERO (M = MASCULINO, F = FEMENINO, O = OTRO): ";
        cin >> sexo;

        while(sexo != 'M' && sexo != 'F' && sexo != 'O'){
            cout << "INGRESE 'M' PARA MASCULINO, 'F' PARA FEMENINO Y 'O' PARA OTRO: ";
            cin >> sexo;
        }

        //VALIDAR TELEFONO

        cout << "TELEFONO: ";
        cin >> telefono;
        while(telefono<10000000){
            cout << "INGRESE UN NUMERO VALIDO DE 8 DIGITOS: ";
            cin >> telefono;
        }
        cout << "DIRECCION: ";
            cargarCadena(direccion, 100);
        cout << "EMAIL: ";
        cin >> email;

        if(cantidad_de_socios()==-1)
            {
            system("cls");
            cout << endl << "ERROR EN ABRIR EL FILE DE SOCIOS" << endl;
            return;
            }

        setNroSocio(cantidad_de_socios()+1);

        grabarEnDisco();

        cout << "SU NUMERO DE SOCIO ES " << nroSocio << endl;
    }

    void Socio::mostrar(){
        cout << "-------------------------------------------------------" << endl;
        cout << "NUMERO DE SOCIO " << nroSocio << endl;
        cout << "NOMBRE COMPLETO: " << nombre << " " << apellido << endl;
        cout << "DNI: " << dni << endl;
        cout << "GENERO: " << sexo << endl;
        cout << "FECHA DE NACIMIENTO: " ;
        mostrar_fecha_nacimiento();
        cout << endl << "TELEFONO: " << telefono << endl;
        cout << "EMAIL: " << email << endl;
        cout << "DIRECCION: " << direccion << endl;
        cout << "-------------------------------------------------------" << endl;

    }


    /// - - - - - - - - - - - - FUNCIONES GLOBALES - - - - - - - - - - - - - -


    bool es_mayor_o_igual_a_la_fecha_actual(Fecha fecha_ingresada){

        Fecha fActual;
        long fActual_long, fIngresada_long;

        time_t t = time(NULL);
        struct tm today = *localtime(&t);
        fActual.mes = today.tm_mon + 1;
        fActual.dia = today.tm_mday;
        fActual.anio = (today.tm_year + 1900);
        fActual.hora = today.tm_hour;

        fActual_long = fActual.hora + (fActual.dia*100) + (fActual.mes*10000) + (fActual.anio*1000000);
        fIngresada_long = fecha_ingresada.hora + (fecha_ingresada.dia*100) + (fecha_ingresada.mes*10000) + (fecha_ingresada.anio*1000000);

        if(fIngresada_long >= fActual_long){
            return true;
        } else {
            return false;
        }
    }

    int cantidad_de_socios(){
        FILE *p;
        int cant_socios;
        p = fopen(FILE_SOCIOS, "rb");
        if(p==NULL){
            p = fopen(FILE_SOCIOS, "wb");
            fclose(p);
            p = fopen(FILE_SOCIOS, "rb");
        }
        fseek(p, 0, 2);
        long cantBytes = ftell(p);
        fclose(p);
        cant_socios = (int ) cantBytes / sizeof(struct Socio);
        return cant_socios;
    }


    bool buscarDNI(long dni_buscado){
        FILE *p;
        p = fopen(FILE_SOCIOS, "rb");
        if(p==NULL) return false;
        Socio reg;
        while(fread(&reg, sizeof(Socio), 1, p)){
            if(reg.getDni() == dni_buscado){
                fclose(p);
                return true;
            }
        }
        fclose(p);
        return false;
    }

    bool buscarSocioXNro(int nro){
        FILE *p;
        p = fopen(FILE_SOCIOS, "rb");
        if(p==NULL)return false;
        Socio reg;
        while(fread(&reg, sizeof(Socio),1 ,p)){
            if(reg.getNroSocio()==nro && reg.getEstado()==true){
                fclose(p);
                return true;
            }
        }
        fclose(p);
        return false;
    }

    void cargarCadena(char *pal, int tam){

      int i;

      fflush(stdin);
      for(i=0;i<tam;i++){
          pal[i]=cin.get();
          if(pal[i]=='\n') break;
          }
      pal[i]='\0';
      fflush(stdin);
    }


    void alta_socio(){
        Socio reg;
        system("cls");
        reg.cargar();
    }


    void buscar_socio_por_nro(int nSocio){
        Socio reg;
        FILE *p;
        p = fopen(FILE_SOCIOS, "rb");
        if(p==NULL)return;
        while(fread(&reg, sizeof(Socio), 1, p)){
            if(reg.getNroSocio() == nSocio && reg.getEstado()==true){
                reg.mostrar();
                fclose(p);
                return;
            }
        }
        cout << endl << "NO HAY NADIE CON ESE NUMERO DE SOCIO" << endl;
        fclose(p);
    }


    void mostrar_todos_los_socios(){
        FILE *p;
        p = fopen(FILE_SOCIOS, "rb");
        if(p==NULL){
            cout << endl << "NO SE PUDO ABRIR EL ARCHIVO, INTENTALO NUEVAMENTE." << endl;
            return;
        }
        Socio reg;
        fseek(p, 0, 0);
        while(fread(&reg, sizeof(Socio), 1, p)){
            if(reg.getEstado()==true){
                reg.mostrar();
                cout << endl;
            }
        }

        fclose(p);
    }


    void baja_socio(){
        int nSocio;
        char opcion;
        Socio reg;

        system("cls");
        cout << "INGRESE EL NUMERO DEL SOCIO QUE DESEA ELIMINAR: ";
        cin >> nSocio;
        if(buscarSocioXNro(nSocio)){
            reg.leerDeDisco(nSocio -1);
            reg.mostrar();
            cout << endl << "SEGURO QUE DESEA ELIMINARLO (S/N): ";
            cin >> opcion;
            switch(opcion){
                case 'S':
                case 's':
                    reg.setEstado(false);
                    reg.modificar_de_disco(nSocio -1);
                    cout << endl << "SE ELIMINO CORRECTAMENTE" << endl;
                    break;
                case 'N':
                case 'n':
                    cout << endl << "ABORTO ELIMINACION DE SOCIO" << endl;
                    break;
                default:
                    break;
            }
        } else {
            cout << "NO EXISTE UN SOCIO CON ESE NUMERO" << endl;
        }

        cout << "presione una tecla para continuar";
        system("pause>nul");
    }

    void modificar_nombre_socio(){

        char nombre_nuevo[50];
        int nSocio;
        char opcion;
        Socio reg;

        cout << "INGRESE EL NUMERO DEL SOCIO QUE DESEA MODIFICAR: ";
        cin >> nSocio;
        if(buscarSocioXNro(nSocio)){
            reg.leerDeDisco(nSocio -1);
            reg.mostrar();
            cout << endl << "SEGURO QUE DESEA MODIFICARLO (S/N): ";
            cin >> opcion;
            switch(opcion){
                case 'S':
                case 's':
                    cout << endl << "INGRESE EL NOMBRE NUEVO: ";
                    cargarCadena(nombre_nuevo, 50);
                    reg.setNombre(nombre_nuevo);
                    reg.modificar_de_disco(nSocio -1);
                    break;
                case 'N':
                case 'n':
                    cout << endl << "ABORTO EDICION DE SOCIO" << endl;
                    break;
                default:
                    break;
            }
        } else {
            cout << "NO EXISTE UN SOCIO CON ESE NUMERO" << endl;
        }

        cout << "presione una tecla para continuar";
        system("pause>nul");
    }

    void modificar_apellido_socio(){

        char apellido_nuevo[50];
        int nSocio;
        char opcion;
        Socio reg;

        cout << "INGRESE EL NUMERO DEL SOCIO QUE DESEA MODIFICAR: ";
        cin >> nSocio;
        if(buscarSocioXNro(nSocio)){
            reg.leerDeDisco(nSocio -1);
            reg.mostrar();
            cout << endl << "SEGURO QUE DESEA MODIFICARLO (S/N): ";
            cin >> opcion;
            switch(opcion){
                case 'S':
                case 's':
                    cout << endl << "INGRESE EL APELLIDO NUEVO: ";
                    cargarCadena(apellido_nuevo, 50);
                    reg.setApellido(apellido_nuevo);
                    reg.modificar_de_disco(nSocio -1);
                    break;
                case 'N':
                case 'n':
                    cout << endl << "ABORTO EDICION DE SOCIO" << endl;
                    break;
                default:
                    break;
            }
        } else {
            cout << "NO EXISTE UN SOCIO CON ESE NUMERO" << endl;
        }

        cout << "presione una tecla para continuar";
        system("pause>nul");
    }

    void modificar_email_socio(){

        char email_nuevo[100];
        int nSocio;
        char opcion;
        Socio reg;

        cout << "INGRESE EL NUMERO DEL SOCIO QUE DESEA MODIFICAR: ";
        cin >> nSocio;
        if(buscarSocioXNro(nSocio)){
            reg.leerDeDisco(nSocio -1);
            reg.mostrar();
            cout << endl << "SEGURO QUE DESEA MODIFICARLO (S/N): ";
            cin >> opcion;
            switch(opcion){
                case 'S':
                case 's':
                    cout << endl << "INGRESE EL EMAIL NUEVO: ";
                    cargarCadena(email_nuevo, 50);
                    reg.setEmail(email_nuevo);
                    reg.modificar_de_disco(nSocio -1);
                    break;
                case 'N':
                case 'n':
                    cout << endl << "ABORTO EDICION DE SOCIO" << endl;
                    break;
                default:
                    break;
            }
        } else {
            cout << "NO EXISTE UN SOCIO CON ESE NUMERO" << endl;
        }

        cout << "presione una tecla para continuar";
        system("pause>nul");
    }

    void modificar_direccion_socio(){

        char direccion_nueva[100];
        char opcion;
        int nSocio;
        Socio reg;

        cout << "INGRESE EL NUMERO DEL SOCIO QUE DESEA MODIFICAR: ";
        cin >> nSocio;
        if(buscarSocioXNro(nSocio)){
            reg.leerDeDisco(nSocio -1);
            reg.mostrar();
            cout << endl << "SEGURO QUE DESEA MODIFICARLO (S/N): ";
            cin >> opcion;
            switch(opcion){
                case 'S':
                case 's':
                    cout << endl << "INGRESE LA DIRECCION NUEVA: ";
                    cargarCadena(direccion_nueva, 50);
                    reg.setDireccion(direccion_nueva);
                    reg.modificar_de_disco(nSocio -1);
                    break;
                case 'N':
                case 'n':
                    cout << endl << "ABORTO EDICION DE SOCIO" << endl;
                    break;
                default:
                    break;
            }
        } else {
            cout << "NO EXISTE UN SOCIO CON ESE NUMERO" << endl;
        }

        cout << "presione una tecla para continuar";
        system("pause>nul");
    }

    void modificar_sexo_socio(){

        char sexo_nuevo, opcion;
        int nSocio;
        Socio reg;

        cout << "INGRESE EL NUMERO DEL SOCIO QUE DESEA MODIFICAR: ";
        cin >> nSocio;
        if(buscarSocioXNro(nSocio)){
            reg.leerDeDisco(nSocio -1);
            reg.mostrar();
            cout << endl << "SEGURO QUE DESEA MODIFICARLO (S/N): ";
            cin >> opcion;
            switch(opcion){
                case 'S':
                case 's':
                    cout << endl << "INGRESE EL SEXO ('M' PARA MASCULINO, 'F' PARA FEMENINO Y 'O' PARA OTRO): ";
                    cin >> sexo_nuevo;
                    switch(sexo_nuevo){
                        case 'M':
                        case 'm':
                            reg.setSexo('M');
                            break;
                        case 'F':
                        case 'f':
                            reg.setSexo('F');
                            break;
                        case 'O':
                        case 'o':
                            reg.setSexo('O');
                            break;
                        default:
                            break;
                    }

                    reg.modificar_de_disco(nSocio -1);

                    break;
                case 'N':
                case 'n':
                    cout << endl << "ABORTO EDICION DE SOCIO" << endl;
                    break;
                default:
                    break;
            }

        } else {
            cout << "NO EXISTE UN SOCIO CON ESE NUMERO" << endl;
        }

        cout << "presione una tecla para continuar";
        system("pause>nul");
    }

    void modificar_dni_socio(){
        long dni_nuevo;
        int nSocio;
        char opcion;
        Socio reg;

        cout << "INGRESE EL NUMERO DEL SOCIO QUE DESEA MODIFICAR: ";
        cin >> nSocio;
        if(buscarSocioXNro(nSocio)){
            reg.leerDeDisco(nSocio -1);
            reg.mostrar();
            cout << endl << "SEGURO QUE DESEA MODIFICARLO (S/N): ";
            cin >> opcion;
            switch(opcion){
                case 'S':
                case 's':
                    cout << endl << "INGRESE EL DNI NUEVO: ";
                    cin >> dni_nuevo;
                    reg.setDni(dni_nuevo);
                    reg.modificar_de_disco(nSocio -1);
                    break;
                case 'N':
                case 'n':
                    cout << endl << "ABORTO EDICION DE SOCIO" << endl;
                    break;
                default:
                    break;
            }
        } else {
            cout << "NO EXISTE UN SOCIO CON ESE NUMERO" << endl;
        }

        cout << "presione una tecla para continuar";
        system("pause>nul");
    }

    void modificar_telefono_socio(){
        long telefono_nuevo;
        int nSocio;
        char opcion;
        Socio reg;

        cout << "INGRESE EL NUMERO DEL SOCIO QUE DESEA MODIFICAR: ";
        cin >> nSocio;
        if(buscarSocioXNro(nSocio)){
            reg.leerDeDisco(nSocio -1);
            reg.mostrar();
            cout << endl << "SEGURO QUE DESEA MODIFICARLO (S/N): ";
            cin >> opcion;
            switch(opcion){
                case 'S':
                case 's':
                    cout << endl << "INGRESE EL TELEFONO NUEVO: ";
                    cin >> telefono_nuevo;
                    reg.setTelefono(telefono_nuevo);
                    reg.modificar_de_disco(nSocio -1);
                    break;
                case 'N':
                case 'n':
                    cout << endl << "ABORTO EDICION DE SOCIO" << endl;
                    break;
                default:
                    break;
            }
        } else {
            cout << "NO EXISTE UN SOCIO CON ESE NUMERO" << endl;
        }

        cout << "presione una tecla para continuar";
        system("pause>nul");
    }

    void modificar_fecha_nacimiento_socio(){
        int nSocio;
        Fecha fNueva;
        char opcion;
        Socio reg;

        cout << "INGRESE EL NUMERO DEL SOCIO QUE DESEA MODIFICAR: ";
        cin >> nSocio;
        if(buscarSocioXNro(nSocio)){
            reg.leerDeDisco(nSocio -1);
            reg.mostrar();
            cout << endl << "SEGURO QUE DESEA MODIFICARLO (S/N): ";
            cin >> opcion;
            switch(opcion){
                case 'S':
                case 's':
                    cout << endl << "INGRESE LOS DATOS DE SU FECHA DE NACIMIENTO: ";
                    cout << endl << "DIA: ";
                    cin >> fNueva.dia;
                    cout << "MES: ";
                    cin >> fNueva.mes;
                    cout << "ANIO: ";
                    cin >> fNueva.anio;
                    reg.setFechaNacimiento(fNueva);
                    reg.modificar_de_disco(nSocio -1);
                    break;
                case 'N':
                case 'n':
                    cout << endl << "ABORTO EDICION DE SOCIO" << endl;
                    break;
                default:
                    break;
            }
        } else {
            cout << "NO EXISTE UN SOCIO CON ESE NUMERO" << endl;
        }

        cout << "presione una tecla para continuar";
        system("pause>nul");
    }


#endif // SOCIO_H_INCLUDED
