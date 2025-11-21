#pragma once

class Production :public Installation
{
public:
	Production();
	~Production();

	void AddResources();
private:
	void SetType() override;
};