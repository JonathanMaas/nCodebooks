#ifndef PARAM
#define PARAM

using namespace std;

#define NR_FEATURES 1296
//nr features is feature dims
typedef struct data_struct DATA;
struct data_struct {
int tot_data;
int class1;
double class2;
double input[NR_FEATURES];
};

#endif // PARAM
