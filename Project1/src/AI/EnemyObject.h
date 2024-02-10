#pragma once
#include "BaseEnemy.h"
#include "../model.h"
class EnemyObject : public BaseEnemy, public Model
{
	
public:

	Transform* target;
	// Inherited via BaseEnemy
	void UpdateEnemy() override;
	void SetEnemyPosition(const glm::vec3& translation) override;
	void SetEnemyScale(const glm::vec3& scaling) override;
	void SetEnemyRotation(const glm::vec3& axis) override;

	 void DrawProperties() override;
	 void SceneDraw() override;

	 void Start() override;
	 void Update(float deltaTime) override;
	 void OnDestroy() override;

	 void Seek();
	 void SetTarget(Transform* transform);
};

