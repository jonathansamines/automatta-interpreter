// ConsoleMenu.h
// Explorador de Menus de Opciones
// Curso : Lenguajes Formales y Automatas
// Autores : Jonathan Raí Samines Solares
//           Emmanuel Rodriguez Dubón

#include<iostream>
#include<vector>
#include<string>
#include<sstream>

#ifdef __cplusplus__
  #include <cstdlib>
#else
  #include <stdlib.h>
#endif

#include "OpcionMenu.h"

using namespace std;

namespace menu{

    // Representa un menu con el que se interactua desde la consola
    class ConsoleMenu{

        public :
            // Constante utilizada para mostrar una línea separadora
            const string APP_LINE_BREAK = ".....................................................................";

            // metodos
            void clearScreen(void);
            void mostrarMenuOpciones(string nombreMenu, vector<OpcionMenu> menus, bool clear);
            bool pedirOpcionMenu(string nombreMenu, vector<OpcionMenu> menu, OpcionMenu &opcionMenu, int opcionSalida, bool clear);

            string getString(string mensaje);
            int getInt(string mensaje);
            void writeLine(string mensaje);
            void write(string mensaje);
            void endLine();
    };

    // Convierte un número entero a una cadena
    string convertIntToString(int numero){
        stringstream stream;
        stream << numero;

        return stream.str();
    }

    // convierte una cadena a un número entero
    int convertStringToInt(string valor){
        int valorEntero;

        stringstream linestream(valor);
        linestream>>valorEntero;

        return valorEntero;
    }

    // limpia la pantalla de la consola
    void ConsoleMenu::clearScreen(void){
        if (system("CLS")) system("clear");
    }

    // Escribe un mensaje en la consola
    // <param name="mensaje">Mensaje a mostrar al usaurio.</param>
    void ConsoleMenu::write(string mensaje){
        cout<<mensaje;
    }

    // Genera un salto de línea en la consola
    void ConsoleMenu::endLine(){
        cout<<endl;
    }

    // Escribe un mensaje en la consola, creando un salto de linea tras mostrarlo
    // <param name="mensaje">Mensaje a mostrar al usaurio.</param>
    void ConsoleMenu::writeLine(string mensaje){
        this->write(mensaje);
        this->endLine();
    }

    // Obtiene una cadena de caracteres de la consola
    // <param name="mensaje">Mensaje a mostrar al usaurio.</param>
    string ConsoleMenu::getString(string mensaje){
        string valor;

        this->write(mensaje);
        getline(cin, valor);

        return valor;
    }

    // Obtiene una cadena de caracteres casteada como entero de la consola
    // <param name="mensaje">Mensaje a mostrar al usaurio.</param>
    int ConsoleMenu::getInt(string mensaje){
        string valor = this->getString(mensaje);

        return convertStringToInt(valor);
    }

    // muestra un menú genérico de opciones
    // <param name='nombreMenu'>Nombre del Menu</param>
    // <param name='menus'>Vector con el menu de opciones de la aplicación.</param>
    // <param name='clear'>Indica si se debe de limpiar la pantalla.</param
    void ConsoleMenu::mostrarMenuOpciones(string nombreMenu, vector<OpcionMenu> menus, bool clear){
        if(clear){
            clearScreen();
        }

        // muestra el titulo del menu
        this->writeLine(APP_LINE_BREAK);
        this->endLine();
        this->writeLine(nombreMenu);
        this->writeLine(APP_LINE_BREAK);

        // se itera a través de las opciones del menu para mostrarlas
        for(vector<int>::size_type i = 0; i < menus.size(); i++) {
            this->writeLine(" [" + convertIntToString(i) + "] " + menus[i].descripcion);
        }

        this->endLine();
    }

    // pide al usuario una opcion del menu de aplicaciones,
    // indicando si la opcion es válida para el menú indicado
    // <param name='nombreMenu'>Nombre del Menu</param>
    // <param name='menu'>Menu de opciones disponible</param>
    // <param name='opcionMenu'>referencia a la opcion seleccionada retornada.</param>
    // <param name='opcionSalida'>posicion de la opcion de salida del menú. Por defecto será el último elemento del array.</param>
    // <param name='clear'>Indica si se debe de limpiar la pantalla.</param>
    bool ConsoleMenu::pedirOpcionMenu(string nombreMenu, vector<OpcionMenu> menu, OpcionMenu &opcionMenu, int opcionSalida, bool clear){

        // se muestra el menu
        this->mostrarMenuOpciones(nombreMenu, menu, clear);

        // se pide al usuario que ingrese una opcion
        int opcionSeleccionada = -1, ultimaOpcion = opcionSalida == -1 ? menu.size() - 1 : opcionSalida;

        opcionSeleccionada = this->getInt(" - Seleccione una opcion del menu : ");

        // se verifica si el valor es válido para el menu
        if(opcionSeleccionada >= ultimaOpcion){
            opcionMenu = menu[ultimaOpcion];
            return false;
        }else{
            opcionMenu = menu[opcionSeleccionada];
            return true;
        }
    }
}

