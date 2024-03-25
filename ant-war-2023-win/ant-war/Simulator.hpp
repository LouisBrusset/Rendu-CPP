// file Simulator.hpp
# ifndef SIMULATOR_HPP_
# define SIMULATOR_HPP_
# include <iostream>
# include <vector>

#include "Vector.hpp"

#ifdef _WIN32
#include <SDL.h>
#define not !
#else
#include <SDL2/SDL.h>
#endif


// Déclaration classe Boid
class Boid;

// Classe représentant le simulateur de la simulation de BOIDS
class Simulator {
private:
    int numBoids;

    float velmax{ 1 };
    float cohesionDistance{ 50 };
    float cohesionForce{ 5 };
    float separationDistance{ 20 };
    float separationForce{ 10 };
    float alignmentDistance{ 30 };
    float alignmentForce{ 5 };

    std::vector<Boid> boids;
    SDL_Renderer* renderer;
    SDL_Window* window;

public:
    const float screenWidth = 800.f;
    const float screenHeight = 600.f;

    Simulator();
    Simulator(int numBoids);
    ~Simulator();

    // Fonction d'initialisation
    int init();

    // Fonction pour mettre à jour la simulation
    void update();

    // Fonction pour afficher la simulation
    void render();

    // Autres fonctions nécessaires
    int Simulation();



};


# endif