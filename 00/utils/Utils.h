/*
 * Utils.h
 *
 *  Created on: 16/01/2014
 *      Author: Iván
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <GL/glew.h>
#include <string>

class Utils {
public:
	static std::string loadShader(const char* filename);
	static GLuint compileShader(const char* filename, GLuint shaderType);
	static bool shaderCompiled(GLuint shaderId);
	static bool loadBMP(const char* filename, unsigned char **pdata, unsigned int &width, unsigned int &height);
	static GLuint loadTeapot(const char* filename, GLuint vpLoc, GLuint tcLoc);
};

#endif /* UTILS_H_ */
