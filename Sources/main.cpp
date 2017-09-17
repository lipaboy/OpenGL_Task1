// vs2010.cpp : Defines the entry point for the console application.
//

//https://www.opengl.org/sdk/docs/man/


#include "task1/task1.h"

using namespace SolarSystem;

const float widthScreen = 512;
const float heightScreen = 512;

float width;
float height;

GLuint vertexShader;
GLuint fragmentShader;
GLuint program;

GLuint attrConstColor;
GLuint bufferPositionSun;
GLuint bufferColorSun;
GLuint bufferPositionEarth;
GLuint bufferColorEarth;
GLuint bufferPositionMoon;
GLuint bufferColorMoon;

Planet sun(0.0f, 0.0f,	//pos
	0.5f,				//edge
	0.5f, 0.5f, 0.0f,	//color RGB
	bufferPositionSun, bufferColorSun); //references to buffers
Planet earth(radiusEarthSun, 0.0f,
	0.2f,
	0.0f, 0.6f, 0.0f,
	bufferPositionEarth, bufferColorEarth);
Planet moon(radiusEarthSun - radiusMoonEarth, 0.0f,
	0.1f,
	0.1f, 0.1f, 0.1f,
	bufferPositionMoon, bufferColorMoon
	);

void InitGeometry() {
	sun.Init();
	earth.Init();
	moon.Init();
}

void Render(void)
{
	glClearColor(0.0f, 0.0f, 0.5f, 1.0f); // Clear the background of our window to red  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear the colour buffer (more buffers later on)
	glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations

	glUseProgram(program);

	// Matrix Projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLdouble)width / (GLdouble)height, 0.01, 100.0);

	// Matrix View
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//gluLookAt(0.0f, 3.0f, 5.0f,	0.0f, 0.0f, 0.0f,	0.0f, 1.0f, 0.0f);

	int k = 3;
	GLfloat radius = 3.0f;
    glm::vec3 eye(0, 3, 1);
	/*static clock_t currTime = clock();
	static GLfloat t = 0;
	//getchar();
	//putchar('a');
	//
	clock_t dt = clock() - currTime;
	if (dt > 1 * 200) {
		t += (double)dt / 200 * PI / 20;
		eye = glm::vec3(radius * cosf(t), radius * sinf(t), k);

		currTime = clock();
		//printf("dsjkfl\a");
	}*/


	glm::mat4x4 matWorld = glm::mat4x4();
	glm::mat4x4 matView = glm::lookAt(eye, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));	//left coord.sys.

	glm::mat4x4 matWorldView = matView * matWorld;

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(&matWorldView[0][0]);

	//wherever i need to paste (init)
	//flEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);

	//clear z-buffer
	glClearDepth(1.0f);
	//square
	{
		sun.draw();
		earth.draw();
		moon.draw();
	}

	glUseProgram(0);

	glFlush(); // Flush the OpenGL buffers to the window  
}

// Calls in loop
void Cycle()
{
	// Вызваем перерисовку экрана (функцию Render)

	solarProcess(sun, earth, moon);
	glutPostRedisplay();
}

// Reshapes the window appropriately
void Reshape(int w, int h)
{
	width = w;
	height = h;

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLdouble)width / (GLdouble)height, 0.01, 100.0);

}

void InitShaders()
{
	//! Исходный код шейдеров
	const char* vsSource =
		//"attribute vec3 coord;\n"
		//"out vec3 fragmentColor;\n"
		"attribute vec4 position;"
		"attribute vec4 color;"
		"uniform vec4 constColor;"
		"void main() {\n"
		//"  gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;\n"
		//"  gl_FrontColor = gl_Color;\n"
		"  gl_Position = gl_ModelViewProjectionMatrix * position;\n"
		"  gl_FrontColor = color * constColor;\n"
		"}\n";
	const char* fsSource =
		//"uniform vec4 color;\n"
		//"in vec3 fragmentColor;\n"
		"void main() {\n"
		//"  gl_FragColor = color;\n"
		"  gl_FragColor = gl_Color;\n"
		//"  gl_FragColor = vec4(fragmentColor, 1.0);\n"
		"}\n";
	int success = 0;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vsSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		const int MAX_INFO_LOG_SIZE = 1024;
		GLchar infoLog[MAX_INFO_LOG_SIZE];
		glGetShaderInfoLog(vertexShader, MAX_INFO_LOG_SIZE, NULL, infoLog);
		fprintf(stderr, "Error in vertex shader compilation!\n");
		fprintf(stderr, "Info log: %s\n", infoLog);
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fsSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		const int MAX_INFO_LOG_SIZE = 1024;
		GLchar infoLog[MAX_INFO_LOG_SIZE];
		glGetShaderInfoLog(fragmentShader, MAX_INFO_LOG_SIZE, NULL, infoLog);
		fprintf(stderr, "Error in vertex shader compilation!\n");
		fprintf(stderr, "Info log: %s\n", infoLog);
	}

	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glBindAttribLocation(program, 0, "position");
	glBindAttribLocation(program, 1, "color");

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		const int MAX_INFO_LOG_SIZE = 1024;
		GLchar infoLog[MAX_INFO_LOG_SIZE];
		glGetProgramInfoLog(program, MAX_INFO_LOG_SIZE, NULL, infoLog);
		fprintf(stderr, "Error in program linkage!\n");
		fprintf(stderr, "Info log: %s\n", infoLog);
	}

	glValidateProgram(program);
	glGetProgramiv(program, GL_VALIDATE_STATUS, &success);
	if (!success)
	{
		const int MAX_INFO_LOG_SIZE = 1024;
		GLchar infoLog[MAX_INFO_LOG_SIZE];
		glGetProgramInfoLog(program, MAX_INFO_LOG_SIZE, NULL, infoLog);
		fprintf(stderr, "Error in program validation!\n");
		fprintf(stderr, "Info log: %s\n", infoLog);
	}

	attrConstColor = glGetUniformLocation(program, "constColor");
}

void DeinitShaders()
{
	glDetachShader(program, vertexShader);
	glDetachShader(program, fragmentShader);

	glDeleteProgram(program);

	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);
}

//int _tmain(int argc, _TCHAR* argv[])
int main(int argc, char* argv[])
{
	glutInit(&argc, argv); // Initialize GLUT  
	glutInitDisplayMode(GLUT_RGBA/* | GLUT_DEPTH | GLUT_DOUBLE*/); // Set up a basic display buffer (only single buffered for now)
																   //glEnable(GL_DEPTH_TEST);
																   // Create the application's window
	{
		glutInitWindowPosition(100, 100);			// Set the position of the window
		glutInitWindowSize(widthScreen, heightScreen);				// Set the width and height of the window
		glutCreateWindow("OpenGL First Window");	// Set the title for the window
	}

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		return 0;
	}

	glutDisplayFunc(Render); // Tell GLUT to use the method "display" for rendering  
	glutReshapeFunc(Reshape);
	glutIdleFunc(Cycle);

	InitGeometry();
	InitShaders();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glCullFace(GL_BACK);

	glutMainLoop(); // Enter GLUT's main loop

					// TODO: Поймать событие закрыти  окна и освободить ресурсы
	DeinitShaders();

	int i = 0;

	return 0;
}
