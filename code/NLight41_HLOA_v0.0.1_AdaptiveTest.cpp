#include <iostream>
#include <cmath>
#include <chrono> 
#include <vector>
#include <functional>
// HLOA v0.0.1_AdaptiveTest  
// 03.21.2025 by NLight41  
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::function;
using std::fabs;
 

// ==== 參數模組 ==== 
struct Parameters {
	double param1;
	double param2;  	
};

// 支援不同的測試函數 (預設為 sin 函數) 
double simulationFunction(const Parameters &p, const function<double(const Parameters&)> &func) {
	return func(p);
}

// 提供 測試函數 (凸 / 非凸)
double convexFunction(const Parameters &p) {
	return fabs(p.param1 * p.param1 + p.param2 * p.param2 - 100);
}
double nonConvexFunction(const Parameters &p) {
	return fabs(p.param1 * sin(p.param2) + 10 - 100);
}

// 有限差分法計算梯度 (ver 2.) 
void computeGradient(const Parameters &p, Parameters &grad, const function<double(const Parameters&)> &func, double delta = 1e-5){
	Parameters p_temp = p;
	double f0 = simulationFunction(p, func);
	
	p_temp.param1 += delta;
	double f1 = simulationFunction(p_temp, func);
	grad.param1 = (f1 - f0) / delta;
	p_temp.param1 = p.param1;	// 重置 
	
	
	p_temp.param2 += delta;
	double f2 = simulationFunction(p_temp, func);
	grad.param2 = (f2 - f0) / delta;
	
}


// ==== HLOA core ====
Parameters  adaptiveHoloLoopOptimizer(Parameters initParams, double learningRate, double momentumFactor, double holoFactor, double threshold, int maxIterations, const function<double(const Parameters&)> &func) {
	Parameters p = initParams;
	Parameters grad{0.0, 0.0};
	Parameters momentum{0.0, 0.0};	// 保存上一輪的梯度動量值  
	
	double prevError = simulationFunction(p, func);
	double currError = prevError;
	int iteration = 0;
	
	
	while (currError > threshold && iteration < maxIterations) {
		
		computeGradient(p, grad, func);
		
		// 動量更新 : 將當前的梯度 與 上一輪測試的梯度 按比例融合 
		momentum.param1 = momentumFactor * momentum.param1 + (1 - momentumFactor) * grad.param1;
		momentum.param2 = momentumFactor * momentum.param2 + (1 - momentumFactor) * grad.param2;
		
		// 全像回饋調整 : 根據梯度變化量調整梯度更新速度 更新fabs 
		double errorDiff = currError - prevError;
		double holoAdjustment = holoFactor * fabs(errorDiff);
		
		// 更新參數 : 將 動量 與 全像回饋變因 結合後，進行梯度下降更新 
		p.param1 -= learningRate * (momentum.param1 + holoAdjustment);
		p.param2 -= learningRate * (momentum.param2 + holoAdjustment);
		
		// 更新誤差值 及 迭代次數 
		prevError = currError;
		currError = simulationFunction(p, func);
		iteration++;
		
		// 輸出當前迭代狀況，用於 追蹤版本 及 方便調整  
		cout << "Iteration: " << iteration
			 << ", Error: " << currError 
			 << ", param1: " << p.param1
			 << ", param2: " << p.param2 << endl; 
				
	}
	
	return p;	
}



// ==== 參數輸入系統 ==== 
void inputParameters(Parameters &initParams, double &learningRate, double &momentumFactor, double &holoFactor, double &threshold, int &maxIterations) {
	cout << "設定初始參數 (param1 param2): " ;
	cin >> initParams.param1 >> initParams.param2;
	cout << "設定學習率: " ;
	cin >> learningRate;
	cout << "設定動量變數: " ;
	cin >> momentumFactor;
	cout << "設定全像回饋變數: " ;
	cin >> holoFactor;
	cout << "設定誤差閥值: " ;
	cin >> threshold;
	cout << "設定最大迭代次數: " ; 
	cin >> maxIterations;
		
}

 
int main() {
	// 輸入參數 
	Parameters initialParams;
	double learningRate, momentumFactor, holoFactor, threshold;
	int maxIterations;
	inputParameters(initialParams, learningRate, momentumFactor, holoFactor, threshold, maxIterations);
	 
	int choice;
	function<double(const Parameters&)> selectedFunction;
	cout << "選擇目標函數: (1) 凸函數 (2) 非凸函數: ";
	cin >> choice;
	
	if (choice == 1) {
		selectedFunction = convexFunction;
		cout << "使用凸函數: f(x, y) = |x^2 + y^2 - 100|" << endl;
	} else {
		selectedFunction = nonConvexFunction;
		cout << "使用非凸函數: f(x, y) = |x * sin(y) + 10 - 100|" << endl;
	}
	
	
	// 計時 觀察性能 
	auto start = std::chrono::high_resolution_clock::now();
	Parameters optimized = adaptiveHoloLoopOptimizer(initialParams, learningRate, momentumFactor, holoFactor, threshold, maxIterations, selectedFunction);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = end - start;
	
	cout << "\n最佳化完成! " << endl;
	cout << "param1: " << optimized.param1 << ", param2: " << optimized.param2 << endl;
	cout << "Time elapsed: " << elapsed.count() << " seconds." << endl;
	
	return 0;
		
}




 




 
