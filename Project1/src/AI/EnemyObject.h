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
	 void SetColor(const EnemyBehaviourType& enemyType);

	 float speed = 5;
private:

	void Seek();
	void Flee();
	
	void Pursue();
	void PursueRotation();

	void Evade();
	void EvadeMovement();

	void Approach();

	Transform* target;

	bool isFleeing = false;
	bool isEvading = false;

	const float enemyScaleValue = 0.25f;
	float deltaTime;
	float currentDistance = 0;
	float fleeStopDistance = 25;
	float fleeStartDistance = 5;
	float runSpeed = 15;
	float predictionTime = 5;
	float evadeDistance = 15;
	float slowingDistance = 6;
	float approachDistance = 6;

	glm::vec3  direction;
	glm::vec4 currentColor;

	glm::vec4 enemyStateColors[6] =
	{   glm::vec4(1,1,1,1),  //None
		glm::vec4(1,0,0,1),  // SEEK
		glm::vec4(0,1,0,1),  // FLEE
		glm::vec4(0,0,1,1),  // PURSUE
		glm::vec4(1,0,1,1),  // EVADE
		glm::vec4(1,1,0,1),  // APROACH
	};


};

