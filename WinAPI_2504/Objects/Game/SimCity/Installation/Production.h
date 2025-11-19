#pragma once

class Production :public Installation
{
public:
	Production();
	~Production();

private:

	// Installation을(를) 통해 상속됨
	void SetTarget() override;
};