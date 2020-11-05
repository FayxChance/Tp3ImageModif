#ifndef _COLOR_HPP_
#define _COLOR_HPP_

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
                arg.setHSV(h, s, val);
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
                return h;
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
            return h;
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
        auto ti = (t / 60) % 6;
        auto f = t / 60 - ti;
        auto l = v * (1 - s);
        auto m = v * (1 - f * s);
        auto n = v * (1 - (1 - f) * s);
        switch (ti)
        {
        case 0:
            red = (unsigned char)v;
            green = (unsigned char)n;
            blue = (unsigned char)l;
            break;
        case 1:
            red = (unsigned char)m;
            green = (unsigned char)v;
            blue = (unsigned char)l;
            break;
        case 2:
            red = (unsigned char)l;
            green = (unsigned char)v;
            blue = (unsigned char)n;
            break;
        case 3:
            red = (unsigned char)l;
            green = (unsigned char)m;
            blue = (unsigned char)v;
            break;
        case 4:
            red = (unsigned char)n;
            green = (unsigned char)l;
            blue = (unsigned char)v;
            break;
        case 5:
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
