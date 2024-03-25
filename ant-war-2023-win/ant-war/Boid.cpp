# include <iostream>
# include <vector>
# include <math.h>
# define SMALL 1e-5f

# include "Boid.hpp"
# include "Simulator.hpp"
# include "Vector.hpp"


Boid::Boid() : x(0.f), y(0.f), vx(1), vy(1), position(x, y), velocity(vx, vy) {}
Boid::Boid(float x, float y, float vx, float vy) : x(x), y(y), vx(vx), vy(vy), position(x, y), velocity(vx, vy) {
}
Boid::Boid(const Boid& other) : x(other.x), y(other.y), vx(other.vx), vy(other.vy), position(other.position), velocity(other.velocity) {
}
Boid::~Boid() {} // std::cout << "Destructor Boid" << std::endl; }


// Fonction pour décrire l'essain de Boids
float Boid::distance(const Boid& other) const {
	return sqrtf((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
}

// Fonctions pour appliquer les règles de cohésion, séparation et alignement
/*
Vector Boid::cohesion(const std::vector<Boid>& boids) const {}
Vector Boid::separation(const std::vector<Boid>& boids) const {}
Vector Boid::alignment(const std::vector<Boid>& boids) const {}
*/

// Règle de cohésion
void Boid::cohesion(const std::vector<Boid>& boids, float cohesionDistance, float cohesionForce) {
    for (auto& boid : boids) {
        float avgX = 0.0;
        float avgY = 0.0;
        int count = 0;
        for (const auto& other : boids) {
            if (&boid != &other) {
                float d = boid.distance(other);
                if (d < cohesionDistance) {
                    avgX += other.x;
                    avgY += other.y;
                    count++;
                }
            }
        }
        if (count > 0) {
            avgX /= count;
            avgY /= count;
            // Calculer la force pour se diriger vers le centre de masse
            vx += (avgX - x) / cohesionForce;
            vy += (avgY - y) / cohesionForce;
        }
    }
}

// Règle de séparation
void Boid::separation(const std::vector<Boid>& boids, float separationDistance, float separationForce) {
    for (auto& boid : boids) {
        float forceX = 0.0;
        float forceY = 0.0;
        for (const auto& other : boids) {
            if (&boid != &other) {
                float d = boid.distance(other);
                if (d < separationDistance) {
                    // Calculer la force répulsive
                    forceX += (x - other.x) / d;
                    forceY += (y - other.y) / d;
                }
            }
        }
        // Appliquer la force
        vx += forceX / separationForce;
        vy += forceY / separationForce;
    }
}


// Règle d'alignement
void Boid::alignment(const std::vector<Boid>& boids, float alignmentDistance, float alignmentForce) {
    for (auto& boid : boids) {
        float avgVX = 0.0;
        float avgVY = 0.0;
        int count = 0;
        for (const auto& other : boids) {
            if (&boid != &other) {
                float d = boid.distance(other);
                if (d < alignmentDistance) {
                    avgVX += other.vx;
                    avgVY += other.vy;
                    count++;
                }
            }
        }
        if (count > 0) {
            avgVX /= count;
            avgVY /= count;
            // Calculer la force pour aligner la vitesse
            vx += (avgVX - vx) / alignmentForce;
            vy += (avgVY - vy) / alignmentForce;
        }
    }
}

void Boid::wallAvoidance() {
    if (x < 0) { x = screenWidth; }
    if (x > screenWidth) { x = 0; }
    if (y < 0) { y = screenHeight; }
    if (y > screenHeight) { y = 0; }
}

void Boid::maxVelocity(int velmax) {
    float norm = velocity.magnitude();
    velocity = velocity * (1 / norm);
}

// Fonction de mise à jour de la position du Boid en fonction des règles
void Boid::update_boid() {
    float dt = 1.f; 
    x += dt * vx;
    y += dt * vy;
}

void Boid::draw_boid(SDL_Renderer* renderer) {
    int radius = 5;
    SDL_SetRenderDrawColor(renderer, 0u, 0u, 0u, SDL_ALPHA_OPAQUE);

    int a = radius - 1;
    int b = 0;
    int da = 1;
    int db = 1;
    int err = da - (radius << 1);
    while (a >= b) {
        SDL_RenderDrawPoint(renderer, x + a, y + b);
        SDL_RenderDrawPoint(renderer, x + b, y + a);
        SDL_RenderDrawPoint(renderer, x - b, y + a);
        SDL_RenderDrawPoint(renderer, x - a, y + b);
        SDL_RenderDrawPoint(renderer, x - a, y - b);
        SDL_RenderDrawPoint(renderer, x - b, y - a);
        SDL_RenderDrawPoint(renderer, x + b, y - a);
        SDL_RenderDrawPoint(renderer, x + a, y - b);
        if (err <= 0) {
            b++;
            err += db;
            db += 2;
        }
        if (err > 0) {
            a--;
            da += 2;
            err += da - (radius << 1);
        }
    }
    Vector norm = velocity.normalized()*15;
    float nX = norm.getX();
    float nY = norm.getY();

    SDL_RenderDrawLine(renderer, x, y, x+nX, y+nY);
    //int offset = 15.f;
    //SDL_Rect r = { x-offset, y-offset, 30., 30. };
    //SDL_RenderFillRect(renderer, &r);
}


