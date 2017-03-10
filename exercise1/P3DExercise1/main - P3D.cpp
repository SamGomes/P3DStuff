///////////////////////////////////////////////////////////////////////
//
// P3D Course
// (c) 2016 by JoÃ£o Madeiras Pereira
// TEMPLATE: Whitted Ray Tracing NFF scenes and drawing points with Modern OpenGL
//
//You should develop your rayTracing( Ray ray, int depth, float RefrIndex) which returns a color and
// to develop your load_NFF function
//
///////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include"glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtx\vector_angle.hpp"
#include "scene.h"
#include "color.h"
#include "ray.h"
#include "object.h"

#define CAPTION "ray tracer"

#define M_PI 3.14159265358979323846
#define VERTEX_COORD_ATTRIB 0
#define COLOR_ATTRIB 1

#define EPSILON 0.0001f

#define MAX_DEPTH 4
#define BLACK_COLOR glm::vec3(0, 0, 0)
#define ANTIALIASING_SAMPLING 16

// Points defined by 2 attributes: positions which are stored in vertices array and colors which are stored in colors array
float *colors;
float *ss_colors;   //super sampling antialiasing
float *vertices;

int nPoints;
int size_vertices;
int size_colors;
int ss_size_colors;

glm::vec3 background;

GLfloat m[16];  //projection matrix initialized by ortho function

GLuint VaoId;
GLuint VboId[2];

GLuint VertexShaderId, FragmentShaderId, ProgramId;
GLint UniformId;

Scene* scene = NULL;
int RES_X, RES_Y;
int SS_RES_X, SS_RES_Y;

/* Draw Mode: 0 - point by point; 1 - line by line; 2 - full frame */
int draw_mode = 2;

int WindowHandle = 0;

///////////////////////////////////////////////////////////////////////  RAY-TRACE SCENE


bool rayCasting(Ray ray, glm::vec3& targetPoint, Object*& targetObject, std::vector<Object*> objects) {

	int count = 0;
	int numObjects = objects.size();
	float minDist = INFINITY;

	int changed = 0;

	for (int count = 0; count < numObjects; count++) {
		glm::vec3 auxPoint;
		if (objects[count]->getIntersectionPoint(auxPoint, ray)){
			float dist = glm::distance(ray.getInitialPoint(), auxPoint);
			if(dist < minDist) {
				targetPoint = auxPoint;
				targetObject = objects[count];
				changed = 1;
				minDist = dist;
			}
		}
	}
	if (changed == 0)
		return false;
	return true;
}

bool inShadow(Ray ray, Object* targetObject) {
	std::vector<Object*>* objects = scene->getObjects();

	int numObjects = objects->size();

	for (std::vector<Object*>::iterator it = objects->begin(); it != objects->end(); ++it) {
		if ((*it)->hasIntersection(ray)) {
			return true;
		}
	}
	return false;
}


/*
vi esta formula k so mexe nos angulos... ¯\_(-.-)_/¯ ASS:Samuel
*/
glm::vec3 refract(glm::vec3 incidentVec, glm::vec3 normal, float eta) {

	float incidentAngleCos = glm::dot(incidentVec, normal);
	float transmittedAngleSinSquared = eta*eta*(1 - incidentAngleCos*incidentAngleCos);
	float tPerpendicularComponent = glm::sqrt(1 - transmittedAngleSinSquared);

	return glm::normalize(eta*-incidentVec + (eta*incidentAngleCos - tPerpendicularComponent)*normal);
}



//a tua tmb funca André, mas como pensei k o erro podesse vir daqui andei a mexer nisto e cheguei a outra solucao...
//claro k podemos usar ambas :b

//glm::vec3 refract(glm::vec3 incidentVec, glm::vec3 normal, float eta) {
//	glm::vec3 perpendicular = glm::dot(incidentVec, normal)*normal - incidentVec;
//	float perpendicularLength = glm::length(perpendicular);
//	perpendicular = perpendicular / perpendicularLength;
//	
//	float sinRefract = eta*perpendicularLength;
//	float cosRefract = glm::sqrt(1 - sinRefract*sinRefract);
//	
//	return glm::normalize(sinRefract*perpendicular - cosRefract*normal);
//}


glm::vec3 rayTracing(Ray ray, int depth) {

	if (depth >= MAX_DEPTH) {
		return BLACK_COLOR;
	}

	glm::vec3 intersectionPoint;
	Object* obj = nullptr;
	bool intersection = rayCasting(ray, intersectionPoint, obj, *scene->getObjects());
	if (!intersection) {
		return background;
	}

	Material* mat = obj->getMaterial(); 
			
	glm::vec3 color = glm::vec3(0, 0, 0);
	glm::vec3 objcolor = *mat->getColor();
	glm::vec3 normal = obj->getNormal(intersectionPoint,ray);
	for (auto light : *scene->getLights()) {
		glm::vec3 L = glm::normalize(intersectionPoint-*light->getPosition());
		float diffuse = glm::dot(-L, normal);
		if (diffuse > 0) {
			Ray shadowRay(intersectionPoint-EPSILON*L, -L);
			if (!inShadow(shadowRay, obj)){ //trace shadow ray
				color += *light->getColor() * diffuse *mat->getDiffuse()*objcolor;
				glm::vec3 reflect = glm::reflect(glm::normalize(-L), normal);
				float dot = glm::dot(reflect, ray.getDirection());
				float base = std::fmaxf(dot, 0.0f);
				float specular = glm::pow(base, mat->getShininess());
				color += mat->getSpecular() * specular*(*light->getColor());
			}

		}

	}

	
			
	float transmitanceCoeff = mat->getTransmittance();
	float reflectionCoeff = mat->getSpecular();


	//if object is reflective
	//calculate reflective direction
	
	/*if (reflectionCoeff > 0) {
		glm::vec3 reflectedDir = glm::reflect(ray.getDirection(), normal);
		Ray reflectedRay(intersectionPoint + EPSILON*reflectedDir, reflectedDir);
		glm::vec3 reflectedColor = rayTracing(reflectedRay, depth + 1);
		color += reflectedColor * reflectionCoeff;
	}*/
			

	//if object is refractive
	//calculate refractive direction
	//if (transmitanceCoeff > 0) {
	//	glm::vec3 refractedDir;
	//	if (obj->isInside((ray.getInitialPoint()+ intersectionPoint)/2.0f)) {
	//		refractedDir = refract(-ray.getDirection(), normal, mat->getIndexOfRefraction()/1.0f);

	//	}
	//	else {
	//		refractedDir = refract(-ray.getDirection(), normal, 1.0f/mat->getIndexOfRefraction());
	//	}
	//	Ray refractedRay(intersectionPoint + EPSILON*refractedDir, refractedDir);
	//	glm::vec3 refractedColor = rayTracing(refractedRay, depth + 1);
	//	color += refractedColor * transmitanceCoeff;
	//}


	return color;
	
}

/*
	x and y are the pixels on the screen
*/
glm::vec3 calculatePrimaryRay(int x, int y, glm::vec3 ze, glm::vec3 xe, glm::vec3 ye, float df, float h, float w) {		
	glm::vec3 xComp = xe * w * (((float)x / (float)SS_RES_X) - 0.5f);
	glm::vec3 yComp = ye * h * (((float)y / (float)SS_RES_Y) - 0.5f);
	glm::vec3 zComp = -df * ze;

	glm::vec3 d = xComp + yComp + zComp;
	return glm::normalize(d);
}

void initCameraVectors(Camera * camera, glm::vec3& ze, glm::vec3& xe, glm::vec3& ye, float & df, float & h, float & w ) {
	float angle = (camera->getFovY() * (float)M_PI) / 180.0f; //in degrees, must be converted
	float aspectratio = SS_RES_X / (float)SS_RES_Y;
	float angleTan = tanf(angle / 2);
	glm::vec3 dir = *camera->getEye() - *camera->getCenter();
	df = glm::length(dir);
	h = 2 * df * angleTan;
	w = aspectratio * h;
	ze = (1 / (df)) * (dir);
	glm::vec3 cross = glm::cross(*camera->getUp(), ze);
	xe = (1 / glm::length(cross)) * cross;
	ye = glm::cross(ze, xe);
}


/////////////////////////////////////////////////////////////////////// ERRORS

bool isOpenGLError() {
	bool isError = false;
	GLenum errCode;
	const GLubyte *errString;
	while ((errCode = glGetError()) != GL_NO_ERROR) {
		isError = true;
		errString = gluErrorString(errCode);
		std::cerr << "OpenGL ERROR [" << errString << "]." << std::endl;
	}
	return isError;
}

void checkOpenGLError(std::string error)
{
	if (isOpenGLError()) {
		std::cerr << error << std::endl;
		exit(EXIT_FAILURE);
	}
}
/////////////////////////////////////////////////////////////////////// SHADERs
const GLchar* VertexShader =
{
	"#version 330 core\n"

	"in vec2 in_Position;\n"
	"in vec3 in_Color;\n"
	"uniform mat4 Matrix;\n"
	"out vec4 color;\n"

	"void main(void)\n"
	"{\n"
	"	vec4 position = vec4(in_Position, 0.0, 1.0);\n"
	"	color = vec4(in_Color, 1.0);\n"
	"	gl_Position = Matrix * position;\n"

	"}\n"
};

const GLchar* FragmentShader =
{
	"#version 330 core\n"

	"in vec4 color;\n"
	"out vec4 out_Color;\n"

	"void main(void)\n"
	"{\n"
	"	out_Color = color;\n"
	"}\n"
};

void createShaderProgram()
{
	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderId, 1, &VertexShader, 0);
	glCompileShader(VertexShaderId);

	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderId, 1, &FragmentShader, 0);
	glCompileShader(FragmentShaderId);

	ProgramId = glCreateProgram();
	glAttachShader(ProgramId, VertexShaderId);
	glAttachShader(ProgramId, FragmentShaderId);

	glBindAttribLocation(ProgramId, VERTEX_COORD_ATTRIB, "in_Position");
	glBindAttribLocation(ProgramId, COLOR_ATTRIB, "in_Color");

	glLinkProgram(ProgramId);
	UniformId = glGetUniformLocation(ProgramId, "Matrix");

	checkOpenGLError("ERROR: Could not create shaders.");
}

void destroyShaderProgram()
{
	glUseProgram(0);
	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);

	glDeleteShader(FragmentShaderId);
	glDeleteShader(VertexShaderId);
	glDeleteProgram(ProgramId);

	checkOpenGLError("ERROR: Could not destroy shaders.");
}
/////////////////////////////////////////////////////////////////////// VAOs & VBOs
void createBufferObjects()
{
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);
	glGenBuffers(2, VboId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);

	/* Não é necessário fazer glBufferData, ou seja o envio dos pontos para a placa gráfica pois isso
	é feito na drawPoints em tempo de execução com GL_DYNAMIC_DRAW */

	glEnableVertexAttribArray(VERTEX_COORD_ATTRIB);
	glVertexAttribPointer(VERTEX_COORD_ATTRIB, 2, GL_FLOAT, 0, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, VboId[1]);
	glEnableVertexAttribArray(COLOR_ATTRIB);
	glVertexAttribPointer(COLOR_ATTRIB, 3, GL_FLOAT, 0, 0, 0);

	// unbind the VAO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	/*glDisableVertexAttribArray(VERTEX_COORD_ATTRIB);
	glDisableVertexAttribArray(COLOR_ATTRIB);*/
	checkOpenGLError("ERROR: Could not create VAOs and VBOs.");
}

void destroyBufferObjects()
{
	glDisableVertexAttribArray(VERTEX_COORD_ATTRIB);
	glDisableVertexAttribArray(COLOR_ATTRIB);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glDeleteBuffers(1, VboId);
	glDeleteVertexArrays(1, &VaoId);
	checkOpenGLError("ERROR: Could not destroy VAOs and VBOs.");
}

glm::vec3 averageColors(int y, int x) {
	
	glm::vec3 samples[ANTIALIASING_SAMPLING * ANTIALIASING_SAMPLING];
	int idxColor = 0;
	for (int i = y; i < y + ANTIALIASING_SAMPLING; ++i) {
		for (int j = x; j < x + ANTIALIASING_SAMPLING; ++j) {
			int idx = (i * SS_RES_Y + j) * 3;
			glm::vec3 color;
			color.r = ss_colors[idx++];
			color.g = ss_colors[idx++];
			color.b = ss_colors[idx++];
			samples[idxColor++] = color;

		}
	}

	glm::vec3 resultColor(0);
	for (auto color : samples) {
		resultColor += color;
	}
	int colorSize = ANTIALIASING_SAMPLING * ANTIALIASING_SAMPLING;
	resultColor.r /= colorSize;
	resultColor.g /= colorSize;
	resultColor.b /= colorSize;
	return samples[0];
}

void drawPoints()
{
	glBindVertexArray(VaoId);
	glUseProgram(ProgramId);

	//Antialiasing

	int index = 0, index_pos = 0;
	if (ANTIALIASING_SAMPLING > 1) {

		for (int y = 0; y < RES_Y; y++)
		{
			for (int x = 0; x < RES_X; x++)
			{

				int superSampledY = y * ANTIALIASING_SAMPLING;
				int superSampledX = x * ANTIALIASING_SAMPLING;
				
				glm::vec3 color = averageColors(superSampledY, superSampledX);

				vertices[index_pos++] = (float)x;
				vertices[index_pos++] = (float)y;
				//printf("vertices[%d] = %d,%d", index_pos - 2, x, y);
				colors[index++] = (float)color.r;
				colors[index++] = (float)color.g;
				colors[index++] = (float)color.b;
				
			}
		}

	}

	glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
	glBufferData(GL_ARRAY_BUFFER, size_vertices, vertices, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, VboId[1]);
	glBufferData(GL_ARRAY_BUFFER, size_colors,  ANTIALIASING_SAMPLING > 1 ? colors : ss_colors, GL_DYNAMIC_DRAW);

	glUniformMatrix4fv(UniformId, 1, GL_FALSE, m);

	glDrawArrays(GL_POINTS, 0, nPoints);
	glFinish();

	glUseProgram(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	checkOpenGLError("ERROR: Could not draw scene.");
}

/////////////////////////////////////////////////////////////////////// CALLBACKS

// Render function by primary ray casting from the eye towards the scene's objects

void renderScene()
{
	int index_pos = 0;
	int index_col = 0;

	Camera * camera = scene->getCamera();

	glm::vec3 ze, xe, ye;
	float df, w, h;

	initCameraVectors(camera, ze, xe, ye, df, w, h);

	for (int y = 0; y < SS_RES_Y; y++)
	{
		
		for (int x = 0; x < SS_RES_X; x++)
		{
			glm::vec3 rayDir = calculatePrimaryRay(x, y, ze, xe, ye, df, w, h);
			Ray ray(*camera->getEye(), rayDir);
			glm::vec3 color = rayTracing(ray, 0);

			if (ANTIALIASING_SAMPLING == 1) {
				vertices[index_pos++] = (float)x;
				vertices[index_pos++] = (float)y;
			}
			ss_colors[index_col++] = (float)color.r;
			ss_colors[index_col++] = (float)color.g;
			ss_colors[index_col++] = (float)color.b;

			if (draw_mode == 0) {  // desenhar o conteúdo da janela ponto a ponto

				drawPoints();
				index_pos = 0;
				index_col = 0;
			}
		}
		//printf("line %d\n", y);
		if (draw_mode == 1) {  // desenhar o conteúdo da janela linha a linha
			drawPoints();
			index_pos = 0;
			index_col = 0;

		}
	}

	if (draw_mode == 2) //preenchar o conteúdo da janela com uma imagem completa
		drawPoints();

	printf("Terminou!\n");

}

void cleanup()
{
	destroyShaderProgram();
	destroyBufferObjects();

	delete colors;
	delete vertices;
	delete ss_colors;
	delete scene;
}

void ortho(float left, float right, float bottom, float top,
	float nearp, float farp)
{
	m[0 * 4 + 0] = 2 / (right - left);
	m[0 * 4 + 1] = 0.0;
	m[0 * 4 + 2] = 0.0;
	m[0 * 4 + 3] = 0.0;
	m[1 * 4 + 0] = 0.0;
	m[1 * 4 + 1] = 2 / (top - bottom);
	m[1 * 4 + 2] = 0.0;
	m[1 * 4 + 3] = 0.0;
	m[2 * 4 + 0] = 0.0;
	m[2 * 4 + 1] = 0.0;
	m[2 * 4 + 2] = -2 / (farp - nearp);
	m[2 * 4 + 3] = 0.0;
	m[3 * 4 + 0] = -(right + left) / (right - left);
	m[3 * 4 + 1] = -(top + bottom) / (top - bottom);
	m[3 * 4 + 2] = -(farp + nearp) / (farp - nearp);
	m[3 * 4 + 3] = 1.0;
}

void reshape(int w, int h)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, w, h);
	ortho(0, (float)RES_X, 0, (float)RES_Y, -1.0, 1.0);
}

/////////////////////////////////////////////////////////////////////// SETUP
void setupCallbacks()
{
	glutCloseFunc(cleanup);
	glutDisplayFunc(renderScene);
	glutReshapeFunc(reshape);
}

void setupGLEW() {
	glewExperimental = GL_TRUE;
	GLenum result = glewInit();
	if (result != GLEW_OK) {
		std::cerr << "ERROR glewInit: " << glewGetString(result) << std::endl;
		exit(EXIT_FAILURE);
	}
	GLenum err_code = glGetError();
	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));
	printf("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

void setupGLUT(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitContextVersion(3, 3);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutInitWindowPosition(640, 100);
	glutInitWindowSize(RES_X, RES_Y);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glDisable(GL_DEPTH_TEST);
	WindowHandle = glutCreateWindow(CAPTION);
	if (WindowHandle < 1) {
		std::cerr << "ERROR: Could not create a new rendering window." << std::endl;
		exit(EXIT_FAILURE);
	}
}

void init(int argc, char* argv[])
{
	setupGLUT(argc, argv);
	setupGLEW();
	std::cerr << "CONTEXT: OpenGL v" << glGetString(GL_VERSION) << std::endl;
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	createShaderProgram();
	createBufferObjects();
	setupCallbacks();
}

int main(int argc, char* argv[])
{
	scene = new Scene();

	if (!(scene->loadSceneFromNFF("scene/balls_low.nff"))) return 0;
	RES_X = scene->getCamera()->getResX();
	RES_Y = scene->getCamera()->getResY();
	SS_RES_X = RES_X * ANTIALIASING_SAMPLING;
	SS_RES_Y = RES_Y * ANTIALIASING_SAMPLING;

	background = *scene->getBackgroundColor();

	if (draw_mode == 0) { // desenhar o conteúdo da janela ponto a ponto
		nPoints = 1;
		printf("DRAWING MODE: POINT BY POINT\n");
	}
	else if (draw_mode == 1) { // desenhar o conteúdo da janela linha a linha
		nPoints = RES_X;
		
		printf("DRAWING MODE: LINE BY LINE\n");
	}
	else if (draw_mode == 2) { // preencher o conteúdo da janela com uma imagem completa
		nPoints = RES_X*RES_Y;

		printf("DRAWING MODE: FULL IMAGE\n");
	}
	else {
		printf("Draw mode not valid \n");
		exit(0);
	}
	printf("MAX_DEPTH x%d\n", MAX_DEPTH);
	if (ANTIALIASING_SAMPLING > 1 && draw_mode != 2) {
		printf("DRAW MODE UNSUPPORTED WITH ANTIALIASING\n");
	}
	else {
		printf("ANTIALIASING x%d\n", ANTIALIASING_SAMPLING);
	}

	size_vertices = 2 * nPoints  * sizeof(float) ;
	size_colors = 3 * nPoints * sizeof(float);
	ss_size_colors = size_colors * ANTIALIASING_SAMPLING * ANTIALIASING_SAMPLING;

	printf("RESX = %d  RESY= %d.\n", RES_X, RES_Y);

	vertices = (float*)malloc(size_vertices);
	if (vertices == NULL) exit(1);

	colors = (float*)malloc(size_colors);
	if (colors == NULL) exit(1);

	ss_colors = (float*)malloc(ss_size_colors);
	if (ss_colors == NULL) exit(1);

	init(argc, argv);
	glutMainLoop();
	exit(EXIT_SUCCESS);
}
///////////////////////////////////////////////////////////////////////