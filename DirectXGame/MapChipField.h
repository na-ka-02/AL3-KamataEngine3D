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

//マップチップのデータの読み込み
struct MapChipDate
{
	std::vector<std::vector<MapChipType>>data;
};

//座標からマップチップ番号を計算
struct IndexSet
{
	uint32_t xIndex;//x
	uint32_t yIndex;//y
};

//ブロックの範囲
struct Rect
{
	float left;  //左端
	float right; //右端
	float bottom;//下端
	float top;   //上端
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
	Vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);
	//マップチップのブロック数の取得(縦)
	int GetNumBlockVirtical();
	//マップチップのブロック数の取得(横)
	int GetNumBlockHorizontal();
	//座標からマップチップ番号を計算
	IndexSet GetMapChipIndexSetByPosition(const Vector3& position);
	//ブロックの範囲取得関数
	Rect GetRectbyIndex(uint32_t xIndex, uint32_t yIndex);

private:
	//ブロックのサイズ
	static inline const float kBlockWidth = 2.0f;
	static inline const float kBlockHeight = 2.0f;
	//ブロックの個数
	static inline const uint32_t kNumBlockVirtical = 20;
	static inline const uint32_t kNumBlockHorizontal = 100;
	//マップチップのデータ
	MapChipDate mapChipData_;
};