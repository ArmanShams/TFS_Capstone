// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "MinerAnimInstance.h"
#include "EnemyAI/Enemy.h"
#include "EnemyAI/Miner/MinerAI.h"
#include "Weapons/Weapon.h"
#include "Weapons/Weapon_Melee.h"
#include "Weapons/Weapon_Ranged.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BrainComponent.h"
#include "AIController.h"

void UMinerAnimInstance::NativeInitializeAnimation()
{
	
	//if (EnemyCharacter)
	//{
	//	//PawnState = Cast<AMinerAI>(EnemyCharacter)->GetMinerState();
	//}
}

void UMinerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	
	Super::NativeUpdateAnimation(DeltaSeconds);

	EnemyCharacter = Cast<AMinerAI>(TryGetPawnOwner());

	if (EnemyCharacter)
	{
		CurrentMinerState = Cast<AMinerAI>(EnemyCharacter)->GetMinerState();
		bCanAttack = Cast<AMinerAI>(EnemyCharacter)->GetBTIsInRange();
	}
}

void UMinerAnimInstance::AnimNotify_MeleeAtkStart()
{
	if (bCanAttack)
	{
		//UE_LOG(LogTemp, Display, TEXT("We are in the beam"));
		//call a function on our characters to enable colliders on melee weapons
		if (AWeapon_Melee* EquippedWeapon = Cast<AWeapon_Melee>(EnemyCharacter->GetEquippedWeapon()))
		{
			EquippedWeapon->ToggleCollider();
		}
	}
}

void UMinerAnimInstance::AnimNotify_MeleeAtkEnd()
{
	//bCanAttack = false;
	if (AWeapon_Melee* EquippedWeapon = Cast<AWeapon_Melee>(EnemyCharacter->GetEquippedWeapon()))
	{
		EquippedWeapon->ToggleCollider();
		EquippedWeapon->bHasHit = false;
		//Cast<AMinerAI>(EnemyCharacter)->SetMinerState(MinerState::IDLE);
	}
	//call a function on our character to disable colliders on melee weapons
}

void UMinerAnimInstance::AnimNotify_ChargeEnd()
{
	//EnemyCharacter = Cast<AMinerAI>(TryGetPawnOwner());

	if (EnemyCharacter)
	{
		//EnemyCharacter->SetStatusEffect(CharacterState::NONE);
	}
}

void UMinerAnimInstance::AnimNotify_ReturnToIdle()
{
	//MarkedToReturnToIdleState
	if (EnemyCharacter)
	{
		if (UBlackboardComponent* BlackboardComponent = Cast<AAIController>(TryGetPawnOwner()->GetController())->GetBrainComponent()->GetBlackboardComponent())
		{
			BlackboardComponent->SetValueAsBool(TEXT("MarkedToReturnToIdleState"), true);
		}
	
	}
}

