#include "task1.h"



namespace SolarSystem {


	TPoint getDecartVector(GLfloat radius, GLfloat angle) {
		TPoint vec;

		vec.x = radius * cosf(angle);
		vec.y = radius * sinf(angle);

		return vec;
	}

	inline GLfloat getAngle(TPoint direction) {
		return (equals(direction.x, 0)) ? ((direction.y > 0) ? PI / 2 : -PI / 2)
			: atanf(direction.y / direction.x) + ((direction.x > 0) ? 0 : PI);
	}


	void Planet::convertToArrayVerticesOfSquare() {

		GLfloat halfEdge = edgeLength / 2;

		TPoint vecVertex = getDecartVector(edgeLength / 2 * sqrt(2), getAngle(vecDirection) + PI / 4);

		//first part
		int j = 0;
		vertices[j * 4 + 0] = position.x + vecVertex.x;
		vertices[j * 4 + 1] = position.y + vecVertex.y;
		vertices[j * 4 + 2] = position.z - halfEdge;
		vertices[j * 4 + 3] = 1.0f;
		j = 1;
		vertices[j * 4 + 0] = position.x + vecVertex.x;
		vertices[j * 4 + 1] = position.y + vecVertex.y;
		vertices[j * 4 + 2] = position.z + halfEdge;
		vertices[j * 4 + 3] = 1.0f;
		j = 2;
		vertices[j * 4 + 0] = position.x + vecVertex.y;
		vertices[j * 4 + 1] = position.y - vecVertex.x;
		vertices[j * 4 + 2] = position.z - halfEdge;
		vertices[j * 4 + 3] = 1.0f;
		j = 3;
		vertices[j * 4 + 0] = position.x + vecVertex.y;
		vertices[j * 4 + 1] = position.y - vecVertex.x;
		vertices[j * 4 + 2] = position.z + halfEdge;
		vertices[j * 4 + 3] = 1.0f;
		j = 4;
		vertices[j * 4 + 0] = position.x - vecVertex.x;
		vertices[j * 4 + 1] = position.y - vecVertex.y;
		vertices[j * 4 + 2] = position.z - halfEdge;
		vertices[j * 4 + 3] = 1.0f;
		j = 5;
		vertices[j * 4 + 0] = position.x - vecVertex.x;
		vertices[j * 4 + 1] = position.y - vecVertex.y;
		vertices[j * 4 + 2] = position.z + halfEdge;
		vertices[j * 4 + 3] = 1.0f;
		j = 6;
		vertices[j * 4 + 0] = position.x - vecVertex.y;
		vertices[j * 4 + 1] = position.y + vecVertex.x;
		vertices[j * 4 + 2] = position.z - halfEdge;
		vertices[j * 4 + 3] = 1.0f;
		j = 7;
		vertices[j * 4 + 0] = position.x - vecVertex.y;
		vertices[j * 4 + 1] = position.y + vecVertex.x;
		vertices[j * 4 + 2] = position.z + halfEdge;
		vertices[j * 4 + 3] = 1.0f;

		int i = 1;
		//second part
		j = 4;
		vertices[32 + j * 4 + 0] = position.x + vecVertex.x;
		vertices[32 + j * 4 + 1] = position.y + vecVertex.y;
		vertices[32 + j * 4 + 2] = position.z - halfEdge;
		vertices[32 + j * 4 + 3] = 1.0f;
		j = 2;
		vertices[32 + j * 4 + 0] = position.x + vecVertex.x;
		vertices[32 + j * 4 + 1] = position.y + vecVertex.y;
		vertices[32 + j * 4 + 2] = position.z + halfEdge;
		vertices[32 + j * 4 + 3] = 1.0f;
		j = 6;
		vertices[32 + j * 4 + 0] = position.x + vecVertex.y;
		vertices[32 + j * 4 + 1] = position.y - vecVertex.x;
		vertices[32 + j * 4 + 2] = position.z - halfEdge;
		vertices[32 + j * 4 + 3] = 1.0f;
		j = 0;
		vertices[32 + j * 4 + 0] = position.x + vecVertex.y;
		vertices[32 + j * 4 + 1] = position.y - vecVertex.x;
		vertices[32 + j * 4 + 2] = position.z + halfEdge;
		vertices[32 + j * 4 + 3] = 1.0f;
		j = 7;
		vertices[32 + j * 4 + 0] = position.x - vecVertex.x;
		vertices[32 + j * 4 + 1] = position.y - vecVertex.y;
		vertices[32 + j * 4 + 2] = position.z - halfEdge;
		vertices[32 + j * 4 + 3] = 1.0f;
		j = 1;
		vertices[32 + j * 4 + 0] = position.x - vecVertex.x;
		vertices[32 + j * 4 + 1] = position.y - vecVertex.y;
		vertices[32 + j * 4 + 2] = position.z + halfEdge;
		vertices[32 + j * 4 + 3] = 1.0f;
		j = 5;
		vertices[32 + j * 4 + 0] = position.x - vecVertex.y;
		vertices[32 + j * 4 + 1] = position.y + vecVertex.x;
		vertices[32 + j * 4 + 2] = position.z - halfEdge;
		vertices[32 + j * 4 + 3] = 1.0f;
		j = 3;
		vertices[32 + j * 4 + 0] = position.x - vecVertex.y;
		vertices[32 + j * 4 + 1] = position.y + vecVertex.x;
		vertices[32 + j * 4 + 2] = position.z + halfEdge;
		vertices[32 + j * 4 + 3] = 1.0f;

		glGenBuffers(1, &bufferPosition);
		glBindBuffer(GL_ARRAY_BUFFER, bufferPosition);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	}

	Planet::Planet(GLfloat posX, GLfloat posY, GLfloat edge, GLfloat a, GLfloat b, GLfloat c,
		GLuint &bufPos, GLuint &bufCol) : bufferPosition(bufPos), bufferColor(bufCol) {
		position.x = posX;
		position.y = posY;
		position.z = 0.0f;
		vecDirection.x = 1.0f;
		vecDirection.y = 0.0f;
		vecDirection.z = 0.0f;
		edgeLength = edge;
//		for (int i = 0; i < COUNT_VERTICES; i++)
//		{
//			colors[i * 4 + 0] = a;
//			colors[i * 4 + 1] = b;
//			colors[i * 4 + 2] = c;
//			colors[i * 4 + 3] = 1.0f;
//		}
            // another color scheme
        for (int i = 0; i < 4;i++) {
		colors[i * 4 + 0] = a;
		colors[i * 4 + 1] = 0;
		colors[i * 4 + 2] = 0;
		colors[i * 4 + 3] = 1.0f;
		}
		for (int i = 4; i < 6; i++) {
		colors[i * 4 + 0] = a;
		colors[i * 4 + 1] = b;
		colors[i * 4 + 2] = 0;
		colors[i * 4 + 3] = 1.0f;
		}
		for (int i = 6; i < 8; i++) {
		colors[i * 4 + 0] = 0;
		colors[i * 4 + 1] = b;
		colors[i * 4 + 2] = 0;
		colors[i * 4 + 3] = 1.0f;
		}
		for (int i = 8; i < 12; i++) {
		colors[i * 4 + 0] = a / 2;
		colors[i * 4 + 1] = 0;
		colors[i * 4 + 2] = 0;
		colors[i * 4 + 3] = 1.0f;
		}
		for (int i = 12; i < 14; i++) {
		colors[i * 4 + 0] = a / 2;
		colors[i * 4 + 1] = b / 2;
		colors[i * 4 + 2] = 0;
		colors[i * 4 + 3] = 1.0f;
		}
		for (int i = 14; i < 16; i++) {
		colors[i * 4 + 0] = 0;
		colors[i * 4 + 1] = b / 2;
		colors[i * 4 + 2] = 0;
		colors[i * 4 + 3] = 1.0f;
        }
	}

	void Planet::Init() {
		convertToArrayVerticesOfSquare();

		glGenBuffers(1, &bufferColor);
		glBindBuffer(GL_ARRAY_BUFFER, bufferColor);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	}

	void Planet::draw() const {
		glUniform4f(attrConstColor, 3, 3, 3, 1);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, bufferPosition);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, bufferColor);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

		glDrawArrays(GL_QUAD_STRIP, 0, 4 * Planet::COUNT_VERTICES);

		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(0);
	}

	void Planet::rotate(GLfloat angleRot) {
		GLfloat currentAngle = getAngle(vecDirection);
		GLfloat newAngle = modff((currentAngle + angleRot) / (2.0f * PI), &currentAngle);

		vecDirection = getDecartVector(1.0f,
			//(newAngle < 0) ? (newAngle + 0.5f) * PI : 
			newAngle * 2.0f * PI);
		convertToArrayVerticesOfSquare();
	}

	void Planet::setNewPosition(TPoint newPos) {
		position = newPos;
		convertToArrayVerticesOfSquare();
	}

	TPoint moveCircular(TPoint startDirection, TPoint center, GLfloat radius, GLfloat t) {
		GLfloat angle0 = getAngle(startDirection);
		TPoint newPos = getDecartVector(radius, angle0 + t);

		newPos.x += center.x;
		newPos.y += center.y;

		return newPos;
	}

	/*static TPoint posE{ 0, 0 },
	posE2;*/

	TPoint transitToNewCoordinateSystem(TPoint oldPoint, TPoint oldOrigin, TPoint newOrigin, GLfloat angle) {
		TPoint newPoint;
		GLfloat &X = oldPoint.x,
			&Y = oldPoint.y;

		newPoint.x = (-oldOrigin.x + newOrigin.x) + X * cosf(angle) - Y * sinf(angle);
		newPoint.y = (-oldOrigin.y + newOrigin.y) + X * sinf(angle) + Y * cosf(angle);

		/*posE2 = newPoint;
		if (pow(posE.x - posE2.x, 2) + pow(posE.y - posE2.y, 2) > 1.0f) {
		//cout << "oops" << endl;
		}*/

		return newPoint;
	}

	void solarProcess(Planet sun, Planet earth, Planet moon) {
//		static clock_t start_t = clock(),
//			end_t;
        using namespace std::chrono;
        static steady_clock::time_point start_t = steady_clock::now(),
                end_t;
		static GLfloat angleRot = 0;
		const GLfloat dt = 0.005;
        static GLfloat total_t = 0;
		//posE = earth.getPosition();

        end_t = steady_clock::now();
        //return;
        if (dt < (double)duration_cast<milliseconds>(end_t - start_t).count() / 1e3) {
			angleRot += PI / 340;       //speed of rotaion
			sun.rotate(angleRot);
			earth.rotate(-angleRot);
			moon.rotate(angleRot);

            total_t += (double)duration_cast<milliseconds>(end_t - start_t).count()  / 1e3;

			earth.setNewPosition(
				transitToNewCoordinateSystem(
					moveCircular(earth.getPosition(), TPoint(0.0f, 0.0f, 0.0f), radiusEarthSun, total_t),
					TPoint(0.0f, 0.0f, 0.0f),
					sun.getPosition(),
					getAngle(sun.getDirection())
					)
				);

			moon.setNewPosition(
				transitToNewCoordinateSystem(
					moveCircular(moon.getPosition(), TPoint(0.0f, 0.0f, 0.0f), radiusMoonEarth, 7 * total_t),
					TPoint(0.0f, 0.0f, 0.0f),
					earth.getPosition(),
					getAngle(earth.getDirection())
					)
				);

			/*posE2 = earth.getPosition();

			if (pow(posE.x - posE2.x, 2) + pow(posE.y - posE2.y, 2) > 1.0f) {
			cout << "oops" << endl;
			}
			posE = earth.getPosition();*/

			start_t = end_t;
		}

	}

}
