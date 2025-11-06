#pragma once

class ModelInstancingScene : public Scene
{
public:
	ModelInstancingScene();
	~ModelInstancingScene();

	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;
	void GUIRender() override;

private:
	//vector<Model*> models;
	//ModelInstancing* modelInstancing;
	//ModelAnimatorInstancing* modelInstancing;

	QuadInstancing* instan;
	vector<Transform*> transforms;

	int instanceIndex = 0;
	int clip = 0;
};