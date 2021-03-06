#include <csvm/csvm_cifar10_parser.h>

/* This class contains functionality to read the CIFAr-10 binary files, parse them to the image class, scale images,
 * and make them available through the Dataset class.
 * 
 * 
 * 
 * 
 */

using namespace std;
using namespace csvm;

	//scale images using bicubic interpolation.
   void CIFAR10::scaleData(unsigned int width, unsigned int height){
      vector<Image> newImages;
      unsigned int nImages = images.size();
      
      for(size_t imIdx = 0; imIdx != nImages; ++imIdx){
         newImages.push_back(interpolator.interpolate_bicubic(images[imIdx], width, height));
         newImages[imIdx].setLabelId(images[imIdx].getLabelId());
         newImages[imIdx].setLabel(images[imIdx].getLabel());
      }
      images = newImages;
   }

   Image CIFAR10::bytesToImage(unsigned char* c){
      //cout << "byteToIm\n";
      
      Image im(32,32,CSVM_IMAGE_UCHAR_RGB);
      int label = c[0];
      
      int byteOffset = 1;
      for(int ch = 0; ch < 3 ;ch++){
         for(int y = 0; y < 32; y++){
            for(int x = 0; x < 32; x++){
               
               im.setPixel(x,y,ch,c[byteOffset++]);
            }
         }
      }
      
      im.setLabel(labels[label]);
      im.setLabelId(label);
      return im;
      
   }
   
   void CIFAR10::readLabels(string dir){
      ifstream file(dir.c_str(),ios::in);
      string label;
      if(!file.is_open()){
         cout << "csvm::CIFAR10::loadLabels(" << dir << "): Warning! Could not open file!\n";
         return;
      }
      while(getline(file, label)){
         
         if(!(label == "\n"))
            labels.push_back(label);
      }
      
      file.close();
   }
   
   string CIFAR10::getLabel(int labelId){
      return labels[labelId];
   }

   void CIFAR10::loadImages(string dir){
      ifstream file(dir.c_str(),ios::in|ios::binary|ios::ate);
      char* block;
      
      if(!file.is_open()){
         cout << "csvm::CIFAR10::loadImages(" << dir << "): Warning! Could not open file!\n";
         return;
      }
      
      int size = file.tellg();
      block = new char[size];
      file.seekg(0,ios::beg);
      file.read(block,size);
      file.close();
      
      //batch is stored in block.
      int prevSize = images.size();
      
      images.resize(prevSize+N_IMAGES_PER_BATCH);
      
      for(int i = 0;i < N_IMAGES_PER_BATCH;i++){  
         
         images[i+prevSize] = bytesToImage((unsigned char*)&block[i*(IMAGE_SIZE+1)]);
      }
      
      delete[] block;
      
   }
   
   Image CIFAR10::getImage(int index){
      /*if(index < 0 || index >= (int)images.size()){
         cout << "csvm::CIFAR10::getImage(int index == " << index << ") out of bounds! Exitting..\n";
         exit(-1);
      }*/
      return images[index];
   }
   
   Image* CIFAR10::getImagePtr(int index){
      if(index < 0 || index >= (int)images.size()){
         cout << "csvm::CIFAR10::getImage(int index == " << index << ") out of bounds! Exitting..\n";
         exit(-1);
      }
      return &images[index];  
   }
   
   int CIFAR10::getSize(){
      return images.size();
   }