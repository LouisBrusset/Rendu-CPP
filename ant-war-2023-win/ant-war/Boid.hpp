// file Boid.hpp
# ifndef BOID_HPP_
# define BOID_HPP_

#include "Vector.hpp"

#ifdef _WIN32
#include <SDL.h>
#define not !
#else
#include <SDL2/SDL.h>
#endif

// Classe représentant un Boid
class Boid {
protected:


public:
    float x, y, vx, vy;
    Vector position;
    Vector velocity;
    const float screenWidth = 800.f;
    const float screenHeight = 600.f;

   
    Boid();
    Boid(float x, float y, float vx, float vy);
    Boid(const Boid& other);
    ~Boid();

    // Fonction pour décrire l'essain de Boids
    float distance(const Boid& other) const;

    // Fonctions pour appliquer les règles de cohésion, séparation et alignement
    void cohesion(const std::vector<Boid>& boids, float cohesionDistance, float cohesionForce);
    void separation(const std::vector<Boid>& boids, float separationDistance, float separationForce);
    void alignment(const std::vector<Boid>& boids, float alignmentDistance, float alignmentForce);

    void wallAvoidance();
    void maxVelocity(int velmax);

    // Fonction de mise à jour de la position du Boid en fonction des règles
    void update_boid();

    // Fonction d'affichage
    void draw_boid(SDL_Renderer* renderer);

};

# endif