#pragma once
#include "BaseEnemy.h"
#include "../model.h"
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

	 void Seek();
	 void SetTarget(Transform* transform);

	 Transform* target;
};

