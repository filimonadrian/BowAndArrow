#pragma once
#include <Component/SimpleScene.h>
#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"
#include "Balloon.h"
#include "Bow.h"
#include "Arrow.h"
#include "Shuriken.h"
#include "Scorebar.h"
#include "BalloonTail.h"
#include "Heart.h"

class Tema1 : public SimpleScene
{
	public:
		Tema1();
		~Tema1();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;
		void shoot(float xPos, float yPos, float toX, float toY, float speed);
		void resetModelMatrix();
		bool Tema1::checkArrowBalloonCollision(Arrow arrow, Balloon balloon);
		bool Tema1::checkArrowShurikenCollision(Arrow arrow, Shuriken shuriken);
		bool Tema1::checkBowShurikenCollision(Bow Bow, Shuriken shuriken);

	protected:
		glm::mat3 modelMatrix;
		float SPEEDUP = 8.0f;
		int score = 0;
		int lives = 3;
		float arrowSpeed = 0, defaultArrowSpeed = 0, maxArrowSpeed = 1080;
		float balloonSpeed = 150.0f;
		float maxBalloonSpeed = 500.0f;
		float hitSpeed = 300.0f;
};
