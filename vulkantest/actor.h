#pragma once
#include"includes.h"



class actor
{
public:

	void addVertices(std::vector<Vertex> &_vertices)
	{
		
		if (!this->vertices.empty())
		{
			size_t vert_size = _vertices.size();
			bool hasIndices = false;
			if (!indices.empty())
			{
				hasIndices = true;
			}
			for (size_t i = 0; i < this->vertices.size(); i++)
			{
				_vertices.push_back(vertices.at(i));
				if (hasIndices)
				{
					
				}
			}
			
		}
		return;
	}
	std::vector<Vertex> vertices = {};
	std::vector<uint32_t> indices = {};
	std::vector<Vertex> debug_relative_vertices = {};
	glm::vec3 location;
	std::vector<Vertex> getActorOnScreenLocation(int screenHeight, int screenWidth)
	{
		if (screenHeight == 0 || screenWidth == 0) { throw std::runtime_error("screen data value was 0"); }
		if (vertices.empty()) { throw std::runtime_error("vertex data is emrty"); }

		glm::vec3 relativePos = {};
		relativePos.x = location.x / screenWidth;
		relativePos.y = location.y / screenHeight;
		relativePos.z = location.z;
		std::vector<Vertex> result;
		/*result.push_back({ { relativePos.x,relativePos.y },this->vertices[0].color });
		if (vertices.size() == 1) { return result; }*/

	
		for (size_t i = 0; i < this->vertices.size(); i++)
		{
			result.push_back({ relativePos + vertices[i].pos,vertices[i].color });
		}
		debug_relative_vertices = result;
		return result;
	}
	actor(std::vector<Vertex> &vertices, std::vector<uint32_t> indices);
	/*actor(std::vector<Vertex> &vertices, std::vector<uint32_t> &indices, glm::vec3 location)
	{
		this->vertices = vertices;
		this->indices = indices;
		this->location = location;
	}*/
	actor(std::vector<Vertex> vertices, std::vector<uint32_t> indices, glm::vec3 location)
	{
		this->vertices = vertices;
		this->indices = indices;
		this->location = location;
	}
	~actor();
};

//emrty class. needed for creating child classes
class Base
{
protected :
	virtual void overload(){}
public:
	Base(){}

};

class Actor:public Base
{
public:
	glm::vec3 location;
	std::vector<Base*>Attachments = {};
	Actor()
	{
		location.x = 0;
		location.y = 0;
		location.z = 0;
	}
	Actor(glm::vec3 location)
	{
		this->location = location;
	}
	~Actor()
	{

	}
};

class Mesh:public Base
{
private:
	std::vector<Vertex> debug_relative_vertices = {};
	std::vector<Vertex> relative_vertices = {};
public:
	std::vector<Vertex> vertices = {};
	std::vector<uint32_t> indices = {};
	VkImage texture;
	VkImageView textureView;
	VkDeviceMemory textureMemory;
	BufferInfo vertexBufferInfo;
	BufferInfo indexBufferInfo;
	std::string texturePath;

	/*std::vector<VkDescriptorImageInfo> imageInfos;*/

	
	Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices)
	{
		this->vertices = vertices;
		this->indices = indices;
	}
	std::vector<Vertex> getComponentOnScreenLocation(int screenHeight, int screenWidth, Actor*&ParentActor)
	{
		if (screenHeight == 0 || screenWidth == 0) { throw std::runtime_error("screen data value was 0"); }
		if (vertices.empty()) { throw std::runtime_error("vertex data is emrty"); }

		glm::vec3 relativePos = {};
		relativePos.x = ParentActor->location.x / screenWidth;
		relativePos.y = ParentActor->location.y / screenHeight;
		relativePos.z = ParentActor->location.z;
		
		relative_vertices.clear();
		for (size_t i = 0; i < this->vertices.size(); i++)
		{
			relative_vertices.push_back({ relativePos + vertices[i].pos,vertices[i].color,vertices[i].texCoord });
		}

		debug_relative_vertices = relative_vertices;
		return relative_vertices;
	}
	~Mesh()
	{
		vertices.~vector();
		indices.~vector();
	}
};
