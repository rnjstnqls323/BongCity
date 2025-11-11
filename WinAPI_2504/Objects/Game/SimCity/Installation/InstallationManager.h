#pragma once

class InstallationManager : public Singleton<InstallationManager>
{
	friend class Singleton;

private:
	const int MAX_SIZE = 1000;
private:
	InstallationManager();
	~InstallationManager();

public:
	void Update(); //필요할까?
	void Render();
	void Edit();

	void SpawnInstallation(InstallationData& data, Vector3 pos, Index2& index, int& rotation);

	void DispawnInstallation(int& key, Index2& index);

private:
	void CreateInstallation();
	Installation*& GetTransformToIndex(int& key, Index2& index);

private:
	unordered_map<int, pair<InstallationInstancing*, vector<Installation*>>> installations;	
};