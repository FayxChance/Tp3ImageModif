#include <iostream>
#include <fstream>
#include "Image2D.hpp"
#include "Color.hpp"
#include "Image2DWriter.hpp"
#include "Image2DReader.hpp"
int main(int argc, char const *argv[])
{
    if (argc < 1)
    {
        std::cerr << "Usage: testColorImage2DBash" << std::endl;
        return 0;
    }
    typedef Image2D<Color> ColorImage2D;
    typedef ColorImage2D::Iterator Iterator;
    typedef ColorImage2D::ConstIterator ConstIterator;
    ColorImage2D img(3, 3, Color(255, 0, 255));

    Iterator it = img.begin();
    for (int y = 0; y < 3; ++y)
    {

        for (int x = 0; x < 3; ++x)
        {
            std::cout << (int)img.at(x, y).red << " " << (int)img.at(x, y).green << " " << (int)img.at(x, y).blue << "| ";
        }
        std::cout << std::endl;
    }
    return 0;
}
