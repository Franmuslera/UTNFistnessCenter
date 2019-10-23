#ifndef SOCIO_H_INCLUDED
#define SOCIO_H_INCLUDED

const char *FILE_SOCIOS = "socios.dat";


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
        int posicionDeSocioEnArchivo(int);
        bool buscarDNI(long);
        int cantidad_de_socios();
        Socio(long, char*, char*, int,int,int,int,int,int,int, char, char*, char*, int, long);
        Socio();

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

    ///- - - - - - - - - - - - - - - - - - - - - - - - - -


    bool Socio::grabarEnDisco(){
        FILE *p;
        p = fopen(FILE_SOCIOS, "ab");
        if(p==NULL)return false;
        fwrite(this, sizeof *this, 1, p);
        fclose(p);
        return true;
    }


    int Socio::posicionDeSocioEnArchivo(int nroS){
        FILE *p;
        p = fopen(FILE_SOCIOS, "rb");
        if(p==NULL) return false;
        while(fread(this, sizeof(Socio), 1, p)){
            if(this->nroSocio == nroS){
                int pos = (ftell(p)-sizeof(Socio))/sizeof(Socio);
                fclose(p);
                return pos;
            }
        };
        fclose(p);
        return -1;
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


    int Socio::cantidad_de_socios(){
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


    bool Socio::buscarDNI(long dni_buscado){
        FILE *p;
        p = fopen(FILE_SOCIOS, "rb");
        if(p==NULL) return false;
        while(fread(this, sizeof(Socio), 1, p)){
            if(this->dni == dni_buscado){
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

        //Socio reg(dni, nombre, apellido, fecha_de_nacimiento.dia, fecha_de_nacimiento.mes, fecha_de_nacimiento.anio,
         //         fecha_de_inicio.dia,fecha_de_inicio.mes,fecha_de_inicio.anio,fecha_de_inicio.hora, sexo, email, direccion, nroSocio, telefono);

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

    Socio::Socio (long dni_const=0, char *nombre_const="",char *apellido_const="",
                   int fechaNac_const_dia = 0, int fechaNac_const_mes = 0, int fechaNac_const_anio = 0,
                    int fechaInicio_const_dia = 0, int fechaInicio_const_mes = 0, int fechaInicio_const_anio = 0, int fechaInicio_const_hora = 0,
                     char sex='M',char *mail_const="", char *direccion_const="", int nroSocio_const=0, long telefono_const=0)
                     {
        dni = dni_const;
        strcpy(nombre, nombre_const);
        strcpy(apellido, apellido_const);
        strcpy(email, mail_const);
        strcpy(direccion, direccion_const);
        fecha_de_nacimiento.dia = fechaNac_const_dia;
        fecha_de_nacimiento.mes = fechaNac_const_mes;
        fecha_de_nacimiento.anio = fechaNac_const_anio;
        fecha_de_inicio.dia = fechaInicio_const_dia;
        fecha_de_inicio.mes = fechaInicio_const_mes;
        fecha_de_inicio.anio = fechaInicio_const_anio;
        fecha_de_inicio.hora = fechaInicio_const_hora;
        sexo = sex;
        nroSocio = nroSocio_const;
        telefono = telefono_const;
    }

//Socio::~Socio(){
//    cout << endl << "EL SOCIO SE ELIMINO CORRECTAMENTE" << endl;
//}

    void alta_socio(){
        Socio reg(0);
        system("cls");
        reg.cargar();
    }


    void buscar_socio_por_nro(int nSocio){
        Socio reg(0);
        FILE *p;
        p = fopen(FILE_SOCIOS, "rb");
        if(p==NULL)return;
        while(fread(&reg, sizeof(Socio), 1, p)){
            if(reg.getNroSocio() == nSocio){
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
        Socio reg(0);
        fseek(p, 0, 0);
        while(fread(&reg, sizeof(Socio), 1, p)){
            reg.mostrar();
            cout << endl;
        }

        fclose(p);
    }

    /*
    void menu_socios(){
        int opcion, nroSoc;
        bool en_curso = true;

        while(en_curso){
            cout << "- - - - - - - MENU DE SOCIOS - - - - - - - -" << endl;
            cout << "1) INSCRIPCION DE NUEVO SOCIO" << endl;
            cout << "2) BUSCAR SOCIO POR SU NUMERO DE SOCIO" << endl;
            cout << "3) MOSTRAR TODOS LOS SOCIOS" << endl;
            cout << "0) VOLVER AL MENU ANTERIOR" << endl;
            cout << "- - - - - - - - - - - - - - - - - - - - - - -" << endl;
            cout << "INGRESE UNA OPCION: ";
            cin >> opcion;

            switch(opcion){
                case 1:
                    alta_socio();
                    system("pause");
                    break;
                case 2:
                    system("cls");
                    cout << "INGRESE EL NUMERO DEL SOCIO QUE DESEA BUSCAR: ";
                    cin >> nroSoc;
                    buscar_socio_por_nro(nroSoc);
                    system("pause");
                    break;
                case 3:
                    system("cls");
                    mostrar_todos_los_socios();
                    system("pause");
                    break;
                case 0:
                    en_curso = false;
                    break;
                default:
                    break;
            }

            system("cls");
        }
    } */





#endif // SOCIO_H_INCLUDED
