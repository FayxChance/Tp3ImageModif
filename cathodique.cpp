// save-green-channel.cpp
#include <cmath>
#include <iostream>
#include <fstream>
#include "Image2D.hpp"
#include "Image2DReader.hpp"
#include "Image2DWriter.hpp"
#include "Accessor.hpp"

int main(int argc, char **argv)
{
    typedef Image2D<Color> ColorImage2D;
    typedef Image2DReader<Color> ColorImage2DReader;
    typedef ColorImage2D::Iterator ColorIterator;
    if (argc < 3)
    {
        std::cerr << "Usage: cathodique <input.ppm> <output.ppm>" << std::endl;
        return 0;
    }
    ColorImage2D img;
    std::ifstream input(argv[1]); // récupère le 1er argument.
    bool ok = ColorImage2DReader::read(img, input);
    if (!ok)
    {
        std::cerr << "Error reading input file." << std::endl;
        return 1;
    }
    input.close();

    typedef ColorImage2D::GenericIterator<ColorRedAccessor> ColorRedIterator;
    typedef ColorImage2D::GenericIterator<ColorGreenAccessor> ColorGreenIterator;
    typedef ColorImage2D::GenericIterator<ColorBlueAccessor> ColorBlueIterator;
    ColorRedIterator itRed = img.begin<ColorRedAccessor>();
    ColorGreenIterator itGreen = img.begin<ColorGreenAccessor>();
    ColorBlueIterator itBlue = img.begin<ColorBlueAccessor>();
    // On écrit la composante verte dans l'image en niveaux de gris.
    int x = 0;
    for (ColorIterator it = img.begin(), itE = img.end();
         it != itE; ++it)
    {
        switch (x % 3)
        {
        case 0:
            *itGreen = *itBlue = 0;
            break;
        case 1:
            *itRed = *itBlue = 0;
            break;
        case 2:
            *itRed = *itGreen = 0;
            break;
        }
        ++itRed;
        ++itGreen;
        ++itBlue;
        x = (x + 1) % img.w();
    }
    std::ofstream output(argv[2]); // récupère le 2eme argument.
    bool ok2 = Image2DWriter<Color>::write(img, output, false);
    if (!ok2)
    {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    output.close();

    return 0;
}
