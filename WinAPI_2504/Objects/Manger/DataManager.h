#pragma once

enum class InstallationType
{
	Building, Production, LandScape, Road
};
struct ScaleData
{
	int key;
	string name;
	float x;
	float y;
	float z;
};
struct PriceData
{
	int key;
	int money;
	int oil;
	int electric;
	int iron;
};
struct DayData
{
	int key;
	string day;
	float morningMagnification;
	float afternoonMagnification;
	float nightMagnification;
};
struct InstallationData
{
	int key;
	string name;
	PriceData* price;
	ScaleData* scale;
	InstallationType type;
	int height;
	int width;
	int range;
	int congestion; //혼잡도 +해주면됨 범위만큼
	int environment; //환경도 +해주면됨
	int value; //시민수나 기름 1시간마다얻는 수
	int electricUsage;//1일마다 사용하는 전기량
};

class DataManager : public Singleton<DataManager>
{
	friend class Singleton;

private:
	DataManager();
	~DataManager();

public:	
	InstallationData& GetInstallationData(const int& key) { return installationDatas[key]; }
	int GetInstallationCount() {return installationDatas.size(); }

	DayData& GetDayData(int key) { return dayDatas[key]; }
private:
	void LoadData();

	void LoadDayData();
	void LoadScaleData();
	void LoadPriceData();
	void LoadInstallationData();
private:
	string filePath = "Resources/Tables/";
	unordered_map<int, DayData> dayDatas;
	unordered_map<int, ScaleData> scaleDatas;
	unordered_map<int, PriceData> priceDatas;
	unordered_map<int, InstallationData> installationDatas;

};