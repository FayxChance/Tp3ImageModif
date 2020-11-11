#include <cmath>
#include <iostream>
#include <fstream>
#include "Image2D.hpp"
#include "Image2DReader.hpp"
#include "Image2DWriter.hpp"
#include "Accessor.hpp"
int main(int argc, char const *argv[])
{

    if (argc < 1)
    {
        std::cerr << "Usage: egaliseur-couleur <input.ppm> " << std::endl;
        return 0;
    }

    std::string inputArg = argv[1];
    std::string delimiter = ".";
    std::string token = inputArg.substr(0, inputArg.find(delimiter)); // Token = nomfichier sans .pgm

    std::string namehisto = token + ("_histoEq.pgm");
    std::string nameEgal = token + ("_egalise.ppm");

    typedef unsigned char GrayLevel;
    typedef Image2D<unsigned char> GrayLevelImage2D;
    typedef Image2DWriter<unsigned char> GrayLevelImage2DWriter;
    typedef Image2DReader<unsigned char> GrayLevelImage2DReader;
    typedef Image2D<Color> ColorImage2D;
    typedef Image2DReader<Color> ColorImage2DReader;
    typedef ColorImage2D::Iterator ColorIterator;
    typedef Color::ColorValueAccessor ColorValueAccessor;

    //**************** RECUPERATION IMAGE COULEUR
    ColorImage2D img(0, 0);
    std::ifstream input(argv[1]); // récupère le 1er argument.
    bool ok = ColorImage2DReader::read(img, input);
    if (!ok)
    {
        std::cerr << "Error reading input file." << std::endl;
        return 1;
    }
    input.close();
    // --------------RECUPERATION IMAGE COULEUR

    //************************* Trait separateur au milieu de l'histo
    GrayLevelImage2D imgHisto(518, 256, 255);
    for (int i = 0; i < 256; i++)
    {
        imgHisto.at((0 + 255 + 4), i) = 0;
    }
    std::ofstream output(namehisto);
    bool ok2 = Image2DWriter<GrayLevel>::write(imgHisto, output, false);
    if (!ok2)
    {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    output.close();
    //-------------------------------- Trait separateur au milieu de l'histo
    //****************************** Generation histogramme
    Histogramme H;
    // fonctionne, car l'itérateur a une valeur de type unsigned char.
    H.init(img.begin<ColorValueAccessor>(), img.end<ColorValueAccessor>());
    // Egalisation
    for (auto it = img.begin<ColorValueAccessor>(), itE = img.end<ColorValueAccessor>(); it < itE; it++)
    {
        // std::cout << "*it --> " << H.egalisation((float)*it) << std::endl;
        // std::cout << "*it avant --> " << ((float)*it) << std::endl;
        *it = H.egalisation(*it);
        // std::cout << "*it apres --> " << ((float)*it) << std::endl;
    }
    H.init(img.begin<ColorValueAccessor>(), img.end<ColorValueAccessor>());
    // std::cout << "taille : " << img.end() - img.begin() << std::endl;
    int maxPer = 0;
    for (int i = 0; i < 256; i++)
    {
        maxPer = maxPer < H.h1[i] ? H.h1[i] : maxPer;
    }

    for (int i = 0; i < 256; i++)
    {
        // std::cout << "I : " << i << "    H[i] : " << H.h1[i] << std::endl;
        for (int j = 0; j < (int)(H.h1[i] * 256 / (maxPer + 1)); j++)
        {
            // std::cout << "I : " << i << " J : " << j << " H[i] : " << H.h1[i] << " Nb sur 255 : " << (int)(H.h1[i] * 256) << std::endl;
            // std::cout << (img2.end<ColorValueAccessor>() - img2.begin<ColorValueAccessor>()) << std::endl;
            imgHisto.at(i, 255 - j) = 0;
        }
    }

    for (int i = 0; i < 256; i++)
    {
        // std::cout << "I : " << i << "    H[i] : " << H.h2[i] << " Nb sur 255 : " << (int)(H.h2[i] * 256) << std::endl;

        for (int j = 0; j < (int)(H.h2[i] * 256 / 100); j++)
        {
            // std::cout << "I : " << i << " J : " << j << "    H[i] : " << H.h2[i] << " Nb sur 255 : " << (int)(H.h2[i] * 256) << std::endl;

            imgHisto.at(i + 255 + 4 * 2, 255 - j) = 0;
        }
    }

    std::ofstream output2(namehisto);

    ok2 = Image2DWriter<GrayLevel>::write(imgHisto, output2, false);
    if (!ok2)
    {
        std::cerr << "Error writing output2 file." << std::endl;
        return 1;
    }
    output2.close();
    //****************************** Generation histogramme
    std::ofstream output3(nameEgal);

    bool ok3 = Image2DWriter<Color>::write(img, output3, false);
    if (!ok3)
    {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    output3.close();
    return 0;
}
