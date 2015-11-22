#ifndef CSVM_MNIST_PARSER_H
#define CSVM_MNIST_PARSER_H

#include <stdint.h>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

namespace csvm{

   struct MNISTImage{
      unsigned char pixels[28 * 28];
   };

   union MNISTTrainSet{
      struct {
         uint32_t magicNumber;
         uint32_t numberOfImages;
         uint32_t numberOfRows;
         uint32_t numberofColumns;
         MNISTImage images[60000];  //so total of (4 * 4) + 60000*28*28 = 
      } formatted;
      unsigned char data[(4 * 4) + 60000*28*28];
      
   };

   union MNISTTrainLabels{
      struct{
         uint32_t magicNumber;
         uint32_t numberOfImages;
         unsigned char labels[60000];
      } formatted;
      unsigned char data[2*4 + 60000];
   };

   union MNISTTestSet{
      struct{
         uint32_t magicNumber;
         uint32_t numberOfImages;
         uint32_t numberOfRows;
         uint32_t numberofColumns;
         MNISTImage images[10000];   
      } formatted;
      unsigned char data[(4 * 4) + 10000*28*28];
   };

   union MNISTTestLabels{
      struct{
         uint32_t magicNumber;
         uint32_t numberOfImages;
         unsigned char labels[10000];
      } formatted;
      unsigned char data[10000 + 2*4];
   };




   class MNISTParser{
      
      MNISTTrainSet trainImages;
      MNISTTrainLabels trainLabels;
      
      MNISTTestSet testImages;
      MNISTTestLabels testLabels;
      
   public:
      void readTrainImages(string filename);
      void readTrainLabels(string filename);
      void readTestImages(string filename);
      void readTestLabels(string filename);
   };
}


#endif