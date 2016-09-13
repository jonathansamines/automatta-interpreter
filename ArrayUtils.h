// ArrayUtils.h
// Utilidades para trabajar con cadenas y arrays
// Curso : Lenguajes Formales y Automatas
// Autores : Jonathan Raí Samines Solares
//           Emmanuel Rodriguez Dubón

#include<vector>
#include<string.h>
#include<string>
#include<sstream>

using namespace std;

namespace utils{

    // Clase que provee métodos utilitarios para trabajar con cadenas y arrays
    class ArrayUtils{

        public :

            // metodos
            int indexOfElementoArray(vector<string> arreglo, string elemento);
            bool elementoEnArray(vector<string> arreglo, string elemento);
            vector<string> split(const string &cadena, string delim);
            string join(string separador, vector<string> elementos);
    };

    // Indica el indice de un elemento dentro de un vector
    // <param name='arreglo'>Array en el que se realizar la busqueda</param>
    // <param name='elemento'>valor a buscar</param>
    int ArrayUtils::indexOfElementoArray(vector<string> arreglo, string elemento){
        for(vector<int>::size_type i = 0; i < arreglo.size(); i++) {
            if(arreglo[i] == elemento){
                return i;
            }
        }

        return -1;
    }

    // Verifica si un elemento existe en un array determinado
    // <param name='arreglo'>Array en el que se realizar la busqueda</param>
    // <param name='elemento'>valor a buscar</param>
    bool ArrayUtils::elementoEnArray(vector<string> arreglo, string elemento){
        if(indexOfElementoArray(arreglo, elemento) == -1){
            return false;
        }else{
            return true;
        }
    }

    // Divide una cadena utilizando un delimitador especificado
    // <param name="s">Cadena a dividir</param>
    // <param name="delim">Simbolo utilizado como delimitador de la division.</param>
    vector<string> ArrayUtils::split(const string &cadena, string delim) {
        vector<string> tokens;

        stringstream scadena(cadena);
        string item;

        // si la caracter delimitador es un espacio vacio, se recorre caracter por caracter
        if(delim.empty() || delim == ""){
            for(int i = 0; i < cadena.size(); i++){
                stringstream schar;
                schar << cadena[i];
                schar >> item;
                tokens.push_back(item);
            }
        }else{
            // de lo contrario se asume que tengo al menos un caracter y puedo usarlo para hacer la division
            char delimc = delim[0];
            while (getline(scadena, item, delimc)) {
                tokens.push_back(item);
            }
        }

        return tokens;
    }

    // une un array utilizando el separador indicado como union entre los elementos
    // <param name="separador">Elemento separador de los elementos</param>
    // <param name="elementos">Elementos a unir</param>
    string ArrayUtils::join(string separador, vector<string> elementos){
        string resultado;

        for(vector<int>::size_type i = 0; i < elementos.size(); i++) {
            string elemento = elementos[i];

            if(i == 0)
                resultado += elemento;
            else
                resultado += "," + elemento;
        }

        return resultado;
    }

}
