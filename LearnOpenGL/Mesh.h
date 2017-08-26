#ifndef MESH_H
#define MESH_H
#include <glad/glad.h> // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <sstream>
#include "Shader.h"

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	unsigned int id;
	std::string type;
};

class Mesh {
public:
	/*  Mesh Data  */
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	/*  Functions  */
	Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, std::vector<Texture> &textures);
	void Draw(Shader shader);
private:
	/*  Render data  */
	unsigned int VAO, VBO, EBO;
	/*  Functions    */
	void setupMesh();
};
#endif