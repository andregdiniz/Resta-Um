/*
	Código Importado:
		https://www.keithlantz.net/2011/10/a-preliminary-wavefront-obj-loader-in-c/
*/

#include "obj.h"


cObj::cObj(std::string filename) {
	carregar_objeto(filename);
}

cObj::~cObj() {
	vertices.clear();
	texcoords.clear();
	normals.clear();
	parameters.clear();
	faces.clear();
	glDeleteLists(list, 1);
}

void cObj::carregar_objeto(std::string filename)
{
	std::ifstream ifs(filename.c_str(), std::ifstream::in);
	std::string line, key;
	while (ifs.good() && !ifs.eof() && std::getline(ifs, line)) {
		key = "";
		std::stringstream stringstream(line);
		stringstream >> key >> std::ws;
		
		if (key == "v") { // vertex
			vertex v; float x;
			while (!stringstream.eof()) {
				stringstream >> x >> std::ws;
				v.v.push_back(x);
			}
			vertices.push_back(v);
		} else if (key == "vp") { // parameter
			vertex v; float x;
			while (!stringstream.eof()) {
				stringstream >> x >> std::ws;
				v.v.push_back(x);
			}
			parameters.push_back(v);
		} else if (key == "vt") { // texture coordinate
			vertex v; float x;
			while (!stringstream.eof()) {
				stringstream >> x >> std::ws;
				v.v.push_back(x);
			}
			texcoords.push_back(v);
		} else if (key == "vn") { // normal
			vertex v; float x;
			while (!stringstream.eof()) {
				stringstream >> x >> std::ws;
				v.v.push_back(x);
			}
			v.normalize();
			normals.push_back(v);
		} else if (key == "f") { // face
			face f; int v, t, n;
			while (!stringstream.eof()) {
				stringstream >> v >> std::ws;
				f.vertex.push_back(v-1);
				if (stringstream.peek() == '/') {
					stringstream.get();
					if (stringstream.peek() == '/') {
						stringstream.get();
						stringstream >> n >> std::ws;
						f.normal.push_back(n-1);
					} else {
						stringstream >> t >> std::ws;
						f.texture.push_back(t-1);
						if (stringstream.peek() == '/') {
							stringstream.get();
							stringstream >> n >> std::ws;
							f.normal.push_back(n-1);
						}
					}
				}
			}
			faces.push_back(f);
		} else {

		}
	}
	ifs.close();
	/*
	std::cout << "               Name: " << filename << std::endl;
	std::cout << "           Vertices: " << number_format(vertices.size()) << std::endl;
	std::cout << "         Parameters: " << number_format(parameters.size()) << std::endl;
	std::cout << "Texture Coordinates: " << number_format(texcoords.size()) << std::endl;
	std::cout << "            Normals: " << number_format(normals.size()) << std::endl;
	std::cout << "              Faces: " << number_format(faces.size()) << std::endl << std::endl;
	*/
	list = glGenLists(1);
}

/*
	Fonte : opengltutorials
*/

GLuint cObj::LoadDDS(){

	unsigned char header[124];

	FILE *fp; 

	/* try to open the file */ 
	char  *  imagepath = new char [local_texture.length()+1];
	std::strcpy(imagepath, local_texture.c_str());
	fp = fopen(imagepath, "rb"); 
	if (fp == NULL){
		printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", imagepath);
		return 0;
	}
   
	/* verify the type of file */ 
	char filecode[4]; 
	fread(filecode, 1, 4, fp); 
	if (std::strncmp(filecode, "DDS ", 4) != 0) { 
		fclose(fp); 
		return 0; 
	}
	
	/* get the surface desc */ 
	fread(&header, 124, 1, fp); 

	unsigned int height      = *(unsigned int*)&(header[8 ]);
	unsigned int width	     = *(unsigned int*)&(header[12]);
	unsigned int linearSize	 = *(unsigned int*)&(header[16]);
	unsigned int mipMapCount = *(unsigned int*)&(header[24]);
	unsigned int fourCC      = *(unsigned int*)&(header[80]);

 
	unsigned char * buffer;
	unsigned int bufsize;
	/* how big is it going to be including all mipmaps? */ 
	bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize; 
	buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char)); 
	fread(buffer, 1, bufsize, fp); 
	/* close the file pointer */ 
	fclose(fp);

	unsigned int components  = (fourCC == FOURCC_DXT1) ? 3 : 4; 
	unsigned int format;
	switch(fourCC) 
	{ 
	case FOURCC_DXT1: 
		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT; 
		break; 
	case FOURCC_DXT3: 
		format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT; 
		break; 
	case FOURCC_DXT5: 
		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT; 
		break; 
	default: 
		free(buffer); 
		return 0; 
	}

	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT,4);	
	
	unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16; 
	unsigned int offset = 0;

	/* load the mipmaps */ 
	for (unsigned int level = 0; level < mipMapCount && (width || height); ++level) 
	{ 
		unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize; 
		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,  
			0, size, buffer + offset); 
	 
		offset += size; 
		width  /= 2; 
		height /= 2; 

		// Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
		if(width < 1) width = 1;
		if(height < 1) height = 1;

	} 

	free(buffer); 

	return textureID;


}

void cObj::carregar_textura(std::string textura)
{
	this->local_texture = textura;
	
}

void cObj::compileList() {
	glNewList(list, GL_COMPILE);

	for (int i = 0; i < faces.size(); i++) {
		if (faces[i].vertex.size() == 3) { // triangle
			if (faces[i].normal.size() == 3) { // with normals and texture
				glBegin(GL_TRIANGLES);
				//textura - desenho 
				glTexCoord2f(texcoords[faces[i].texture[0]].v[0], texcoords[faces[i].texture[0]].v[1]);
				glNormal3f(normals[faces[i].normal[0]].v[0], normals[faces[i].normal[0]].v[1], normals[faces[i].normal[0]].v[2]);
				glVertex3f(vertices[faces[i].vertex[0]].v[0], vertices[faces[i].vertex[0]].v[1], vertices[faces[i].vertex[0]].v[2]);
				glTexCoord2f(texcoords[faces[i].texture[1]].v[0], texcoords[faces[i].texture[1]].v[1]);
				glNormal3f(normals[faces[i].normal[1]].v[0], normals[faces[i].normal[1]].v[1], normals[faces[i].normal[1]].v[2]);
				glVertex3f(vertices[faces[i].vertex[1]].v[0], vertices[faces[i].vertex[1]].v[1], vertices[faces[i].vertex[1]].v[2]);
				glTexCoord2f(texcoords[faces[i].texture[2]].v[0], texcoords[faces[i].texture[2]].v[1]);
				glNormal3f(normals[faces[i].normal[2]].v[0], normals[faces[i].normal[2]].v[1], normals[faces[i].normal[2]].v[2]);
				glVertex3f(vertices[faces[i].vertex[2]].v[0], vertices[faces[i].vertex[2]].v[1], vertices[faces[i].vertex[2]].v[2]);
				glEnd();
			} else { // without normals -- evaluate normal on quad
				vertex v = (vertices[faces[i].vertex[1]] - vertices[faces[i].vertex[0]]).cross(vertices[faces[i].vertex[2]] - vertices[faces[i].vertex[0]]);
				v.normalize();
				glBegin(GL_TRIANGLES);
				glNormal3f(v.v[0], v.v[1], v.v[2]);
				glTexCoord2f(texcoords[faces[i].texture[0]].v[0], texcoords[faces[i].texture[0]].v[1]);
				glVertex3f(vertices[faces[i].vertex[0]].v[0], vertices[faces[i].vertex[0]].v[1], vertices[faces[i].vertex[0]].v[2]);
				glTexCoord2f(texcoords[faces[i].texture[1]].v[0], texcoords[faces[i].texture[1]].v[1]);
				glVertex3f(vertices[faces[i].vertex[1]].v[0], vertices[faces[i].vertex[1]].v[1], vertices[faces[i].vertex[1]].v[2]);
				glTexCoord2f(texcoords[faces[i].texture[2]].v[0], texcoords[faces[i].texture[2]].v[1]);
				glVertex3f(vertices[faces[i].vertex[2]].v[0], vertices[faces[i].vertex[2]].v[1], vertices[faces[i].vertex[2]].v[2]);
				glEnd();
			}
		} else if (faces[i].vertex.size() == 4) { // quad
			if (faces[i].normal.size() == 4) { // with normals and texture
				glBegin(GL_QUADS);
				glTexCoord2f(texcoords[faces[i].texture[0]].v[0], texcoords[faces[i].texture[0]].v[1]);
				glNormal3f(normals[faces[i].normal[0]].v[0], normals[faces[i].normal[0]].v[1], normals[faces[i].normal[0]].v[2]);
				glVertex3f(vertices[faces[i].vertex[0]].v[0], vertices[faces[i].vertex[0]].v[1], vertices[faces[i].vertex[0]].v[2]);
				glTexCoord2f(texcoords[faces[i].texture[1]].v[0], texcoords[faces[i].texture[1]].v[1]);
				glNormal3f(normals[faces[i].normal[1]].v[0], normals[faces[i].normal[1]].v[1], normals[faces[i].normal[1]].v[2]);
				glVertex3f(vertices[faces[i].vertex[1]].v[0], vertices[faces[i].vertex[1]].v[1], vertices[faces[i].vertex[1]].v[2]);
				glTexCoord2f(texcoords[faces[i].texture[2]].v[0], texcoords[faces[i].texture[2]].v[1]);
				glNormal3f(normals[faces[i].normal[2]].v[0], normals[faces[i].normal[2]].v[1], normals[faces[i].normal[2]].v[2]);
				glVertex3f(vertices[faces[i].vertex[2]].v[0], vertices[faces[i].vertex[2]].v[1], vertices[faces[i].vertex[2]].v[2]);
				glTexCoord2f(texcoords[faces[i].texture[3]].v[0], texcoords[faces[i].texture[3]].v[1]);
				glNormal3f(normals[faces[i].normal[3]].v[0], normals[faces[i].normal[3]].v[1], normals[faces[i].normal[3]].v[2]);
				glVertex3f(vertices[faces[i].vertex[3]].v[0], vertices[faces[i].vertex[3]].v[1], vertices[faces[i].vertex[3]].v[2]);
				glEnd();
			} else { // without normals -- evaluate normal on quad
				vertex v = (vertices[faces[i].vertex[1]] - vertices[faces[i].vertex[0]]).cross(vertices[faces[i].vertex[2]] - vertices[faces[i].vertex[0]]);
				v.normalize();
				glBegin(GL_QUADS);
				glNormal3f(v.v[0], v.v[1], v.v[2]);
				glTexCoord2f(texcoords[faces[i].texture[0]].v[0], texcoords[faces[i].texture[0]].v[1]);
				glVertex3f(vertices[faces[i].vertex[0]].v[0], vertices[faces[i].vertex[0]].v[1], vertices[faces[i].vertex[0]].v[2]);
				glTexCoord2f(texcoords[faces[i].texture[1]].v[0], texcoords[faces[i].texture[1]].v[1]);
				glVertex3f(vertices[faces[i].vertex[1]].v[0], vertices[faces[i].vertex[1]].v[1], vertices[faces[i].vertex[1]].v[2]);
				glTexCoord2f(texcoords[faces[i].texture[2]].v[0], texcoords[faces[i].texture[2]].v[1]);
				glVertex3f(vertices[faces[i].vertex[2]].v[0], vertices[faces[i].vertex[2]].v[1], vertices[faces[i].vertex[2]].v[2]);
				glTexCoord2f(texcoords[faces[i].texture[3]].v[0], texcoords[faces[i].texture[3]].v[1]);
				glVertex3f(vertices[faces[i].vertex[3]].v[0], vertices[faces[i].vertex[3]].v[1], vertices[faces[i].vertex[3]].v[2]);
				glEnd();
			}
		}
	}
	glEndList();
}

void cObj::render() {

	this->texture[0] = cObj::LoadDDS();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_3D, texture[0]);
	glEnable(GL_TEXTURE_2D); 
	//glShadeModel(GL_FLAT); 

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	glCallList(list);
	compileList();

	glDeleteLists(list, 1);
	glFlush();
	glDeleteTextures(1, texture);
}
