#include "EnemyObject.h"
#include "../GraphicsRender.h"
EnemyObject::EnemyObject()
{
	name = "Enemy";

	LoadModel("Models/Zombie/zombies.obj");
	transform.SetScale(glm::vec3(enemyScaleValue));
	GraphicsRender::GetInstance().AddModelAndShader(this, GraphicsRender().GetInstance().defaultShader);

	SetEnemyState(EnemyBehaviourType::NONE);
}

EnemyObject::~EnemyObject()
{
}

void EnemyObject::UpdateEnemy()
{
	if (target == nullptr) return;

	switch (enemyType)
	{
	case NONE:
		break;
	case FLEE:
		Flee();
		break;
	case SEEK:
		Seek();
		break;
	case PURSUE:
		Pursue();
		break;
	case EVADE:
		Evade();
		break;
	case APPROACH:
		Approach();
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

	//ImGui::Columns(2);
	
	//ImGui::Text("isFlee state");
	//ImGui::NextColumn();

	ImGui::Columns(2);
	ImGui::Spacing();
	ImGui::SetColumnWidth(0, 150);
	ImGui::Checkbox("Is Flee", &isFleeing);
	ImGui::NextColumn();


	ImGui::Columns(3);
	ImGui::SetColumnWidth(0, 150);
	ImGui::InputFloat("Current Distance", &currentDistance);
	ImGui::NextColumn();

	ImGui::Columns(3);


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
	this->deltaTime = deltaTime;

	UpdateEnemy();
}

void EnemyObject::OnDestroy()
{
}

void EnemyObject::Seek()
{
	

	direction = target->position - transform.position;

	if (glm::length(direction) != 0)
	{
		direction = glm::normalize(direction);
	}

	glm::quat rotation = glm::quatLookAt(-direction, glm::vec3(0, 1, 0));

	transform.SetQuatRotation(rotation);

	transform.position += direction * speed * deltaTime;
}

void EnemyObject::Flee()
{
	

	direction = transform.position - target->position;

	currentDistance = glm::length(direction);

	if (currentDistance != 0)
	{
		direction = glm::normalize(direction);
	}


	glm::quat rotation = glm::quatLookAt(direction * (isFleeing ? -1.0f : 1.0f), glm::vec3(0, 1, 0));

	transform.SetQuatRotation(rotation);

	if (!isFleeing)
	{
		if (currentDistance <= fleeStartDistance)
		{
			isFleeing = true;
			return;
		}
		
	}
	else
	{
		if (currentDistance >= fleeStopDistance)
		{
			isFleeing = false;
			return;
		}
		transform.position += direction * runSpeed * deltaTime;

	}
	
}

void EnemyObject::Pursue()
{
	
	glm::vec3 predictedTarget = target->position + target->GetForward() * predictionTime;

	direction = (predictedTarget - transform.position);

	currentDistance = glm::length(direction);

	if (currentDistance != 0)
	{
		direction = glm::normalize(direction);
	}

	if (currentDistance <= 1) return;

	glm::quat rotationQuat = glm::quatLookAt(-direction, glm::vec3(0, 1, 0));

	transform.SetQuatRotation(rotationQuat);

	transform.position += direction * speed * deltaTime;
}

void EnemyObject::Evade()
{

	//void Update()
	//{
	//	

	//	// Calculate the predicted future position based on a constant prediction time
	//	Vector3 predictedTarget = target.position + target.forward * predictionTime;

	//	Vector3 direction = (transform.position - predictedTarget).normalized;

	//	transform.position += direction * speed * Time.deltaTime;
	//}


	glm::vec3  predictedTarget = target->position + target->GetForward() * predictionTime;

	direction = (transform.position - predictedTarget);

	currentDistance = glm::length(direction);

	if (currentDistance!= 0)
	{
		direction = glm::normalize(direction);
	}
	

	EvadeMovement();
;

	glm::quat rotationQuat = glm::quatLookAt(direction * (isEvading ? -1.0f : 1.0f), glm::vec3(0, 1, 0));
	transform.SetQuatRotation(rotationQuat);
}

void EnemyObject::EvadeMovement()
{

	isEvading = false;
	if (currentDistance > evadeDistance) return;

	transform.position += direction * speed * deltaTime;

	isEvading = true;
}

void EnemyObject::Approach()
{
	direction = target->position - transform.position;

	currentDistance = glm::length(direction);

	if (currentDistance != 0)
	{
		direction = glm::normalize(direction);
	}

	float adjustedSpeed = speed;
	if (currentDistance < approachDistance)
	{
		// Gradually reduce speed as it approaches the target
		adjustedSpeed *= glm::max(0.0f, currentDistance / slowingDistance);
	}
	if (currentDistance<=1)
	{
		return;
	}

	transform.position += direction * adjustedSpeed * deltaTime;


	glm::quat rotationQuat = glm::quatLookAt(-direction, glm::vec3(0, 1, 0));

	transform.SetQuatRotation(rotationQuat);



}

void EnemyObject::SetTarget(Transform* transform)
{
	target = transform;
}

void EnemyObject::SetEnemyState(const EnemyBehaviourType& enemyType)
{
	this->enemyType = enemyType;
}
