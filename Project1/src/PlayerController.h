#pragma once
#include "Renderer.h"
#include "model.h"

class GraphicsRender;

class PlayerController : public Model
{
public:
	PlayerController();
	~PlayerController();

    void InitializePlayer();
     void DrawProperties() override;
     void SceneDraw() override;

     void Start() override;
     void Update(float deltaTime) override;
     void OnDestroy()override;

     void OnKeyPressed(int key);
     void OnKeyReleased(int key);
     void OnKeyHold(int key);

     void MovePlayer(glm::vec3 movement);

private:

    float moveSpeed = 10;
    float deltaTime = 0;

    glm::vec2 keyPressed = glm::vec2(0);
    glm::vec3 playerRotation = glm::vec3(0,90,0);
    float playerScale = 0.25f;

};

