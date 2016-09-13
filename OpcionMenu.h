// OpcionMenu.h
// Representa el estado de una opcion de menu
// Curso : Lenguajes Formales y Automatas
// Autores : Jonathan Raí Samines Solares
//           Emmanuel Rodriguez Dubón

#include<string>

using namespace std;

namespace menu{

    // Representa una opcion de un menú de aplicaciones
    class OpcionMenu{

        public :

            // propiedades
            int codigoOpcion;
            string descripcion;
            vector<OpcionMenu> opciones;
    };
}
