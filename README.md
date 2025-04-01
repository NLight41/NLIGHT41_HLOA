# NLight41_HLOA project  
> 建立時間：03.20.2025 by NLight41  
> [返回 NLight41 本站](https://nlight41.github.io/NLight41_LearningRepo/)  

---
# 何謂 HLOA project ？  
《 HLOA 》 Holo Loop Optimization Algorithm，全像迴圈最佳化演算法 by NLight41  
- 使用梯度下降(Gradient Descent) 與 動量法(Momentum Method)  
- 結合 全像回饋(Holo Feedback)來最小化系統模擬誤差，使系統趨近於最佳解  

### 目標  
1. 

---  
## HLOA 核心創新 與 設計理念 
  
### 結合動量與全像回饋  
- 動量（Momentum）可加速收斂，減少局部震盪  
- 全像回饋（Holographic Feedback）可根據誤差變化 **動態調整學習率**，提升適應性  

### 自適應全像回饋因子
- `H = HoloFactor * |誤差變化量|`  
- 當誤差變化大時，提高學習步長，加快收斂  
- 當誤差變化小時，自動降低步長，避免過度修正  


---

## [HLOA v0.1.0] - 03.24.2025  
### 版本內容:  
- 新增 CppAD 與 Eigen 函數庫運用  
- 新增 並行運算  
- 新增 自動微分框架  
- 嘗試由 Dev-C++ 轉移至 VScode  

---

## [HLOA v0.0.0_AdaptiveTest] - 03.21.2025  
### 版本內容：  
- 新增 凸/非凸變數 選項  
- 新增 參數設定功能

---
  
## [HLOA v0.0.0] - 03.20.2025  
### 版本內容：  
- HLOA 初版設計完成  
- 採用 MinGW  

---
  
## [HLOA test] - 03.18.2025  
### 版本內容：  
- 初步構想 內容結構 與 運作邏輯  
  
---




