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
                        int opcion_muestra;
                        system("cls");
                        cout << endl << "COMO DESEA VER TODOS LOS EMPLEADOS (1: MOSTRAR EMPLEADOS POR POSICION; 2: MOSTRAR EMPLEADOS POR NRO DE EMPLEADO): ";
                        cin >> opcion_muestra;
                        system("cls");
                        switch(opcion_muestra){
                            case 1:
                                mostrar_todos_los_empleados();
                                system("pause");
                                break;
                            case 2:
                                mostrar_todos_los_empleados_x_nro_empleado();
                                system("pause");
                                break;
                            default:
                                break;
                        }
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

    void menu_rutina(){
        int opcion, nroRutina, opcion_mostrar, opcion_asignacion;
        bool estado = true;

        while(estado){

            cout << "- - - - - - - MENU DE RUTINAS - - - - - - - -" << endl;
            cout << "1) CREAR NUEVA RUTINA" << endl;
            cout << "2) BAJA DE RUTINA" << endl;
            cout << "3) BUSCAR RUTINA" << endl;
            cout << "4) MOSTRAR RUTINAS" << endl;
            cout << "5) ASIGNACION DE RUTINA A CLIENTE" << endl;
            cout << "0) VOLVER AL MENU ANTERIOR" << endl;
            cout << "- - - - - - - - - - - - - - - - - - - - - - -" << endl;
            cout << "INGRESE UNA OPCION: ";
            cin >> opcion;

            switch(opcion){
                case 1:
                    alta_rutina();
                    system("pause");
                    break;
                case 2:
                    system("cls");
                    baja_logica_rutina();
                    break;
                case 3:
                    system("cls");
                    cout << "INGRESE EL NUMERO DE RUTINA QUE DESEA BUSCAR: ";
                    cin >> nroRutina;
                    buscar_rutina_x_codigo(nroRutina);
                    break;
                case 4:
                    system("cls");
                    cout << "COMO DESEA VER EL ORDEN DE LAS RUTINAS ( 1 - POR NUMERO DE RUTINA / 2 - POR NIVEL DE RUTINA / 3 - POR TIPO DE RUTINA): ";
                    cin >> opcion_mostrar;
                    system("cls");
                    switch(opcion_mostrar){
                        case 1:
                            mostrar_rutinas_x_codigo();
                            break;
                        case 2:
                            mostrar_rutinas_x_niveles();
                            break;
                        case 3:
                            mostrar_rutinas_x_tipos();
                            break;
                        default:
                            break;
                    }
                    cout << "presione una tecla para continuar";
                    system("pause>nul");
                    break;
                case 5:
                    system("cls");
                    cout << "- - - - - - - MENU DE ASIGNACION DE RUTINAS - - - - - - - -" << endl;
                    cout << "1) ASIGNAR RUTINA A CLIENTE" << endl;
                    cout << "2) BAJA DE ASIGNACION DE RUTINA" << endl;
                    cout << "0) VOLVER AL MENU ANTERIOR" << endl;
                    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
                    cout << "INGRESE UNA OPCION: ";
                    cin >> opcion_asignacion;
                    switch(opcion_asignacion){
                        case 1:
                            system("cls");
                            cargarRutinaXCliente();
                            break;
                        case 2:
                            system("cls");
                            bajaRutinaXCliente();
                            break;
                        case 0:
                            break;
                        default:
                            break;
                    }
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

      /*  void menu_reservas(){
            int opcion;
            bool en_curso = true;

            while(en_curso){
                cout << "- - - - - - - MENU DE RESERVAS - - - - - - - -" << endl;
                cout << "1) CARGAR RESERVA" << endl;
                cout << "2) BUSCAR RESERVA POR NUMERO DE SOCIO" << endl;
                cout << "3) MOSTRAR TODAS LAS RESERVAS" << endl;
                cout << "0) VOLVER AL MENU ANTERIOR" << endl;
                cout << "- - - - - - - - - - - - - - - - - - - - - - -" << endl;
                cout << "INGRESE UNA OPCION: ";
                cin >> opcion;
                system("cls");
                switch(opcion){
                    case 1:
                        cargarReserva();
                        system("pause");
                        break;
                    case 2:
                       cout << "INGRSE NUMERO DE SOCIO: ";
                        cin >> nroSocio;
                        buscar_reserva_x_nroSocio(nroSocio);
                        system("pause");
                        break;
                    case 3:
                        mostrar_todas_las_reservas();
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
    }*/

#endif // MENUS_H_INCLUDED
