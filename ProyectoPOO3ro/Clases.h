//
// Created by pollofeliz on 29/04/25.
//

#ifndef DICCIONARIOS_DE_CLASES_H
#define DICCIONARIOS_DE_CLASES_H

#include <array>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

#define CANTIDADPRENDAS 200

// Clase Prenda
class Prenda {
public:
    string nombre;
    int id;
    double precio;
    int stock;

    // Constructor
    Prenda(string nombre, int id, double precio, int stock)
        : nombre(nombre), id(id), precio(precio), stock(stock) {}

    // Método para mostrar información
    void mostrarInfo() const {
        cout << "ID: " << id << " | Nombre: " << nombre
             << " | Precio: $" << fixed << setprecision(2) << precio
             << " | Stock: " << stock << endl;
    }
};

// Clase Ticket
class Ticket {
public:
    Prenda prenda; // Prenda asociada al ticket
    int cantidad;  // Cantidad comprada
    double total;  // Total pagado (precio * cantidad)

    // Constructor
    Ticket(const Prenda& prenda, int cantidad)
        : prenda(prenda), cantidad(cantidad), total(prenda.precio * cantidad) {}

    // Método para mostrar información del ticket
    void mostrarInfo() const {
        cout << "Ticket para: " << prenda.nombre
             << " | Cantidad: " << cantidad
             << " | Total: $" << fixed << setprecision(2) << total << endl;
    }
};

// Clase Almacen
class Almacen {
private:
    vector<Prenda> arrayDePrendas; // Inventario dinámico
    const size_t capacidadMaxima = CANTIDADPRENDAS; // Límite máximo

public:
    // Constructor
    Almacen() = default;

    // Método para agregar una prenda
    bool agregarPrenda(const Prenda& prenda) {
        if (arrayDePrendas.size() < capacidadMaxima) {
            arrayDePrendas.push_back(prenda);
            return true;
        }
        return false; // Almacen lleno
    }

    // Método para modificar stock
    bool modificarStock(int id, int nuevoStock) {
        for (auto& prenda : arrayDePrendas) {
            if (prenda.id == id) {
                prenda.stock = nuevoStock;
                return true;
            }
        }
        return false; // Prenda no encontrada
    }

    // Método para obtener prenda por ID
    Prenda* getPrenda(int id) {
        for (auto& prenda : arrayDePrendas) {
            if (prenda.id == id) {
                return &prenda;
            }
        }
        return nullptr; // Prenda no encontrada
    }

    // Método para mostrar inventario
    void mostrarInventario() const {
        cout << "\nInventario del Almacen:\n";
        for (const auto& prenda : arrayDePrendas) {
            prenda.mostrarInfo();
        }
    }

    // Método para obtener el inventario completo
    const vector<Prenda>& getInventario() const {
        return arrayDePrendas;
    }
};

// Clase abstracta Persona
class Persona {
protected:
    string nombre;
    int id;
    string contacto;
    array<Ticket, 2> arrayDeTickets; // Hasta 2 tickets por persona
    int ticketsUsados = 0; // Contador de tickets usados

public:
    // Constructor
    Persona(string nombre, int id, string contacto): nombre(nombre), id(id), contacto(contacto), arrayDeTickets(arrayDeTickets){};

    // Destructor virtual
    virtual ~Persona() = default;

    // Métodos virtuales puros
    virtual void realizarAccion(Almacen& almacen) = 0;
    virtual string getRol() const = 0;

    // Métodos getters
    string getNombre() const { return nombre; }
    int getId() const { return id; }
    string getContacto() const { return contacto; }

    // Método para agregar un ticket
    bool agregarTicket(const Ticket& ticket) {
        if (ticketsUsados < 2) {
            arrayDeTickets[ticketsUsados] = ticket;
            ticketsUsados++;
            return true;
        }
        return false; // Límite de tickets alcanzado
    }

    // Método para mostrar tickets
    void mostrarTickets() const {
        cout << "Tickets de " << nombre << ":\n";
        for (int i = 0; i < ticketsUsados; i++) {
            arrayDeTickets[i].mostrarInfo();
        }
    }
};

// Clase Administrador
class Administrador : public Persona {
public:
    Administrador(string nombre, int id, string contacto)
        : Persona(nombre, id, contacto) {}

    string getRol() const override {
        return "Administrador";
    }

    void realizarAccion(Almacen& almacen) override {
        cout << "Administrador " << nombre << " gestionando almacen.\n";
        int opcion;
        do {
            cout << "\n1. Agregar prenda\n2. Modificar stock\n3. Mostrar inventario\n4. Salir\nOpcion: ";
            cin >> opcion;
            if (opcion == 1) {
                string nom;
                int id, stock;
                double precio;
                cout << "Nombre: ";
                cin.ignore();
                getline(cin, nom);
                cout << "ID: ";
                cin >> id;
                cout << "Precio: ";
                cin >> precio;
                cout << "Stock: ";
                cin >> stock;
                Prenda prenda(nom, id, precio, stock);
                if (almacen.agregarPrenda(prenda)) {
                    cout << "Prenda agregada.\n";
                } else {
                    cout << "Almacen lleno.\n";
                }
            } else if (opcion == 2) {
                int id, nuevoStock;
                cout << "ID de la prenda: ";
                cin >> id;
                cout << "Nuevo stock: ";
                cin >> nuevoStock;
                if (almacen.modificarStock(id, nuevoStock)) {
                    cout << "Stock actualizado.\n";
                } else {
                    cout << "Prenda no encontrada.\n";
                }
            } else if (opcion == 3) {
                almacen.mostrarInventario();
            }
        } while (opcion != 4);
    }
};

// Clase Empleado
class Empleado : public Persona {
public:
    Empleado(string nombre, int id, string contacto)
        : Persona(nombre, id, contacto) {}

    string getRol() const override {
        return "Empleado";
    }

    void realizarAccion(Almacen& almacen) override {
        cout << "Empleado " << nombre << " asistiendo venta.\n";
        int id, cantidad;
        cout << "ID de la prenda: ";
        cin >> id;
        cout << "Cantidad: ";
        cin >> cantidad;
        Prenda* prenda = almacen.getPrenda(id);
        if (prenda && prenda->stock >= cantidad) {
            prenda->stock -= cantidad;
            Ticket ticket(*prenda, cantidad);
            if (agregarTicket(ticket)) {
                cout << "Venta registrada. Total: $" << fixed << setprecision(2)
                     << ticket.total << endl;
                ticket.mostrarInfo();
            } else {
                cout << "Límite de tickets alcanzado.\n";
            }
        } else {
            cout << (prenda ? "Stock insuficiente.\n" : "Prenda no encontrada.\n");
        }
    }
};

// Clase Cliente
class Cliente : public Persona {
public:
    Cliente(string nombre, int id, string contacto)
        : Persona(nombre, id, contacto) {}

    string getRol() const override {
        return "Cliente";
    }

    void realizarAccion(Almacen& almacen) override {
        cout << "Cliente " << nombre << " comprando.\n";
        int id, cantidad;
        cout << "ID de la prenda: ";
        cin >> id;
        cout << "Cantidad: ";
        cin >> cantidad;
        Prenda* prenda = almacen.getPrenda(id);
        if (prenda && prenda->stock >= cantidad) {
            prenda->stock -= cantidad;
            Ticket ticket(*prenda, cantidad);
            if (agregarTicket(ticket)) {
                cout << "Compra exitosa. Total: $" << fixed << setprecision(2)
                     << ticket.total << endl;
                ticket.mostrarInfo();
            } else {
                cout << "Límite de tickets alcanzado.\n";
            }
        } else {
            cout << (prenda ? "Stock insuficiente.\n" : "Prenda no encontrada.\n");
        }
    }
};

#endif // DICCIONARIOS_DE_CLASES_H