/**
 *Creado por Jesus Emmanuel 29/04/25
 */
#include <iostream>
#include <vector>
#include "Clases.h"


using namespace std;


int main() {
    Almacen almacen;
    almacen.agregarPrenda(Prenda("Camisa", 1, 25.99, 50));
    almacen.agregarPrenda(Prenda("Pantalon", 2, 39.99, 30));
    almacen.agregarPrenda(Prenda("Chaqueta", 3, 59.99, 20));

    vector<Persona*> personas = {
        new Administrador("Ana", 101, "ana@tienda.com"),
        new Empleado("Carlos", 102, "carlos@tienda.com"),
        new Cliente("Maria", 103, "maria@cliente.com")
    };

    int opcion;
    do {
        cout << "\n1. Mostrar inventario\n2. Realizar accion\n3. Salir\nOpcion: ";
        cin >> opcion;
        if (opcion == 1) {
            almacen.mostrarInventario();
        } else if (opcion == 2) {
            int id;
            cout << "ID de la persona: ";
            cin >> id;
            for (auto* persona : personas) {
                if (persona->getId() == id) {
                    cout << "Rol: " << persona->getRol() << endl;
                    persona->realizarAccion(almacen);
                    persona->mostrarTickets();
                    break;
                }
            }
        }
    } while (opcion != 3);

    // Liberar memoria
    for (auto* persona : personas) {
        delete persona;
    }

    return 0;
}