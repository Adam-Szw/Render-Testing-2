#pragma once
#include "Entity.h"
#include <vector>
#include "Maths.h"

class Renderer
{
private:
	struct SimpleRender
	{
		unsigned int VAO;
		unsigned int vertexVBO;					//vertex data
		unsigned int IBO;						//index data
		unsigned int modelMatrixVBO;
		std::vector<Texture*> textures;
		unsigned int elementCounter = 0;
		unsigned int instances = 0;
	};

	static void bindExistingBuffers(SimpleRender* render, Model* m, int* attributeOffset);
	static unsigned int createmodelMatrixBuffer(std::vector<Maths::mat4>* modelMatrixsData, int* attributeOffset);
	static unsigned int createVertexBuffer(std::vector<Model::Vertex>* data, int* attributeOffset);
	static unsigned int createIndexbuffer(std::vector<int>* data, unsigned int* elementCounter);

	static std::vector<SimpleRender*> simpleRenderTable;
	static std::map<Entity*, std::vector<SimpleRender*>> entityReference;		//	These help in determining which SimpleRender
	static std::map<Model*, std::vector<SimpleRender*>> modelReference;			//	objects should be updated, when given resource
	static std::map<Texture*, std::vector<SimpleRender*>> textureReference;		//	is updated.

	//returns true if asset already has a render associated to it
	static bool createReference(Entity* entity, SimpleRender* render);
	static bool createReference(Model* model, SimpleRender* render);
	static bool createReference(Texture* texture, SimpleRender* render);

public:
	static Maths::mat4 viewMatrix;
	static Maths::mat4 projectionMatrix;

	static void createRender(Entity* ent, unsigned short renderer);

	static void render();

	//placeholder for message system
	//for now I'm just using this crude way of moving things around the screen until I implement proper messaging system
	enum class action
	{
		add, remove, swap
	};
	static void updateEntityMatrixOrientation(action action, Entity* target, unsigned int mapping,
		std::vector<unsigned int> offsets, const std::vector<Maths::mat4> data);

	static Maths::vec3 lightPositionTest;	//testing light features
};

