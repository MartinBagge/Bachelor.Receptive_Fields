#include <iostream>
#include "ReceptiveFields.h"
using namespace std;

int main(){
	cout << "Test" << endl;

	ReceptiveFields* RF = new ReceptiveFields(45, 180, 20, 0.025, 0.2, 100, 1000);
	RF->toString();
	cout << "lala";
	return 0;
}
