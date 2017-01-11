// Fill out your copyright notice in the Description page of Project Settings.
// this is the enemy base class which will derive the enemys health, attacks, and status effects.

#include "Wanted_B01.h"
#include "Enemy.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Health = 100;

	MoveSpeed = .4f;

	TurnRate = 0.25f;

	Range = 1.0f;

	Skill1Cooldown = 5.0f;

	Skill2Cooldown = 5.0f;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	EnemyState = EState::Idle;
}

// Called every frame
void AEnemy::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AEnemy::Enemy()
{
	//kills nothing, does nothing. 
	//if (isPhil == true)
	//{
	//philbertSuspended = PhilbertDoesStupid + ArmanFlipsShit;
	//}
}

void AEnemy::BasicAttack(Effects effect, float Range)
{
	//attack has effect application

	//range also gets applied for specific attack

}

void AEnemy::Skill1(Effects effect, float Range)
{
	//attack has effect application

	//range also gets applied for specific attack

}

void AEnemy::Skill2(Effects effect, float Range)
{
	//attack has effect application

	//range also gets applied for specific attack

}



