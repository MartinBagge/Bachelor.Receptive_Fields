#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "ReceptiveFields.h"
#include <gtest/gtest.h>

using namespace std;
/*
TEST(Re){

}
*/

__global__ void createKernel(double *kernelCenter, double *step, double *kernelWidth, double *kernel, int n){
	int i = threadIdx.x;
	if(i < n)
		*kernel = exp((-(((*kernelCenter)-(*step))*((*kernelCenter)-(*step)))/2)*(*kernelWidth));
}

int main(){
	
	cout << "Test" << endl;

	ReceptiveFields RF(60, 120, 40, 0.1, 0.4, 50000, 85);
	//Read data file
	string inputString;
	string token;
	vector<string> splitStrings;
	ifstream filein;
	filein.open("runbot_leftknee_output.log");
	//while(getline(filein,inputString)){
			//stringstream lineStream(inputString);
			//splitStrings.clear();
	std::cout << "fileread" << std::endl;
			while(getline(filein, token, ',')){
				splitStrings.push_back(token);
			}
			for(int i = 0; i < splitStrings.size(); i++){
				RF.generateTarget(atof(splitStrings[i].c_str()));
			}
			std::cout << "fileread done" << std::endl;
		//}
	int tmp = 1;
	for(int i = 0; i < 85; i++){
		RF.createStep(tmp);
		tmp++;
	}
	RF.applyDeltaRule();
	/*
	cout << "start" << endl;

	int N = 1;
	  double kernelCenter[1], step[1], kernelWidth[1], kernel[1], *d_kernelCenter, *d_step, *d_kernelWidth, *d_kernel;
	  
	  cout << "start malloc" << endl;

	  cudaMalloc(&d_kernelCenter, N*sizeof(double));
	  cudaMalloc(&d_step, N*sizeof(double));
	  cudaMalloc(&d_kernelWidth, N*sizeof(double));
	  cudaMalloc(&d_kernel, N*sizeof(double));
	  
	  cout << "end malloc" << endl;
	  
	  kernelCenter[0] = 41.9231f;
	  step[0] = 20.0f;
	  kernelWidth[0] = 0.1f;
	  kernel[0] = 0;
	  
	  cout << "start memcpy" << endl;

	  cudaMemcpy(d_kernelCenter, kernelCenter, N*sizeof(double), cudaMemcpyHostToDevice);
	  cudaMemcpy(d_step, step, N*sizeof(double), cudaMemcpyHostToDevice);
	  cudaMemcpy(d_kernelWidth, kernelWidth, N*sizeof(double), cudaMemcpyHostToDevice);
	  cudaMemcpy(d_kernel, kernel, N*sizeof(double), cudaMemcpyHostToDevice);
	  
	  cout << "end memcpy" << endl;

	  //function call
	  cout << "start call function" << endl;
	  createKernel <<<1, N>>>(d_kernelCenter, d_step, d_kernelWidth, d_kernel, N);
	  cout << "end function call" << endl;
	  
	  cout << "start memcpy" << endl;

	  cudaMemcpy(kernelCenter, d_kernelCenter, N*sizeof(double), cudaMemcpyDeviceToHost);
	  cudaMemcpy(step, d_step, N*sizeof(double), cudaMemcpyDeviceToHost);
	  cudaMemcpy(kernelWidth, d_kernelWidth, N*sizeof(double), cudaMemcpyDeviceToHost);
	  cudaMemcpy(kernel, d_kernel, N*sizeof(double), cudaMemcpyDeviceToHost);
	  
	  cout << "end memcpy" << endl;
	  
	  cout << "start free" << endl;


	  cudaFree(d_kernelCenter);
	  cudaFree(d_step);
	  cudaFree(d_kernelWidth);
	  cudaFree(d_kernel);
	  
	  cout << "end free" << endl;
	  cout << kernelCenter[0] << endl;
	  cout << step[0] << endl;
	  cout << kernelWidth[0] << endl;
	  cout << kernel[0] << endl;
	  */
	return 0;
}
