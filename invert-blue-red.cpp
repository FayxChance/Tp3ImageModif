#include <iostream>
#include <fstream>
#include "Image2D.hpp"
#include "Color.hpp"
#include "Image2DWriter.hpp"
#include "Image2DReader.hpp"

int main(int argc, char const *argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage: invert-blue-red <input.ppm> <output.ppm>" << std::endl;
        return 0;
    }
    typedef Image2D<Color> ColorImage2D;
    typedef ColorImage2D::Iterator Iterator;
    typedef ColorImage2D::ConstIterator ConstIterator;
    ColorImage2D img;
    std::ifstream input(argv[1]);
    Image2DReader<Color>::read(img, input);
    input.close();
    for (auto it = img.begin(), itE = img.end(); it != itE; it++)
    {
        *it = Color(it->blue, it->green, it->red);
    }
    std::ofstream output(argv[2]);
    Image2DWriter<Color>::write(img, output, false);
    output.close();
    return 0;
}
