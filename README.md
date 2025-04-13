# [NLight41_HLOA 專案子倉庫](https://github.com/NLight41/NLIGHT41_HLOA)
> 建立時間：03.31.2025 by NLight41  
> [返回 NLight41 本站](https://nlight41.github.io/NLight41_LearningRepo/)  

---
# HLOA - Holo Loop Optimization Algorithm   
> 創建者：NLight41  
> 構思起始：2024 年中  
> 實作啟動：03.09.2025   
  
---  
## 演算法簡介  
> HLOA（Holo Loop Optimization Algorithm）是一個源於物理「全像原理」的最佳化結構構想，由我在高中階段自發性構思與開發。  
> 下方為我以英文撰寫的命名說明，供讀者參考與理解這套演算法的邏輯與精神。  

### HLOA（Holo Loop Optimization Algorithm）   
> 是一種原創的最佳化演算法架構，靈感來自全像原理與動態系統的自我調整機制。    
  
其核心設計融合了：  
- 動量加速（Momentum Boost）：穩定梯度方向，減少局部震盪，加速收斂。  
- 全像回饋（Holographic Feedback）：模擬資訊在系統中的全像映射與能量再分配，動態調整學習率，提升適應性。  
- 自適應全像回饋因子：根據誤差變化量調整學習步長，實現智慧式收斂。  
  
HLOA 旨在針對複雜問題求得更具穩定性與收斂性的解，適用於多種最佳化應用場景。  

---  
## HLOA 核心創新 與 設計理念   
  
### 1. 動量加速（Momentum Boost）  
- 利用動量法（Momentum Method）穩定梯度方向，減少局部震盪，加速收斂。​  
  
### 2. 全像回饋（Holographic Feedback）   
- 參考全像原理的概念，將誤差變化視為系統邊界訊號，動態調整學習率，提升適應性。  
  
### 3. 自適應全像回饋因子  
- `H = HoloFactor * |誤差變化量|`  
- 當誤差變化大時，提高學習步長，加快收斂  
- 當誤差變化小時，自動降低步長，避免過度修正  


---

## [HLOA v0.1.1] - 03.24.2025  
### 版本內容:  
#### 🔹技術更新：  
- 以 Cppad 自動微分框架 取代原有限差分法，解決了數值不穩定等問題。  
- 結合 Eigen 與 OpenMP(透過#pragma omp實現並行運算)，大幅提升運算效能與資源運用效率。  

#### 🔹平台遷移挑戰：  
- 從 Dev-C++ 轉換至 Visual Studio 2022，現遇到 CMakeLists 與VS設定問題。  

#### 🔹整體創新亮點：  
- 構想從數值計算、並行運算到自動微分的全流程創新應用。  

---
  
## [HLOA v0.0.0_AdaptiveTest] - 03.21.2025  
### 版本內容：  
#### 🔹新增功能：  
- 增加使用者參數輸入功能，並提供自由更換測試目標（包含凸/非凸函數）。  
- 更新有限差分法計算，融入偏微分概念，提升計算精度。  
  
#### 🔹模組化改善：  
- 程式碼模組化 與 統一標識性 助於後續維護與擴充，為後續演算法推廣鋪路。  

---
  
## [HLOA v0.0.0] - 03.20.2025  
### 版本內容：  
#### 🔹主要技術：  
- 採用 有限差分法 進行梯度下降，結合 動量法 與 自創的全像迴圈回饋概念，進而達到自適應最佳化。  

#### 🔹創新思路：  
- 將 有限差分 與 全像原理 結合，嘗試從不同角度進行演算法改良。  

#### 🔹待探討問題：  
- GUI迭代次數設定：  
> 過大： 可能導致計算成本過高、收斂速度變慢、記憶體使用增加。  
> 過小： 可能使最佳化運算不足，無法充分探索解空間。  
> 延伸： 如何動態調整或根據目標函數特性自適應決定最佳迭代次數，甚至引入如自動學習率或後向反饋機制。  

---
  
## 🧾 命名理念與開發背景（Naming Philosophy and Background）  
### 中文引言：  
> HLOA 的命名來自我對「資訊結構動態回饋」與「全像原理」的長期觀察與興趣。  
> 這是一套由我在 2024 年中開始構思，2025 年初進入實作的原創性演算法架構。  
> 希望能透過這個命名傳達我對最佳化不只是數學模型，更是動態系統與內部回饋機制的理解。  
  
### 英文部分:   
> The name **HLOA (Holo Loop Optimization Algorithm)** comes from the core idea of simulating an optimization process inspired by **holographic feedback loops**.   
> Rather than following a conventional path of gradient descent alone, HLOA introduces a dynamic structure that mimics how systems can self-correct, adapt, and resonate internally through feedback.  
> 
> The term *"Holo Loop"* emphasizes the cyclical, reflective nature of learning—where every update carries memory, momentum, and self-awareness, similar to holographic interference patterns in physics.  
> 
> This naming concept was originally conceived by me (NLight41) in mid-2024, and I began implementation and experimentation in early 2025.   
> As a high school student passionate about optimization theory and computational logic, I wanted to design an algorithm that pushes beyond traditional methods by blending mathematical reasoning with structural design thinking.  
> 
> HLOA is not only a technical framework but also a reflection of how I perceive adaptive intelligence: recursive, nonlinear, and ever-evolving.  
