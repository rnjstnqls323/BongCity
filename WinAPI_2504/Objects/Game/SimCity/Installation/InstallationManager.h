#pragma once

class InstallationManager : public Singleton<InstallationManager>
{
	friend class Singleton;

private:
	const int MAX_SIZE = 100;
private:
	InstallationManager();
	~InstallationManager();

public:
	void Update(); //필요할까?
	void Render();
	void Edit();

	bool SpawnInstallation(int& key, Vector3 pos, Index2& index);

private:
	void CreateInstallation();

private:
	unordered_map<int, pair<InstallationInstancing*, vector<Installation*>>> installations;	
};