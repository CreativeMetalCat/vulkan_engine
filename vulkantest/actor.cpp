#include "actor.h"



actor::actor(std::vector<Vertex> &vertices, std::vector<uint32_t> indices)
{
	this->vertices = vertices;
	this->indices = indices;
	this->location = location;
}


actor::~actor()
{
	this->debug_relative_vertices.~vector();
	this->vertices.~vector();
	this->indices.~vector();
}
