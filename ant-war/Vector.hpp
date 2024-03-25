// file Vector.hpp
# ifndef VECTOR_HPP_
# define VECTOR_HPP_


// Classe représentant un vecteur en 2D

class Vector {
protected:
    

public:
    float a, b;

    Vector();
    Vector(float a, float b);
    Vector(const Vector& other);
    ~Vector();

    // Fonctions pour les opérations vectorielles (addition, soustraction, normalisation, etc.)
    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator*(float scalar) const;
    Vector normalized() const;
    float magnitude() const;
    float getX() const;
    float getY() const;

    // ...
};

# endif