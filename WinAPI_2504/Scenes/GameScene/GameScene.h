#pragma once

class GameScene :public Scene
{
public:
	GameScene();
	~GameScene();

	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;
	void GUIRender() override;

private:

private:
	
};