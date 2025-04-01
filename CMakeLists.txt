# ============== CMakeLists.txt ================
# [v0.2.4] - 03.31.2025 by NLight41

# 主要功能: 
# 1. 設定 CMake 版本、專案名稱與 C++ 標準
# 2. 設定與檢查函式庫 (Eigen、CppAD)，支援自動下載 (如果本機無法找到相對應的檔案)
# 3. 確保 `configure.hpp.in` 能成功轉換為 `configure.hpp` 
# 4. 設定編譯輸出目錄，確保 VS2022 找的到執行檔
# 5. 設定可執行檔，並正確連結至 目標函式庫(Library)
# 6. 禁用pkg-config檢查，確保在Windows環境中正確配置


# 設定 CMake 最低版本 & 專案名稱
cmake_minimum_required(VERSION 3.16)
project(NLight41_LearningRepo LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 禁用pkg-config（針對Windows/VS2022）
set(PKG_CONFIG_EXECUTABLE "" CACHE FILEPATH "Disable pkg-config")

# 啟用 FetchContent
include(FetchContent)


# ============ 透過 FetchContent 下載 & 設定路徑 ===============

message(STATUS "檢查與下載所需的第三方函式庫...")

# Eigen 3.4.0
FetchContent_Declare(
	eigen
	GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
	GIT_TAG 3.4.0
)


# CppAD (最新版本)
FetchContent_Declare(
	cppad
	GIT_REPOSITORY https://github.com/coin-or/CppAD.git
	GIT_TAG master
	CMAKE_ARGS
		-DCPPAD_PKG_CONFIG_FILE=OFF		# 關閉 pkg-config 檔案生成
)

# 執行下載
FetchContent_MakeAvailable(eigen cppad)

# 明確設置Eigen的包含目錄，並強制使用MODULE模式查找
set(EIGEN_INCLUDE_DIR ${eigen_SOURCE_DIR} CACHE PATH "Eigen include directory" FORCE)
find_package(EIGEN REQUIRED NO_MODULE)

# 設定 include 目錄
set(EIGEN_INCLUDE_DIR ${eigen_SOURCE_DIR})
set(CPPAD_INCLUDE_DIR ${cppad_SOURCE_DIR}/include)
include_directories(${EIGEN_INCLUDE_DIR} ${CPPAD_INCLUDE_DIR})

message(STATUS "Eigen 位於: ${EIGEN_INCLUDE_DIR}")
message(STATUS "CppAD 位於: ${CPPAD_INCLUDE_DIR}")



# ================ 編譯設定 ===================

# 設定輸出目錄
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# 確保 `configure.hpp` 存在
set(CONFIGURE_HPP_IN "${cppad_SOURCE_DIR}/cppad/configure.hpp.in")
set(CONFIGURE_HPP_OUT "${CMAKE_BINARY_DIR}/cppad/configure.hpp")
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/cppad/")

# 使用 `configure_file()` 進行變數替換 (如果有 `@VAR@` 變數)
if(EXISTS ${CONFIGURE_HPP_IN})
	configure_file(
		${CONFIGURE_HPP_IN}
		${CONFIGURE_HPP_OUT}
		@ONLY
	)
else()
	message(WARNING "找不到 configure.hpp.in，將使用 `add_custum_command()`")
endif()

# 使用 `add_custom_command()` 確保 `configure.hpp` 會自動更新
if(EXISTS ${CONFIGURE_HPP_IN})
	add_custom_command(
		OUTPUT ${CONFIGURE_HPP_OUT}
		COMMAND ${CMAKE_COMMAND} -E copy
			${CONFIGURE_HPP_IN}
			${CONFIGURE_HPP_OUT}
		DEPENDS ${CONFIGURE_HPP_IN}
		COMMENT "轉換 configure.hpp.in 為 configure.hpp"
	)

	# 確保 `configure.hpp` 轉換後才能執行編譯
	add_custom_target(GenerateConfigHPP ALL DEPENDS ${CONFIGURE_HPP_OUT})
endif()

# 設定可執行檔
file(GLOB SOURCE_FILES "*.cpp")
add_executable(NLight41_LearningRepo ${SOURCE_FILES})

# 如果 `configure.hpp` 存在，則加入相依性
if(TARGET GenerateConfigHPP)
	add_dependencies(NLight41_LearningRepo GenerateConfigHPP)
endif()

# 確保專案能找到 `configure.hpp`
include_directories(${CMAKE_BINARY_DIR}/cppad)

# 為Windows和Visual Studio添加特定設置
if(WIN32)
    # 禁用警告作為錯誤（如果需要）
    if(MSVC)
        # 設置MSVC特定編譯器標誌
        add_compile_options(/MP /W3 /wd4996)
        # 禁用特定警告（如果有問題）
        add_compile_options(/wd4251 /wd4275)
    endif()
endif()


message(STATUS "CMake 設定完成！")