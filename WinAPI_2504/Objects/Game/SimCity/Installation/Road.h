#pragma once

class Road :public Installation
{
public:
	Road();
	~Road();



private:
	void SetType() override;

};