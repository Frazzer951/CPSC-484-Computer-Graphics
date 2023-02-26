#ifndef __RANDOM_UTILS__
#define __RANDOM_UTILS__


// replaces rand_int(), rand_float(), and rand_double()
//   with QRandomGenerator

int rand_int(void);
int rand_int(int low, int high);


float rand_float(void);
float rand_float(float high);
float rand_float(float low, float high);


double rand_double(void);
double rand_double(double high);
double rand_double(double low, double high);


#endif  // __RANDOM_UTILS__
