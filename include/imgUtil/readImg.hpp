#ifndef std::string
    #include <string>
#endif


#ifndef cimg_imagepath
#define cimg_imagepath "img/"
#include <include/external/CImg.h>
using namespace cimg_library;
#endif
CImg<unsigned char> readImgFile(const std::string imgFile, int argc, char **argv)
{
   using namespace std;
   FILE * pFile;
   char buffer [1000];

   string fileName = __FILE__;
   std::string replaceName = "readImg.hpp";
   fileName.replace(fileName.size() - replaceName.size(), replaceName.size(), cimg_imagepath + imgFile);

   pFile = fopen ( fileName.c_str(), "r");
   
   string src;


   if (pFile == NULL)
   {
       fileName = "." + imgFile;
       pFile = fopen ( fileName.c_str(), "r");
   }
   string errorMessage = "Error opening file at path: " + fileName;

   if (pFile == NULL)
   {
       perror (errorMessage.c_str());
        //check if we're using Windows
       #if defined(__WIN32__) || defined(_WIN32) || defined(WIN32) || defined(__WINDOWS__) || defined(__TOS_WIN__)
           //if so, pause because the console usually closes at the end of execution
           system("Pause");
       #endif
       exit(1);
   }
   const char* fileO = cimg_option("-i", fileName.c_str(),"Input image");
   CImg<unsigned char> image = CImg<>(fileO);
   return image;
}
