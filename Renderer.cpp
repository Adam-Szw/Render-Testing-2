#include "Renderer.h"
#include "ShaderReader.h"
#include <iostream>
#include <cassert>
#include <glad/glad.h>

Maths::mat4 Renderer::viewMatrix;
Maths::mat4 Renderer::projectionMatrix;
Maths::vec3 Renderer::lightPositionTest;

std::vector<Renderer::SimpleRender*> Renderer::simpleRenderTable;
std::map<Entity*, std::vector<Renderer::SimpleRender*>> Renderer::entityReference;
std::map<Model*, std::vector<Renderer::SimpleRender*>> Renderer::modelReference;
std::map<Texture*, std::vector<Renderer::SimpleRender*>> Renderer::textureReference;

const int initValues[32] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31 };

void Renderer::bindExistingBuffers(Renderer::SimpleRender* render, Model* m, int* attributeOffset)
{
	render->IBO = modelReference[m][0]->IBO;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, render->IBO);
	render->elementCounter = modelReference[m][0]->elementCounter;

	glBindBuffer(GL_ARRAY_BUFFER, modelReference[m][0]->vertexVBO);
	//positions
	glVertexAttribPointer(*attributeOffset, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(*attributeOffset);
	//normals
	glVertexAttribPointer(*attributeOffset + 1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(*attributeOffset + 1);
	//texture uv
	glVertexAttribPointer(*attributeOffset + 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(*attributeOffset + 2);
	*attributeOffset += 3;
}

//Creates IBO buffer and updates element counter
unsigned int Renderer::createIndexbuffer(std::vector<int>* data, unsigned int* elementCounter)
{
	unsigned int indexBuffer;
	glGenBuffers(1, &indexBuffer);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ((*data).size()) * sizeof(int), &((*data)[0]), GL_STATIC_DRAW);
	*elementCounter = (*data).size();

	return indexBuffer;
}

//Creates VBO containing vertices of a model and updates attribute offset
unsigned int Renderer::createVertexBuffer(std::vector<Model::Vertex>* data, int* attributeOffset)
{
	unsigned int vertexBuffer;
	glGenBuffers(1, &vertexBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8 * data->size(), &((*data)[0]), GL_STATIC_DRAW);
	//positions
	glVertexAttribPointer(*attributeOffset, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(*attributeOffset);
	//normals
	glVertexAttribPointer(*attributeOffset + 1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(*attributeOffset + 1);
	//texture uv
	glVertexAttribPointer(*attributeOffset + 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(*attributeOffset + 2);

	*attributeOffset += 3;

	return vertexBuffer;
}

//Creates instanced VBO containing mat4 modelMatrix for different instances and updates offset
unsigned int Renderer::createmodelMatrixBuffer(std::vector<Maths::mat4>* modelMatrixData, int* attributeOffset)
{
	unsigned int modelMatrixBuffer;
	glGenBuffers(1, &modelMatrixBuffer);

	int size = modelMatrixData->size();

	glBindBuffer(GL_ARRAY_BUFFER, modelMatrixBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Maths::mat4) * size, (*modelMatrixData)[0].values, GL_STATIC_DRAW);
	glVertexAttribPointer(*attributeOffset, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)0);
	glVertexAttribPointer(*attributeOffset + 1, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)16);
	glVertexAttribPointer(*attributeOffset + 2, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)32);
	glVertexAttribPointer(*attributeOffset + 3, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)48);
	glVertexAttribDivisor(*attributeOffset, 1);
	glVertexAttribDivisor(*attributeOffset + 1, 1);
	glVertexAttribDivisor(*attributeOffset + 2, 1);
	glVertexAttribDivisor(*attributeOffset + 3, 1);
	glEnableVertexAttribArray(*attributeOffset);
	glEnableVertexAttribArray(*attributeOffset + 1);
	glEnableVertexAttribArray(*attributeOffset + 2);
	glEnableVertexAttribArray(*attributeOffset + 3);

	*attributeOffset += 4;

	return modelMatrixBuffer;
}

bool Renderer::createReference(Entity* entity, SimpleRender* render)
{
	auto it = entityReference.find(entity);
	if (it != entityReference.end())
	{
		entityReference.insert(std::make_pair(entity, std::vector<SimpleRender*>({ render })));
		return true;
	}
	else
	{
		entityReference[entity].push_back(render);
		return false;
	}
}

bool Renderer::createReference(Model* model, SimpleRender* render)
{
	auto it = modelReference.find(model);
	if (it != modelReference.end())
	{
		modelReference.insert(std::make_pair(model, std::vector<SimpleRender*>({ render })));
		return true;
	}
	else
	{
		modelReference[model].push_back(render);
		return false;
	}
}

bool Renderer::createReference(Texture* texture, SimpleRender* render)
{
	auto it = textureReference.find(texture);
	if (it != textureReference.end())
	{
		textureReference.insert(std::make_pair(texture, std::vector<SimpleRender*>({ render })));
		return true;
	}
	else
	{
		textureReference[texture].push_back(render);
		return false;
	}
}

void Renderer::createRender(Entity* ent, unsigned short renderer)
{
	switch (renderer)
	{
	case 0:
	{
		//################SIMPLE RENDERER#####################
		int attribOffset = 0;

		//go through all models used by entity
		for (unsigned int i = 0; i < ent->models.size(); i++)
		{
			Model* m = ent->models[i];
			assert(m->loaded);

			//each model gets it's own Simple Renderer table row
			SimpleRender* newRender = new SimpleRender();
			createReference(ent, newRender);

			glGenVertexArrays(1, &(newRender->VAO));
			glBindVertexArray(newRender->VAO);

			//associate already existing VBO with this VAO if model already exists
			if (!createReference(m, newRender))
			{
				newRender->vertexVBO = createVertexBuffer(&(m->vertexData), &attribOffset);
				newRender->IBO = createIndexbuffer(&(m->indexData), &(newRender->elementCounter));
			}
			else
			{
				newRender->vertexVBO = modelReference[m][0]->vertexVBO;
				bindExistingBuffers(newRender, m, &attribOffset);
			}

			for (Texture* t : ent->texturesMap[i])
			{
				assert(t->loaded);
				newRender->textures.push_back(t);
				createReference(t, newRender);
			}

			//modelMatrix - each different instance of same model
			newRender->modelMatrixVBO = createmodelMatrixBuffer(&(ent->modelMatrixMap[i]), &attribOffset);
			newRender->instances = ent->modelMatrixMap[i].size();

			simpleRenderTable.push_back(newRender);

			attribOffset = 0;
			glBindVertexArray(0);
		}
	}
		break;
	}
}

void Renderer::render()
{
	for (SimpleRender* rend : simpleRenderTable)
	{
		glBindVertexArray(rend->VAO);

		//shader settings
		glUseProgram(ShaderReader::shaderPrograms[0]);	//hard-coded shader 0 until materials introduced
		unsigned int texUniform = glGetUniformLocation(ShaderReader::shaderPrograms[0], "textureObj");
		glUniform1iv(texUniform, 32, initValues);
		unsigned int lightPosUniform = glGetUniformLocation(ShaderReader::shaderPrograms[0], "lightPos");
		unsigned int lightColorUniform = glGetUniformLocation(ShaderReader::shaderPrograms[0], "lightColor");
		unsigned int ambientStrengthUniform = glGetUniformLocation(ShaderReader::shaderPrograms[0], "ambientStrength");
		unsigned int diffuseStrengthUniform = glGetUniformLocation(ShaderReader::shaderPrograms[0], "diffuseStrength");
		glUniform3f(lightPosUniform, lightPositionTest.values[0], lightPositionTest.values[1], lightPositionTest.values[2]);
		glUniform3f(lightColorUniform, 1.0f, 1.0f, 1.0f);
		glUniform1f(ambientStrengthUniform, 0.1f);
		glUniform1f(diffuseStrengthUniform, 500.0f);

		//perspective
		unsigned int projectionMatrixLoc = glGetUniformLocation(ShaderReader::shaderPrograms[0], "projectionMatrix");
		glUniformMatrix4fv(projectionMatrixLoc, 1, GL_FALSE, projectionMatrix.values);

		//camera input
		unsigned int viewMatrixLoc = glGetUniformLocation(ShaderReader::shaderPrograms[0], "viewMatrix");
		glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, viewMatrix.values);

		//texture setting
		for (unsigned int i = 0; i < rend->textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0+i);
			glBindTexture(GL_TEXTURE_2D, rend->textures[i]->textureObject);
		}

		glDrawElementsInstanced(GL_TRIANGLES, rend->elementCounter, GL_UNSIGNED_INT, 0, rend->instances);
	}
}

/* This is a placeholder system. TBA proper message system */
void Renderer::updateEntityMatrixOrientation(action action, Entity* target, unsigned int mapping,
	std::vector<unsigned int> offsets, const std::vector<Maths::mat4> data)
{
	unsigned int offsetIndex = 0;
	unsigned int dataIndex = 0;

	switch (action)
	{
	case action::add:
	{
		auto it = target->modelMatrixMap.find(mapping);
		if (it != target->modelMatrixMap.end())
		{
			for (const Maths::mat4& mat : data)
			{
				target->modelMatrixMap[mapping].push_back(mat);
			}
		}
		else
		{
			target->modelMatrixMap.insert(std::make_pair(mapping, data));
		}
	}
	break;
	case action::remove:
	{
		std::vector<Maths::mat4> newVec;
		std::sort(offsets.begin(), offsets.end());
		unsigned int index = 0;
		int j = offsets[0];
		for (int i = 0; i < target->modelMatrixMap[mapping].size(); i++)
		{
			if (i != j)
			{
				newVec.push_back(target->modelMatrixMap[mapping][i]);
			}
			else
			{
				index++;
				if (index < offsets.size())
				{
					j = offsets[index];
				}
			}
		}
		target->modelMatrixMap[mapping] = newVec;
	}
	break;
	case action::swap:
	{
		unsigned int index = 0;
		for (unsigned int i : offsets)
		{
			target->modelMatrixMap[mapping][i] = data[index];
			index++;
		}
	}
	break;
	}

	Model* m = target->models[mapping];
	auto it2 = modelReference.find(m);
	if (it2 != modelReference.end())
	{
		for (SimpleRender* rend : modelReference[m])
		{
			glDeleteBuffers(1, (const GLuint*)&(rend->modelMatrixVBO));
			int attribOffset = 3;
			glBindVertexArray(rend->VAO);
			rend->modelMatrixVBO = createmodelMatrixBuffer(&(target->modelMatrixMap[mapping]), &attribOffset);
			rend->instances = target->modelMatrixMap[mapping].size();
		}
		glBindVertexArray(0);
	}
}