#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED

    void menu_personas();
    void menu_empleados();
    void sub_menu_empleados_modificar();
    void sub_menu_empleados_buscar();
    void menu_socios();
    void sub_menu_socios_modificar();
    void menu_rutina();
    void sub_menu_rutina_modificar();
    void menu_reservas();
    void sub_menu_reservas_buscar();
    void sub_menu_reservas_mostrar();
    void sub_menu_reservas_modificar();
    void menu_actividades();
    void sub_menu_actividades_modificar();
    void menu_principal();
    void menu_principal_entrenadores();
    void menu_principal_limpieza();
    void menu_principal_socios();
    void sub_menu_principal_socios_rutinas();
    void sub_menu_principal_socios_actividades();
    void menu_login();

    void menu_login(){
        int opcion, nSocio, nEmpleado;
        Empleado reg;
        bool estado = true;

        while(estado){
            cout << "- - - - - MENU LOGIN - - - - - -" << endl;
            cout << "1) MENU SOCIOS" << endl;
            cout << "2) MENU EMPLEADOS" << endl;
            cout << "0) SALIR DEL PROGRAMA" << endl;
            cout << "- - - - - - - - - - - - - - - - " << endl;
            cout << "INGRESE UNA OPCION: ";
            cin >> opcion;

            system("cls");
            switch(opcion){
                case 1:

                    cout << "INGRESE SU NUMERO DE SOCIO: ";
                    cin >> nSocio;

                    if(buscarSocioXNro(nSocio)){
                        socio_actual = get_socio(nSocio);
                        menu_principal_socios();
                    }



                    break;
                case 2:

                    cout << "INGRESE SU NUMERO DE EMPLEADO: ";
                    cin >> nEmpleado;

                    reg = buscar_empleado_x_nro_empleado(nEmpleado);

                    if(reg.getNroEmpleado()!=nEmpleado){
                        system("cls");
                        cout << endl << "EL EMPLEADO NO EXISTE" << endl;
                        break;
                    }

                    empleado_actual = reg;

                    if(strcmp(reg.getTipoDeEmpleado(), ADMINISTRATIVO)==0){

                        menu_principal();

                    } else if(strcmp(reg.getTipoDeEmpleado(), ENTRENADOR)==0){

                        menu_principal_entrenadores();

                    } else {

                        menu_principal_limpieza();
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

    void menu_principal_socios(){
        int opcion;
        bool estado = true;

        while(estado){


            cout << "- - - - - - - MENU PRINCIPAL DE " << socio_actual.getNombre() << " - - - - - - - -" << endl;
            cout << "1) VER PERFIL" << endl;
            cout << "2) GESTIONAR RUTINAS" << endl;
            cout << "3) GESTIONAR ACTIVIDADES" << endl;
            cout << "4) VER MIS RESERVAS" << endl;
            cout << "0) CERRAR SESION" << endl;
            cout << "- - - - - - - - - - - - - - - - - - - - - - -" << endl;
            cout << "INGRESE UNA OPCION: ";
            cin >> opcion;

            system("cls");
            switch(opcion){
                case 1:
                    socio_actual.mostrar();
                    system("pause");
                    break;
                case 2:
                    sub_menu_principal_socios_rutinas();
                    break;
                case 3:
                    sub_menu_principal_socios_actividades();
                    break;
                case 4:
                    buscar_reservas_x_nroSocio(socio_actual.getNroSocio());
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

    void menu_principal_entrenadores(){
        int opcion;
        bool estado = true;

        while(estado){

            cout << "- - - MENU PRINCIPAL ENTRENADORES - - -" << endl;
            cout << "1) VER PERFIL" << endl;
            cout << "2) GESTIONAR RUTINAS" << endl;
            cout << "3) GESTIONAR ACTIVIDADES" << endl;
            cout << "0) CERRAR SESION" << endl;
            cout << "- - - - - - - - - - - - - - - - - - - -" << endl;
            cout << "INGRESE UNA OPCION: ";
            cin >> opcion;

            system("cls");
            switch(opcion){
                case 1:
                    break;
                case 2:
                    break;
                case 3:
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

    void menu_principal_limpieza(){
        int opcion;
        bool estado = true;

        while(estado){

            cout << "- - - MENU PRINCIPAL LIMPIEZA - - -" << endl;
            cout << "1) VER PERFIL" << endl;
            cout << "2) VER NOTICIAS" << endl;
            cout << "0) CERRAR SESION" << endl;
            cout << "- - - - - - - - - - - - - - - - - -" << endl;
            cout << "INGRESE UNA OPCION: ";
            cin >> opcion;

            system("cls");
            switch(opcion){
                case 1:
                    break;
                case 2:
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

    void menu_principal(){

        int opcion;
        bool estado = true;

        while(estado){


            cout << "- - - - - - - MENU PRINCIPAL - - - - - - - -" << endl;
            cout << "1) GESTION SOCIOS Y EMPLEADOS" << endl;
            cout << "2) GESTION DE RUTINAS" << endl;
            cout << "3) GESTION DE RESERVAS" << endl;
            cout << "4) GESTION DE ACTIVIDADES" << endl;
            cout << "0) CERRAR PROGRAMA" << endl;
            cout << "- - - - - - - - - - - - - - - - - - - - - - -" << endl;
            cout << "INGRESE UNA OPCION: ";
            cin >> opcion;

            switch(opcion){
                case 1:
                    system("cls");
                    menu_personas();
                    break;
                case 2:
                    system("cls");
                    menu_rutina();
                    break;
                case 3:
                    system("cls");
                    menu_reservas();
                    break;

                case 4:
                    system("cls");
                    menu_actividades();
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


    void menu_empleados(){

            int opcion, nroDni;
            bool estado = true;

            while(estado){
                cout << "- - - - - - - MENU DE EMPLEADOS - - - - - - - -" << endl;
                cout << "1) ALTA DE NUEVO EMPLEADO" << endl;
                cout << "2) BUSCAR EMPLEADO" << endl;
                cout << "3) MOSTRAR TODOS LOS EMPLEADOS" << endl;
                cout << "4) BAJA EMPLEADO" << endl;
                cout << "5) MODIFICAR EMPLEADO" << endl;
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
                        sub_menu_empleados_buscar();
                        break;
                    case 3:
                        int opcion_muestra;
                        system("cls");
                        cout << endl << "COMO DESEA VER TODOS LOS EMPLEADOS: " << endl;
                        cout << "1)MOSTRAR EMPLEADOS POR POSICION" << endl;
                        cout << "2)MOSTRAR EMPLEADOS POR NRO DE EMPLEADO"<< endl;
                        cout << "INGRESE UNA OPCION: ";
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

                    case 4:
                        baja_empleado();
                        break;
                    case 5:
                        sub_menu_empleados_modificar();
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

    void sub_menu_principal_socios_rutinas(){

        int opcion, cRutina;
        bool estado = true;

        while(estado){

            cout << "- - - MENU GESTION RUTINAS - - -" << endl;
            cout << "1) VER TODAS LAS RUTINAS" << endl;
            cout << "2) GUARDAR RUTINA" << endl;
            cout << "3) DAR DE BAJA RUTINA" << endl;
            cout << "4) VER MIS RUTINAS" << endl;
            cout << "0) VOLVER AL MENU ANTERIOR" << endl;
            cout << "- - - - - - - - - - - - - - - - -" << endl;
            cout << "OPCION: ";
            cin >> opcion;

            system("cls");
            switch(opcion){
                case 1:
                    mostrar_rutinas_x_tipos();
                    cout << endl << "presione una tecla para continuar";
                    system("pause>nul");
                    break;
                case 2:
                    cargarRutinaXCliente();
                    break;
                case 3:
                    cout << "INGRESE EL CODIGO DE LA RUTINA QUE DESEA ELIMINAR: ";
                    cin >> cRutina;
                    baja_de_rutina_por_cliente_menu_cliente(cRutina, socio_actual.getNroSocio());
                    break;
                case 4:
                    mostrar_rutinas_x_cliente(socio_actual.getNroSocio());
                    cout << endl << "presione una tecla para continuar";
                    system("pause>nul");
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

    void sub_menu_principal_socios_actividades(){

        int opcion, cActividad;
        bool estado = true;

        while(estado){

            cout << "- - - MENU GESTION ACTIVIDADES - - -" << endl;
            cout << "1) VER TODAS LAS ACTIVIDADES" << endl;
            cout << "2) GUARDAR ACTIVIDAD" << endl;
            cout << "3) DAR DE BAJA ACTIVIDAD" << endl;
            cout << "4) VER MIS ACTIVIDADES" << endl;
            cout << "0) VOLVER AL MENU ANTERIOR" << endl;
            cout << "- - - - - - - - - - - - - - - - -" << endl;
            cout << "OPCION: ";
            cin >> opcion;

            system("cls");
            switch(opcion){
                case 1:
                    mostrar_todas_las_actividades();
                    cout << endl << "presione una tecla para continuar";
                    system("pause>nul");
                    break;
                case 2:
                    cargarActividadXCliente();
                    break;
                case 3:
                    cout << "INGRESE EL CODIGO DE LA ACTIVIDAD QUE DESEA ELIMINAR: ";
                    cin >> cActividad;
                    baja_actividad_por_cliente_menu_cliente(socio_actual.getNroSocio(), cActividad);
                    break;
                case 4:
                    mostrar_actividades_x_nro_socio(socio_actual.getNroSocio());
                    cout << endl << "presione una tecla para continuar";
                    system("pause>nul");
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
        void menu_actividades(){
        bool est = true;
        int opcion,opcion_asignacion_act;

        while(est){

            cout << "- - - - - - -  GESTION ACTIVIDADES - - - - - - - -" << endl;
            cout << "1) CARGAR ACTIVIDAD" << endl;
            cout << "2) MOSTRAR ACTIVIDADES" << endl;
            cout << "3) BUSCAR ACTIVIDAD POR ID" << endl;
            cout << "4) ASIGNACION DE ACTIVIDAD A CLIENTE" << endl;
            cout << "5) MODIFICACION DE ACTIVIDAD" << endl;
            cout << "0) VOLVER AL MENU ANTERIOR" << endl;
            cout << "- - - - - - - - - - - - - - - - - - - - - - -" << endl;
            cout << "INGRESE UNA OPCION: ";
            cin >> opcion;

            switch(opcion){
                case 1:
                    system("cls");
                    alta_actividad();
                    system("pause");
                    break;
                case 2:
                    system("cls");
                    mostrar_todas_las_actividades();
                    system("pause");
                    break;
                case 3:
                    system("cls");
                    buscar_actividad_x_id();
                    system("pause");
                    break;
                case 4:
                     system("cls");
                    cout << "- - - - - - - MENU DE ASIGNACION DE ACTIVIDADES - - - - - - - -" << endl;
                    cout << "1) ASIGNAR ACTIVIDAD A CLIENTE" << endl;
                    cout << "2) BAJA DE ASIGNACION DE ACTIVIDAD" << endl;
                    cout << "0) VOLVER AL MENU ANTERIOR" << endl;
                    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
                    cout << "INGRESE UNA OPCION: ";
                    cin >> opcion_asignacion_act;
                    switch(opcion_asignacion_act){
                        case 1:
                            system("cls");
                           cargarActividadXCliente();
                            break;
                        case 2:
                            system("cls");
                            bajaActividadXCliente();
                            break;
                        case 0:
                            break;
                        default:
                            break;
                    }
                    break;
                        case 5:
                           sub_menu_actividades_modificar();
                           break;
                case 0:
                    est = false;
                    break;
                    default:
                    break;
            }

            system("cls");

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

     void sub_menu_empleados_modificar(){
        system("cls");
        int opcion;
        cout << "- - - - - - - SUB MENU MODIFICAR EMPLEADO - - - - - - -" << endl;
        cout << "1) MODIFICAR NOMBRE" << endl;
        cout << "2) MODIFICAR APELLIDO" << endl;
        cout << "3) MODIFICAR DNI" << endl;
        cout << "4) MODIFICAR SUELDO" << endl;
        cout << "5) MODIFICAR POSICION" << endl;
        cout << "6) MODIFICAR SEXO" << endl;
        cout << "7) MODIFICAR FECHA DE NACIMIENTO" << endl;
        cout << "0) VOLVER AL MENU ANTERIOR" << endl;
        cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
        cout << "INGRESE UNA OPCION: ";
        cin >> opcion;
        system("cls");
        switch(opcion){
            case 1:
                modificar_nombre_empleado();
                break;
            case 2:
                modificar_apellido_empleado();
                break;
            case 3:
                modificar_dni_empleado();
                break;
            case 4:
                modificar_sueldo_empleado();
                break;
            case 5:
                modificar_posicion_empleado();
                break;
            case 6:
                modificar_sexo_empleado();
                break;
            case 7:
                modificar_fecha_nacimiento_empleado();
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

    void sub_menu_actividades_modificar(){
        system("cls");
        int opcion;
        cout << "- - - - - - - SUB MENU MODIFICAR ACTIVIDAD - - - - - - -" << endl;
        cout << "1) MODIFICAR NOMBRE" << endl;
        cout << "2) MODIFICAR ENTRENADOR" << endl;
        cout << "3) MODIFICAR HORA" << endl;
        cout << "4) MODIFICAR DURACION" << endl;
        cout << "0) VOLVER AL MENU ANTERIOR" << endl;
        cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
        cout << "INGRESE UNA OPCION: ";
        cin >> opcion;
        system("cls");
        switch(opcion){
            case 1:
                modificar_nombre_actividad();
                break;
            case 2:
                modificar_entrenador();
                break;
            case 3:
                modificar_hora_actividad();
                break;
            case 4:
                modificar_duracion_actividad();
            case 0:
                break;
            default:
                break;
        }
    }

    void sub_menu_empleados_buscar(){
        long nro_dni;
        int nro_empleado;
        system("cls");
        int opcion;
        cout << "- - - - - - - SUB MENU MODIFICAR ACTIVIDAD - - - - - - -" << endl;
        cout << "1) BUSCAR POR DNI" << endl;
        cout << "2) BUSCAR POR NUMERO DE EMPLEADO" << endl;
        cout << "0) VOLVER AL MENU ANTERIOR" << endl;
        cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
        cout << "INGRESE UNA OPCION: ";
        cin >> opcion;
        system("cls");
        switch(opcion){
            case 1:
                cout << "INGRESE EL NUMERO DE DNI: ";
                cin >> nro_dni;
                buscar_empleado_x_dni(nro_dni);
                cout << "presione una tecla para continuar";
                system("pause>nul");
                break;
            case 2:
                mostrar_empleado_x_nro_empleado();
                break;
            case 0:
                break;
            default:
                break;
        }
    }

#endif // MENUS_H_INCLUDED
