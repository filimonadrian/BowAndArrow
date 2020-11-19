#include "Tema1.h"

#include <vector>
#include <iostream>
#include <ctime>
#include <Core/Engine.h>
#include "Tema1.h"


Bow bow(40, 250);
Scorebar scorebar(100, 200);
Heart heart(100, 200);
BalloonTail balloonTail(200, 200);


std::vector<Arrow> arrows(5);
std::vector<Shuriken> shurikens(10);
std::vector<Balloon> balloons(10);
clock_t TimeZeroBalloons = clock();
clock_t TimeZeroShurikens = clock();

double deltaTimeBalloon = 0;
double deltaTimeShuriken = 0;
double delayBalloons = 1;
double delayShurikens = 3;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 corner = glm::vec3(0, 0, 0);
	float squareSide = 100;

	for (int i = 0; i < 2; i++) {
		balloons[i].generateBalloon();
	}
	bow.modelMatrix *= Transform2D::Rotate(-3.14/2);

	AddMeshToList(scorebar.CreateScorebar("scorebar", glm::vec3(1, 0, 1), true));
	AddMeshToList(scorebar.CreateScorebar("scorebarOutline", glm::vec3(1, 1, 1), false));

	AddMeshToList(heart.CreateHeart("redHeart", glm::vec3(1, 0, 0), true));
	AddMeshToList(heart.CreateHeart("blackHeart", glm::vec3(1, 0, 0), false));


	AddMeshToList(balloonTail.CreateBalloonTail("yellow-BalloonTail", glm::vec3(1, 1, 0)));
	AddMeshToList(balloonTail.CreateBalloonTail("red-BalloonTail", glm::vec3(1, 0, 0)));

	AddMeshToList(balloons[0].CreateBalloon("yellow-balloon", 40, 40, glm::vec3(1, 1, 0), true));
	AddMeshToList(balloons[0].CreateBalloon("red-balloon", 40, 40, glm::vec3(1, 0, 0), true));

	AddMeshToList(bow.CreateBow("bow", 20, glm::vec3(1, 0, 0)));

	AddMeshToList(arrows[0].CreateArrow("arrow", 50, corner, glm::vec3(1, 0, 0)));

	AddMeshToList(shurikens[0].CreateShuriken("shuriken", 10, corner, 30, glm::vec3(1, 0, 0)));

}

void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{

	if (lives == 0) {
		std::cout << "Game Over!\n";
		std::exit(0);
	}
	// render the bow
	RenderMesh2D(meshes["bow"], shaders["VertexColor"], bow.modelMatrix);

	auto resolution = window->GetResolution();
	bow.MAX_WIDTH = resolution.x;
	bow.MAX_HEIGHT = resolution.y;

	// BONUS
	// change dynamically speed and generating time depending on the score
	if (score > 200 && balloonSpeed < maxBalloonSpeed) {
		balloonSpeed += score / 1000;
	}
	if (score > 200 && delayShurikens > 1.0f) {
		delayShurikens -= 0.01;
	}
	if (score > 200 && delayBalloons > 0.2f) {
		delayBalloons -= 0.01;
	}

	// if the score is over 1000 change de min arrow speed
	if (score > 1000) {
		defaultArrowSpeed = 400;
	}
	
	int nr_lives = 0;
	// render the remaining lives
	for (nr_lives = 0; nr_lives < lives; nr_lives++) {
		resetModelMatrix();
		modelMatrix *= Transform2D::Translate(10 + nr_lives * 50, resolution.y - 50);
		modelMatrix *= Transform2D::Scale(5, 5);
		RenderMesh2D(meshes["redHeart"], shaders["VertexColor"], modelMatrix);
	}
	// render the rest of the lives
	while (nr_lives != 3 ) {
		resetModelMatrix();
		modelMatrix *= Transform2D::Translate(10 + nr_lives * 50, resolution.y - 50);
		modelMatrix *= Transform2D::Scale(5, 5);
		RenderMesh2D(meshes["blackHeart"], shaders["VertexColor"], modelMatrix);
		nr_lives++;
	}

	
	// render the scorebar outline
	resetModelMatrix();
	modelMatrix *= Transform2D::Translate(bow.x - 30, bow.y - bow.length);
	modelMatrix *= Transform2D::Scale(10.2f, 12);
	RenderMesh2D(meshes["scorebarOutline"], shaders["VertexColor"], modelMatrix);

	// render the scorebar 
	resetModelMatrix();
	modelMatrix *= Transform2D::Translate(bow.x - 30, bow.y + 1 - bow.length);
	modelMatrix *= Transform2D::Scale(10 * arrowSpeed / (maxArrowSpeed), 10);
	RenderMesh2D(meshes["scorebar"], shaders["VertexColor"], modelMatrix);

	// render the arrows
	for (int i = 0; i < arrows.size(); i++) {
		arrows[i].MAX_HEIGHT = resolution.y;
		arrows[i].MAX_WIDTH = resolution.x;
		resetModelMatrix();
		
		arrows[i].move(&modelMatrix, deltaTimeSeconds); 
		if (!arrows[i].ready) {
			RenderMesh2D(meshes["arrow"], shaders["VertexColor"], modelMatrix);
		}
	}

	// logic for balloons
	for (int i = 0; i < balloons.size(); i++) {
		balloons[i].MAX_HEIGHT = resolution.y;
		balloons[i].MAX_WIDTH = resolution.x;

		resetModelMatrix();
		deltaTimeBalloon = (clock() - TimeZeroBalloons) / CLOCKS_PER_SEC;
		// if time passed and there is "free" balloons => generate balloons
		if (deltaTimeBalloon > delayBalloons && balloons[i].ready) {
			balloons[i].generateBalloon();
			//reset the clock timers
			deltaTimeBalloon = clock();
			TimeZeroBalloons = clock();
		}
		// if the balloon is used
		if (!balloons[i].ready) {
			// if the balloon was hit => scale it, and move down
			if (balloons[i].hit) {
				// move de balloon and make it broken
				balloons[i].move(&modelMatrix, deltaTimeSeconds, hitSpeed);
				modelMatrix *= Transform2D::Scale(0.5f, 1.0f);
			}
			else {
				balloons[i].move(&modelMatrix, deltaTimeSeconds, balloonSpeed);
			}

			RenderMesh2D(meshes[balloons[i].color], shaders["VertexColor"], modelMatrix);
			// rander the balloon tail
			// pay attention to the collor
			resetModelMatrix();
			modelMatrix *= Transform2D::Translate(balloons[i].x - 20, balloons[i].y -60);
			modelMatrix *= Transform2D::Scale(20, 20);
			if (balloons[i].color == "yellow-balloon") {
				RenderMesh2D(meshes["yellow-BalloonTail"], shaders["VertexColor"], modelMatrix);
			} else {
				RenderMesh2D(meshes["red-BalloonTail"], shaders["VertexColor"], modelMatrix);

			}
		}
	}

	// logic for shurikens
	for (int i = 0; i < shurikens.size(); i++) {
		shurikens[i].MAX_HEIGHT = resolution.y;
		shurikens[i].MAX_WIDTH = resolution.x;
		resetModelMatrix();
		deltaTimeShuriken = (clock() - TimeZeroShurikens) / CLOCKS_PER_SEC;
		// if time passed and there are "free" shurikens => generate shurikens
		if (deltaTimeShuriken > delayShurikens && (shurikens[i].x < -10 || shurikens[i].ready)) {
			shurikens[i].generateShuriken();
			//reset the clock timers
			deltaTimeShuriken = clock();
			TimeZeroShurikens = clock();
		}

		// if the shuriken is used
		if (!shurikens[i].ready) {
			// if the shuriken was hit => scale it and move down
			if (shurikens[i].hit) {
				shurikens[i].move(&modelMatrix, deltaTimeSeconds, hitSpeed);
				modelMatrix *= Transform2D::Scale(0.5f, 1.0f);
			}
			else {
				shurikens[i].move(&modelMatrix, deltaTimeSeconds, balloonSpeed);
			}
				RenderMesh2D(meshes["shuriken"], shaders["VertexColor"], modelMatrix);
		}
	}

	// check collisions for arrows with balloons
	for (int i = 0; i < arrows.size(); i++) {
		for (int j = 0; j < balloons.size(); j++) {
			if (!arrows[i].ready && !balloons[j].hit && checkArrowBalloonCollision(arrows[i], balloons[j])) {
				// mark balloon as hit
				if (balloons[j].color == "red-balloon") {
					score += 10;
				}
				else if (balloons[j].color == "yellow-balloon") {
					score -= 20;
				}
				std::cout << "Score: " << score << "\n";
				balloons[j].hit = true;


			}
		}
	}
	
	//check collisions for arrows with shurikens
	for (int i = 0; i < arrows.size(); i++) {
		for (int j = 0; j < shurikens.size(); j++) {
			if (!arrows[i].ready && !shurikens[j].hit && checkArrowShurikenCollision(arrows[i], shurikens[j])) {
				// mark shuriken as hit
				score += 40;
				std::cout << "Score: " << score << "\n";
				shurikens[j].hit = true;

			}
		}
	}

	//check collisions for bow with shurikens
		for (int i = 0; i < shurikens.size(); i++) {
			if (!shurikens[i].ready && checkBowShurikenCollision(bow, shurikens[i])) {
				// reset the balloon
				// balloons[j].scale(&modelMatrix, deltaTimeSeconds);
				lives--;
				shurikens[i].reset();
				std::cout << "You have " << lives << " lives!\n";
			}
		}
}

void Tema1::resetModelMatrix() {
	modelMatrix = glm::mat3(1);
}

bool Tema1::checkArrowBalloonCollision(Arrow arrow, Balloon balloon) {

	if (arrow.ready) {
		return false;
	}

	if (arrow.topX >= balloon.x - balloon.collisionX && arrow.topX <= balloon.x + balloon.collisionX &&
		arrow.topY >= balloon.y - balloon.collisionY && arrow.topY <= balloon.y + balloon.collisionY) {

		return true;
	}

	return false;
}

bool Tema1::checkArrowShurikenCollision(Arrow arrow, Shuriken shuriken) {

	if (arrow.ready) {
		return false;
	}

	if (arrow.topX >= shuriken.x - shuriken.collisionX && arrow.topX <= shuriken.x + shuriken.collisionX &&
		arrow.topY >= shuriken.y - shuriken.collisionY && arrow.topY <= shuriken.y + shuriken.collisionY) {
		return true;
	}

	return false;
}

bool Tema1::checkBowShurikenCollision(Bow bow, Shuriken shuriken) {

	float bowY = bow.y + bow.length/2;

	if (shuriken.x - shuriken.collisionX <= bow.x + 30 &&
		(shuriken.y + shuriken.collisionY >= bow.y - bow.length/2 && shuriken.y - shuriken.collisionY <= bowY)) {
		return true;
	}
	return false;
}

void Tema1::FrameEnd()
{

}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	if (window->KeyHold(GLFW_KEY_W)) {
		bow.moveUp(deltaTime);
	}

	if (window->KeyHold(GLFW_KEY_S)) {
		bow.moveDown(deltaTime);
	}
	if (window->MouseHold(GLFW_MOUSE_BUTTON_1)) {
		if (arrowSpeed <= maxArrowSpeed) {
			arrowSpeed += 20;
		}
	}

}

void Tema1::OnKeyPress(int key, int mods)
{
	// add key press event

	if (window->KeyHold(GLFW_KEY_SPACE)) {
		shoot(bow.x, bow.y, 1, 1, 400);
	}
}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event
}
// logic for creation and reusage of arrows
void Tema1::shoot(float xPos, float yPos, float mouseX, float mouseY, float speed) {
	bool free = false;

	// check if there is a ready arrow
	for (int i = 0; i < arrows.size(); i++) {
		// "use" the arrow
		if (arrows[i].ready) {
			arrows[i].ready = false;
			arrows[i].speed = speed;
			arrows[i].x = xPos;
			arrows[i].y = yPos;
			arrows[i].mouseX = mouseX;
			arrows[i].mouseY = window->GetResolution().y - mouseY;

			free = true;
			break;
		}
	}
	if (free == false) {
		std::cout << "Wait to recharge your arrows!\n";
	}
}
void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	bow.rotate(mouseX, mouseY);
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	shoot(bow.x, bow.y, mouseX, mouseY, arrowSpeed);
	arrowSpeed = defaultArrowSpeed;
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}
