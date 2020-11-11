// #include "GrayLevelImage2D.hpp"
// #include <fstream> // flux sur les fichiers
// #include <iostream>
// #include <sstream> // flux sur les chaînes de caractères
// #include <string>  // chaînes de caractères

// using namespace std;

// int main(int argc, char **argv) {
//   /*{
//     //! [tgli2d-sec3]
//     GrayLevelImage2D img( 8, 8, 5 ); // imagette 8x8 remplie de 5
//     for ( int y = 0; y < img.h(); ++y )
//       for ( int x = 0; x < img.w(); ++x )
//               std::cout << " " << (int) img.at( x, y ); // la conversion
//               permet
//   de voir les caractères sous forme d'entiers. std::cout << std::endl;
//     //! [tgli2d-sec3]
//   }*/
//   /*{
//     GrayLevelImage2D img( 8, 8, 5 ); // imagette 8x8 remplie de 5
//     //! [tgli2d-sec4]
//     for ( GrayLevelImage2D::Iterator it = img.begin(), itE = img.end(); it !=
//   itE; ++it ) std::cout << " " << (int) *it; // la conversion permet de voir
//   les caractères sous forme d'entiers.
//     //! [tgli2d-sec4]
//   }*/

// typedef GrayLevelImage2D::GrayLevel GrayLevel;
// typedef GrayLevelImage2D::Iterator Iterator;
// GrayLevelImage2D img;
// std::cout << argv[1] << std::endl;
// ifstream input(argv[1]);
// try {
//   img.importPGM(input);
// } catch (char const *msg) {
//   std::cerr << "Exception: " << msg << std::endl;
// } catch (...) {
//   std::cerr << "Exception." << std::endl;
// }
// input.close();
// for (Iterator it = img.begin(), itE = img.end(); it != itE; ++it) {
//   const GrayLevel g = (1 * ((int)(*it))) % 256;
//   *it = g;
// }
// ofstream output(argv[2]);
// img.exportPGM(output, false);
// output.close();
// std::cout << std::endl;

//   return 0;
// }

#include "Image2D.hpp"
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
  if (argc < 1)
  {
    std::cerr << "Usage: testGrayLevelImage2D" << std::endl;
    return 0;
  }
  typedef unsigned char GrayLevel;
  typedef Image2D<GrayLevel> GrayLevelImage2D;
  GrayLevelImage2D img(8, 8, 5); // imagette 8x8 remplie de 5
  for (int y = 0; y < img.h(); ++y)
  {
    for (int x = 0; x < img.w(); ++x)
      std::cout << " " << (int)img.at(x, y); // la conversion permet de
                                             //     voir les
                                             // caractères sous forme
                                             //  d'entiers.
    std::cout << std::endl;
  }
  return 0;
}
