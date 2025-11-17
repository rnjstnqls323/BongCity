#pragma once

class ScrollButton : public Button
{
public:
	ScrollButton(wstring imagePath, Vector2 size);
	~ScrollButton();

	void Update() override;
	float UpdateTransform(int size);
	void Edit() override;

	void SetOriginPos(Vector3 pos) { this->originPos = pos; }
	Vector3& GetOriginPos(){ return originPos; }

	void Reset();
private:
	bool isMove = false;
	float xPos;

	Vector3 prePos;
	Vector3 originPos;
};