#include "BOX.h"
#include <IGL/IGlib.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>


//Idenficadores de los objetos de la escena
int objId =-1;
int objId1 =0;

//Declaración de CB
void resizeFunc(int width, int height);
void idleFunc();
void keyboardFunc(unsigned char key, int x, int y);
void mouseFunc(int button, int state, int x, int y);
void mouseMotionFunc(int x, int y);


float f = 1.0f / tan(3.141592f / 6.0f);
float far = 10.0f;
float near = 0.1f;

glm::mat4 view = glm::mat4(1.0);

int main(int argc, char** argv)
{
	std::locale::global(std::locale("spanish"));// acentos ;)
	if (!IGlib::init("../shaders_P2/shader.v2.vert", "../shaders_P2/shader.v2.frag"))
		return -1;
  //Se ajusta la cámara
	//Si no se da valor se cojen valores por defecto
	view[3].z = -6;

	glm::mat4 proj = glm::mat4(1.0);

	proj[0].x = f;
	proj[1].y = f;
	proj[2].z = (far + near) / (near - far);
	proj[2].w = -1.0f;
	proj[3].z = (2.0f * far * near) / (near - far);
	proj[3].w = 0.0f;
	IGlib::setProjMat(proj);
	IGlib::setViewMat(view);

	//Creamos el objeto que vamos a visualizar
	objId = IGlib::createObj(cubeNTriangleIndex, cubeNVertex, cubeTriangleIndex, 
			cubeVertexPos, cubeVertexColor, cubeVertexNormal,cubeVertexTexCoord, cubeVertexTangent);

	objId1 = IGlib::createObj(cubeNTriangleIndex, cubeNVertex, cubeTriangleIndex,
		cubeVertexPos, cubeVertexColor, cubeVertexNormal, cubeVertexTexCoord, cubeVertexTangent);

	//IGlib::addColorTex(objId, "../img/color.png");
	IGlib::addColorTex(objId, "../img/color2.png");
	IGlib::addSpecularTex(objId, "../img/specMap.png");
	IGlib::addEmissiveTex(objId, "../img/emissive.png");
		
	IGlib::addColorTex(objId1, "../img/color3.png");
	IGlib::addSpecularTex(objId1, "../img/specMap.png");
	IGlib::addEmissiveTex(objId1, "../img/emissive.png");

	glm::mat4 modelMat = glm::mat4(1.0f);
	glm::mat4 modelMat1 = glm::mat4(1.0f);

	
	IGlib::setModelMat(objId, modelMat);
	IGlib::setModelMat(objId1, modelMat1);

	
	//CBs
	IGlib::setIdleCB(idleFunc);
	IGlib::setResizeCB(resizeFunc);
	IGlib::setKeyboardCB(keyboardFunc);
	IGlib::setMouseCB(mouseFunc);
	IGlib::setMouseMoveCB(mouseMotionFunc);
	
	//Mainloop
	IGlib::mainLoop();
	IGlib::destroy();
	return 0;
}

void resizeFunc(int width, int height)
{
	
	//Ajusta el aspect ratio al tamaño de la venta
}

void idleFunc()
{
	glm::mat4 modelMat(1.0f);
	
	glm::mat4 modelMat1(1.0f);
	
	static float angle = 0.0f;
	static float angle1 = 0.0f;

	angle = (angle > 3.141592f * 2.0f) ? 0 : angle + 0.0005f;
	angle1 = (angle1 > 3.141592f * 2.0f) ? 0 : angle1 + 0.0002f;
	
	modelMat = glm::rotate(modelMat, angle, glm::vec3(1.0f, 1.0f, 0.0f));
	modelMat1 = glm::rotate(modelMat1, angle1, glm::vec3(0.0f, 1.0f, 0.0f)); // el segundo cubo rota en el sisema de referencia del mundo virtual
	modelMat1 = glm::translate(modelMat1, glm::vec3(3.0f,0.0f,0.0f));
	modelMat1 = glm::rotate(modelMat1, angle1, glm::vec3(0.0f, 1.0f, 0.0f));	//el segundo cubo rota en el sistema de referencia del objeto


	IGlib::setModelMat(objId, modelMat);
	IGlib::setModelMat(objId1, modelMat1);
}

void keyboardFunc(unsigned char key, int x, int y)
{
	std::cout << "Se ha pulsado la tecla " << key << std::endl << std::endl;
	if (key == 's')			//wasd para el movimiento, no altera el frustum por lo que el cubo desaparece al alejarse mucho
	{
	view[3].z += -0.1;

	IGlib::setViewMat(view);
	}
	if (key == 'w')
	{
		view[3].z += 0.1;

		IGlib::setViewMat(view);
	}
	if (key == 'a')
	{
		view[3].x += 0.1;

		IGlib::setViewMat(view);
	}
	if (key == 'd')
	{
		view[3].x += -0.1;

		IGlib::setViewMat(view);
	}
	if (key == 'q')
	{
		glm::vec3 traslation = glm::vec3(view[3].x, view[3].y, view[3].z);		//rotación de cámara a izqda
		view = glm::translate(view, -traslation);
		view = glm::rotate(view, -0.05f, glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, traslation);
		

		IGlib::setViewMat(view);
	}
	if (key == 'e')
	{
		glm::vec3 traslation = glm::vec3(view[3].x, view[3].y, view[3].z);	//rotacion camara a dcha
		view = glm::translate(view, -traslation);
		view = glm::rotate(view, 0.05f, glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, traslation);

		IGlib::setViewMat(view);
	}
}  

void mouseFunc(int button, int state, int x, int y)
{
	if (state==0)
		std::cout << "Se ha pulsado el botón ";
	else
		std::cout << "Se ha soltado el botón ";
	
	if (button == 0) std::cout << "de la izquierda del ratón " << std::endl;
	if (button == 1) std::cout << "central del ratón " << std::endl;
	if (button == 2) std::cout << "de la derecha del ratón " << std::endl;

	std::cout << "en la posición " << x << " " << y << std::endl << std::endl;
}

void mouseMotionFunc(int x, int y)	//rotación con raton
{
	//glm::vec3 traslation = glm::vec3(view[3].x, view[3].y, view[3].z);
	//view = glm::translate(view, -traslation);
	//view = glm::rotate(view, -0.05f, glm::vec3(x-centro.x, y-centro.y, 0.0f));
	//view = glm::translate(view, traslation);

	//IGlib::setViewMat(view);
}
