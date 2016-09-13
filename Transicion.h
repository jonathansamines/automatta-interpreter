// Transicion.h
// Entidad que representa el estado de una transición
// Curso : Lenguajes Formales y Automatas
// Autores : Jonathan Raí Samines Solares
//           Emmanuel Rodriguez Dubón

namespace automatas{

    // Clase que representa un estado de una transición
    // Corresponde al conjunto de estadoAnterior - estadoSiguiente - SimboloEntrada
    // que representa el estado de una funcion de transicion del automata
    class Transicion{

        public :

            // propiedades
            string estadoEntrada;
            string estadoResultado;
            string simboloEntrada;
    };
}
