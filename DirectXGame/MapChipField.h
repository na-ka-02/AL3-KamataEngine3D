#pragma once
#include<iostream>
#include<vector>
#include<string>
#include"Vector3.h"

enum class MapChipType
{
	kBlank,//空白
	kBlock//ブロック
};

struct MapChipDate
{
	std::vector<std::vector<MapChipType>>data;
};

class MapChipField
{
public:
	//マップチップのリセット
	void ResetMapChipData();
	//マップチップの読み込み
	void LoadMapChipCsv(const std::string& filePath);
	//マップチップ種別の取得
	MapChipType GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex);
	//マップチップの座標の所得
	Vector3 GetMapChipPositionByIndex(uint32_t xIndex,uint32_t yIndex);

private:
	//ブロックのサイズ
	static inline const float kBlockWidth = 1.0f;
	static inline const float kBlockHeight = 1.0f;
	//ブロックの個数
	static inline const uint32_t kNumBlockVirtical = 20;
	static inline const uint32_t kNumBlockHorizontal = 100;
	//マップチップのデータ
	MapChipDate mapChipData_;
};