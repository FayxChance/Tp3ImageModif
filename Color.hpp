#ifndef _COLOR_HPP_
#define _COLOR_HPP_

#include <math.h>
struct Histogramme
{
    double h1[256];
    double h2[256];
    template <typename InputIterator>
    void init(InputIterator it, InputIterator itE)
    {
        auto itDebutInit = it;
        auto itFinInit = itE;
        auto taille = itFinInit - itDebutInit;
        double somme = 0;
        for (int i = 0; i < 256; i++)
        {
            h1[i] = 0;
            h2[i] = 0;
        }
        while (it != itE)
        {
            int i = *it;
            // std::cout << " III : " << (double)i << std::endl;
            // somme += 1;
            h1[(int)i] += 1.0;
            ++it;
        }
        for (int i = 0; i < 256; i++)
        {
            h1[i] = h1[i] * 100 / taille;
            somme += h1[i];
            // std::cout << "------------------ SOMME TEMP ------- : i : " << i << "    " << (h1[i]) << std::endl;
        }

        // std::cout << "------------------ SOMME ------- : " << somme << std::endl;
        h2[0] = h1[0];
        for (int i = 1; i < 256; i++)
        {
            h2[i] = h1[i] + h2[i - 1];
            // std::cout << "------------------ SOMME ------- : " << h2[i] << std::endl;
        }
    }
    int egalisation(int i) const
    {
        return (int)(h2[i] / 100 * 255);
    }
};

/**
   Représente une couleur avec un codage RGB. Ce codage utilise 3
   octets, le premier octet code l'intensité du rouge, le deuxième
   l'intensité du vert, le troisième l'intensité du bleu.
*/
struct Color
{
    typedef unsigned char Byte;

    /// Code les 3 canaux RGB sur 3 octets.
    Byte red, green, blue;

    Color() {}
    /// Crée la couleur spécifiée par (_red,_green,_blue).
    Color(Byte _red, Byte _green, Byte _blue)
        : red(_red), green(_green), blue(_blue) {}

    /// @return l'intensité de rouge (entre 0.0 et 1.0)
    float r() const { return ((float)red) / 255.0; }
    /// @return l'intensité de vert (entre 0.0 et 1.0)
    float g() const { return ((float)green) / 255.0; }
    /// @return l'intensité de bleu (entre 0.0 et 1.0)
    float b() const { return ((float)blue) / 255.0; }

    /// Sert à désigner un canal.
    enum Channel
    {
        Red,
        Green,
        Blue
    };
    /// @return le canal le plus intense.
    Channel argmax() const
    {
        if (red >= green)
            return red >= blue ? Red : Blue;
        else
            return green >= blue ? Green : Blue;
    }
    float static max(float a, float b)
    {
        return a < b ? b : a;
    }
    float static min(float a, float b)
    {
        return a > b ? b : a;
    }
    /// @return l'intensité maximale des canaux
    float max() const { return max(max(r(), g()), b()); }
    /// @return l'intensité minimale des canaux
    float min() const { return min(min(r(), g()), b()); }
    /**
     Convertit la couleur RGB en le modèle HSV (TSV en français).
     @param h la teinte de la couleur (entre 0 et 359), hue en anglais.
     @param s la saturation de la couleur (entre 0.0 et 1.0)
     @param v la valeur ou brillance de la couleur (entre 0.0 et 1.0).
  */
    void getHSV(int &h, float &s, float &v) const
    {
        // Taking care of hue
        if (max() == min())
            h = 0;
        else
        {
            switch (argmax())
            {
            case Red:
                h = ((int)(60.0 * (g() - b()) / (max() - min()) + 360.0)) % 360;
                break;
            case Green:
                h = ((int)(60.0 * (b() - r()) / (max() - min()) + 120.0));
                break;
            case Blue:
                h = ((int)(60.0 * (r() - g()) / (max() - min()) + 240.0));
                break;
            }
        }
        // Taking care of saturation
        s = max() == 0.0 ? 0.0 : 1.0 - min() / max();
        // Taking care of value
        v = max();
    }

    struct ColorValueAccessor
    {
        typedef unsigned char Value;
        typedef Color Argument;
        struct ColorValueReference
        {
            Argument &arg;
            ColorValueReference(Argument &someArg) : arg(someArg) {}

            // Cette fonction sera appelée lors d'un `*it = ...`.
            // S'occupe de changer la valeur de la couleur arg
            // en fonction de la valeur donnée val.
            // Il faut utiliser arg.getHSV et arg.setHSV.
            ColorValueReference &operator=(Value val)
            {
                int h;
                float s;
                float v;
                arg.getHSV(h, s, v);
                // std::cout << " operator = Initial " << (float)v << std::endl;
                arg.setHSV(h, s, (float)val);
                // std::cout << " operator = val " << (float)val << std::endl;
                // arg.getHSV(h, s, v);
                // std::cout << " operator = v final " << (float)v << std::endl;
                return *this;
            }

            // S'occupe de retourner la valeur de la couleur arg (sans la changer).
            // Un simple appel à arg.getHSV suffira.
            operator Value() const
            {
                int h;
                float s;
                float v;
                arg.getHSV(h, s, v);
                // std::cout << " value const " << (int)(v * 255) << std::endl;
                // std::cout << " value const double " << (double)(v * 255) << std::endl;

                return (unsigned char)(v * 255);
            }
        };

        typedef ColorValueReference Reference;

        // Il s'agit d'un simple accès en lecture à la valeur de la couleur arg.
        // Un simple appel à arg.getHSV suffira.
        static Value access(const Argument &arg)
        {
            int h;
            float s, v;
            arg.getHSV(h, s, v);
            // std::cout << " value access " << v << std::endl;

            return (unsigned char)v * 255;
        }

        // Il suffit de créer et retourner un objet de type ColorValueReference référençant arg.
        static Reference access(Argument &arg)
        {
            ColorValueReference t = arg;
            return t;
        }
    };

    void setHSV(int t, float s, float v)
    {

        // auto c = v * s;
        // auto hp = h / 60;
        // auto x = c * (1 - (abs(hp % 2 - 1)));
        // Color color;
        // if (0 <= hp <= 1)
        // {
        //     color = Color(c, x, 0);
        // }
        // else if (1 < hp <= 2)
        // {
        //     color = Color(x, c, 0);
        // }
        // else if (2 < hp <= 3)
        // {
        //     color = Color(0, c, x);
        // }
        // else if (3 < hp <= 4)
        // {
        //     color = Color(0, x, c);
        // }
        // else if (4 < hp <= 5)
        // {
        //     color = Color(x, 0, c);
        // }
        // else if (5 < hp <= 6)
        // {
        //     color = Color(c, 0, x);
        // }
        // auto m = v - c;
        // red = (color.red + m);
        // green = (color.green + m);
        // blue = (color.blue + m);

        int ti = (int)floor(t / 60) % 6;
        float f = t / 60.0 - ti;
        float l = v * (1.0 - s);
        float m = v * (1.0 - f * s);
        float n = v * (1.0 - (1.0 - f) * s);
        switch (ti)
        {
        case 0:
            // std::cout << " case0 init: " << (int)red;
            red = (unsigned char)v;
            // std::cout << "  case0 fini: " << (int)red << std::endl;
            green = (unsigned char)n;
            blue = (unsigned char)l;
            break;
        case 1:
            // std::cout << " case1" << std::endl;

            red = (unsigned char)m;
            green = (unsigned char)v;
            blue = (unsigned char)l;
            break;
        case 2:
            // std::cout << " case2" << std::endl;

            red = (unsigned char)l;
            green = (unsigned char)v;
            blue = (unsigned char)n;
            break;
        case 3:
            // std::cout << " case3" << std::endl;

            red = (unsigned char)l;
            green = (unsigned char)m;
            blue = (unsigned char)v;
            break;
        case 4:
            // std::cout << " case4" << std::endl;

            red = (unsigned char)n;
            green = (unsigned char)l;
            blue = (unsigned char)v;
            break;
        case 5:
            // std::cout << " case5" << std::endl;

            red = (unsigned char)v;
            green = (unsigned char)l;
            blue = (unsigned char)m;
            break;
        default:
            break;
        }
    }
};

#endif //_COLOR_HPP_
