#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>      
#include <assimp/postprocess.h>     
#include <assimp/cimport.h>
#include<GL/freeglut.h>
#include <string>
#include <map>
#include <iostream>
#include <glm.hpp>
class Loader
{
	static Loader* loader;
	std::map<std::string, GLuint> loadedOBJS;
	std::map<std::string, const aiScene*> loadedOBJS2;
	Assimp::Importer* importer;
	Loader();

	void recursive_render(const aiScene* sc, const aiNode* nd);
	void apply_material(const aiMaterial* mtl);
	void set_float4(float f[4], float a, float b, float c, float d);
	void color4_to_float4(const aiColor4D* c, float f[4]);
public:
	void loadOBJ(std::string path, std::string nume);
	void draw(std::string nume);
	static Loader* getInstance();

};

