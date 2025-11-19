#pragma once

class LandScape :public Installation
{
public:
	LandScape();
	~LandScape();

private:


	// Installation을(를) 통해 상속됨
	void SetTarget() override;

};