#include "EnemyObject.h"

void EnemyObject::UpdateEnemy()
{
	switch (enemyType)
	{
	case NONE:
		break;
	case FLEE:
		break;
	case SEEK:
		break;
	default:
		break;
	}
}

void EnemyObject::SetEnemyPosition(const glm::vec3& translation)
{
}

void EnemyObject::SetEnemyScale(const glm::vec3& scaling)
{
}

void EnemyObject::SetEnemyRotation(const glm::vec3& axis)
{
}

void EnemyObject::DrawProperties()
{
	Model::DrawProperties();
}

void EnemyObject::SceneDraw()
{
}

void EnemyObject::Start()
{
}

void EnemyObject::Update(float deltaTime)
{
	UpdateEnemy();
}

void EnemyObject::OnDestroy()
{
}

void EnemyObject::Seek()
{
}

void EnemyObject::SetTarget(Transform* transform)
{
	target = transform;
}
