#include "ThirdPersonCameraController.h"
#include "ImGui/EditorLayout.h"
ThirdPersonCameraController::ThirdPersonCameraController()
{
	name = "Thirdperson Camera";
	tag = "ThirdPersonCamera";
	playerController = nullptr;
}

ThirdPersonCameraController::ThirdPersonCameraController(PlayerController* player) : playerController(player)
{
	name = "Thirdperson Camera";
	tag = "ThirdPersonCamera";
}

ThirdPersonCameraController::~ThirdPersonCameraController()
{
}

void ThirdPersonCameraController::SetPlayer(Transform* player)
{
//	this->player = player;
}

void ThirdPersonCameraController::SetCamera(Camera* mainCamera)
{
	this->mainCamera = mainCamera;
}

void ThirdPersonCameraController::IntializeCamera()
{

	InitializeEntity(this);
}

void ThirdPersonCameraController::Start()
{

}

void ThirdPersonCameraController::Update(float deltaTime)
{
	this->deltaTime = deltaTime;

	CameraUpdate();
	MouseInput();

}

void ThirdPersonCameraController::OnDestroy()
{
}

void ThirdPersonCameraController::Destroy()
{
}

void ThirdPersonCameraController::DrawProperties()
{
	Entity::DrawProperties();
}

void ThirdPersonCameraController::SceneDraw()
{
	
}

void ThirdPersonCameraController::ProccessCameraMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	//xoffset *= 0.1f;
	//yoffset *= 0.1f;

	//mainCamera->transform.rotation.y = - xoffset;
	//mainCamera->transform.rotation.x += yoffset;

	////if (mainCamera->transform.rotation.y>60)
	////{
	////	mainCamera->transform.rotation.y = 60;
	////}
	//// if(mainCamera->transform.rotation.y < -60)
	////{
	////	mainCamera->transform.rotation.y = -60;
	////}
	//if (mainCamera->transform.rotation.z == 180 || mainCamera->transform.rotation.z == -180)
	//{
	//	if (mainCamera->transform.rotation.x > 89.0f + 180)	mainCamera->transform.rotation.x = 89.0f + 180;
	//	if (mainCamera->transform.rotation.x < -89.0f - 180)	mainCamera->transform.rotation.x = -89.0f - 180;
	//}
	//else
	//{
	//	if (mainCamera->transform.rotation.x > 89.0f)	mainCamera->transform.rotation.x = 89;
	//	if (mainCamera->transform.rotation.x < -89.0f)	mainCamera->transform.rotation.x = -89.0f;
	//}

	////mainCamera->transform.rotation.y = glm::clamp(mainCamera->transform.rotation.y, -60.0f, 60.0f);

	//mainCamera->transform.SetRotation(mainCamera->transform.rotation);
}

void ThirdPersonCameraController::SetPlayerController(PlayerController* player)
{
	this->playerController = player;
}

void ThirdPersonCameraController::MouseInput()
{
	
	glm::vec2 currentMousePosition = glm::vec2(InputManager::GetInstance().GetMouseX(), 
		InputManager::GetInstance().GetMouseY());

	if (lastMousePosition == glm::vec2(0))
	{
		lastMousePosition = currentMousePosition;
		return;
	}

	mouseDeltaPosition = lastMousePosition - currentMousePosition;


	yaw -= mouseDeltaPosition.x * rotaionSpeed * deltaTime;
	pitch += mouseDeltaPosition.y * rotaionSpeed * deltaTime;

	if (pitch < -maxPitchvalue) 
	{ 
		pitch = -maxPitchvalue;
	}
	if (pitch > maxPitchvalue) 
	{ 
		pitch = maxPitchvalue; 
	}

	lastMousePosition = currentMousePosition;
}

void ThirdPersonCameraController::CameraUpdate()
{
	
	cameraOffsetPosition = playerController->transform.position + cameraOffset;

	cameraForward = GetCameraForward();

	glm::vec3 cameraPosition = cameraOffsetPosition + (-cameraForward * followDistance);

	mainCamera->transform.SetPosition(cameraPosition);

	glm::quat rotation = glm::quatLookAt(cameraForward, UpVector);

	mainCamera->transform.SetQuatRotation(rotation);

}

glm::vec3 ThirdPersonCameraController::GetCameraForward()
{
	glm::vec3 forward;
	forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward.y = sin(glm::radians(pitch));
	forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	return glm::normalize(forward);
}