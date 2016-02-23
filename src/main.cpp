#include <iostream>
using namespace std;
using namespace ReceptiveFields;

int main(){
	cout << "Test" << endl;

	ReceptiveFields RF = new ReceptiveFields(45, 180, 20, 0.025, 0.2, 100, 1000);
	cout << RF.toString();
	cout << endl;
	return 0;
}
