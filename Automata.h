// Automata.h
// Entidad que representa el estado de un automata y sus funciones básicas
// Curso : Lenguajes Formales y Automatas
// Autores : Jonathan Raí Samines Solares
//           Emmanuel Rodriguez Dubón

#include<iostream>
#include <iomanip>
#include<vector>
#include<stdexcept>
#include<string.h>
#include<string>
#include<sstream>

#include "ArrayUtils.h"
#include "Transicion.h"

using namespace std;

namespace automatas{

    // Clase que representa la estructura de un automata
    // y las funciones de transicion básicas para un AFD
    class Automata{

        private :

            // helpers
            utils::ArrayUtils arrayUtil;

        public :
            // propiedades
            vector<string> alfabeto;
            vector<string> estados;

            vector<string> estadosAceptacion;

            string estadoInicial;
            string estadoActual;

            vector<Transicion> transiciones;

            // métodos
            Transicion transicion(string simbolo);

            void addTransicion(Transicion transicion);
            void addEstadoAutomata(string estado);
            void addEstadoAceptacion(string estado);
            void addSimboloAutomata(string simbolo);
            void setEstadoInicial(string simbolo);


            bool procesarEntrada(string cadena);
            bool esUnEstadoValido(string estado);
            bool esUnSimboloValido(string simbolo);
            bool esUnEstadoAceptacionValido(string estado);
    };


    // Indica si un estado determinado es válido para el automata
    // <param name="estado">Estado a validar</param>
    bool Automata::esUnEstadoValido(string estado){
        return this->arrayUtil.elementoEnArray(this->estados, estado);
    }


    // Indica si un simbolo determiando es válido para el automata
    bool Automata::esUnSimboloValido(string simbolo){
        return this->arrayUtil.elementoEnArray(this->alfabeto, simbolo);
    }

    // Indica si un estado determiando es un estado de aceptacion valido
    bool Automata::esUnEstadoAceptacionValido(string estado){
        return this->arrayUtil.elementoEnArray(this->estadosAceptacion, estado);
    }

     // Agrega un nuevo estado al automata, asegurandose de que no exista, en los estados ya agregados
    // <param name='estado'>Estado a agregar al automata.</param>
    void Automata::addEstadoAutomata(string estado){
        if(!this->esUnEstadoValido(estado)){
            this->estados.push_back(estado);
        }else{
            throw invalid_argument("El estado '" + estado + "'ya fue agregado al automata.");
        }
    }

    // Agrega un nuevo simbolo al automata, asegurandose de que no existe en los simbolos ya agregados
    // <param name='simbolo'>Simbolo a agregar al automata</param>
    void Automata::addSimboloAutomata(string simbolo){
        if(!this->esUnSimboloValido(simbolo)){
            this->alfabeto.push_back(simbolo);
        }else{
            throw invalid_argument("El simbolo '" + simbolo + "' ya fue agregado al automata.");
        }
    }

    // Agrega un nuevo estado de aceptación verificando que sea un estado válido para el automata
    // y que no exista en la lista de estados de aceptación
    // <param name="estado">Estado de aceptacion por agregar.</param>
    void Automata::addEstadoAceptacion(string estado){
        if(this->esUnEstadoValido(estado)){
            this->estadosAceptacion.push_back(estado);
        }else{
            throw invalid_argument("El estado de aceptacion '" + estado + "' no es válido.");
        }
    }

    // Establece un estado determinado como el estado inicial, a partir del cual
    // se realizan las transiciones del automata.
    // <param name="estado">Estado inicial a configurar.</param>
    void Automata::setEstadoInicial(string estado){
        // se verifica el simbolo inicial
        if(this->esUnEstadoValido(estado)){
            this->estadoInicial = estado;

            // se establece que el estado actual es el inicial
            this->estadoActual = this->estadoInicial;
        }else{
            throw invalid_argument("El estado inicial '" + estado + "' no es parte de los estados del automata.");
        }
    }

    // Agrega una nueva transicion, procesando las validaciones del estado de la transicion
    // para el automata en curso
    // <param name="transicion">Transicion a agregar.</param>
    void Automata::addTransicion(Transicion transicion){
        if(!this->esUnEstadoValido(transicion.estadoEntrada)){
            throw invalid_argument("El estado de entrada '" + transicion.estadoEntrada + "' de la transicion no es valido.");
        }

        if(!this->esUnEstadoValido(transicion.estadoResultado)){
            throw invalid_argument("El estado resultado '" + transicion.estadoResultado + "' de la transicion no es valido.");
        }

        if(!this->esUnSimboloValido(transicion.simboloEntrada)){
            throw invalid_argument("El simbolo de entrada '" + transicion.simboloEntrada + "' no es valido.");
        }

        this->transiciones.push_back(transicion);
    }


    // Representa el procesamiento realizado por una función de transicion
    // Devuelve el nuevo estado de transicion al que se llega a partir de un simbolo de entrada.
    Transicion Automata::transicion(string simbolo){
        // se valida el estado del automata
        if(this->estadoInicial == string() || this->estados.size() == 0 || this->alfabeto.size() == 0 || this->estadosAceptacion.size() == 0){
            throw invalid_argument("El automata no se ha configurado correctamente. Revise el estado del automata para porder procesar una transicion.");
        }


        // El proceso de encontrar el siguiente estado de transicion
        // consiste en encontrar el estado de transicion cuyo simbolo de entrada
        // sea el simbolo proporcionado y cuyo estado de entrada sea igual al estado actual del automata
        for(vector<int>::size_type i = 0; i < this->transiciones.size(); i++){
            Transicion transicion = this->transiciones[i];

            if(transicion.simboloEntrada == simbolo && transicion.estadoEntrada == this->estadoActual){
                this->estadoActual = transicion.estadoResultado;
                return transicion;
            }
        }

        return Transicion();
    }

    // Procesa una cadena de caracteres, caracter a caracter a través de las transiciones del automata
    // para verificar si la cadena es válida o no lo es
    bool Automata::procesarEntrada(string cadena){
        this->estadoActual = this->estadoInicial;

        // se divide la cadena en simbolos
        vector<string> simbolos = this->arrayUtil.split(cadena, "");

        // se valida caracter por caracter de la cadena
        for(int indexSimbolo = 0; indexSimbolo < simbolos.size(); indexSimbolo++){
            string simbolo = simbolos[indexSimbolo];

            // se procesa cada simbolo a través de las funciones de transicion
            this->transicion(simbolo);
        }

        // si el estado actual es parte de los estados de aceptación,
        // entonces la cadena se considera aceptada
        return this->esUnEstadoAceptacionValido(this->estadoActual);
    }
}
