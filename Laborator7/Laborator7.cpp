#include "Laborator7.h"

#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <Core/Engine.h>
#include <Component/Camera/Camera.h>

using namespace std;

void Laborator7::rotesteNoriAleator() {
	rotatieNor1 = 0.0 + (rand() % 134) / 100.0;
	rotatieNor2 = 0.0 + (rand() % 134) / 100.0;
	rotatieNor3 = 0.0 + (rand() % 134) / 100.0;
	rotatieNor4 = 0.0 + (rand() % 134) / 100.0;
	rotatieNor5 = 0.0 + (rand() % 134) / 100.0;
}

void Laborator7::scleazaNoriAleator() {
	scalareNor1 = 0.08 + (rand() % 30) / 100.0;
	scalareNor2 = 0.08 + (rand() % 30) / 100.0;
	scalareNor3 = 0.08 + (rand() % 30) / 100.0;
	scalareNor4 = 0.08 + (rand() % 30) / 100.0;
	scalareNor5 = 0.08 + (rand() % 30) / 100.0;
}

bool intersect(Sfera sphere, Cutie box) 
{
	// get box closest point to sphere center by clamping
	double x = max(box.x, min(sphere.x, box.x + 0.1));
	double y = max(box.y, min(sphere.y, box.y + 0.1));
	double z = max(box.z, min(sphere.z, box.z + 0.1));

	// this is the same as isPointInsideSphere
	double distanta = sqrt((x - sphere.x) * (x - sphere.x) + (y - sphere.y) * (y - sphere.y) + (z - sphere.z) * (z - sphere.z));
	if (distanta < sphere.raza)
		return 1;
	return 0;
}

void Laborator7::restart()
{
	rotatieElice = 0;
	rotatieMare = 0;
	fpsCamera = false;
	pozitieZ = 0;
	nrObstacol = 0;
	XDeplasare = 0;
	for (int i = 0; i < 1000; i++) {
		YObstacole[i] = 2 + (rand() % 12) / 10.0;
	}
	offset = (rand() % 60) / 10.0 - 3;
	scleazaNoriAleator();
	rotesteNoriAleator();
	axaX = 2.9;
	XNor = 2.9;
	prabusireAvion = false;
	obstacol1Lovit = false;
	obstacol2Lovit = false;
	obstacol1Afisat = true;
	obstacol2Afisat = true;
	nrAfisariLovitura = 0;
	nrVieti = 3;
}
Laborator7::Laborator7()
{
	restart();
}

Laborator7::~Laborator7()
{
}

void Laborator7::Init()
{
	{
		Mesh* mesh = new Mesh("viata");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "estrellica2obj.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("marea");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "cilindru.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("avion");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "avion.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("obstacol1");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("obstacol2");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("nor1");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("nor2");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("nor3");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("nor4");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("nor5");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader* shader = new Shader("ShaderLab7");
		shader->AddShader("Source/Laboratoare/Laborator7/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Laborator7/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	//Proprietati de lumina si material
	{
		lightPosition = glm::vec3(0, 2, 2);
		materialShininess = 30;
		materialKd = 0.5;
		materialKs = 0.5;
	}
}

void Laborator7::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0.42, 0.65, 0.80, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Laborator7::Update(float deltaTimeSeconds)
{
	Sleep(20);
	axaX -= 0.1;
	XDeplasare += 1;
	XNor -= 0.1;
	nrAfisariLovitura++;
	if (XDeplasare % 70 == 0) {
		XNor = 2.9;
		scleazaNoriAleator();
		rotesteNoriAleator();
	}
	if ((int)axaX == -3 && !prabusireAvion) {
		axaX = 2.9;
		nrObstacol++;
		offset = (rand() % 20) / 10.0;
		obstacol1Afisat = true;
		obstacol2Afisat = true;
	}
	if (prabusireAvion) {
		if (deplasare >= -2) {
			deplasare -= 0.05;
		}
	}

	/*
		Desenez vietile 
	*/

	// viata 1
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.5, 3.2, pozitieZ));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.02));
		if (!obstacol1Lovit && nrVieti == 3 && !fpsCamera)
			RenderSimpleMesh(meshes["viata"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1, 0, 0));
	}
	// viata 2
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.95, 3.2, pozitieZ));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.02));
		if (nrVieti >= 2 && !fpsCamera)
			RenderSimpleMesh(meshes["viata"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1, 0, 0));
	}
	//  viata 3
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-2.4, 3.2, pozitieZ));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.02));
		if (nrVieti >= 1 && !fpsCamera)
			RenderSimpleMesh(meshes["viata"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1, 0, 0));
	}

	/*
		Desenez obstacole
	*/

	// obstacolul 1
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(axaX + offset, YObstacole[nrObstacol], pozitieZ));
		obstacol1.x = axaX + offset;
		obstacol1.y = YObstacole[nrObstacol];
		obstacol1.z = pozitieZ;
		obstacol1.raza = 0.1;
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
		if (obstacol1Afisat)
			RenderSimpleMesh(meshes["obstacol1"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0, 0));
	}
	// obstacolul 2
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(axaX, YObstacole[nrObstacol + 1], pozitieZ));
		obstacol2.x = axaX;
		obstacol2.y = YObstacole[nrObstacol + 1];
		obstacol2.z = pozitieZ;
		obstacol2.raza = 0.1;
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
		if (!obstacol2Afisat)
			RenderSimpleMesh(meshes["obstacol2"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0, 0));
	}

	/*
		Desenam norii
	*/

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(XNor+0.2, 2.6, pozitieZ));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(scalareNor1));
		modelMatrix = glm::rotate(modelMatrix, rotatieNor1, glm::vec3(1,1,1));
		RenderSimpleMesh(meshes["nor1"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0.9, 0.9, 1.1));
	}
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(XNor+0.1, 2.5, pozitieZ));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(scalareNor2));
		modelMatrix = glm::rotate(modelMatrix, rotatieNor2, glm::vec3(1, 1, 1));
		RenderSimpleMesh(meshes["nor2"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0.9, 0.9, 1.3));
	}
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(XNor+0.3, 2.6, pozitieZ));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(scalareNor3));
		modelMatrix = glm::rotate(modelMatrix, rotatieNor3, glm::vec3(1, 1, 1));

		RenderSimpleMesh(meshes["nor3"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0.9, 0.9, 1.5));
	}
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(XNor+0.4, 2.5, pozitieZ));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(scalareNor4));
		modelMatrix = glm::rotate(modelMatrix, rotatieNor4, glm::vec3(1, 1, 1));
		RenderSimpleMesh(meshes["nor4"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0.9, 0.9, 1.7));
	}
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(XNor+0.5, 2.5, pozitieZ));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(scalareNor5));
		modelMatrix = glm::rotate(modelMatrix, rotatieNor5, glm::vec3(1, 1, 1));

		RenderSimpleMesh(meshes["nor5"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0.9, 0.9, 1.3));
	}

	/* 
		Desenez avionul
	*/

	// desenam cutia din spate
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		if (obstacol1Lovit || obstacol2Lovit) {
			modelMatrix = glm::translate(modelMatrix, glm::vec3(0.02 - 0.04 * nrAfisariLovitura - 0.16 - 0.08, 3 + 0.1 + deplasare, pozitieZ));
		}
		else {
			modelMatrix = glm::translate(modelMatrix, glm::vec3(0.02 + 0 - 0.16 - 0.08, 3 + 0.1 + deplasare, pozitieZ));
		}
		modelMatrix = glm::rotate(modelMatrix, 1.57f / 30.0f, glm::vec3(1, 0, 0));
		modelMatrix = glm::rotate(modelMatrix, 1.57f / 2.0f, glm::vec3(0, 0, 1));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.03f, 0.12, 0.03));
		if (prabusireAvion)
			modelMatrix = glm::rotate(modelMatrix, 1.57f / 3.0f * deplasare, glm::vec3(0, 0, 1));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1, 0, 0));
	}

	// desenam cutia din mijloc
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		if (obstacol1Lovit || obstacol2Lovit) {
			modelMatrix = glm::translate(modelMatrix, glm::vec3(0.02 - 0.04 * nrAfisariLovitura, 3 + deplasare, pozitieZ));
		}
		else {
			modelMatrix = glm::translate(modelMatrix, glm::vec3(0.02 + 0, 3 + deplasare, pozitieZ));
		}
		modelMatrix = glm::rotate(modelMatrix, 1.57f / 30.0f, glm::vec3(1, 0, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.09, 0.08, 0.16));
		if (prabusireAvion)
			modelMatrix = glm::rotate(modelMatrix, 1.57f / 3.0f * deplasare, glm::vec3(0, 0, 1));
		RenderSimpleMesh(meshes["avion"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1, 0, 0));
	}

	// desenam cutia din fata
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		if (obstacol1Lovit || obstacol2Lovit) {
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.04 * nrAfisariLovitura + 0.16 + 0.08, 3 + deplasare, pozitieZ));
		}
		else {
			modelMatrix = glm::translate(modelMatrix, glm::vec3(0.16 + 0.08, 3 + deplasare, pozitieZ));
		}
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.02, 0.1, 0.1));
		avion.x = 0 + 0.16 + 0.08;
		avion.y = 3 + deplasare;
		avion.z = pozitieZ;
		if (prabusireAvion) {
			modelMatrix = glm::rotate(modelMatrix, 1.57f / 3.0f * deplasare, glm::vec3(0, 0, 1));
		}
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0, 1));
	}

	// desenam elice
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		if (obstacol1Lovit || obstacol2Lovit) {
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.04 * nrAfisariLovitura + 0.2 + 0.08, 3.0 + deplasare, pozitieZ));
		}
		else
		{
			modelMatrix = glm::translate(modelMatrix, glm::vec3(0 + 0.2 + 0.08, 3.0 + deplasare, pozitieZ));
		}
		// rotim elice
		modelMatrix = glm::rotate(modelMatrix, 1.57f / 2 * rotatieElice, glm::vec3(1, 0, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.01, 0.2, 0.02));

		if (prabusireAvion)
			modelMatrix = glm::rotate(modelMatrix, 1.57f / 3.0f * deplasare, glm::vec3(0, 0, 1));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1, 1, 1));
		
		modelMatrix = glm::mat4(1);
		if (obstacol1Lovit || obstacol2Lovit) {
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.04 * nrAfisariLovitura + 0.2 + 0.08, 3.0 + deplasare, pozitieZ));
		}
		else
		{
			modelMatrix = glm::translate(modelMatrix, glm::vec3(0 + 0.2 + 0.08, 3.0 + deplasare, pozitieZ));
		}
		// rotim elice
		modelMatrix = glm::rotate(modelMatrix, 1.57f / 2, glm::vec3(1, 0, 0));
		modelMatrix = glm::rotate(modelMatrix, 1.57f / 2 * rotatieElice, glm::vec3(1, 0, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.01, 0.2, 0.02));
		if (prabusireAvion)
			modelMatrix = glm::rotate(modelMatrix, 1.57f / 3.0f * deplasare, glm::vec3(0, 0, 1));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1, 1, 1));
		rotatieElice++;
	}
	// desenam aripile
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		if (obstacol1Lovit || obstacol2Lovit) {
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.04 * nrAfisariLovitura, 3.0 + deplasare, pozitieZ));
		}
		else {
			modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 3.0 + deplasare, pozitieZ));
		}

		modelMatrix = glm::rotate(modelMatrix, 1.57f / 30.0f, glm::vec3(1, 0, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.18, 0.01, 0.8));

		if (prabusireAvion)
			modelMatrix = glm::rotate(modelMatrix, 1.57f / 3.0f * deplasare, glm::vec3(0, 0, 1));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0, 1));
	}

	/*
		Desenez marea
	*/
	
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -0.1, pozitieZ));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.6f));
		// rotim cilindrul pe Ox astfel incat sa dea impresia de mare
		modelMatrix = glm::rotate(modelMatrix, 1.57f, glm::vec3(1, 0, 0));
		//rotim cilindrul pe Oy astfel incat sa se invarteasca
		modelMatrix = glm::rotate(modelMatrix, 1.57f / 100 * rotatieMare, glm::vec3(0, 1, 0));
		Sleep(10);
		rotatieMare++;
		RenderSimpleMesh(meshes["marea"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0.7 , 1 , 1.3));
	}
	if (!obstacol1Lovit && intersect(obstacol1, avion) == 1) 
	{
		nrAfisariLovitura = 0;
		nrVieti--;
		obstacol1Lovit = true;
		obstacol1Afisat = false;
	}
	if (!obstacol2Lovit && intersect(obstacol2, avion) == 1)
	{
		nrAfisariLovitura = 0;
		nrVieti--;
		obstacol2Lovit = true;
		obstacol1Afisat = false;
	}
	if (nrAfisariLovitura == 10)
	{
		obstacol1Lovit = false;
		obstacol2Lovit = false;
		nrAfisariLovitura = 0;
	}

	if (nrVieti == 0)
	{
		prabusireAvion = true;;
	}

}

void Laborator7::FrameEnd()
{
	//desenam sistemul de coordonate
	//DrawCoordinatSystem();
}

void Laborator7::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Set shader uniforms for light & material properties
	// TODO: Set light position uniform
	GLint loc_light_position = glGetUniformLocation(shader->program, "light_position");
	glUniform3fv(loc_light_position, 1, glm::value_ptr(lightPosition));

	// TODO: Set eye position (camera position) uniform
	glm::vec3 eyePosition = GetSceneCamera()->transform->GetWorldPosition();

	GLint loc_eye_position = glGetUniformLocation(shader->program, "eye_position");
	glUniform3fv(loc_eye_position, 1, glm::value_ptr(eyePosition));

	// TODO: Set material property uniforms (shininess, kd, ks, object color) 
	GLint loc = glGetUniformLocation(shader->program, "material_shininess");
	glUniform1i(loc, materialShininess);

	loc = glGetUniformLocation(shader->program, "material_kd");  // componenta difuza
	glUniform1f(loc, materialKd);

	loc = glGetUniformLocation(shader->program, "material_ks");  // componenta speculara
	glUniform1f(loc, materialKs);

	loc = glGetUniformLocation(shader->program, "object_color");
	glUniform3fv(loc, 1, glm::value_ptr(color));

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Laborator7::OnInputUpdate(float deltaTime, int mods)
{
	float speed = 2;
	if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		glm::vec3 up = glm::vec3(0, 1, 0);
		glm::vec3 right = GetSceneCamera()->transform->GetLocalOXVector();
		glm::vec3 forward = GetSceneCamera()->transform->GetLocalOZVector();
		forward = glm::normalize(glm::vec3(forward.x, 0, forward.z));
	}
}

void Laborator7::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_R) {
		restart();
	}
	if (key == GLFW_KEY_Z) {
		pozitieZ--;
	}
	if (key == GLFW_KEY_X) {
		pozitieZ++;
	}
	// resetare/modificare camera
	if (key == GLFW_KEY_M) {
		if (fpsCamera == true) 
		{
			GetSceneCamera()->transform->SetWorldPosition(glm::vec3(0, 1.9, 2.5));
			GetSceneCamera()->transform->SetWorldRotation(glm::vec3(-5, 0, 0));
			GetSceneCamera()->Update();
		}
		else
		{
			GetSceneCamera()->transform->SetWorldPosition(glm::vec3(-1.9, 2.8, 0.03));
			GetSceneCamera()->transform->RotateWorldOY(-1.55f);
			GetSceneCamera()->Update();
		}
		// 1->0 0->1
		fpsCamera = 1 - fpsCamera;
	}
}

void Laborator7::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Laborator7::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	if (!prabusireAvion) 
	{
		if (deplasare >= -1 && deplasare <= 0.4)
		{
			if (mouseY >= oldMouseY)
				deplasare -= deltaY * 1.0 / 100;
			else
				deplasare -= deltaY * 1.0 / 100;
		}
		if (deplasare < -1) {
			deplasare = -0.95;
		}
		if (deplasare > 0.4) {
			deplasare = 0.35;
		}
		oldMouseY = mouseY;
	}
}

void Laborator7::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Laborator7::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator7::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator7::OnWindowResize(int width, int height)
{
}
