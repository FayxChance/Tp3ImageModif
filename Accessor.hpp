#ifndef _ACCESSOR_HPP_
#define _ACCESSOR_HPP_

#include "Color.hpp"
/// Accesseur trivial générique
template <typename TValue>
struct TrivialAccessor
{
    typedef TValue Value;
    typedef Value Argument;
    typedef Value &Reference;
    // Acces en lecture.
    static Value access(const Argument &arg)
    {
        return arg;
    }
    // Acces en écriture.
    static Reference access(Argument &arg)
    {
        return arg;
    }
};

// Accesseur trivial pour une image en niveaux de gris
typedef TrivialAccessor<unsigned char> GrayLevelTrivialAccessor;
// Accesseur trivial pour une image en couleur.
typedef TrivialAccessor<Color> ColorTrivialAccessor;

/// Accesseur à la composante verte.
struct ColorGreenAccessor
{
    typedef unsigned char Value;
    typedef Color Argument;

    /// Même astuce que pour les références à un bit dans un tableau de bool.
    struct ColorGreenReference
    {
        Argument &arg;
        ColorGreenReference(Argument &someArg) : arg(someArg) {}

        // Accesseur lvalue (écriture)
        // permet d'écrire *it = 120 pour changer l'intensité du vert
        ColorGreenReference &operator=(Value val)
        {
            arg.green = val;
            return *this;
        }

        // Accesseur rvalue (lecture)
        // permet d'écrire *it pour récupérer l'intensité du vert
        operator Value() const
        {
            return arg.green; // arg.green est de type Value.
        }
    };
    typedef ColorGreenReference Reference;

    // Acces en lecture.
    static Value access(const Argument &arg)
    {
        return arg.green;
    }
    // Acces en écriture.
    static Reference access(Argument &arg)
    {
        return ColorGreenReference(arg);
    }
};

struct ColorBlueAccessor
{
    typedef unsigned char Value;
    typedef Color Argument;

    /// Même astuce que pour les références à un bit dans un tableau de bool.
    struct ColorBlueReference
    {
        Argument &arg;
        ColorBlueReference(Argument &someArg) : arg(someArg) {}

        // Accesseur lvalue (écriture)
        // permet d'écrire *it = 120 pour changer l'intensité du vert
        ColorBlueReference &operator=(Value val)
        {
            arg.blue = val;
            return *this;
        }

        // Accesseur rvalue (lecture)
        // permet d'écrire *it pour récupérer l'intensité du vert
        operator Value() const
        {
            return arg.blue; // arg.green est de type Value.
        }
    };
    typedef ColorBlueReference Reference;

    // Acces en lecture.
    static Value access(const Argument &arg)
    {
        return arg.blue;
    }
    // Acces en écriture.
    static Reference access(Argument &arg)
    {
        return ColorBlueReference(arg);
    }
};

struct ColorRedAccessor
{
    typedef unsigned char Value;
    typedef Color Argument;

    /// Même astuce que pour les références à un bit dans un tableau de bool.
    struct ColorRedReference
    {
        Argument &arg;
        ColorRedReference(Argument &someArg) : arg(someArg) {}

        // Accesseur lvalue (écriture)
        // permet d'écrire *it = 120 pour changer l'intensité du vert
        ColorRedReference &operator=(Value val)
        {
            arg.red = val;
            return *this;
        }

        // Accesseur rvalue (lecture)
        // permet d'écrire *it pour récupérer l'intensité du vert
        operator Value() const
        {
            return arg.red; // arg.green est de type Value.
        }
    };
    typedef ColorRedReference Reference;

    // Acces en lecture.
    static Value access(const Argument &arg)
    {
        return arg.red;
    }
    // Acces en écriture.
    static Reference access(Argument &arg)
    {
        return ColorRedReference(arg);
    }
};

#endif // _ACCESSOR_HPP_
