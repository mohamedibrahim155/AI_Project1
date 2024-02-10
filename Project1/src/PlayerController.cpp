#include "PlayerController.h"
#include "GraphicsRender.h"
PlayerController::PlayerController()
{
	name = "Player Controller";
	tag = "Player";
	
	InitializePlayer();
}

PlayerController::~PlayerController()
{
}

void PlayerController::InitializePlayer()
{
	LoadModel("Models/Player/Player.fbx");

	transform.SetScale(glm::vec3(playerScale));
	transform.SetRotation(glm::vec3(playerRotation));

	GraphicsRender::GetInstance().AddModelAndShader(this, GraphicsRender::GetInstance().defaultShader);
}

void PlayerController::DrawProperties()
{
	Model::DrawProperties();
}

void PlayerController::SceneDraw()
{
	Model::SceneDraw();
}

void PlayerController::Start()
{
}

void PlayerController::Update(float deltaTime)
{
	this->deltaTime = deltaTime;

	glm::vec3 playerMovement = glm::vec3(keyPressed.x, 0, keyPressed.y);

	MovePlayer(playerMovement);
}

void PlayerController::OnDestroy()
{
}

void PlayerController::OnKeyPressed(int key)
{
	if (key == GLFW_KEY_W)
	{
		keyPressed.y = 1;
	}
	else if (key == GLFW_KEY_A)
	{
		keyPressed.x = 1;
	}
	else if (key == GLFW_KEY_S)
	{
		keyPressed.y = -1;
	}
	else if (key == GLFW_KEY_D)
	{
		keyPressed.x = -1;
	}
}

void PlayerController::OnKeyReleased(int key)
{
	if (key == GLFW_KEY_W)
	{
		keyPressed.y = 0;
	}
	else if (key == GLFW_KEY_A)
	{
		keyPressed.x = 0;

	}
	else if (key == GLFW_KEY_S)
	{
		keyPressed.y = 0;

	}
	else if (key == GLFW_KEY_D)
	{
		keyPressed.x =0;

	}
}

void PlayerController::OnKeyHold(int key)
{
	if (key == GLFW_KEY_W)
	{
		keyPressed.y = 1;
	}
	else if (key == GLFW_KEY_A)
	{
		keyPressed.x = 1;
	}
	else if (key == GLFW_KEY_S)
	{
		keyPressed.y = -1;
	}
	else if (key == GLFW_KEY_D)
	{
		keyPressed.x = -1;
	}
}

void PlayerController::MovePlayer(glm::vec3 movement)
{
	transform.SetPosition(transform.position + movement * moveSpeed * deltaTime);
}
