#ifndef CSVM_CLASSIFIER_H
#define CSVM_CLASSIFIER_H

#include <vector>
#include <cstdlib>
#include <ctime>

#include "csvm_settings.h"
#include "csvm_dataset.h"
#include "csvm_codebook.h"
#include "csvm_image_scanner.h"
//#include "csvm_cluster_analyser.h"
#include "csvm_feature.h"
#include "csvm_feature_extractor.h"
#include "csvm_svm.h"
#include "csvm_linear_network.h"
#include "csvm_deep_codebook.h"
#include "csvm_conv_svm.h"


using namespace std;
namespace csvm{
   
   class CSVMClassifier{
      CSVMSettings settings;
      Codebook codebook;
      DeepCodebook* deepCodebook;
      ImageScanner imageScanner;
      //ClusterAnalyser analyser;
      FeatureExtractor featExtr;
      vector< SVM > svms;
      LinNetwork linNetwork;
      ConvSVM convSVM;
      
      vector < vector< vector<double> > > classicTrainActivations;
      
            
      void constructDeepCodebook();
      
      void trainLinearNetwork();
      unsigned int lnClassify(Image* image);

      
      void trainConvSVMs();
      unsigned int classifyConvSVM(Image* im);
      
      void trainClassicSVMs();
      unsigned int classifyClassicSVMs(Image* im, bool printResults);
      
   public:
      //public vars
      CSVMDataset dataset;
      
      CSVMClassifier();
      ~CSVMClassifier();
      void setSettings(string settingsFile);
      void constructCodebook();
      void exportCodebook(string filename);
      void importCodebook(string filename);
      
      void initSVMs();
      //unsigned int classify(Image* image);
      unsigned int getNoClasses();
      //CSVMClassifier();
      
      bool useClassicSVM();

      void train();
      unsigned int classify(Image* im);
   };
   
}
#endif
