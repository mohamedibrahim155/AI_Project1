#include "EnemyObject.h"

EnemyObject::EnemyObject()
{
	name = "Enemy";
}

EnemyObject::~EnemyObject()
{
}

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
	transform.SetPosition(translation);
}

void EnemyObject::SetEnemyScale(const glm::vec3& scaling)
{
	transform.SetScale(scaling);
}

void EnemyObject::SetEnemyRotation(const glm::vec3& axis)
{
	transform.SetRotation(axis);
}

void EnemyObject::DrawProperties()
{
	Model::DrawProperties();
}

void EnemyObject::SceneDraw()
{
	Model::SceneDraw();
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
