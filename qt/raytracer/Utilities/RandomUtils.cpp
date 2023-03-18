#include <QRandomGenerator>
#include "RandomUtils.h"
#include <QDebug>

QRandomGenerator gen;

void set_rand_seed( int seed_val ) { return gen.seed( seed_val ); }

int rand_int( void ) { return gen.bounded( INT_MAX ); }
int rand_int( int high ) { return gen.bounded( high ); }
int rand_int( int low, int high ) {
  if ( low == high ) {
    //        qDebug() << "WARNING: low == high in rand_int()";
    return low;
  }
  //    qDebug() << "randomInt(" << low << ", " << high << ")";
  return gen.bounded( low, high );
}

float rand_float( void ) { return (float) rand_double(); }
float rand_float( float high ) { return (float) rand_double( high ); }
float rand_float( float low, float high ) {
  //    qDebug() << "\t\trandomFloat(" << low << ", " << high << ")";
  return (float) rand_double( low, high );
}

double rand_double( void ) { return gen.generate(); }
double rand_double( double high ) { return gen.bounded( high ); }
double rand_double( double low, double high ) {
  //    qDebug() << "\t\t\t\trandomDouble(" << low << ", " << high << ")";
  return low + rand_double( high - low );
}
