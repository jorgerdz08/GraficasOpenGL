/*
 * Utils.cpp
 *
 *  Created on: 16/01/2014
 *      Author: Iván
 */

#include "Utils.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

string Utils::loadShader(const char* filename) {
	string contents;
    ifstream stream(filename);

    if(stream.is_open()) {
    	string line = "";
        while(getline(stream, line)) {
        	contents += line + "\n";
        }
        stream.close();
    } else {
    	return "No se pudo leer el archivo";
    }
    return contents;
}

GLuint Utils::compileShader(const char* filename, GLuint shaderType) {
	string source_str = loadShader(filename);
	char const *source = source_str.c_str();
	GLuint shaderId = glCreateShader(shaderType);
	glShaderSource(shaderId, 1, &source, NULL);
	glCompileShader(shaderId);
	return shaderId;
}

bool Utils::shaderCompiled(GLuint shaderId) {
	GLint params;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &params);
	if(params == 1) return true;

	GLint maxLength = 0;
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);
	vector<GLchar> errors(maxLength);
	glGetShaderInfoLog(shaderId, maxLength, &maxLength, &errors[0]);
	vector<GLchar>::iterator iterador = errors.begin();
	while(iterador != errors.end()) {
		GLchar valor = *iterador;
	    cout << valor;
	    iterador ++;
	}
	return false;
}

bool Utils::loadBMP(const char* filename, unsigned char **pdata, unsigned int &width, unsigned int &height) {
      unsigned char header[54];
      FILE * file = fopen(filename, "rb");
      fread(header, 1, 54, file);
      if(header[0] != 'B' || header[1] != 'M' ) {
          printf("Not a correct BMP file\n");
          return false;
      }

      unsigned char *bytePointerW      = &(header[0x12]);
      unsigned int  *fourBytesPointerW = (unsigned int*) bytePointerW;
      width = *fourBytesPointerW;
      unsigned char *bytePointerH      = &(header[0x16]);
      unsigned int  *fourBytesPointerH = (unsigned int*) bytePointerH;
      height = *fourBytesPointerH;
      *pdata = new unsigned char[width * height * 3];
      fread(*pdata, 1, width * height * 3, file);
      fclose(file);
      return true;
}


GLuint Utils::loadTeapot(const char* filename, GLuint vpLoc, GLuint tcLoc) {
	float *positions, *texcoords;
	unsigned int *indexes;
	int max_positions, max_normals, max_triangles;
	ifstream teapotFile("Teapot.txt");
   	string token = "";
   	// Read vertex Positions
    teapotFile >> token;  // Read v
    teapotFile >> token;  // Read 530
    stringstream ss1(token);
    ss1 >> max_positions;
    positions = new float[3 * max_positions];
       for(int i = 0; i < 3 * max_positions; i ++) {
       	teapotFile >> token;
       	stringstream ss(token);
       	ss >> positions[i];
    }

   	// Read vertex normals (Se ignoran las normales en esta aplicación)
    teapotFile >> token;  // Read n
    teapotFile >> token;  // Read 530
    stringstream ss2(token);
    ss2 >> max_normals;
    for(int i = 0; i < 3 * max_normals; i ++) teapotFile >> token;

   	// Read indexes
    teapotFile >> token;  // Read i
    teapotFile >> token;  // Read 1024
    stringstream ss3(token);
    ss3 >> max_triangles;
    indexes = new unsigned int[3 * max_triangles];
    for(int i = 0; i < 3 * max_triangles; i ++) {
    	teapotFile >> token;
    	stringstream ss(token);
    	ss >> indexes[i];
    }

    texcoords = new float[2 * max_positions];
    for(int i = 0; i < max_positions; i += 2) {
    	texcoords[i] = 0;
    	texcoords[i + 1] = 0;
    }

    GLuint vaId, bufferId[3];
	glGenVertexArrays(1, &vaId);
    glBindVertexArray(vaId);
	glGenBuffers(3, bufferId);

	glBindBuffer(GL_ARRAY_BUFFER, bufferId[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
    glVertexAttribPointer(vpLoc, 3, GL_FLOAT, 0, 0, 0);
    glEnableVertexAttribArray(vpLoc);

    glBindBuffer(GL_ARRAY_BUFFER, bufferId[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texcoords), texcoords, GL_STATIC_DRAW);
    glVertexAttribPointer(tcLoc, 2, GL_FLOAT, 0, 0, 0);
    glEnableVertexAttribArray(tcLoc);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);

    delete[] positions;
    delete[] indexes;
    delete[] texcoords;
    teapotFile.close();
    return vaId;
}
