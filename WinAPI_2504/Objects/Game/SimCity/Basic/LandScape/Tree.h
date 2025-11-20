#pragma once

class Tree
{
public:
	Tree(Vector2 range, int size, Vector2 noBuildRange = Vector2{ 0,0 }, Vector3 pos = {0,1,0});
	~Tree();

	Material* GetMaterial() { return material; }
	void Render();

private:
	void CreateTrees();
	Vector3 GetRandomPos();
private:
	int size;

	Vector2 range;
	Vector2 noBuildRange;

	Vector3 pos;

	Material* material;
	VertexBuffer* vertexBuffer;
	GeometryShader* geometryShader;

	vector<VertexUV> vertices;
};