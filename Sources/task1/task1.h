#ifndef TASK1_H
#define TASK1_H

#include "../stdafx.h"
#include "GL/glew.h" // Include the GLEW header file
#include "GL/glut.h" // Include the GLUT header file
#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"

#include <chrono>

using namespace std;

const GLfloat PI = 3.141592653589793238463;
extern GLuint attrConstColor;

namespace SolarSystem {

	const GLfloat radiusEarthSun = 1.4f;
	const GLfloat radiusMoonEarth = 0.5f;

	inline bool equals(GLfloat a, GLfloat b) { return (abs(a - b) < 1e-5) ? true : false; }

	class TPoint {
	public:
		GLfloat x, y, z;

		TPoint() : x(0.0f), y(0.0f), z(0.0f) {}
		TPoint(GLfloat xx, GLfloat yy, GLfloat zz) : x(xx), y(yy), z(zz) {}
	};

	class Planet {
	public:
		static const int COUNT_VERTICES = 8 * 2;
	private:

		GLfloat vertices[4 * COUNT_VERTICES];
		GLfloat colors[4 * COUNT_VERTICES];

		TPoint position;
		TPoint vecDirection;
		GLfloat edgeLength;

		GLuint &bufferPosition;
		GLuint &bufferColor;

	public:
		Planet(GLfloat posX, GLfloat posY, GLfloat edge, GLfloat a, GLfloat b, GLfloat c,
			GLuint &bufPos, GLuint &bufCol);
		void Init();

		//GLuint getBufferPosition() { return bufferPosition; }
		//GLuint getBufferColor() { return bufferColor; }
		void rotate(GLfloat angleRot);
		void setNewPosition(TPoint newPos);

		void draw() const;
		TPoint getPosition() const { return position; }
		TPoint getDirection() const { return vecDirection; }

	protected:
		void convertToArrayVerticesOfSquare();
	};

	void solarProcess(Planet sun, Planet earth, Planet moon);

}

#endif
