#pragma once

class Building : public Installation
{
public:
	Building();
	~Building();

private:

	// Installation을(를) 통해 상속됨
	void SetTarget() override;
};