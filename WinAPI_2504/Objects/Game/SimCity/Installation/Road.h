#pragma once

class Road :public Installation
{
public:
	Road();
	~Road();



private:
	void SetTarget() override;

};