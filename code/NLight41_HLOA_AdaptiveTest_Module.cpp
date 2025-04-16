#include <iostream>
#include <cmath>
#include <chrono> 
#include <vector>
#include <functional>
// HLOA AdaptiveTest Module  
// 03.24.2025 by NLight41  
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::function;
using std::fabs;
 

// ==== 把计家舱 ==== 
struct Parameters {
	double param1;
	double param2;  	
};

// や穿ぃ代刚ㄧ计 (箇砞 sin ㄧ计) 
double simulationFunction(const Parameters &p, const function<double(const Parameters&)> &func) {
	return func(p);
}

// 矗ㄑ 代刚ㄧ计 ( / 獶)
double convexFunction(const Parameters &p) {
	return fabs(p.param1 * p.param1 + p.param2 * p.param2 - 100);
}
double nonConvexFunction(const Parameters &p) {
	return fabs(p.param1 * sin(p.param2) + 10 - 100);
}

// Τ畉だ猭璸衡辫 (ver 2.) 
void computeGradient(const Parameters &p, Parameters &grad, const function<double(const Parameters&)> &func, double delta = 1e-5){
	Parameters p_temp = p;
	double f0 = simulationFunction(p, func);
	
	p_temp.param1 += delta;
	double f1 = simulationFunction(p_temp, func);
	grad.param1 = (f1 - f0) / delta;
	p_temp.param1 = p.param1;	// 竚 
	
	
	p_temp.param2 += delta;
	double f2 = simulationFunction(p_temp, func);
	grad.param2 = (f2 - f0) / delta;
	
}



/*

跋办竚 ML 祘Α絏 

*/




// ==== 把计块╰参 ==== 
void inputParameters(Parameters &initParams, double &learningRate, double &momentumFactor, double &holoFactor, double &threshold, int &maxIterations) {
	cout << "砞﹚﹍把计 (param1 param2): " ;
	cin >> initParams.param1 >> initParams.param2;
	cout << "砞﹚厩策瞯: " ;
	cin >> learningRate;
	cout << "砞﹚笆秖跑计: " ;
	cin >> momentumFactor;
	cout << "砞﹚钩鮔跑计: " ;
	cin >> holoFactor;
	cout << "砞﹚粇畉恢: " ;
	cin >> threshold;
	cout << "砞﹚程Ω计: " ; 
	cin >> maxIterations;
		
}

 
int main() {
	// 块把计 
	Parameters initialParams;
	double learningRate, momentumFactor, holoFactor, threshold;
	int maxIterations;
	inputParameters(initialParams, learningRate, momentumFactor, holoFactor, threshold, maxIterations);
	 
	int choice;
	function<double(const Parameters&)> selectedFunction;
	cout << "匡拒ヘ夹ㄧ计: (1) ㄧ计 (2) 獶ㄧ计: ";
	cin >> choice;
	
	if (choice == 1) {
		selectedFunction = convexFunction;
		cout << "ㄏノㄧ计: f(x, y) = |x^2 + y^2 - 100|" << endl;
	} else {
		selectedFunction = nonConvexFunction;
		cout << "ㄏノ獶ㄧ计: f(x, y) = |x * sin(y) + 10 - 100|" << endl;
	}
	
	
	// 璸 芠诡┦ 
	auto start = std::chrono::high_resolution_clock::now();
	Parameters optimized = adaptiveHoloLoopOptimizer(initialParams, learningRate, momentumFactor, holoFactor, threshold, maxIterations, selectedFunction);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = end - start;
	
	cout << "\n程ㄎてЧΘ! " << endl;
	cout << "param1: " << optimized.param1 << ", param2: " << optimized.param2 << endl;
	cout << "Time elapsed: " << elapsed.count() << " seconds." << endl;
	
	return 0;
		
}




 




 
