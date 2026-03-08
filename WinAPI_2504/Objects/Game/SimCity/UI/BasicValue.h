#pragma once

class BasicValue : public GameObject
{
protected:
	const int MAX_NUM = 6; //6자리로 넘버즈 구현
public:
	BasicValue(Resources resource);
	~BasicValue();

	void Update();
	void Render();
protected:
	void CreateQuad(Resources resource);

private:
	void ChangeNumbers(int number);
protected:
	int preValue = 0;

	Resources resource;

	Quad* backGround;
	vector<Quad*> numbers;
	
};