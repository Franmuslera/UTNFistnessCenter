#ifndef PERSONA_H_INCLUDED
#define PERSONA_H_INCLUDED

struct Fecha{
    int anio;
    int mes;
    int dia;
    int hora;
};


class Persona {
    protected:
        char nombre[50], apellido[50];
        long dni;
        Fecha fecha_de_nacimiento;
        Fecha fecha_de_inicio;
        char sexo;
        bool estado = true;
    public:
        long getDni();
        char* getNombre();
        char* getApellido();
        bool getEstado();
        Fecha getFechaNacimiento();
        Fecha getFechaDeInicio();
        char getSexo();
        void setEstado(bool);
        void setNombre(char*);
        void setApellido(char*);
        void setSexo(char);
        void setDni(long);
        void setFechaNacimiento(Fecha);
        void setFechaDeInicio(Fecha);
        void mostrar_fecha_nacimiento();
        void mostrar_fecha_de_inicio();
};


    long Persona::getDni(){
        return dni;
    }

    char* Persona::getNombre(){
        return nombre;
    }

    char* Persona::getApellido(){
        return apellido;
    }

    bool Persona::getEstado(){
        return estado;
    }

    Fecha Persona::getFechaNacimiento(){
        return fecha_de_nacimiento;
    }

    Fecha Persona::getFechaDeInicio(){
        return fecha_de_inicio;
    }

    char Persona::getSexo(){
        return sexo;
    }

    void Persona::setEstado(bool estado_nuevo){
        estado = estado_nuevo;
    }

    void Persona::setNombre(char *n){
        strcpy(nombre, n);
    }

    void Persona::setApellido(char *a){
        strcpy(apellido, a);
    }

    void Persona::setSexo(char s){
        sexo = s;
    }

    void Persona::setDni(long dni_nuevo){
        dni = dni_nuevo;
    }

    void Persona::setFechaNacimiento(Fecha f){
        fecha_de_nacimiento = f;
    }

    void Persona::setFechaDeInicio(Fecha f){
        fecha_de_inicio = f;
    }

    void Persona::mostrar_fecha_nacimiento(){
        cout << fecha_de_nacimiento.dia << "/" << fecha_de_nacimiento.mes << "/" << fecha_de_nacimiento.anio;
    }

    void Persona::mostrar_fecha_de_inicio(){
        cout << fecha_de_inicio.dia << "/" << fecha_de_inicio.mes << "/" << fecha_de_inicio.anio;
    }

   /* void menu_personas(){
        bool estado = true;
        int opcion;

        while(estado){

            cout << "- - - - - - - MENU GESTION SOCIOS Y EMPLEADOS - - - - - - - -" << endl;
            cout << "1) GESTION DE SOCIOS" << endl;
            cout << "2) GESTION DE EMPLEADOS" << endl;
            cout << "0) CERRAR PROGRAMA" << endl;
            cout << "- - - - - - - - - - - - - - - - - - - - - - -" << endl;
            cout << "INGRESE UNA OPCION: ";
            cin >> opcion;

            switch(opcion){
                case 1:
                    system("cls");
                    menu_socios();
                    break;
                case 2:
                    system("cls");
                    menu_empleados();
                    break;
                case 0:
                    estado = false;
                    break;
                    default:
                    break;
            }

            system("cls");

        }
    }*/

#endif // PERSONA_H_INCLUDED
