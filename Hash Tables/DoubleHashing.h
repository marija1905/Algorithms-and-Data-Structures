#ifndef _DoubleHashing_h_
#define _DoubleHashing_h_
#include "AdressFunction.h"

class DoubleHashing : public AdressFunction{
public:
	int getAdress(int k, int a, int i, unsigned int n) { return (a + i * (1 + (k % (n - 2)))) % n; }
};


#endif