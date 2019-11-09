#ifndef EMPLEADO_H_INCLUDED
#define EMPLEADO_H_INCLUDED

const char *FILE_EMPLEADOS = "Empleados.dat";
const char *ADMINISTRATIVO = "administrativo";
const char *ENTRENADOR = "entrenador";
const char *LIMPIEZA = "limpieza";

class Empleado :
    public Persona{

    private:
        int nroEmpleado;
        float sueldo;
        char tipo_de_empleado[30];
    public:
        int getNroEmpleado();
        float getSueldo();
        char* getTipoDeEmpleado();
        void setNroEmpleado(int);
        void setSueldo(float);
        void setTipoDeEmpleado(char*);
        void mostrar();
        void cargar();
        bool grabarEnDisco();
    };


    int Empleado::getNroEmpleado(){
        return nroEmpleado;
    }

    float Empleado::getSueldo(){
        return sueldo;
    }

    char* Empleado::getTipoDeEmpleado(){
        return tipo_de_empleado;
    }

    void Empleado::setNroEmpleado(int nro){
        nroEmpleado = nro;
    }

    void Empleado::setSueldo(float s){
        sueldo = s;
    }

    void Empleado::setTipoDeEmpleado(char *tipo){
        strcpy(tipo_de_empleado, tipo);
    }


    int cantidad_de_empleados(){
        FILE *p;
        int cant_empleados;
        p = fopen(FILE_EMPLEADOS, "rb");
        if(p==NULL){
            p = fopen(FILE_EMPLEADOS, "wb");
            fclose(p);
            p = fopen(FILE_EMPLEADOS, "rb");
        }
        fseek(p, 0, 2);
        long cantBytes = ftell(p);
        fclose(p);
        cant_empleados = (int ) cantBytes / sizeof(struct Empleado);
        return cant_empleados;
        }



    void Empleado::mostrar(){
        cout << "-------------------------------------------------------" << endl;
        cout << "NUMERO DE EMPLEADO " << nroEmpleado << endl;
        cout << "NOMBRE COMPLETO: " << nombre << " " << apellido << endl;
        cout << "DNI: " << dni << endl;
        cout << "GENERO: " << sexo << endl;
        cout << "FECHA DE NACIMIENTO: " ;
        mostrar_fecha_nacimiento();
        cout << endl << "TIPO DE EMPLEADO: " << tipo_de_empleado << endl;
        cout << "SUELDO: " << sueldo << endl;
        cout << "FECHA DE INICIO: ";
        mostrar_fecha_de_inicio();
        cout << endl;
        cout << "-------------------------------------------------------" << endl;
    }


    bool buscar_empleado_x_dni(long dni_buscado){
        FILE *p;
        p  = fopen(FILE_EMPLEADOS, "rb");
        if(p == NULL)return false;
        Empleado reg;
        while(fread(&reg, sizeof(Empleado), 1, p)){
            if( reg.getDni() == dni_buscado){
                fclose(p);
                return true;
            }
        }
        fclose(p);
        return false;
    }


    bool Empleado::grabarEnDisco(){
        FILE *p;
        p = fopen(FILE_EMPLEADOS, "ab");
        if(p==NULL)return false;
        fwrite(this, sizeof *this, 1, p);
        fclose(p);
        return true;
    }


    void Empleado::cargar(){

        time_t t = time(NULL);
        struct tm today = *localtime(&t);
        fecha_de_inicio.mes = today.tm_mon + 1;
        fecha_de_inicio.dia = today.tm_mday;
        fecha_de_inicio.anio = (today.tm_year + 1900);
        fecha_de_inicio.hora = 0;

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
        while(buscar_empleado_x_dni(dni)){
            cout << "DNI YA EXISTENTE, INGRESE UNO QUE NO ESTE EN LA BASE DE DATOS: ";
            cin >> dni;
        }

        //VALIDAR SEXO

        cout << "GENERO (M = MASCULINO, F = FEMENINO, O = OTRO): ";
        cin >> sexo;
        while(sexo != 'M' && sexo != 'F' && sexo != 'O'){
            cout << "INGRESE 'M' PARA MASCULINO, 'F' PARA FEMENINO Y 'O' PARA OTRO: ";
            cin >> sexo;
        }

        //VALIDAR FECHA DE NACIMIENTO

        cout << "FECHA DE NACIMIENTO: " << endl;
        cout << "DIA: ";
        cin >> fecha_de_nacimiento.dia;
        while(fecha_de_nacimiento.dia < 1 && fecha_de_nacimiento.dia > 31){
            cout << "INGRESE UN DIA VALIDO (1-31): ";
            cin >> fecha_de_nacimiento.dia;
        }
        cout << "MES: ";
        cin >> fecha_de_nacimiento.mes;
        while(fecha_de_nacimiento.mes < 1 && fecha_de_nacimiento.mes > 12){
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

        //VALIDAR SUELDO

        cout << "SUELDO: ";
        cin >> sueldo;
        while(sueldo<1){
            cout << "INGRESE UN SUELDO VALIDO MAYOR A 1: ";
            cin >> sueldo;
        }

        //VALIDAR POSICION

        cout << "INGRESE LA POSICION DEL EMPLEADO: ";
        cargarCadena(tipo_de_empleado, 30);
        while(strcmp(tipo_de_empleado, ADMINISTRATIVO) && strcmp(tipo_de_empleado, ENTRENADOR) && strcmp(tipo_de_empleado, LIMPIEZA)){
            cout << "INGRESE UNA POSICION VALIDA (administrativo , entrenador y limpieza): ";
            cargarCadena(tipo_de_empleado, 30);
        }

        nroEmpleado = (cantidad_de_empleados() + 1);

        if(grabarEnDisco()){
            system("cls");
            cout << endl << "EMPLEADO GRABADO CON EXITO EN EL DISCO" << endl;
        } else {
            system("cls");
            cout << endl << "NO SE PUDO GUARDAR CORRECTAMENTE EL EMPLEADO EN EL DISCO, INTENTELO NUEVAMENTE" << endl;
        }
    }



    Empleado buscar_empleado_x_nro_empleado(int numeroDeEmpleado){
        FILE *p;
        Empleado reg;
        p = fopen(FILE_EMPLEADOS, "rb");
        if(p == NULL) {
            system("cls");
            cout << "NO SE PUDO ABRIR EL ARCHIVO" << endl;
            return reg;
                }

        while(fread(&reg, sizeof(Empleado), 1, p)){
            if (reg.getNroEmpleado() == numeroDeEmpleado){
                return reg;
            }
        }
        system("cls");
        cout << "NO SE ENCONTRO EL EMPLEADO BUSCADO, INGRESE UN NUMERO DE ID EXISTENTE" << endl;
        return reg;
    }

    void alta_empleado(){
        Empleado reg;
        system("cls");
        reg.cargar();
    }

    void buscar_empleado_x_dni(int dni_empleado){
        FILE *p;
        p = fopen(FILE_EMPLEADOS, "rb");
        if(p==NULL){
            cout << endl << "NO SE PUDO ABRIR LA BASE DE DATOS" << endl;
            return;
        }
        Empleado reg;
        while(fread(&reg, sizeof(Empleado), 1, p)){
            if(reg.getDni() == dni_empleado){
                cout << "SE ENCONTRO EL EMPLEADO EN LA BASE DE DATOS: " << endl;
                reg.mostrar();
                return;
            }
        }
        cout << "NO SE ENCONTRO UN EMPLEADO CON ESE DNI" << endl;
    }

    void mostrar_todos_los_empleados(){
        FILE *p;
        p = fopen(FILE_EMPLEADOS,"rb");

        if(p==NULL){
            cout << "NO SE PUDO ABRIR LA BASE DE DATOS" << endl;
            return;
        }

        Empleado reg;
        cout << "EMPLEADOS: " << endl;
        cout << "______________________________________________________________________" << endl;
        cout << "                      ADMINISTRATIVOS" << endl;
        while(fread(&reg, sizeof(Empleado), 1, p)){
            if(strcmp(reg.getTipoDeEmpleado(),ADMINISTRATIVO)==0){
                reg.mostrar();
            }
        }

        fseek(p, 0, 0);
        cout << "______________________________________________________________________" << endl;
        cout << endl << "                      ENTRENADORES" << endl;
        while(fread(&reg, sizeof(Empleado), 1, p)){
            if(strcmp(reg.getTipoDeEmpleado(),ENTRENADOR)==0){
                reg.mostrar();
            }
        }

        fseek(p, 0, 0);
        cout << "______________________________________________________________________" << endl;
        cout << endl << "                      LIMPIEZA" << endl;
        while(fread(&reg, sizeof(Empleado), 1, p)){
            if(strcmp(reg.getTipoDeEmpleado(),LIMPIEZA)==0){
                reg.mostrar();
            }
        }
    }

    void mostrar_todos_los_empleados_x_nro_empleado(){
        FILE *p;
        p = fopen(FILE_EMPLEADOS, "rb");
        if(p==NULL){
            cout << endl << "NO SE PUDO ABRIR EL ARCHIVO, INTENTALO NUEVAMENTE." << endl;
            return;
        }
        Empleado reg;
        fseek(p, 0, 0);
        while(fread(&reg, sizeof(Empleado), 1, p)){
            reg.mostrar();
            cout << endl;
        }

        fclose(p);
    }


#endif // EMPLEADO_H_INCLUDED
