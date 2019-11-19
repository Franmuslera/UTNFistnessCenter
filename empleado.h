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
        void modificar_de_disco(int pos);
        bool leerDeDisco(int pos);

    };

void mostrar_empleado_x_nro_empleado();
int cantidad_de_empleados();
bool existe_empleado_x_dni(long);
Empleado buscar_empleado_x_nro_empleado(int);


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


    bool existe_empleado_x_dni(long dni_buscado){
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

    bool Empleado::leerDeDisco(int pos){
        FILE *p;
        p = fopen(FILE_EMPLEADOS, "rb");
        if(p==NULL) return false;
        if(pos==-1)return false;
        int x;
        fseek(p, pos*sizeof*this,0);
        x = fread(this, sizeof(Empleado), 1, p);
        fclose(p);
        if(x){
            return true;
        } else return false;
    }

    void Empleado::modificar_de_disco(int pos){
        FILE *p;
        p = fopen(FILE_EMPLEADOS, "rb+");
        if(p==NULL){cout<<"ERROR DE ARCHIVO";exit(1);}
        fseek(p,pos*sizeof *this,0);
        fwrite(this,sizeof *this,1,p);
        fclose(p);
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
        while(existe_empleado_x_dni(dni)){
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
        while(fecha_de_nacimiento.anio < 1900 || fecha_de_nacimiento.anio >  fecha_de_inicio.anio){
            cout << "INGRESE UN ANIO VALIDO (1900-" << fecha_de_inicio.anio <<"): ";
            cin >> fecha_de_nacimiento.anio;
        }

        //VALIDAR SUELDO

        cout << "SUELDO: ";
        cin >> sueldo;
        while(sueldo<1){
            cout << "INGRESE UN SUELDO VALIDO MAYOR A 1: ";
            cin >> sueldo;
        }

        //VALIDAR POSICION

        int opcion_pos;
        bool estado_pos = true;

        while(estado_pos){

            cout << "INGRESE LA POSICION DEL EMPLEADO: ";
            cout << endl << "1) ADMINISTRATIVO";
            cout << endl << "2) ENTRENADOR";
            cout << endl << "3) LIMPIEZA";
            cout << endl << "OPCION: ";
            cin >> opcion_pos;
            switch(opcion_pos){
                case 1:
                    strcpy(tipo_de_empleado, ADMINISTRATIVO);
                    estado_pos = false;
                    break;
                case 2:
                    strcpy(tipo_de_empleado, ENTRENADOR);
                    estado_pos = false;
                    break;
                case 3:
                    strcpy(tipo_de_empleado, LIMPIEZA);
                    estado_pos = false;
                    break;
                default:
                    cout << endl << "INGRESE UNA OPCION VALIDA" << endl;
                    break;
            }
        }

        nroEmpleado = (cantidad_de_empleados() + 1);

        if(grabarEnDisco()){
            system("cls");
            cout << "NUMERO DE EMPLEADO : " << nroEmpleado;
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

    bool buscar_empleado_x_nro_y_tipo(int numeroDeEmpleado,const char* tipoEmpleado){
        FILE *p;
        Empleado reg;
        p = fopen(FILE_EMPLEADOS, "rb");
        if(p == NULL) {
            system("cls");
            cout << "NO SE PUDO ABRIR EL ARCHIVO" << endl;
            return false;
                }
        while(fread(&reg, sizeof(Empleado), 1, p)){
            if (reg.getNroEmpleado() == numeroDeEmpleado && strcmp(reg.getTipoDeEmpleado(),tipoEmpleado)){
                fclose(p);
                return true;
            }
        }
        fclose(p);
        return false;
    }



    void alta_empleado(){
        Empleado reg;
        system("cls");
        reg.cargar();
    }

    void buscar_empleado_x_dni(long dni_empleado){
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
            if(strcmp(reg.getTipoDeEmpleado(),ADMINISTRATIVO)==0 && reg.getEstado()==true){
                reg.mostrar();
            }
        }

        fseek(p, 0, 0);
        cout << "______________________________________________________________________" << endl;
        cout << endl << "                      ENTRENADORES" << endl;
        while(fread(&reg, sizeof(Empleado), 1, p)){
            if(strcmp(reg.getTipoDeEmpleado(),ENTRENADOR)==0 && reg.getEstado()==true){
                reg.mostrar();
            }
        }

        fseek(p, 0, 0);
        cout << "______________________________________________________________________" << endl;
        cout << endl << "                      LIMPIEZA" << endl;
        while(fread(&reg, sizeof(Empleado), 1, p)){
            if(strcmp(reg.getTipoDeEmpleado(),LIMPIEZA)==0 && reg.getEstado()==true){
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
                if(reg.getEstado()==true){
                  reg.mostrar();
            cout << endl;
                }

        }

        fclose(p);
    }

    void mostrar_empleado_x_posicion(const char* tipo){
     FILE *p;
        p = fopen(FILE_EMPLEADOS, "rb");
        if(p==NULL){
            cout << endl << "NO SE PUDO ABRIR EL ARCHIVO, INTENTALO NUEVAMENTE." << endl;
            return;
        }
        Empleado reg;
        fseek(p, 0, 0);
        while(fread(&reg, sizeof(Empleado), 1, p)){
           if(strcmp(reg.getTipoDeEmpleado(),tipo)){
            reg.mostrar();
             cout << endl;
           }

        }

        fclose(p);
    }

    bool buscarEmpleadoXNro(int nro){
        FILE *p;
        p = fopen(FILE_EMPLEADOS, "rb");
        if(p==NULL)return false;
        Empleado reg;
        while(fread(&reg, sizeof(Empleado),1 ,p)){
            if(reg.getNroEmpleado()==nro && reg.getEstado()==true){
                fclose(p);
                return true;
            }
        }
        fclose(p);
        return false;
    }


     void baja_empleado(){
        int nEmpleado;
        char opcion;
        Empleado reg;

        system("cls");
        cout << "INGRESE EL NUMERO DEL EMPLEADO QUE DESEA ELIMINAR: ";
        cin >> nEmpleado;
        if(buscarEmpleadoXNro(nEmpleado)){
            reg.leerDeDisco(nEmpleado -1);
            reg.mostrar();
            cout << endl << "SEGURO QUE DESEA ELIMINARLO (S/N): ";
            cin >> opcion;
            switch(opcion){
                case 'S':
                case 's':
                    reg.setEstado(false);
                    reg.modificar_de_disco(nEmpleado -1);
                    cout << endl << "SE ELIMINO CORRECTAMENTE" << endl;
                    break;
                case 'N':
                case 'n':
                    cout << endl << "ABORTO ELIMINACION DE EMPLEADO" << endl;
                    break;
                default:
                    break;
            }
        } else {
            cout << "NO EXISTE UN EMPLEADO CON ESE NUMERO" << endl;
        }

        cout << "presione una tecla para continuar";
        system("pause>nul");
    }



    void modificar_nombre_empleado(){

        char nombre_nuevo[50];
        int nEmpleado;
        char opcion;
        Empleado reg;

        cout << "INGRESE EL NUMERO DEL EMPLEADO QUE DESEA MODIFICAR: ";
        cin >> nEmpleado;
        if(buscarEmpleadoXNro(nEmpleado)){
            reg.leerDeDisco(nEmpleado -1);
            reg.mostrar();
            cout << endl << "SEGURO QUE DESEA MODIFICARLO (S/N): ";
            cin >> opcion;
            switch(opcion){
                case 'S':
                case 's':
                    cout << endl << "INGRESE EL NOMBRE NUEVO: ";
                    cargarCadena(nombre_nuevo, 50);
                    reg.setNombre(nombre_nuevo);
                    reg.modificar_de_disco(nEmpleado -1);
                    break;
                case 'N':
                case 'n':
                    cout << endl << "ABORTO EDICION DE EMPLEADO" << endl;
                    break;
                default:
                    break;
            }
        } else {
            cout << "NO EXISTE UN EMPLEADO CON ESE NUMERO" << endl;
        }

        cout << "presione una tecla para continuar";
        system("pause>nul");
    }

    void modificar_apellido_empleado(){

        char apellido_nuevo[50];
        int nEmpleado;
        char opcion;
        Empleado reg;

        cout << "INGRESE EL NUMERO DEL EMPLEADO QUE DESEA MODIFICAR: ";
        cin >> nEmpleado;
        if(buscarEmpleadoXNro(nEmpleado)){
            reg.leerDeDisco(nEmpleado -1);
            reg.mostrar();
            cout << endl << "SEGURO QUE DESEA MODIFICARLO (S/N): ";
            cin >> opcion;
            switch(opcion){
                case 'S':
                case 's':
                    cout << endl << "INGRESE EL APELLIDO NUEVO: ";
                    cargarCadena(apellido_nuevo, 50);
                    reg.setApellido(apellido_nuevo);
                    reg.modificar_de_disco(nEmpleado -1);
                    break;
                case 'N':
                case 'n':
                    cout << endl << "ABORTO EDICION DE EMPLEADO" << endl;
                    break;
                default:
                    break;
            }
        } else {
            cout << "NO EXISTE UN EMPLEADO CON ESE NUMERO" << endl;
        }

        cout << "presione una tecla para continuar";
        system("pause>nul");
    }

    void modificar_posicion_empleado(){

        char posicion_nueva[50];
        int nEmpleado;
        char opcion;
        Empleado reg;

        cout << "INGRESE EL NUMERO DEL EMPLEADO QUE DESEA MODIFICAR: ";
        cin >> nEmpleado;
        if(buscarEmpleadoXNro(nEmpleado)){
            reg.leerDeDisco(nEmpleado -1);
            reg.mostrar();
            cout << endl << "SEGURO QUE DESEA MODIFICARLO (S/N): ";
            cin >> opcion;
            switch(opcion){
                case 'S':
                case 's':
                    cout << endl <<"INGRESE UNA POSICION NUEVA (administrativo , entrenador y limpieza): ";
                    cargarCadena(posicion_nueva, 50);
                    while(strcmp(posicion_nueva, ADMINISTRATIVO) && strcmp(posicion_nueva, ENTRENADOR) && strcmp(posicion_nueva, LIMPIEZA)){
                    cout << "INGRESE UNA POSICION VALIDA (administrativo , entrenador y limpieza): ";
                    cargarCadena(posicion_nueva, 30);
                    }
                    reg.setTipoDeEmpleado(posicion_nueva);
                    reg.modificar_de_disco(nEmpleado -1);
                    break;
                case 'N':
                case 'n':
                    cout << endl << "ABORTO EDICION DE EMPLEADO" << endl;
                    break;
                default:
                    break;
            }
        } else {
            cout << "NO EXISTE UN EMPLEADO CON ESE NUMERO" << endl;
        }

        cout << "presione una tecla para continuar";
        system("pause>nul");
    }





    void modificar_sexo_empleado(){

        char sexo_nuevo, opcion;
        int nEmpleado;
        Empleado reg;

        cout << "INGRESE EL NUMERO DEL EMPLEADO QUE DESEA MODIFICAR: ";
        cin >> nEmpleado;
        if(buscarEmpleadoXNro(nEmpleado)){
            reg.leerDeDisco(nEmpleado -1);
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

                    reg.modificar_de_disco(nEmpleado -1);

                    break;
                case 'N':
                case 'n':
                    cout << endl << "ABORTO EDICION DE EMPLEADO" << endl;
                    break;
                default:
                    break;
            }

        } else {
            cout << "NO EXISTE UN EMPLEADO CON ESE NUMERO" << endl;
        }

        cout << "presione una tecla para continuar";
        system("pause>nul");
    }

    void modificar_dni_empleado(){
        long dni_nuevo;
        int nEmpleado;
        char opcion;
        Empleado reg;

        cout << "INGRESE EL NUMERO DEL EMPLEADO QUE DESEA MODIFICAR: ";
        cin >> nEmpleado;
        if(buscarEmpleadoXNro(nEmpleado)){
            reg.leerDeDisco(nEmpleado -1);
            reg.mostrar();
            cout << endl << "SEGURO QUE DESEA MODIFICARLO (S/N): ";
            cin >> opcion;
            switch(opcion){
                case 'S':
                case 's':
                    cout << endl << "INGRESE EL DNI NUEVO: ";
                    cin >> dni_nuevo;
                    if(existe_empleado_x_dni(dni_nuevo)){
                        reg.setDni(dni_nuevo);
                        reg.modificar_de_disco(nEmpleado -1);
                    } else {
                        cout << endl << "EL DNI YA EXISTE, INTENTE NUEVAMENTE CON UNO DIFERENTE";
                    }

                    break;
                case 'N':
                case 'n':
                    cout << endl << "ABORTO EDICION DE EMPLEADO" << endl;
                    break;
                default:
                    break;
            }
        } else {
            cout << "NO EXISTE UN EMPLEADO CON ESE NUMERO" << endl;
        }

        cout << "presione una tecla para continuar";
        system("pause>nul");
    }

    void modificar_sueldo_empleado(){
        float sNuevo;
        int nEmpleado;
        char opcion;
        Empleado reg;

        cout << "INGRESE EL NUMERO DEL EMPLEADO QUE DESEA MODIFICAR: ";
        cin >> nEmpleado;
        if(buscarEmpleadoXNro(nEmpleado)){
            reg.leerDeDisco(nEmpleado -1);
            reg.mostrar();
            cout << endl << "SEGURO QUE DESEA MODIFICARLO (S/N): ";
            cin >> opcion;
            switch(opcion){
                case 'S':
                case 's':
                    cout << endl << "INGRESE EL SUELDO NUEVO: ";
                    cin >> sNuevo;
                    reg.setSueldo(sNuevo);
                    reg.modificar_de_disco(nEmpleado -1);
                    break;
                case 'N':
                case 'n':
                    cout << endl << "ABORTO EDICION DE EMPLEADO" << endl;
                    break;
                default:
                    break;
            }
        } else {
            cout << "NO EXISTE UN EMPLEADO CON ESE NUMERO" << endl;
        }

        cout << "presione una tecla para continuar";
        system("pause>nul");
    }

    void modificar_fecha_nacimiento_empleado(){
        int nEmpleado;
        Fecha fNueva;
        char opcion;
        Empleado reg;

        cout << "INGRESE EL NUMERO DEL EMPLEADO QUE DESEA MODIFICAR: ";
        cin >> nEmpleado;
        if(buscarEmpleadoXNro(nEmpleado)){
            reg.leerDeDisco(nEmpleado -1);
            reg.mostrar();
            cout << endl << "SEGURO QUE DESEA MODIFICARLO (S/N): ";
            cin >> opcion;
            switch(opcion){
                case 'S':
                case 's':
                    cout << endl << "INGRESE LOS DATOS DE SU FECHA DE NACIMIENTO: ";
                    cout << "FECHA DE NACIMIENTO: " << endl;

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
                    while(fNueva.dia < 1900 || fNueva.dia >  fNueva.anio){
                        cout << "INGRESE UN ANIO VALIDO (1900-" << fNueva.anio <<"): ";
                        cin >> fNueva.dia;
                    }

                    reg.setFechaNacimiento(fNueva);
                    reg.modificar_de_disco(nEmpleado -1);

                    break;
                case 'N':
                case 'n':
                    cout << endl << "ABORTO EDICION DE EMPLEADO" << endl;
                    break;
                default:
                    break;
            }
        } else {
            cout << "NO EXISTE UN EMPLEADO CON ESE NUMERO" << endl;
        }

        cout << "presione una tecla para continuar";
        system("pause>nul");
    }

    void mostrar_empleado_x_nro_empleado(){
        Empleado reg;
        int nroEmpleado;
        cout << "INGRESE EL NUMERO DE EMPLEADO: ";
        cin >> nroEmpleado;
        reg = buscar_empleado_x_nro_empleado(nroEmpleado);
        if(reg.getNroEmpleado()==nroEmpleado){
            reg.mostrar();
        }
        cout << "presione una tecla para continuar";
        system("pause>nul");
    }





#endif // EMPLEADO_H_INCLUDED
