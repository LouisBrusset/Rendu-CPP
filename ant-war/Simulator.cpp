# include <iostream>
# include <random>
# include <vector>
# include <math.h>
# define SMALL 1e-5f

# include "Simulator.hpp"
# include "Boid.hpp"
# include "Vector.hpp"


Simulator::Simulator() : numBoids(5) {}
Simulator::Simulator(const int n) : numBoids(n) {}
// Pas besoin de constructeur par copie parce qu'on va faire qu'un seule simulation
Simulator::~Simulator() {} // std::cout << "Destructor Simulation" << std::endl; }


int Simulator::init() {

    // Initialisation SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_TIMER) != 0) {
        std::cerr << "Erreur lors de l'initialisation de SDL : " << SDL_GetError() << std::endl;
        return 1;
    }
    // Création de la fenêtre
    const float initVelocity = 1.f;
    window = SDL_CreateWindow("Boids Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_RESIZABLE);
    if (!window) {
        std::cerr << "Erreur lors de la création de la fenêtre : " << SDL_GetError() << std::endl;
        SDL_CloseAudio();
        SDL_Quit();
        return 1;
    }
    // Création du rendu
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Erreur lors de la création du rendu : " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    // Création des outils aléatoires
    std::seed_seq seed{ 1 };
    /*std::random_device rd;*/
    std::default_random_engine gen(seed);
    std::uniform_real_distribution<float> distrX(0, screenWidth);
    std::uniform_real_distribution<float> distrY(0, screenHeight);
    std::uniform_real_distribution<float> distrV(-initVelocity, initVelocity);
    
    // Création de l'essaim de Boids
    for (int i = 0; i < numBoids; i++) {
        float x = distrX(gen);
        float y = distrY(gen);
        float vx = distrV(gen);
        float vy = distrV(gen);
        /*
        bool test = false;
        for (int j = 0; j < i; j++) {
            if (abs(boids[j].x-x) <= SMALL && abs(boids[j].y-y) <= SMALL) {
                test = true;
            }
        }
        if (test) { i--; break; }
        */
        boids.push_back(Boid(x, y, vx, vy));
    }
    return 0;
}


void Simulator::update() {
    
    for (auto& boid : boids) {
        boid.wallAvoidance();

        boid.cohesion( boids, cohesionDistance, cohesionForce );
        boid.separation( boids, separationDistance, separationForce);
        boid.alignment( boids, alignmentDistance, alignmentForce );

        boid.maxVelocity(velmax);

        boid.update_boid();
        /*
            Ici pour update les prédateur et créer la nourriture.
        */
    }
}


void Simulator::render() {
    SDL_SetRenderDrawColor(renderer, 255u, 255u, 255u, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    
    for (Boid boid : boids) {
        boid.draw_boid(this->renderer);
    }

    SDL_RenderPresent(renderer);
}


int Simulator::Simulation() {

    bool end = false;
    while (not end) {
        SDL_Event event;
        if (SDL_WaitEventTimeout(&event, 20)) {
            switch (event.type) {
            case SDL_WINDOWEVENT:
                switch (event.window.event) {
                case SDL_WINDOWEVENT_CLOSE:
                    end = true;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        end = true;
                    }
                case SDL_WINDOWEVENT_SIZE_CHANGED:
                    // Should never happen
                    break;
                default:
                    break;
                }
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    end = true;
                }
                break;
            case SDL_KEYUP:
                break;
            }
        }
        else {
            // Got time out or error
            char const* e = SDL_GetError();
            if (e != NULL) {
                if (strlen(e) != 0) {
                    // Got error
                    return 1;
                }
            }
            render();
            update();
            SDL_Delay(10);
            
        }
    }

    // Nettoyage
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_CloseAudio();
    SDL_Quit();

    return 0;
}
