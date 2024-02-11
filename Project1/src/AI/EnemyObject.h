#pragma once
#include "BaseEnemy.h"
#include "../model.h"

class GraphicsRender;

class EnemyObject : public BaseEnemy, public Model
{
	
public:

	EnemyObject();
	~EnemyObject();


	// Inherited via BaseEnemy
	void UpdateEnemy() override;
	void SetEnemyPosition(const glm::vec3& translation) override;
	void SetEnemyScale(const glm::vec3& scaling) override;
	void SetEnemyRotation(const glm::vec3& axis) override;

	// Inherited via Object
	 void DrawProperties() override;
	 void SceneDraw() override;

	 // Inherited via Entity
	 void Start() override;
	 void Update(float deltaTime) override;
	 void OnDestroy() override;

	 void SetTarget(Transform* transform);

	 void SetEnemyState(const EnemyBehaviourType& enemyType);


	 float speed = 2.0f;
private:


	void Seek();
	

	float deltaTime;
	const float enemyScaleValue = 0.25f;
	glm::vec3  direction;
	float currentDistance = 0;
	Transform* target;

	void Flee();

	float fleeStopDistance = 15;
	float fleeStartDistance = 5;
	float runSpeed = 8;
	
	bool isFleeing = false;


	void Pursue();

	float predictionTime = 5;
	

	void Evade();
	void EvadeMovement();
	float evadeDistance = 10;
	bool isEvading = false;

	void Approach();

	float slowingDistance = 7;
	float approachDistance = 6;




};

