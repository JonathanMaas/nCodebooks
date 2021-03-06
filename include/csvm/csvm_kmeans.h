#ifndef CSVM_KMEANS_H
#define CSVM_KMEANS_H

/*  A class implementing KMeans.
 * 
 * 
 * 
 * */

#include <limits>
#include <vector>
#include <iostream>
#include <fstream>
//#include <iomanip>
#include "csvm_feature.h"
#include "csvm_centroid.h"

#include <cstdlib>
using namespace std;

namespace csvm{
  
   struct KMeans_settings{
      int nClusters;
      double alpha;
      unsigned int nIter;
      bool normalOut;
      bool liveROut;
   };
  
 

   class KMeans{
      KMeans_settings settings;
      vector<Centroid> initCentroids(vector<Feature> collection, unsigned int nClusters);
      
   public:
      bool debugOut, normalOut;
      
      void setSettings(KMeans_settings s);
      vector<Centroid> cluster(vector<Feature>& collection, unsigned int nClusters);
   };
}


#endif
