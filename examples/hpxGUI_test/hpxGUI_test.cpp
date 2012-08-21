////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2012 Andrew Kemp
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

// Naive SMP version implemented with futures.

#include <hpx/hpx_init.hpp>
#include <hpx/include/actions.hpp>
#include <hpx/include/util.hpp>
#include <hpx/include/lcos.hpp>

#include <include/imgUtil/readImg.hpp>
#ifndef cimg_imagepath
#define cimg_imagepath "img/"
#include <include/external/CImg.h>
using namespace cimg_library;
#endif

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>


int hpx_main(int argc, char **argv)
{
    std::cout << "Hello world!";
    {
        using namespace cimg_library;
        // Read image filename from the command line (or set it to "img/parrot_original.ppm" if option '-i' is not provided).
        std::string imgFile = "pixelArt.bmp";//cimg_option("-i", "./logo.bmp","Input image");

        // Load an image, transform it to a color image (if necessary) and blur it with the standard deviation sigma.
        CImg<unsigned char> image = readImgFile(imgFile, argc, argv);

        // Display
        CImgDisplay
        main_disp(image,"Color image",0);

        // Enter event loop. This loop ends when one of the two display window is closed or when the keys 'ESC' or 'Q' are pressed.
        while (!main_disp.is_closed() &&
               !main_disp.is_keyESC() && !main_disp.is_keyQ()) {

          // Handle display window resizing (if any)
          if (main_disp.is_resized())
              main_disp.resize().display(image);
        }
    }
    return hpx::finalize(); // Handles HPX shutdown
}
int main(int argc, char **argv)
{
    int code = hpx::init(argc, argv);
    std::cout << std::endl;
    //check if we're using Windows
    #if defined(__WIN32__) || defined(_WIN32) || defined(WIN32) || defined(__WINDOWS__) || defined(__TOS_WIN__)
    //if so, pause because the console usually closes at the end of execution
    system("Pause");
    #endif
    return code;
}
