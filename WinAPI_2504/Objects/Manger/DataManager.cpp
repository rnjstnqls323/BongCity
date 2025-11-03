#include "Framework.h"

DataManager::DataManager()
{
	LoadData();
}

DataManager::~DataManager()
{
}

void DataManager::LoadData()
{
	LoadDayData();
	LoadPriceData();
	LoadInstallationData();
}

void DataManager::LoadDayData()
{
	ifstream file(filePath + "DayData.csv");
	if (!file.is_open())
	{
		MessageBox(nullptr, L"Failed to open file", L"Error", MB_OK);
		return;
	}

	string line;

	bool isFirstLine = true;

	while (getline(file, line))
	{
		if (isFirstLine)
		{
			isFirstLine = false;
			continue;
		}

		vector<string> data = Utility::SplitString(line, ",");

		DayData dayData;
		dayData.key = stoi(data[0]);
		dayData.day = data[1];
		dayData.morningMagnification = stof(data[2]);
		dayData.afternoonMagnification = stof(data[3]);
		dayData.nightMagnification = stof(data[4]);

		dayDatas[dayData.key] = dayData;
	}
	file.close();

}

void DataManager::LoadPriceData()
{
	ifstream file(filePath + "PriceData.csv");
	if (!file.is_open())
	{
		MessageBox(nullptr, L"Failed to open file", L"Error", MB_OK);
		return;
	}

	string line;

	bool isFirstLine = true;

	while (getline(file, line))
	{
		if (isFirstLine)
		{
			isFirstLine = false;
			continue;
		}

		vector<string> data = Utility::SplitString(line, ",");

		PriceData price;

		price.key = stoi(data[0]);
		price.money = stoi(data[1]);
		price.oil = stoi(data[2]);
		price.electric = stoi(data[3]);
		price.iron = stoi(data[4]);

		priceDatas[price.key] = price;
	}
	file.close();
}

void DataManager::LoadInstallationData()
{
	ifstream file(filePath + "InstallationData.csv");
	if (!file.is_open())
	{
		MessageBox(nullptr, L"Failed to open file", L"Error", MB_OK);
		return;
	}

	string line;

	bool isFirstLine = true;

	while (getline(file, line))
	{
		if (isFirstLine)
		{
			isFirstLine = false;
			continue;
		}

		vector<string> data = Utility::SplitString(line, ",");

		InstallationData ins;

		ins.key = stoi(data[0]);
		ins.name = data[1];
		ins.price = &priceDatas[stoi(data[2])];
		ins.type = (InstallationType)stoi(data[3]);
		ins.height = stoi(data[4]);
		ins.width = stoi(data[5]);
		ins.range = stoi(data[6]);
		ins.congestion = stoi(data[7]);
		ins.environment = stoi(data[8]);
		ins.value = stoi(data[9]);
		ins.electricUsage = stoi(data[10]);

		installationDatas[ins.key] = ins;
	}
	file.close();
}
