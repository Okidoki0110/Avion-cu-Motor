#pragma once
#include <Component/SimpleScene.h>
#include <Component/Transform/Transform.h>
#include <Core/GPU/Mesh.h>

class Cutie {
public:
	double x;
	double y;
	double z;
};
class Sfera {
public:
	double x;
	double y;
	double z;
	double raza;
};

class Laborator7 : public SimpleScene
{
	public:
		Laborator7();
		~Laborator7();
		void restart();
		void scleazaNoriAleator();
		void rotesteNoriAleator();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;
		void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix, const glm::vec3 &color = glm::vec3(1));
		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

		glm::vec3 lightPosition;
		unsigned int materialShininess;
		float materialKd;
		float materialKs;
		float deplasare;
		int oldMouseY;
		int rotatieElice;
		int rotatieMare;
		bool fpsCamera;
		int pozitieZ;
		int XDeplasare;
		double XObstacole[1000];
		double YObstacole[1000];
		double XNor;
		double scalareNor1;
		double scalareNor2;
		double scalareNor3;
		double scalareNor4;
		double scalareNor5;
		float rotatieNor1;
		float rotatieNor2;
		float rotatieNor3;
		float rotatieNor4;
		float rotatieNor5;
		int nrObstacol=1000;
		int nrNor = 1000;
		double axaX;
		double offset;
		Cutie avion;
		Sfera obstacol1;
		Sfera obstacol2;
		bool prabusireAvion;
		bool obstacol1Lovit;
		bool obstacol2Lovit;
		bool obstacol1Afisat;
		bool obstacol2Afisat;
		int nrAfisariLovitura;
		int nrVieti = 3;
};
