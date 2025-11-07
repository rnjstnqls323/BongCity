#include "Framework.h"


Installation::Installation()
{
	sideTiles.reserve(50);
}

Installation::~Installation()
{
}

void Installation::SetData(const int& key)
{
	data = DataManager::Get()->GetInstallationData(key);
}

void Installation::Render()
{
}

void Installation::Update()
{
	if (!isSelect) return;

	//선택시 위치 옮기는거 조정하기
}

void Installation::Build(const Vector3 pos)
{
	//환경도, 혼잡도 올려주기
	//값 추가하는거 상속받아서 해주기
	transform->SetLocalPosition(pos);
	isBuild = true;
}

void Installation::Distroy()
{
}

bool Installation::CheckSide()
{
	if (data.type == InstallationType::Road) return true;

	sideTiles.clear();

	Index2 leftTop = centerIndex;

	//왼쪽 위 찾기
	leftTop.row -= (data.width * 0.5f);
	leftTop.col -= (data.height * 0.5f);

	Index2 index;
	for (int row = 1; row <= data.width; row++)
	{
		index = { leftTop.row - row , leftTop.col };
		sideTiles.push_back(TileManager::Get()->GetTileToIndex(index));
		index = { leftTop.row - row , leftTop.col + data.height + 1 };
		sideTiles.push_back(TileManager::Get()->GetTileToIndex(index));
	}
	for (int col = 1; col <= data.height; col++)
	{
		index = { leftTop.row, leftTop.col + col };
		sideTiles.push_back(TileManager::Get()->GetTileToIndex(index));
		index = { leftTop.row-data.width-1 , leftTop.col + col };
		sideTiles.push_back(TileManager::Get()->GetTileToIndex(index));
	}

	for (Tile* tile : sideTiles)
	{
		if (tile->GetTileType() == InstallationType::Road)
			return true;
	}
	return false;
}

