#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED

    void menu_personas();
    void menu_empleados();
    void menu_socios();
    void sub_menu_socios_modificar();
    void menu_rutina();
    void sub_menu_rutina_modificar();
    void menu_reservas();
    void sub_menu_reservas_buscar();
    void sub_menu_reservas_mostrar();
    void sub_menu_reservas_modificar();


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
                cout << "4) BAJA SOCIO" << endl;
                cout << "5) MODIFICAR SOCIO" << endl;
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
                    case 4:
                        baja_socio();
                        break;
                    case 5:
                        sub_menu_socios_modificar();
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
            cout << "0) VOLVER AL MENU ANTERIOR" << endl;
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
            cout << "6) MODIFICAR RUTINA" << endl;
            cout << "0) VOLVER AL MENU ANTERIOR" << endl;
            cout << "- - - - - - - - - - - - - - - - - - - - - - -" << endl;
            cout << "INGRESE UNA OPCION: ";
            cin >> opcion;

            switch(opcion){
                case 1:
                    alta_rutina();
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
                    cout << "COMO DESEA VER EL ORDEN DE LAS RUTINAS";
                    cout << endl << "1) - POR NUMERO DE RUTINA ";
                    cout << endl << "2) - POR NIVEL DE RUTINA ";
                    cout << endl << "3) - POR TIPO DE RUTINA ";
                    cout << endl << "OPCION: ";
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
                case 6:
                    sub_menu_rutina_modificar();
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

    void menu_reservas(){
            int opcion, opcion_buscar, opcion_mostrar;
            bool en_curso = true;

            while(en_curso){
                cout << "- - - - - - - MENU DE RESERVAS - - - - - - - -" << endl;
                cout << "1) CARGAR RESERVA" << endl;
                cout << "2) BUSCAR RESERVAS" << endl;
                cout << "3) MOSTRAR RESERVAS" << endl;
                cout << "4) ELIMINAR RESERVA" << endl;
                cout << "5) MODIFICAR RESERVA" << endl;
                cout << "0) VOLVER AL MENU ANTERIOR" << endl;
                cout << "- - - - - - - - - - - - - - - - - - - - - - -" << endl;
                cout << "INGRESE UNA OPCION: ";
                cin >> opcion;
                system("cls");
                switch(opcion){
                    case 1:
                        system("cls");
                        alta_reserva();
                        break;
                    case 2:
                        sub_menu_reservas_buscar();
                        break;
                    case 3:
                        sub_menu_reservas_mostrar();
                        break;
                    case 4:
                        baja_reserva();
                        break;
                    case 5:
                        sub_menu_reservas_modificar();
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

    void sub_menu_reservas_buscar(){
        system("cls");
        int opcion, nReserva, nSocio, nCancha;
        cout << "- - - - - - - SUB MENU BUSCAR RESERVAS - - - - - - - -" << endl;
        cout << "1) BUSCAR RESERVAS POR NUMERO DE SOCIO" << endl;
        cout << "2) BUSCAR RESERVAS POR NUMERO DE CANCHA" << endl;
        cout << "3) BUSCAR RESERVAS POR NUMERO DE RESERVA" << endl;
        cout << "0) VOLVER AL MENU ANTERIOR" << endl;
        cout << "- - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
        cout << "INGRESE UNA OPCION: ";
        cin >> opcion;
        system("cls");
        switch(opcion){
            case 1:
                cout << "INGRESE EL NUMERO DE SOCIO: ";
                cin >> nSocio;
                buscar_reservas_x_nroSocio(nSocio);
                cout << "presione una tecla para continuar";
                system("pause>nul");
                break;
            case 2:
                cout << "INGRESE EL NUMERO DE CANCHA: ";
                cin >> nCancha;
                buscar_reserva_x_cancha(nCancha);
                cout << "presione una tecla para continuar";
                system("pause>nul");
                break;
            case 3:
                cout << "INGRESE EL NUMERO DE RESERVA: ";
                cin >> nReserva;
                buscar_reserva_x_nroReserva(nReserva);
                cout << "presione una tecla para continuar";
                system("pause>nul");
                break;
            case 0:
                break;
            default:
                break;
        }
    }

    void sub_menu_reservas_mostrar(){
        system("cls");
        int opcion, nCancha;
        cout << "- - - - - - - SUB MENU MOSTRAR RESERVAS - - - - - - - - - - - - -" << endl;
        cout << "1) MOSTRAR RESERVAS ORDENADAS POR NUMERO DE RESERVA" << endl;
        cout << "2) MOSTRAR RESERVAS POR NUMERO DE CANCHA" << endl;
        cout << "3) MOSTRAR TODAS LAS RESERVAS ORDENADAS POR NUMERO DE CANCHA" << endl;
        cout << "0) VOLVER AL MENU ANTERIOR" << endl;
        cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
        cout << "INGRESE UNA OPCION: ";
        cin >> opcion;
        system("cls");
        switch(opcion){
           case 1:
                mostrar_todas_las_reservas_x_nro_reserva();
                cout << "presione una tecla para continuar";
                system("pause>nul");
                break;
            case 2:
                cout << "INGRESE EL NUMERO DE CANCHA: ";
                cin >> nCancha;
                buscar_reserva_x_cancha(nCancha);
                cout << "presione una tecla para continuar";
                system("pause>nul");
                break;
            case 3:
                mostrar_todas_las_reservas();
                break;
            case 0:
                break;
            default:
                break;
        }
    }

    void sub_menu_socios_modificar(){
        system("cls");
        int opcion;
        cout << "- - - - - - - SUB MENU MODIFICAR SOCIO - - - - - - -" << endl;
        cout << "1) MODIFICAR NOMBRE" << endl;
        cout << "2) MODIFICAR APELLIDO" << endl;
        cout << "3) MODIFICAR DNI" << endl;
        cout << "4) MODIFICAR EMAIL" << endl;
        cout << "5) MODIFICAR DIRECCION" << endl;
        cout << "6) MODIFICAR SEXO" << endl;
        cout << "7) MODIFICAR TELEFONO" << endl;
        cout << "8) MODIFICAR FECHA DE NACIMIENTO" << endl;
        cout << "0) VOLVER AL MENU ANTERIOR" << endl;
        cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
        cout << "INGRESE UNA OPCION: ";
        cin >> opcion;
        system("cls");
        switch(opcion){
            case 1:
                modificar_nombre_socio();
                break;
            case 2:
                modificar_apellido_socio();
                break;
            case 3:
                modificar_dni_socio();
                break;
            case 4:
                modificar_email_socio();
                break;
            case 5:
                modificar_direccion_socio();
                break;
            case 6:
                modificar_sexo_socio();
                break;
            case 7:
                modificar_telefono_socio();
                break;
            case 8:
                modificar_fecha_nacimiento_socio();
                break;
            case 0:
                break;
            default:
                break;
        }
    }

    void sub_menu_reservas_modificar(){
        system("cls");
        int opcion;
        cout << "- - - - - - - SUB MENU MODIFICAR RESERVA - - - - - - -" << endl;
        cout << "1) MODIFICAR FECHA" << endl;
        cout << "2) MODIFICAR NUMERO DE CANCHA" << endl;
        cout << "3) MODIFICAR DURACION" << endl;
        cout << "0) VOLVER AL MENU ANTERIOR" << endl;
        cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
        cout << "INGRESE UNA OPCION: ";
        cin >> opcion;
        system("cls");
        switch(opcion){
            case 1:
                modificar_fecha_reserva();
                break;
            case 2:
                modificar_cancha_reserva();
                break;
            case 3:
                modificar_duracion_reserva();
                break;
            case 0:
                break;
            default:
                break;
        }
    }

    void sub_menu_rutina_modificar(){
         system("cls");
        int opcion;
        cout << "- - - - - - - SUB MENU MODIFICAR RUTINA - - - - - - -" << endl;
        cout << "1) MODIFICAR DURACION" << endl;
        cout << "2) MODIFICAR TIPO" << endl;
        cout << "3) MODIFICAR NIVEL" << endl;
        cout << "0) VOLVER AL MENU ANTERIOR" << endl;
        cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
        cout << "INGRESE UNA OPCION: ";
        cin >> opcion;
        system("cls");
        switch(opcion){
            case 1:
                modificar_duracion_rutina();
                break;
            case 2:
                modificar_tipo_de_rutina();
                break;
            case 3:
                modificar_nivel_de_rutina();
                break;
            case 0:
                break;
            default:
                break;
        }
    }

#endif // MENUS_H_INCLUDED
