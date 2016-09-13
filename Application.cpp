// Application.cpp
// Clase lanzador de la aplicación
// Curso : Lenguajes Formales y Automatas
// Autores : Jonathan Raí Samines Solares
//           Emmanuel Rodriguez Dubón

#include<iostream>
#include<vector>
#include<string>
#include<stdexcept>

#include "ConsoleMenu.h"
#include "Automata.h";
#include "Alumno.h";

namespace automatas{

    // Clase que representa una instancia de la aplicación de validación
    // de cadenas utilizando automatas
    class Application{

        private :
            // propiedades
            menu::ConsoleMenu console;
            vector<menu::OpcionMenu> menuOpciones;

            // metodos
            vector<menu::OpcionMenu> generarMenuOpciones();
            void mostrarEncabezadoAplicacion();

        public :
            // propiedades
            string nombreProyecto;
            vector<Alumno> integrantes;

            // constructor
            Application(string nombreProyecto);

            // metodos
            void start();
    };

    // Constructor de la clase Application
    // <param name="nombreProyecto">Nombre del proyecto</param>
    Application::Application(string nombreProyecto){
        this->nombreProyecto = nombreProyecto;
        this->menuOpciones = this->generarMenuOpciones();
    }

    // Muestra la informacion de cabecera de la aplicación
    void Application::mostrarEncabezadoAplicacion(){
        cout<<"\t\t "<<this->nombreProyecto<<"\t\t"<<endl;
        cout<<this->console.APP_LINE_BREAK<<endl;

        // se muestra la lista de integrantes
        for(vector<string>::size_type i = 0; i < this->integrantes.size(); i++){
            Alumno alumno = this->integrantes[i];
            cout<<" Nombre : "<<alumno.nombreAlumno<< "\t"<<" Carné : "<<alumno.carneAlumno<<endl;
        }

        cout<<this->console.APP_LINE_BREAK<<endl;

        // instrucciones
        cout<<" A continuación se le presenta el funcionamiento de un automata "<<endl;
        cout<<" que permite validar cadenas de entrada en base a una quintupla "<<endl;
        cout<<" predefinida del automata."<<endl;
    }

    // Genera el menu de opciones de la aplicación
    vector<menu::OpcionMenu> Application::generarMenuOpciones(){

        // menu de opciones global
        vector<menu::OpcionMenu> opciones;
        menu::OpcionMenu configAutomata;
        configAutomata.codigoOpcion = 0;
        configAutomata.descripcion = "Parametrizar Automata";

        menu::OpcionMenu verAutomata;
        verAutomata.codigoOpcion = 1;
        verAutomata.descripcion = "Ver Automata";

        menu::OpcionMenu analizarCadena;
        analizarCadena.codigoOpcion = 2;
        analizarCadena.descripcion = "Analizar Cadena";

        menu::OpcionMenu opcionSalir;
        opcionSalir.codigoOpcion = 3;
        opcionSalir.descripcion = "Salir de Aplicacion";

        // configuracion de automata
        vector<menu::OpcionMenu> menusConfigAutomata;

        menu::OpcionMenu asignarAlfabeto;
        asignarAlfabeto.codigoOpcion = 0;
        asignarAlfabeto.descripcion = "Asignar alfabeto";

        menu::OpcionMenu asignarEstados;
        asignarEstados.codigoOpcion = 1;
        asignarEstados.descripcion = "Asignar estados";

        menu::OpcionMenu escogerEstadoInicial;
        escogerEstadoInicial.codigoOpcion = 2;
        escogerEstadoInicial.descripcion = "Escoger estado inicial";

        menu::OpcionMenu agregarAceptacion;
        agregarAceptacion.codigoOpcion = 3;
        agregarAceptacion.descripcion = "Agregar estados de aceptacion";

        menu::OpcionMenu paramFunciones;
        paramFunciones.codigoOpcion = 4;
        paramFunciones.descripcion = "Asignar funciones de transicion";

        menu::OpcionMenu finConfig;
        finConfig.codigoOpcion = 5;
        finConfig.descripcion = "Finalizar configuracion";

        menusConfigAutomata.push_back(asignarAlfabeto);
        menusConfigAutomata.push_back(asignarEstados);
        menusConfigAutomata.push_back(escogerEstadoInicial);
        menusConfigAutomata.push_back(agregarAceptacion);
        menusConfigAutomata.push_back(paramFunciones);
        menusConfigAutomata.push_back(finConfig);

        configAutomata.opciones = menusConfigAutomata;

        // se agregan los menus principales
        opciones.push_back(configAutomata);
        opciones.push_back(verAutomata);
        opciones.push_back(analizarCadena);
        opciones.push_back(opcionSalir);

        return opciones;
    }

    // Inicializa la aplicación
    void Application::start(){

        // configuracion de la aplicacion
        menu::OpcionMenu opcionSeleccionada, opcionAccion;
        utils::ArrayUtils arrayHelper;

        // se crea el contenedor de informacion del automata
        automatas::Automata automata = automatas::Automata();

        // se muestran los encabezados de la aplicación
        this->mostrarEncabezadoAplicacion();
        this->console.pedirOpcionMenu("Menu de Opciones", this->menuOpciones, opcionSeleccionada, -1, false);

        do{

            // opciones de configuracion del automata
            if(opcionSeleccionada.codigoOpcion == 0){

                while(this->console.pedirOpcionMenu(opcionSeleccionada.descripcion, opcionSeleccionada.opciones, opcionAccion, -1, true)){

                    this->console.writeLine(" + " + opcionAccion.descripcion + "  [ Deje en blanco para salir ]");
                    this->console.writeLine(this->console.APP_LINE_BREAK);

                    // asignacion del alfabeto al automata
                    if(opcionAccion.codigoOpcion == 0){
                        // se limpia la informacion del alfabeto
                        automata.alfabeto.clear();

                        while(true){
                            string simbolo = this->console.getString(" - Ingrese el símbolo por agregar al alfabeto : ");

                            if(simbolo !=  ""){
                                try{
                                    automata.addSimboloAutomata(simbolo);
                                }catch(invalid_argument e){
                                    this->console.writeLine(e.what());
                                }
                            }else{ break; }
                        }
                    }

                    // asignacion de los estados
                    if(opcionAccion.codigoOpcion == 1){
                        // reasignar los estados, tambien resetea el estado inicial y de aceptacion
                        // asi como la tabla de transiciones
                        automata.estadoInicial = string();
                        automata.estadosAceptacion.clear();
                        automata.transiciones.clear();

                        while(true){
                            string estado = this->console.getString(" - Ingrese el identificador del estado : ");

                            if(estado!=  ""){
                                try{
                                    automata.addEstadoAutomata(estado);
                                }catch(invalid_argument e){
                                    this->console.writeLine(e.what());
                                }
                            }else{ break; }
                        }
                    }

                    // escoger estado inicial
                    if(opcionAccion.codigoOpcion == 2){
                        string estadoInicial = this->console.getString(" - Ingrese el identificador del estado inicial : ");
                        try{
                            automata.setEstadoInicial(estadoInicial);
                        }catch(invalid_argument e){
                            this->console.writeLine(e.what());
                        }
                    }

                    // escoger estados de aceptacion
                    if(opcionAccion.codigoOpcion == 3){

                        // se limpian los estados de aceptacion
                        automata.estadosAceptacion.clear();

                        while(true){
                            string estado = this->console.getString(" - Ingrese el identificador del estado : ");

                            if(estado !=  ""){
                                try{
                                    automata.addEstadoAceptacion(estado);
                                }catch(invalid_argument e){
                                    this->console.writeLine(e.what());
                                }
                            }else{ break; }
                        }
                    }

                    // parametrizar funciones de transicion
                    if(opcionAccion.codigoOpcion == 4){
                        // se limpian las transiciones
                        automata.transiciones.clear();


                        this->console.writeLine(" + Funciones de transicion ");
                        this->console.writeLine(this->console.APP_LINE_BREAK);

                        // se recorre la lista de estados del alfabeto y se parametriza
                        // la funcion de transicion para cada estado y simbolo
                        for(vector<int>::size_type e = 0; e < automata.estados.size(); e++){
                            for(vector<int>::size_type a = 0; a < automata.alfabeto.size(); a++) {
                                Transicion transicion;
                                transicion.estadoEntrada = automata.estados[e];
                                transicion.simboloEntrada = automata.alfabeto[a];
                                transicion.estadoResultado = console.getString("  - d( " + transicion.estadoEntrada + ", " + transicion.simboloEntrada + " ) = ");

                                try{
                                    automata.addTransicion(transicion);
                                }catch(invalid_argument e){
                                    this->console.writeLine(e.what());
                                    a--;
                                }
                            }
                        }
                    }

                }


            }

            // opcion de visualizacion de informacion del automata
            if(opcionSeleccionada.codigoOpcion == 1){
                this->console.mostrarMenuOpciones(opcionSeleccionada.descripcion, opcionSeleccionada.opciones, true);

                this->console.writeLine(" Lenguaje :  {" + arrayHelper.join(",", automata.alfabeto) + "}");
                this->console.writeLine(" Estados  :  {" + arrayHelper.join(",", automata.estados) + "}");
                this->console.writeLine(" Estado Inicial :  " + automata.estadoInicial);
                this->console.writeLine(" Aceptacion :  {" + arrayHelper.join(",", automata.estadosAceptacion) + "}");
                this->console.writeLine(" Funciones de Transicion : ");

                for(int i = 0 ; i < automata.transiciones.size(); i++){
                    Transicion transicion = automata.transiciones[i];
                    this->console.writeLine("  d( " + transicion.estadoEntrada + " , " + transicion.simboloEntrada + " ) = " + transicion.estadoResultado);
                }

                this->console.endLine();
                this->console.getString(" PRESIONE ENTER PARA SALIR DEL MENU.");
            }

            // opcion de analizar cadena
            if(opcionSeleccionada.codigoOpcion == 2){
                this->console.mostrarMenuOpciones(opcionSeleccionada.descripcion, opcionSeleccionada.opciones, true);

                string cadena = this->console.getString(" + Ingrese una cadena a validar : ");

                try{
                    bool estadoProcesamiento = automata.procesarEntrada(cadena);

                    if(estadoProcesamiento){
                        this->console.writeLine(" - Cadena válida para el automata.");
                    }else{
                        this->console.writeLine(" - Cadena inválida para el automata.");
                    }
                }catch(invalid_argument e){
                    this->console.writeLine(e.what());
                }

                this->console.endLine();
                this->console.getString(" PRESIONE ENTER PARA SALIR DEL MENU.");
            }

            this->console.clearScreen();
            this->mostrarEncabezadoAplicacion();
        }while(this->console.pedirOpcionMenu("Menu de Opciones", this->menuOpciones, opcionSeleccionada, -1, false));

    }
}

int main(){

    // Se crea una instancia de la aplicacion
    automatas::Application app = automatas::Application("Proyecto Final de Automatas");
    app.integrantes.push_back(automatas::Alumno("Jonathan Raí Samines Solares", "6590-13-3813"));
    app.integrantes.push_back(automatas::Alumno("Emmanuel Rodriguez Dubon", "0000-00-0000"));

    app.start();

    return 0;
}

