#include <iostream>


/**
 *Creado por Jesus Emmanuel 29/04/25
 */

using namespace std;

class Producto {
public:
    string nombre;
    int id;
    double precio;
    int stock;

    Producto(string nombre, int id, double precio, int stock)
        : nombre(nombre), id(id), precio(precio), stock(stock) {}

    void mostrarInfo() const {
        cout << "ID: " << id << " | Nombre: " << nombre 
             << " | Precio: $" << fixed << setprecision(2) << precio 
             << " | Stock: " << stock << endl;
    }
};

// Clase abstracta Persona


// Clase Administrador
class Administrador : public Persona {
public:
    Administrador(string nombre, int id) : Persona(nombre, id) {}

    string getRol() const override {
        return "Administrador";
    }
    int modificar_inventario(){

    }
    int eliminar_prenda(){

    }

class Inventario {


}:


using namespace std;
int main() {

    return 0;
}




