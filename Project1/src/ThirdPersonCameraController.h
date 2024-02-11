#pragma once
#include "Camera.h"
#include "EntityManager/Entity.h"
#include "InputManager.h"
#include "PlayerController.h"

class ThirdPersonCameraController : public Entity
{
public:
	ThirdPersonCameraController();
	ThirdPersonCameraController(PlayerController* player);
	~ThirdPersonCameraController();



	void SetPlayer(Transform* player);
	void SetCamera(Camera* mainCamera);
	void IntializeCamera();


	// Inherited via Entity
	void Start() override;

	void Update(float deltaTime) override;

	void OnDestroy() override;

	 void Destroy() override;

	//Inherited from Object
     void DrawProperties() override;
     void SceneDraw() override;

	 void ProccessCameraMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	 void SetPlayerController(PlayerController* player);

	 void MouseInput();
	 void CameraUpdate();

	 glm::vec3 GetCameraForward();

private :
	Camera* mainCamera = nullptr;
	 PlayerController* playerController = nullptr;

	 float rotaionSpeed =30;
	 float pitch = 0;
	 float yaw = -90;
	 float maxPitchvalue = 70;

	 float deltaTime;
	 float followDistance = 15;

	 glm::vec2 lastMousePosition;
	 glm::vec2 mouseDeltaPosition;

	 glm::vec3 cameraForward =  glm::vec3(0,0,-1);
	 glm::vec3 cameraOffsetPosition;
	 glm::vec3 cameraOffset = glm::vec3(5, 3, 0);
	 glm::vec3 UpVector = glm::vec3(0, 1, 0);

};

