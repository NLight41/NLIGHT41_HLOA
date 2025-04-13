#include <iostream>
#include <cmath>
#include <chrono> 
using std::cout;
using std::endl;
// 程式名稱: NLight41 全像迴圈最佳化器 / NLight41 HoloLoop Optimizer 
// 初步構想: 03.18.2025 初版: 03.20.2025 by NLight41 
// 預計不只使用 std 函式庫，故不先宣告命名空間 
// 但先針對宣告 std 的 cout, endl 以利程式碼撰寫 

// 定義系統參數結構 (視情況增加參數) 
struct Parameters {
	double param1;
	double param2;
	// 計畫研究擴展成向量形式，用以處裡更複雜的參數 
	
};


// 模擬函式 : 模擬系統運作，並計算 模擬結果 與 預期值 之間的誤差 
// 設定 預期值為 100，而模擬模型為 param1 * sin(param2) + 10 
inline double simulationFunction(const Parameters &p) {
	double outcome = p.param1 * std::sin(p.param2) + 10;
	double expected = 100.0;
	return std::fabs(outcome - expected);
	
}


// 使用有限差分法估計梯度 (初版) 
inline void computeGradient(const Parameters &p, Parameters &grad, double delta = 1e-5){
	Parameters p_temp = p;
	double f0 = simulationFunction(p);
	
	// 計算 param1 對誤差的梯度  
	p_temp.param1 = p.param1 + delta;
	double f1 = simulationFunction(p_temp);
	grad.param1 = (f1 - f0) / delta;
	p_temp.param1 = p.param1;	// 重置
	
	// 計算 param2 對誤差的梯度 
	p_temp.param2 = p.param2 + delta;
	double f2 = simulationFunction(p_temp);
	grad.param2 = (f2 - f0) / delta;
	
}


// 自適應全像迴圈最佳化演算法 : 結合動量法則 與 全像回饋概念理論 進行參數更新 
// mometumFactor : 動量比例 / HoloFactor : 全像回饋因子 
Parameters  adaptiveHoloLoopOptimizer(Parameters initParams, double learningRate, double momentumFactor, double holoFactor, double threshold, int maxIterations) {
	Parameters p = initParams;
	Parameters grad{0.0, 0.0};
	Parameters momentum{0.0, 0.0}; // 保存上一輪的梯度動量值  
	
	double prevError = simulationFunction(p);
	double currError = prevError;
	int iteration = 0;
	
	
	while (currError > threshold && iteration < maxIterations) {
		
		// 1. 計算梯度 (初版) 
		computeGradient(p, grad);
		
		// 2. 動量更新 : 將當前的梯度 與 上一輪測試的梯度 按比例融合
		momentum.param1 = momentumFactor * momentum.param1 + (1 - momentumFactor) * grad.param1;
		momentum.param2 = momentumFactor * momentum.param2 + (1 - momentumFactor) * grad.param2;
		
		// 3. 全像回饋調整 : 根據梯度變化量調整梯度更新速度 
		double errorDiff = currError - prevError;
		// holoAdjustment : 全像回饋變因，會隨著誤差 上升與下降 進行 動態修正
		double holoAdjustment = holoFactor * errorDiff;
		
		// 4. 更新參數 : 將 動量 與 全像回饋變因 結合後，進行梯度下降更新 
		p.param1 -= learningRate * (momentum.param1 + holoAdjustment);
		p.param2 -= learningRate * (momentum.param2 + holoAdjustment);
		
		// 5. 更新誤差值 及 迭代次數
		prevError = currError;
		currError = simulationFunction(p);
		iteration++;
		
		// 6. 輸出當前迭代狀況，用於 追蹤版本 及 方便調整  
		cout << "Iteration: " << iteration
			 << ", Error: " << currError 
			 << ", param1: " << p.param1
			 << ", param2: " << p.param2 << endl; 
				
	}
	
	return p;	
}


int main() {
	// 初始參數設定  
	Parameters initialParams {50.0, 1.0};
	double learningRate = 0.01;
	double momentumFactor = 0.9;	// 通常預設 momentum 參數為 0.9，經驗法則顯示 0.9 在加速收斂與保持穩定性之間有著良好的平衡點 
	double holoFactor = 0.05;		// 根據誤差變化調整步長 
	double threshold = 1e-3;		// 收斂判定閥值  
	int maxIterations = 10000;
	
	// 計時 觀察性能 
	auto start = std::chrono::high_resolution_clock::now();
	Parameters optimized = adaptiveHoloLoopOptimizer(initialParams, learningRate, momentumFactor, holoFactor, threshold, maxIterations);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = end - start;
	
	cout << "\nOptimized Parameters:" << endl;
	cout << "param1: " << optimized.param1 << endl;
	cout << "param2: " << optimized.param2 << endl;
	cout << "Time elapsed: " << elapsed.count() << " seconds." << endl;
	
	return 0;
		
}



 
