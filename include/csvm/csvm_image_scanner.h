
#ifndef CSVM_IMAGE_SCANNER_H
#define CSVM_IMAGE_SCANNER_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "csvm_image.h"
#include "csvm_patch.h"

//TODO: Add zero padding while scanning.

using namespace std;

namespace csvm{

   struct ImageScannerSettings{
      unsigned int stride;
      unsigned int patchWidth;
      unsigned int patchHeight;
      unsigned int nRandomPatches;
      bool useDifferentCodebooksPerClass;
   };


   class ImageScanner{
      
      
   public:
      ImageScannerSettings settings;

      ImageScanner();
      void setSettings(ImageScannerSettings set);
      vector<Patch> scanImage(Image* image);
      Patch getRandomPatch(Image* image);
      Patch getPatchAt(Image* image, unsigned int x, unsigned int y);
   };

}

#endif
