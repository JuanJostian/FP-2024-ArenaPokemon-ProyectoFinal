#include <iostream>
#include "string"
#include <fstream>
#include <sstream>
using namespace std;

// Arena Pokemon

// Empezamos declarando las funciones y donde guardaremos los datos de todos los pokemones

// Como con esta funcio class, lo que hace la funcion enum class es que enumera tipos de clases y podemos guardar estos datos dentro de estructuras como la que usaremos despues para guardar todos los datos de los pokemones
enum class Tipos{ // Con 
    Agua, 
    Fuego,
    Planta,
};

// Con esta funcion convertimos el class como un string asi podremos usarlo para guardarlo dentro de un archivo o en general para poder usarlo como si fuera un string
string tipoToString(Tipos tipo) {
    switch (tipo) {
        case Tipos::Agua: return "Agua";
        case Tipos::Fuego: return "Fuego";
        case Tipos::Planta: return "Planta";
        default: return "Desconocido";
    }
}

// El primer struct, este guardara los datos de todos los pokemons que despues aplicaremos a los que deseemos usar
struct PokemonData
{
    string nombre;
    int hp;
    int ataques[2];
    int curacion;
    Tipos tipo1;
};

// Y en el segundo struct se guardaron los datos del Entrenador pokemon, su nombre, los pokemones que tenga, y los items que cargue
struct EntrenadorPokemon
{
    string nombre;
    PokemonData pokemon;
    int caramelo = 5;
};

//Luego declaramos todos los pokemons que se puedan elegir

//Empezamos con Charmander:
PokemonData charmander = {"Charmander", 100, {30, 20}, 10, Tipos::Fuego};

//Seguimos con Bulbasaur:
PokemonData bulbasaur = {"Bulbasaur", 100, {25, 15}, 12, Tipos::Planta};

//Squirtle:
PokemonData squirtle = {"Squirtle", 100, {28, 18}, 11, Tipos::Agua};

//Seran dos entrenadores quienes pelearan en la arena pokemon, asi que los guardamos
EntrenadorPokemon entrenador1;
EntrenadorPokemon entrenador2;

// Con los siguientes dos void guardaremos los datos de los entrenadores en un archivo txt 
void guardarEntrenadorPokemon1(const EntrenadorPokemon& entrenador1, const PokemonData& pokemon1)
{
    ofstream archivo1("inventario1.txt", ios::out); // El ios::out nos marca que abriremos o crearemos el archivo txt para guardar datos en el.
    if (archivo1.is_open()) // Verificamos que el archivo se abra correctamente
    {
        // Y guardamos todos los datos del inventario del entrenador:
        archivo1 << "Nombre del entrenador: " << entrenador1.nombre << endl; 
        archivo1 << "Pokemon: " << pokemon1.nombre << " " << pokemon1.hp << " " << pokemon1.ataques[0] << " " << pokemon1.ataques[1] << " " << pokemon1.curacion << " " << tipoToString(pokemon1.tipo1) << endl;
        archivo1 << "Cantidad de caramelos: " << entrenador1.caramelo << endl;
        archivo1 << "-----------------------" << endl;
        archivo1.close();
        cout << "Bienvenido a tu aventura pokemon!" << endl;
    } else {
        cout << "No se pudo guardar tus datos" << endl;
    }
    
}

void guardarEntrenadorPokemon2(const EntrenadorPokemon& entrenador2, const PokemonData& pokemon2) // Hacemos lo mismo en el archivo del entrenador 2
{
    ofstream archivo2("inventario2.txt", ios::out);
    if (archivo2.is_open())
    {
        archivo2 << "Nombre del entrenador: " << entrenador2.nombre << endl;
        archivo2 << "Pokemon: " << pokemon2.nombre << " " << pokemon2.hp << " " << pokemon2.ataques[0] << " " << pokemon2.ataques[1] << " " << pokemon2.curacion << " " << tipoToString(pokemon2.tipo1) << endl;
        archivo2 << "Cantidad de caramelos: " << entrenador2.caramelo << endl;
        archivo2 << "-----------------------" << endl;
        archivo2.close();
        cout << "Bienvenido a tu aventura pokemon!" << endl;
    } else {
        cout << "No se pudo guardar tus datos" << endl;
    }
    
}

// Creamos una funcion booleana para poder cargar los datos del entrenador
bool cargarEntrenadorPokemon1(EntrenadorPokemon& entrenador1, PokemonData& pokemon1) {
    ifstream archivo1("inventario1.txt");
    if (archivo1.is_open()) {
        string linea; // creamos una variable string
        while (getline(archivo1, linea)) { // la funcion get.line analizara todo el archivo asi como tambien el string que creamos para poder usar de nuevo los datos del entrenador
            if (linea.find("Nombre del entrenador:") != string::npos) { // Si encuentra la linea "nombre del entrenador"
                entrenador1.nombre = linea.substr(22); // Quita de esa linea "Nombre del entrenador, asi solo tomara especificamente el nombre del entrenador" 
            }
            else if (linea.find("Pokemon:") != string::npos) { // Hacemos lo mismo con el pokemon
                string tipo; // Pero creamos un string 'tipo' para poder separar y definir el tipo de cada pokemon y volver a usarlo como un class
                istringstream iss(linea.substr(9)); // Quita "Pokemon: " para solo usar el nombre y separa todos los demas datos del pokemon
                iss >> pokemon1.nombre >> pokemon1.hp >> pokemon1.ataques[0] >> pokemon1.ataques[1] >> pokemon1.curacion >> tipo;
                pokemon1.tipo1 = (tipo == "Agua") ? Tipos::Agua : (tipo == "Fuego") ? Tipos::Fuego : Tipos::Planta; // Y analiza cual tipo es para cargar el dato nuevamente y usarlo en la pelea pokemon
            }
            else if (linea.find("Caramelos:") != string::npos) {
                entrenador1.caramelo = stoi(linea.substr(10)); // Quita "Caramelos: "
            }
        }
        archivo1.close(); // Cerramos el archivo
        return true;
    } else {
        cout << "Error al abrir el archivo para cargar los datos.\n";
        return false;
    }
}

bool cargarEntrenadorPokemon2(EntrenadorPokemon& entrenador2, PokemonData& pokemon2) { // Hacemos lo mismo con el segundo entrenador
    ifstream archivo2("inventario2.txt");
    if (archivo2.is_open()) {
        string linea;
        while (getline(archivo2, linea)) {
            if (linea.find("Nombre del entrenador:") != string::npos) {
                entrenador2.nombre = linea.substr(22); // Quita "Entrenador: "
            }
            else if (linea.find("Pokemon:") != string::npos) {
                string tipo;
                istringstream iss(linea.substr(9)); // Quita "Pokemon: "
                iss >> pokemon2.nombre >> pokemon2.hp >> pokemon2.ataques[0] >> pokemon2.ataques[1] >> pokemon2.curacion >> tipo;
                pokemon2.tipo1 = (tipo == "Agua") ? Tipos::Agua : (tipo == "Fuego") ? Tipos::Fuego : Tipos::Planta;
            }
            else if (linea.find("Caramelos:") != string::npos) {
                entrenador2.caramelo = stoi(linea.substr(10)); // Quita "Caramelos: "
            }
        }
        archivo2.close();
        return true;
    } else {
        cout << "Error al abrir el archivo para cargar los datos.\n";
        return false;
    }
}

// Funciones para mostrar las estadisticas del entrenador y su pokemon
void mostrarEntrenadorPokemon1(const EntrenadorPokemon& entrenador1, const PokemonData& pokemon1){ // Esta funcion solo mostrara los datos y estadisticas del entrenador
    cout << "-----TusEstadisticas-----\n";
    cout << "Nombre: " << entrenador1.nombre << endl;
    cout << "Nombre: " << pokemon1.nombre 
         << ", HP: " << pokemon1.hp 
         << ", Ataque 1: " << pokemon1.ataques[0] 
         << ", Ataque 2: " << pokemon1.ataques[1] 
         << ", Curación: " << pokemon1.curacion 
         << ", Tipo: " << tipoToString(pokemon1.tipo1) << endl;
    
    cout << "Cuantos caramelos tienes: " << entrenador1.caramelo << endl;
}

void mostrarEntrenadorPokemon2(const EntrenadorPokemon& entrenador2, const PokemonData& pokemon2){ // Hacemos lo mismo para el segundo entrenador:
    cout << "-----TusEstadisticas-----\n";
    cout << "Nombre: " << entrenador2.nombre << endl;
    cout << "Nombre: " << pokemon2.nombre 
         << ", HP: " << pokemon2.hp 
         << ", Ataque 1: " << pokemon2.ataques[0] 
         << ", Ataque 2: " << pokemon2.ataques[1] 
         << ", Curación: " << pokemon2.curacion 
         << ", Tipo: " << tipoToString(pokemon2.tipo1) << endl;
    
    cout << "Cuantos caramelos tienes: " << entrenador2.caramelo << endl;
}


// Hay cierta ventaja o desventaja si usamos unos pokemons contra otros, para eso creamos una funcion que guarde esa informacion:
double elementalModifier(Tipos attackType, Tipos defenderType) { // Con esta funcion se podran cambiar la ventaja o desventaja elemental que tenga cada pokemon
    if ((attackType == Tipos::Planta && defenderType == Tipos::Agua) || 
        (attackType == Tipos::Agua && defenderType == Tipos::Fuego) || 
        (attackType == Tipos::Fuego && defenderType == Tipos::Planta) )
        return 1.2; // Ventaja elemental

    if ((attackType == Tipos::Agua && defenderType == Tipos::Planta) ||
        (attackType == Tipos::Fuego && defenderType == Tipos::Agua) ||
        (attackType == Tipos::Planta && defenderType == Tipos::Fuego)
        )
        return 0.8; // Desventaja elemental

    return 1.0; // Daño neutral
}

// En este void tendremos la pelea pokemon
void battle(EntrenadorPokemon& entrenador1, EntrenadorPokemon& entrenador2, PokemonData& pokemon1, PokemonData& pokemon2) {

    cout << "\n===== ¡COMIENZA LA BATALLA! =====" << endl;

    cout << entrenador1.nombre << " (Jugador 1) VS " << entrenador2.nombre << " (Jugador 2)" << endl;

    while (pokemon1.hp > 0 && pokemon2.hp > 0) {
        // Esto mostrara las opciones que tiene el entrenador para usar
        cout << entrenador1.nombre << " ataca con " << pokemon1.nombre << " (HP: " << pokemon1.hp << ")" << endl;
        cout << "1. Ataque 1 (" << pokemon1.ataques[0] << " daño)\n";
        cout << "2. Ataque 2 (" << pokemon1.ataques[1] << " daño)\n";
        cout << "3. Curacion (" << pokemon1.curacion << " de curacion)\n";

        // Y creamos la opcion que elegira el entrenador
        int attackChoice;
        cin >> attackChoice;
        if (attackChoice == 1 || attackChoice == 2)
        {
            int damage1 = pokemon1.ataques[attackChoice - 1] * elementalModifier(pokemon1.tipo1, pokemon2.tipo1); // Aqui se guardan dos cosas, primero el daño que hara el pokemon con el ataque que haya elegido, despues llamamos la funcion de modificador elemental para poder verificar si hay ventaja u desventaja en el ataque que hara el pokemon
            pokemon2.hp -= damage1; // Y se resta ese daño
        } else {
            int curacion1 = pokemon1.curacion; // creamos un entero para que le añada vida al pokemon cuando se use
            pokemon1.hp += curacion1;
            if (pokemon1.hp > 100)
            {
                pokemon1.hp = 100;
            }
            
        }
        

        if (pokemon2.hp <= 0) {
            cout << pokemon2.nombre << " ha sido derrotado. ¡" << entrenador1.nombre << " gana!" << endl;
            break;
        }


        // Turno del jugador 2, lo mismo ocurre que con el entrenador 1

        cout << entrenador2.nombre << " ataca con " << pokemon2.nombre << " (HP: " << pokemon2.hp << ")" << endl;
        cout << "1. Ataque 1 (" << pokemon2.ataques[0] << " daño)\n";
        cout << "2. Ataque 2 (" << pokemon2.ataques[1] << " daño)\n";
        cout << "3. Curacion (" << pokemon2.curacion << " daño)\n"; 

        cin >> attackChoice;

        if(attackChoice == 1 || attackChoice == 2){
        int damage2 = pokemon2.ataques[attackChoice - 1] * elementalModifier(pokemon2.tipo1, pokemon1.tipo1);
        pokemon1.hp -= damage2;
        } else {
            int curacion2 = pokemon2.curacion;
            pokemon2.hp += curacion2;
            if (pokemon2.hp > 100)
            {
                pokemon2.hp = 100;
            }
            
        }

        if (pokemon1.hp <= 0) {
            cout << pokemon1.nombre << " ha sido derrotado. ¡" << entrenador2.nombre << " gana!" << endl;
            break;
        }

    }

}

void IniciodeSesion(EntrenadorPokemon& entrenador1, EntrenadorPokemon& entrenador2, PokemonData& pokemon1, PokemonData& pokemon2){
    char opcion_InicioSesion1;
    char opcion_InicioSesion2;
    cout << "BIENVENIDO A LA ARENA POKEMON! \n";
    cout << "Eres nuevo o ya eres un entrenador pokemon? (s/n): ";
    cin >> opcion_InicioSesion1;

    if (opcion_InicioSesion1 == 's' || opcion_InicioSesion1 == 'S')
    {
        if (cargarEntrenadorPokemon1(entrenador1, pokemon1))
        {
            cout << "Datos cargados bienvenido " << entrenador1.nombre << "! \n";
            mostrarEntrenadorPokemon1(entrenador1, pokemon1);
        } else {
            cout << "No encontramos tus datos, pero puedes registrarte! \n";
            cout << "Ingresa tu nombre: \n";
            cin >> entrenador1.nombre;
            cout << "Elije un pokemon: \n";
            cout << "1. Charmander: " << endl;
            cout << "   Tipo: " << tipoToString(charmander.tipo1) << endl;
            cout << "2. Bulbasaur: " << endl;
            cout << "   Tipo: " << tipoToString(bulbasaur.tipo1) << endl;
            cout << "3. Squirtle: " << endl;
            cout << "   Tipo: " << tipoToString(squirtle.tipo1) << endl;
            int eleccion1;

            cin >> eleccion1;
            pokemon1 = (eleccion1 == 1 ? charmander : eleccion1 == 2 ? bulbasaur : squirtle);

            guardarEntrenadorPokemon1(entrenador1, pokemon1);
        }
        
    } else
    {
        cout << "Eres nuevo por aqui, registrate! \n";
        cout << "Ingresa tu nombre: \n";
        cin >> entrenador1.nombre;
        cout << "Elije un pokemon: \n";
        cout << "1. Charmander: " << endl;
        cout << "   Tipo: " << tipoToString(charmander.tipo1) << endl;
        cout << "2. Bulbasaur: " << endl;
        cout << "   Tipo: " << tipoToString(bulbasaur.tipo1) << endl;
        cout << "3. Squirtle: " << endl;
        cout << "   Tipo: " << tipoToString(squirtle.tipo1) << endl;
        int eleccion1;

        cin >> eleccion1;
        pokemon1 = (eleccion1 == 1 ? charmander : eleccion1 == 2 ? bulbasaur : squirtle);

        guardarEntrenadorPokemon1(entrenador1, pokemon1);
    }
    

    cout << "Segundo jugador, BIENVENIDO A LA ARENA POKEMON! \n";
    cout << "Eres nuevo o ya eres un entrenador pokemon? (s/n) \n";
    cin >> opcion_InicioSesion2;
    if (opcion_InicioSesion2 == 's' || opcion_InicioSesion2 == 'S')
    {
        if (cargarEntrenadorPokemon2(entrenador2, pokemon2))
        {
            cout << "Datos cargados bienvenido " << entrenador2.nombre << "! \n";
            mostrarEntrenadorPokemon2(entrenador2, pokemon2);
        } else {
            cout << "No encontramos tus datos, pero puedes registrarte! \n";
            cout << "Ingresa tu nombre: \n";
            cin >> entrenador2.nombre;
            cout << "Elije un pokemon: \n";
            cout << "1. Charmander: " << endl;
            cout << "   Tipo: " << tipoToString(charmander.tipo1) << endl;
            cout << "2. Bulbasaur: " << endl;
            cout << "   Tipo: " << tipoToString(bulbasaur.tipo1) << endl;
            cout << "3. Squirtle: " << endl;
            cout << "   Tipo: " << tipoToString(squirtle.tipo1) << endl;
            int eleccion2;

            cin >> eleccion2;
            pokemon2 = (eleccion2 == 1 ? charmander : eleccion2 == 2 ? bulbasaur : squirtle);

            guardarEntrenadorPokemon2(entrenador2, pokemon2);
        }
        
    } else 
    {
        cout << "Eres nuevo tambien, entonces registrate! \n";
        cout << "Ingresa tu nombre: \n";
        cin >> entrenador2.nombre;
        cout << "Elije un pokemon: \n";
        cout << "1. Charmander: " << endl;
        cout << "   Tipo: " << tipoToString(charmander.tipo1) << endl;
        cout << "2. Bulbasaur: " << endl;
        cout << "   Tipo: " << tipoToString(bulbasaur.tipo1) << endl;
        cout << "3. Squirtle: " << endl;
        cout << "   Tipo: " << tipoToString(squirtle.tipo1) << endl;
        int eleccion2;

        cin >> eleccion2;

        pokemon2 = (eleccion2 == 1 ? charmander : eleccion2 == 2 ? bulbasaur : squirtle);

        guardarEntrenadorPokemon2(entrenador2, pokemon2);
    }
}

void Menu(EntrenadorPokemon& entrenador1, EntrenadorPokemon& entrenador2, PokemonData& pokemon1, PokemonData& pokemon2){
    int opcion_Menu;
    int salir;
    do
    {
        cout << "   ----- Bienvenido a la Arena Pokemon ----- " << endl;
        cout << "--------------------Menu-------------------- " << endl;
        cout << "---- 1. Pelea ---- " << endl;
        cout << "---- 2. Instrucciones ----" << endl;
        cout << "---- 3. Pokedex ----" << endl;
        cout << "---- 4. Salir ---- " << endl;
        cout << "---- Elija su opcion ----: " << endl;
        cin >> opcion_Menu;

        switch (opcion_Menu)
        {
            case 1:

                battle(entrenador1, entrenador2, pokemon1, pokemon2);
                break;

            case 2:
                cout << "En la Arena Pokemon tendran un combate entre pokemons, cada uno con sus habilidades especiales." << endl;
                cout << "El combate ocurrira por turnos y cada turno aparecera un menu de ataques para cada pokemon." << endl;
                cout << "Elige tu habilidad, ya sea ataque o vida. En cada turno se actualizara la vida de ti y de tu oponente." << endl;
                break;

            case 3:
                cout << "------------ Pokédex ------------" << endl;
                cout << "1. Charmander: " << endl;
                cout << "   Tipo: " << tipoToString(charmander.tipo1) << endl;
                cout << "   Habilidad: Llama" << endl;
                cout << "   Descripcion: Charmander es un Pokémon de tipo fuego, conocido por su llamita en la punta de su cola." << endl;
                cout << "2. Bulbasaur: " << endl;
                cout << "   Tipo: " << tipoToString(bulbasaur.tipo1) << endl;
                cout << "   Habilidad: Chlorophyll" << endl;
                cout << "   Descripcion: Bulbasaur es un Pokémon de tipo planta/veneno que tiene una planta en su espalda que crece con el tiempo." << endl;
                cout << "3. Squirtle: " << endl;
                cout << "   Tipo: " << tipoToString(squirtle.tipo1) << endl;
                cout << "   Habilidad: Torrente" << endl;
                cout << "   Descripcion: Squirtle es un Pokémon de tipo agua, conocido por su caparazón resistente y su habilidad para disparar agua." << endl;
                break;

            case 4:
                cout << "Saliendo..." << endl;
                break;

            default:
                cout << "Opción inválida." << endl;
                break;

        }

        if (opcion_Menu != 4)
        {
            cout << "Presiona 0 para regresar al menu \n";
            cin >> salir;
        }
        
    } while (opcion_Menu != 4);
}

// Ahora empecemos con el cuerpo del codigo
int main(){
    EntrenadorPokemon entrenador1;
    EntrenadorPokemon entrenador2;
    PokemonData pokemon1;
    PokemonData pokemon2;

    IniciodeSesion(entrenador1, entrenador2, pokemon1, pokemon2); //Llamamos la funcion para iniciar sesion

    Menu(entrenador1, entrenador2, pokemon1, pokemon2); // El menu que mostrara para las cuatro diferentes opciones

    return 0;
}