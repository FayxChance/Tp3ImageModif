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
    if (argc < 2)
    {
        std::cerr << "Usage: save-green-channel <input.ppm>" << std::endl;
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

    std::string inputArg = argv[1];
    std::string delimiter = ".";
    std::string token = inputArg.substr(0, inputArg.find(delimiter)); // Token = nomfichier sans .pgm

    std::string nameGreen = token + ("_green.pgm");
    std::string nameRed = token + ("_red.pgm");
    std::string nameBlue = token + ("_blue.pgm");

    typedef Image2D<unsigned char> GrayLevelImage2D;
    typedef Image2DWriter<unsigned char> GrayLevelImage2DWriter;
    typedef GrayLevelImage2D::Iterator GrayLevelIterator;
    GrayLevelImage2D imgGreen(img.w(), img.h());
    GrayLevelImage2D imgBlue(img.w(), img.h());
    GrayLevelImage2D imgRed(img.w(), img.h());

    typedef ColorImage2D::GenericConstIterator<ColorGreenAccessor> ColorGreenConstIterator;
    ColorGreenConstIterator itGreen = img.begin<ColorGreenAccessor>();
    for (GrayLevelIterator it = imgGreen.begin(), itE = imgGreen.end();
         it != itE; ++it)
    {
        *it = *itGreen;
        ++itGreen;
    }

    std::ofstream outputGreen(nameGreen); // récupère le 2eme argument.
    bool ok2 = GrayLevelImage2DWriter::write(imgGreen, outputGreen, false);
    if (!ok2)
    {
        std::cerr << "Error writing outputGreen file." << std::endl;
        return 1;
    }
    outputGreen.close();

    std::ofstream outputBlue(nameBlue); // récupère le 2eme argument.
    typedef ColorImage2D::GenericConstIterator<ColorBlueAccessor> ColorBlueConstIterator;
    ColorBlueConstIterator itBlue = img.begin<ColorBlueAccessor>();
    for (GrayLevelIterator it = imgBlue.begin(), itE = imgBlue.end();
         it != itE; ++it)
    {
        *it = *itBlue;
        ++itBlue;
    }
    bool ok3 = GrayLevelImage2DWriter::write(imgBlue, outputBlue, false);
    if (!ok3)
    {
        std::cerr << "Error writing outputBlue file." << std::endl;
        return 1;
    }
    outputBlue.close();

    typedef ColorImage2D::GenericConstIterator<ColorRedAccessor> ColorRedConstIterator;
    ColorRedConstIterator itRed = img.begin<ColorRedAccessor>();
    for (GrayLevelIterator it = imgRed.begin(), itE = imgRed.end();
         it != itE; ++it)
    {
        *it = *itRed;
        ++itRed;
    }
    std::ofstream outputRed(nameRed); // récupère le 2eme argument.
    ok2 = GrayLevelImage2DWriter::write(imgRed, outputRed, false);
    if (!ok2)
    {
        std::cerr << "Error writing outputRed file." << std::endl;
        return 1;
    }
    outputRed.close();

    return 0;
}
