#pragma once
#include "glm/glm.hpp"
enum EnemyBehaviourType
{
	NONE =0,
	FLEE =1,
	SEEK =2
};

class BaseEnemy 
{
	
public :

	EnemyBehaviourType enemyType;

	virtual void UpdateEnemy() =0;

	virtual void SetEnemyPosition(const glm::vec3& translation)=0;
	virtual void SetEnemyScale(const glm::vec3& scaling)=0;
	virtual void SetEnemyRotation(const glm::vec3& axis)=0;
};

