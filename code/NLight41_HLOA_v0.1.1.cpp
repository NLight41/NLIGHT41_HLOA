#include <iostream>
#include <cmath>
#include <chrono> 
#include <vector>
#include <Eigen/Dense>
#include <cppad/cppad.hpp>
#include <omp.h>
// HLOA v0.1.0  
// 03.24.2025 by NLight41 
using std::cin;
using std::cout;
using std::endl;
using Eigen::VectorXd;
// 定義參數型別  
using Parameters = VectorXd;
constexpr int DIM = 2; // 參數維度  



// 目標函數 (非凸)  
CppAD::AD<double> simulationFunction(const Parameters &p) {
	return p(0) * CppAD::sin(p(1)) + 10;
}



// 自動微分計算梯度 
Parameters computeGradient(const Parameters &p) {
	CppAD::ADFun<double> f;
	std::vector<CppAD::AD<double>> X(DIM);
	std::vector<CppAD::AD<double>> Y(1);
	
	for (int i = 0; i < DIM; ++i) X[i] = p(i);
	Y[0] = simulationFunction(p);
	f.Dependent(X, Y);
	
	std::vector<double> x(DIM);
	for (int i = 0; i < DIM; ++i) x[i] = p(i);
	
	std::vector<double> grad = f.Jacobian(x);
	Parameters gradient(DIM);
	for (int i = 0; i < DIM; ++i) gradient(i) = grad[i];
	
	return gradient;
}



// ==== HLOA core ====
Parameters  adaptiveHoloLoopOptimizer(Parameters initParams, double learningRate, double momentumFactor, double holoFactor, double threshold, int maxIterations) {
	Parameters p = initParams;
	Parameters grad = Parameters::Zero(DIM);
	Parameters momentum = Parameters::Zero(DIM);	// 更新為 Eigen::VectorXd 函數  
	
	double prevError = CppAD::Value(simulationFunction(p));
	double currError = prevError;
	int iteration = 0;
	
	
	while (currError > threshold && iteration < maxIterations) {
		// 並行計算梯度 與 動量更新 
		
		#pragma omp parallel sections
		{
			#pragma omp section
			grad = computeGradient(p);
			
			#pragma omp section
			for (int i = 0; i < DIM; ++i){
				momentum(i) = momentumFactor * momentum(i) + (1 - momentumFactor) * grad(i);
				
			}
		}
		
		// 向量化參數更新  
		double errorDiff = currError - prevError;
		double holoAdjustment = holoFactor * errorDiff;
		
		#pragma omp parallel for
		for (int i = 0; i < DIM; ++i){
			p(i) -= learningRate * (momentum(i) + holoAdjustment);
			
		}
	
		prevError = currError;
		currError = CppAD::Value(simulationFunction(p));
		iteration++;
		
		cout << "Iteration: " << iteration
			 << ", Error: " << currError 
			 << ", param: " << p.transpose() << endl; 
				
	}
	
	return p;	
}



int main() {
	// 初始參數設定 
	Parameters initialParams (DIM);
	initialParams << 50.0, 1.0;
	
	double learningRate = 0.01;
	double momentumFactor = 0.9;	// 通常預設 momentum 參數為 0.9，經驗法則顯示 0.9 在加速收斂與保持穩定性之間有著良好的平衡點 
	double holoFactor = 0.05;		// 根據誤差變化調整步長 
	double threshold = 1e-3;		// 收斂判定閥值 
	int maxIterations = 10000;
	
	// 計時測試運行時間 
	auto start = std::chrono::high_resolution_clock::now();
	Parameters optimized = adaptiveHoloLoopOptimizer(initialParams, learningRate, momentumFactor, holoFactor, threshold, maxIterations);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = end - start;
	
	// 輸出結果 
	cout << "\nOptimized Parameters:" << optimized.transpose() << endl;
	cout << "Time elapsed: " << elapsed.count() << " seconds." << endl;
	
	return 0;
		
}



 
