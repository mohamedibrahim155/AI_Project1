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
	LoadModel("Models/Player/Player1.ply");
	
	transform.SetPosition(glm::vec3(0, 0, 5));
	transform.SetScale(glm::vec3(playerScale));
	
	meshes[0]->meshMaterial->material()->SetBaseColor(glm::vec4(0.75f, 0.25f, 0, 1));
	GraphicsRender::GetInstance().AddModelAndShader(this, GraphicsRender::GetInstance().defaultShader);
}

void PlayerController::DrawProperties()
{
	Model::DrawProperties();

	ImGui::NewLine();
	if (!ImGui::TreeNodeEx("Player Properties", ImGuiTreeNodeFlags_DefaultOpen))
	{
		return;
	}

	ImGui::InputFloat("Player Speed", &moveSpeed);

	ImGui::TreePop();
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
	UpdateMouseAxis();
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
		keyPressed.y = -1;

		isUpPressed = true;
	}
	else if (key == GLFW_KEY_A)
	{
		keyPressed.x = -1;

		isRightPressed = true;
	}
	else if (key == GLFW_KEY_S)
	{
		keyPressed.y = 1;

		isDownPressed = true;
	}
	else if (key == GLFW_KEY_D)
	{
		keyPressed.x = 1;

		isLeftPressed = true;
	}
}

void PlayerController::OnKeyReleased(int key)
{
	if (key == GLFW_KEY_W)
	{
		keyPressed.y = 0;

		isUpPressed = false;
	}
	else if (key == GLFW_KEY_A)
	{
		keyPressed.x = 0;

		isRightPressed = false;

	}
	else if (key == GLFW_KEY_S)
	{
		keyPressed.y = 0;

		isDownPressed = false;

	}
	else if (key == GLFW_KEY_D)
	{
		keyPressed.x =0;

		isLeftPressed = false;

	}
}

void PlayerController::OnKeyHold(int key)
{
	if (key == GLFW_KEY_W)
	{
		keyPressed.y = -1;
	}
	else if (key == GLFW_KEY_A)
	{
		keyPressed.x = -1;
	}
	else if (key == GLFW_KEY_S)
	{
		keyPressed.y = 1;
	}
	else if (key == GLFW_KEY_D)
	{
		keyPressed.x = 1;
	}
}

void PlayerController::MovePlayer(glm::vec3 movement)
{

	transform.position += transform.GetForward() * -mouseDirection.y *
		moveSpeed * deltaTime;

	transform.position += transform.GetRight() * mouseDirection.x *
		moveSpeed * deltaTime;

	glm::vec3 rotation = transform.rotation;

	if (mainCamera == nullptr) return;

	rotation.y = mainCamera->transform.rotation.y + 180;

     transform.SetRotation(rotation);
	//transform.position += movement * moveSpeed * deltaTime;
}

void PlayerController::SetCamera(Camera* camera)
{
	this->mainCamera = camera;
}

	


void PlayerController::UpdateMouseAxis()
{
	xMouseAxis = 0;
	yMouseAxis = 0;

	xMouseAxis += isRightPressed ? 1 : 0;
	xMouseAxis -= isLeftPressed ? 1 : 0;

	yMouseAxis += isUpPressed ? 1 : 0;
	yMouseAxis -= isDownPressed ? 1 : 0;

	mouseDirection.x = xMouseAxis;
	mouseDirection.y = yMouseAxis;

	if (glm::length(mouseDirection)!=0)
	{
		mouseDirection = glm::normalize(mouseDirection);
	}
}
