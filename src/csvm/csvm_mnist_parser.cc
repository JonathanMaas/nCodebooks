#include <csvm/csvm_mnist_parser.h>
#include <stdint.h>

using namespace std;
using namespace csvm;

   union MagicInt{
      uint32_t intVal;
      char bytes[4];      
   };
   
   void swapByte(char* byte){
      char newByte = 0;
      char bit;
      for(size_t bIdx = 0; bIdx < 8; ++ bIdx){
         bit = ((1 << bIdx) & *byte);
         newByte |= bit << (7 - bIdx);
      }
      *byte = newByte;
   }
   
   void swapInt(uint32_t* val){
      MagicInt pre;
      pre.intVal = *val;
      char buffer;
      
      for(size_t bIdx = 0; bIdx < 2; ++bIdx){
         buffer = pre.bytes[bIdx];
         pre.bytes[bIdx] = pre.bytes[3 - bIdx];
         pre.bytes[3 - bIdx] = buffer;
         
         
      }
      *val = pre.intVal;
   }
   
   MNISTParser::MNISTParser(){
      trainImages = NULL;
      trainLabels = NULL;
      testImages = NULL;
      testLabels = NULL;
      
      trainImagesFile = "train-images.idx3-ubyte";
      trainLabelFile = "train-labels.idx1-ubyte";
      testImagesFile = "t10k-images.idx3-ubyte";
      testLabelFile = "t10k-labels.idx1-ubyte";
   }
   
   void MNISTParser::readTrainImages(string dir){
      //basic_ifstream<unsigned char> file((dir + trainImagesFile).c_str(),ios::in|ios::binary|ios::ate);
      ifstream file((dir + trainImagesFile).c_str(),ios::in|ios::binary|ios::ate);
      trainImages = new MNISTTrainSet;
      if(!file.is_open()){
         cout << "csvm::MNISTParser::readTrainImages(" << (dir + trainImagesFile) << "): Warning! Could not open file!\n";
         return;
      }
      
      int size = file.tellg();
      
      file.seekg(0,ios::beg);
      file.read(trainImages->data,size);
      
      swapInt( &(trainImages->formatted.magicNumber));
      swapInt( &(trainImages->formatted.numberOfImages));
      swapInt( &(trainImages->formatted.numberofColumns));
      swapInt( &(trainImages->formatted.numberOfRows));
      
      if(trainImages->formatted.magicNumber != 2051)
         cout << "csvm::MNISTParser::readTrainImages: Magic number mismatch! It says " << trainImages->formatted.magicNumber << " and reads " << trainImages->formatted.numberOfImages << " images\n";
      
      file.close();
   }
   
   void MNISTParser::readTrainLabels(string dir){
      ifstream file((dir + trainLabelFile).c_str(),ios::in|ios::binary|ios::ate);
      trainLabels = new MNISTTrainLabels;     
      if(!file.is_open()){
         cout << "csvm::MNISTParser::readTrainLabels(" << (dir + trainLabelFile) << "): Warning! Could not open file!\n";
         return;
      }
      
      int size = file.tellg();
            
      file.seekg(0,ios::beg);
      file.read(trainLabels->data,size);
      
      swapInt( &(trainLabels->formatted.magicNumber));
      swapInt( &(trainLabels->formatted.numberOfImages));
      
      if(trainLabels->formatted.magicNumber != 2049)
         cout << "csvm::MNISTParser::readTrainLabels: Magic number mismatch! It says " << trainLabels->formatted.magicNumber<< "\n";
      
      file.close();
   }
   
   void MNISTParser::readTestImages(string dir){
      ifstream file((dir + testImagesFile).c_str(),ios::in|ios::binary|ios::ate);
      testImages = new MNISTTestSet;    
      if(!file.is_open()){
         cout << "csvm::MNISTParser::readTestImages(" << (dir + testImagesFile) << "): Warning! Could not open file!\n";
         return;
      }
      
      int size = file.tellg();
            
      file.seekg(0,ios::beg);
      file.read(testImages->data,size);
      
      swapInt( &(testImages->formatted.magicNumber));
      swapInt( &(testImages->formatted.numberOfImages));
      swapInt( &(testImages->formatted.numberofColumns));
      swapInt( &(testImages->formatted.numberOfRows));
      
      if(testImages->formatted.magicNumber != 2051)
         cout << "csvm::MNISTParser::readTestImages: Magic number mismatch! It says " << testImages->formatted.magicNumber <<  "\n";
      
      
      file.close();
   }
   
   void MNISTParser::readTestLabels(string dir){
      ifstream file((dir + testLabelFile).c_str(),ios::in|ios::binary|ios::ate);
      testLabels = new MNISTTestLabels;
      
      if(!file.is_open()){
         cout << "csvm::MNISTParser::readTestLabels(" << (dir + testLabelFile) << "): Warning! Could not open file!\n";
         return;
      }
      
      int size = file.tellg();
            
      file.seekg(0,ios::beg);
      file.read(testLabels->data,size);
      
      swapInt( &(testLabels->formatted.magicNumber));
      swapInt( &(testLabels->formatted.numberOfImages));
      
      if(testLabels->formatted.magicNumber != 2049)
         cout << "csvm::MNISTParser::readTestLabels: Magic number mismatch! It says " << testLabels->formatted.magicNumber << "\n";
      
      file.close();
   }
   
   void MNISTParser::convertTrainSetToImages(){
      
      if(trainImages == NULL && trainLabels != NULL){
         size_t nImages = trainImages->formatted.numberOfImages;
         
         size_t width = trainImages->formatted.numberOfRows;
         size_t height = trainImages->formatted.numberofColumns;
         
         for(size_t imIdx = 0; imIdx < nImages; ++imIdx){
            Image im(width, height, CSVM_IMAGE_UCHAR_GREY);
            im.setImageData(vector<unsigned char>(trainImages->formatted.images[imIdx].pixels, trainImages->formatted.images[imIdx].pixels + sizeof(trainImages->formatted.images[imIdx].pixels) / sizeof(trainImages->formatted.images[imIdx].pixels[0])));
            char label = trainLabels->formatted.labels[imIdx];
            im.setLabel(string(&label));
            im.setLabelId(trainLabels->formatted.labels[imIdx]);
            images.push_back(im);
            labels.push_back(string(&label));
         }
         
      }
      
   }
   
   
   void MNISTParser::convertTestSetToImages(){
      
      if(trainImages == NULL && trainLabels != NULL){
         size_t nImages = testImages->formatted.numberOfImages;
         
         size_t width = testImages->formatted.numberOfRows;
         size_t height = testImages->formatted.numberofColumns;
         
         for(size_t imIdx = 0; imIdx < nImages; ++imIdx){
            Image im(width, height, CSVM_IMAGE_UCHAR_GREY);
            im.setImageData(vector<unsigned char>(testImages->formatted.images[imIdx].pixels, testImages->formatted.images[imIdx].pixels + sizeof(testImages->formatted.images[imIdx].pixels) / sizeof(testImages->formatted.images[imIdx].pixels[0])));
            char label = testLabels->formatted.labels[imIdx];
            im.setLabel(string(&label));
            im.setLabelId(testLabels->formatted.labels[imIdx]);
            images.push_back(im);
            labels.push_back(string(&label));
         }
         
      }
      
   }
   
   void MNISTParser::deleteUnformattedData(){
      delete trainImages;
      delete trainLabels;
      delete testImages;
      delete testLabels;
   }
   
