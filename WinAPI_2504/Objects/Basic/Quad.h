#pragma once

class Quad : public GameObject
{
private:
	typedef VertexUV VertexType;

public:
	Quad(Vector2 size = Vector2(1, 1));
	Quad(wstring textureFile, Vector2 startUV = Vector2(), Vector2 endUV = Vector2(1, 1));
	Quad(wstring textureFile, bool isFit);
	~Quad();

	void Render();	
	void RenderInstanced(UINT count);

	Vector2 GetSize() const { return size; }

private:
	void MakeMesh();

protected:
	Vector2 startUV;
	Vector2 endUV = { 1, 1 };

	Vector2 size;

	Mesh<VertexUV>* mesh;
};