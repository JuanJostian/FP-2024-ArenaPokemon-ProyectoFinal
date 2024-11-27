double elementalModifier(Tipos attackType, Tipos defenderType) { 
    if ((attackType == Tipos::Planta && defenderType == Tipos::Agua) || 
        (attackType == Tipos::Agua && defenderType == Tipos::Fuego) || 
        (attackType == Tipos::Fuego && defenderType == Tipos::Planta) )
        return 1.2; 

    if ((attackType == Tipos::Agua && defenderType == Tipos::Planta) ||
        (attackType == Tipos::Fuego && defenderType == Tipos::Agua) ||
        (attackType == Tipos::Planta && defenderType == Tipos::Fuego)
        )
        return 0.8;

    return 1.0;
}


void battle(EntrenadorPokemon& entrenador1, EntrenadorPokemon& entrenador2, PokemonData& pokemon1, PokemonData& pokemon2) {

    cout << "\n===== ¡COMIENZA LA BATALLA! =====" << endl;

    cout << entrenador1.nombre << " (Jugador 1) VS " << entrenador2.nombre << " (Jugador 2)" << endl;

    while (pokemon1.hp > 0 && pokemon2.hp > 0) {
        cout << entrenador1.nombre << " ataca con " << pokemon1.nombre << " (HP: " << pokemon1.hp << ")" << endl;
        cout << "1. Ataque 1 (" << pokemon1.ataques[0] << " daño)\n";
        cout << "2. Ataque 2 (" << pokemon1.ataques[1] << " daño)\n";
        cout << "3. Curacion (" << pokemon1.curacion << " de curacion)\n";

        int attackChoice;
        cin >> attackChoice;
        if (attackChoice == 1 || attackChoice == 2)
        {
            int damage1 = pokemon1.ataques[attackChoice - 1] * elementalModifier(pokemon1.tipo1, pokemon2.tipo1); 
            pokemon2.hp -= damage1; 
        } else {
            int curacion1 = pokemon1.curacion; 
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