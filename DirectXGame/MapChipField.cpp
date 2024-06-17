#include"MapChipField.h"
#include<map>
#include<fstream>
#include<sstream>
#include <cassert>

//マップチップテーブル
namespace
{
	std::map<std::string, MapChipType>mapChipTable =
	{
		{"0",MapChipType::kBlank},
		{"1",MapChipType::kBlock},
	};
}

//マップチップのリセット
void MapChipField::ResetMapChipData()
{
	mapChipData_.data.clear();
	mapChipData_.data.resize(kNumBlockVirtical);
	for (std::vector<MapChipType>& mapChipDataLine : mapChipData_.data)
	{
		mapChipDataLine.resize(kNumBlockHorizontal);
	}
}

//マップチップの読み込み
void MapChipField::LoadMapChipCsv(const std::string& filePath)
{
	//マップチップのデータをリセット
	ResetMapChipData();

	//ファイルをひらく
	std::ifstream file;
	file.open(filePath);
	assert(file.is_open());

	//マップチップCSV
	std::stringstream mapChipCsv;
	//ファイルの内容を文字列ストリームにコピー
	mapChipCsv << file.rdbuf();
	//ファイルを閉じる
	file.close();

	//CSVからマップチップデータを読み込む
	for (uint32_t i = 0; i < kNumBlockVirtical; ++i)
	{
		std::string line;
		getline(mapChipCsv, line);
		//1行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);
		for (uint32_t j = 0; j < kNumBlockHorizontal; ++j)
		{
			std::string word;
			getline(line_stream, word, ',');

			if (mapChipTable.contains(word))
			{
				mapChipData_.data[i][j] = mapChipTable[word];
			}
		}

	}
}

//マップチップ種別の取得
MapChipType MapChipField::GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex)
{
	if (xIndex < 0 || kNumBlockHorizontal - 1 < xIndex)
	{
		return MapChipType::kBlank;
	}
	if (yIndex < 0 || kNumBlockVirtical - 1 < yIndex)
	{
		return MapChipType::kBlank;
	}
	return mapChipData_.data[yIndex][xIndex];
}

//マップチップ座標の取得
Vector3 MapChipField::GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex)
{
	return Vector3(kBlockWidth * xIndex, kBlockHeight * (kNumBlockVirtical - 1 - yIndex), 0);
}

//ブロック数を返す(縦)
int MapChipField::GetNumBlockVirtical()
{
	return kNumBlockVirtical;
}
//ブロック数を返す(横)
int MapChipField::GetNumBlockHorizontal()
{
	return kNumBlockHorizontal;
}

//座標からマップチップ番号を計算
IndexSet MapChipField::GetMapChipIndexSetByPosition(const Vector3& position)
{
	IndexSet indexSet = {};
	indexSet.xIndex = static_cast<uint32_t>((int(position.x) + kBlockWidth / 2) / kBlockWidth);//x座標
	//反転前Y番号
	indexSet.yIndex = static_cast<uint32_t>((int(position.y) + kBlockHeight / 2) / kBlockHeight);//y座標

	uint32_t maxIndexY = kNumBlockVirtical - 1;
	indexSet.yIndex = maxIndexY - indexSet.yIndex;

	return IndexSet(indexSet);
}

//ブロックの範囲取得関数
Rect MapChipField::GetRectbyIndex(uint32_t xIndex, uint32_t yIndex)
{
	//指定ブロックの中心座標を取得する
	Vector3 center = GetMapChipPositionByIndex(xIndex, yIndex);

	Rect rect{};
	rect.left = center.x - kBlockWidth / 2.0f;    //左端
	rect.right = center.x + kBlockWidth / 2.0f;   //右端
	rect.bottom = center.y - kBlockHeight / 2.0f; //下端
	rect.top = center.y + kBlockHeight / 2.0f;    //上端

	return Rect(rect);
}



