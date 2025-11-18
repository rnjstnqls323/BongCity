#pragma once

class Input : public Singleton<Input>
{
	friend class Singleton;
private:
	static const int KEY_MAX = 256;

	enum KeyState
	{
		None, Down, Up, Press
	};

private:
	Input() = default;
	~Input() = default;
public:
	void Update();

	bool IsKeyDown(int key) const { return mapState[key] == Down; }
	bool IsKeyUp(int key) const { return mapState[key] == Up; }
	bool IsKeyPress(int key) const { return mapState[key] == Press; }

	void SetMouseWheel(int delta) { wheelDelta += delta; }
	int GetMouseWheel() { return wheelDelta; }

	void ClearMouseWheel() { wheelDelta = 0; }
private:
	int wheelDelta = 0; // 스크롤 값 저장

	BYTE curState[KEY_MAX] = {};
	BYTE oldState[KEY_MAX] = {};
	KeyState mapState[KEY_MAX] = {};
};