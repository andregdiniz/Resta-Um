/*

	Código Importado:
		https://www.keithlantz.net/2011/10/a-preliminary-wavefront-obj-loader-in-c/

*/

#ifndef OBJ_H
#define OBJ_H

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include "misc.h"

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

struct vertex {
	std::vector<float> v;
	void normalize() {
		float magnitude = 0.0f;
		for (int i = 0; i < v.size(); i++)
			magnitude += pow(v[i], 2.0f);
		magnitude = sqrt(magnitude);
		for (int i = 0; i < v.size(); i++)
			v[i] /= magnitude;
	}
	vertex operator-(vertex v2) {
		vertex v3;
		if (v.size() != v2.v.size()) {
			v3.v.push_back(0.0f);
			v3.v.push_back(0.0f);
			v3.v.push_back(0.0f);
		} else {
			for (int i = 0; i < v.size(); i++)
				v3.v.push_back(v[i] - v2.v[i]);
		}
		return v3;
	}
	vertex cross(vertex v2) {
		vertex v3;
		if (v.size() != 3 || v2.v.size() != 3) {
			v3.v.push_back(0.0f);
			v3.v.push_back(0.0f);
			v3.v.push_back(0.0f);
		} else {
			v3.v.push_back(v[1]*v2.v[2]-v[2]*v2.v[1]);
			v3.v.push_back(v[2]*v2.v[0]-v[0]*v2.v[2]);
			v3.v.push_back(v[0]*v2.v[1]-v[1]*v2.v[0]);
		}
		return v3;
	}
};

struct face {
	std::vector<int> vertex;
	std::vector<int> texture;
	std::vector<int> normal;
};

class cObj {
  protected:
	std::vector<vertex> vertices;
	std::vector<vertex> texcoords;
	std::vector<vertex> normals;
	std::vector<vertex> parameters;
	std::vector<face> faces;
	GLuint list;

	GLuint texture[1];
	std::string local_texture;
	std::string sel_texture;
	//carrega a primeira textura e depois nao carrega mais

  public:
  	cObj(){};
	cObj(std::string filename);
	~cObj();
	
	//carrega textura no objeto desejado
	GLuint LoadDDS();
	void carregar_objeto(std::string filename);
	void carregar_textura(std::string textura);
	void compileList();
	void render();
};

#endif