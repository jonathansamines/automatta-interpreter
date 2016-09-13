// Alumno.h
// Entidad que representa la información de un alumno
// Curso : Lenguajes Formales y Automatas
// Autores : Jonathan Raí Samines Solares
//           Emmanuel Rodriguez Dubón

#include<string>

using namespace std;

namespace automatas{

    // Representa la información de un alumno
    class Alumno{

        public :
            string nombreAlumno;
            string carneAlumno;

            Alumno(string nombre, string carne);
    };

    // Constructor de la clase Alumno
    // <param name="nombre">Nombre completo del alumno</param>
    // <param name="carne">Número de carné del alumno</param>
    Alumno::Alumno(string nombre, string carne){
        this->nombreAlumno = nombre;
        this->carneAlumno = carne;
    }


}
