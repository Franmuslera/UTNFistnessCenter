#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED

    void menu_empleados(){

            int opcion, nroDni;
            bool estado = true;

            while(estado){
                cout << "- - - - - - - MENU DE EMPLEADOS - - - - - - - -" << endl;
                cout << "1) ALTA DE NUEVO EMPLEADO" << endl;
                cout << "2) BUSCAR EMPLEADO POR DNI" << endl;
                cout << "3) MOSTRAR TODOS LOS EMPLEADOS" << endl;
                cout << "0) VOLVER AL MENU ANTERIOR" << endl;
                cout << "- - - - - - - - - - - - - - - - - - - - - - -" << endl;
                cout << "INGRESE UNA OPCION: ";
                cin >> opcion;

                switch(opcion){
                    case 1:
                        system("cls");
                        alta_empleado();
                        system("pause");
                        break;
                    case 2:
                        system("cls");
                        cout << "INGRESE EL DNI DEL EMPLEADO QUE DESEA BUSCAR: ";
                        cin >> nroDni;
                        buscar_empleado_x_dni(nroDni);
                        system("pause");
                        break;
                    case 3:
                        system("cls");
                        mostrar_todos_los_empleados();
                        system("pause");
                        break;
                    case 0:
                        estado = false;
                        break;
                    default:
                        break;
                }
                system("cls");
            }
        }


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
        }


    void menu_personas(){
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
    }


#endif // MENUS_H_INCLUDED
