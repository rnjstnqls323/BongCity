#pragma once

class Building : public Installation
{
public:
	Building();
	~Building();


	void Spawn(const Vector3 pos, int& rotation) override;
	void Dispawn() override; 
private:

	// Installation을(를) 통해 상속됨
	void SetType() override;
};