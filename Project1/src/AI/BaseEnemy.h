#pragma once
#include "glm/glm.hpp"
enum EnemyBehaviourType
{
	NONE = 0,
	FLEE = 1,
	SEEK = 2,
	PURSUE = 3,
	EVADE = 4,
	APPROACH = 5, 
};

class BaseEnemy 
{
	
public :

	EnemyBehaviourType enemyType = EnemyBehaviourType::NONE;

	virtual void UpdateEnemy() =0;

	virtual void SetEnemyPosition(const glm::vec3& translation)=0;
	virtual void SetEnemyScale(const glm::vec3& scaling)=0;
	virtual void SetEnemyRotation(const glm::vec3& axis)=0;
};

