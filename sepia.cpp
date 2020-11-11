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
        std::cerr << "Usage: sepia <input.ppm> <output.ppm>" << std::endl;
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
        *it = Color((it->red * .393 + it->green * .769 + it->blue * .189 > 255 ? 255 : it->red * .393 + it->green * .769 + it->blue * .189),
                    (it->red * .349 + it->green * .686 + it->blue * .168 > 255 ? 255 : it->red * .349 + it->green * .686 + it->blue * .168),
                    (it->red * .272 + it->green * .534 + it->blue * .131 > 255 ? 255 : it->red * .272 + it->green * .534 + it->blue * .131));
    }
    std::ofstream output(argv[2]);
    Image2DWriter<Color>::write(img, output, false);
    output.close();
    return 0;
}
