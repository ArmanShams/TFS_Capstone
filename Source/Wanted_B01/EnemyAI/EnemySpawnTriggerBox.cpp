// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "EnemySpawnTriggerBox.h"

EnemySpawnTriggerBox::EnemySpawnTriggerBox() : triggered(false)
{
	//GetCollisionComponent()->OnComponentBeginOverlap.AddDynamic(this, &EnemySpawnTriggerBox::OnBeginOverlap);
	//GetCollisionComponent()->OnComponentEndOverlap.AddDynamic(this, &EnemySpawnTriggerBox::OnEndOverlap);

	if (!MaxTriggers)
	{
		MaxTriggers = 1;
	}
}

EnemySpawnTriggerBox::~EnemySpawnTriggerBox()
{

}

void EnemySpawnTriggerBox::OnBeginOverlap(AActor * Other, UPrimitiveComponent * Box, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & hitResult)
{
	AEnemy* Enemy = Cast<AEnemy>(Other);
	if (Enemy && !triggered && MaxTriggers > 0)
	{
		triggered = true;
		/* Player overlapped the Enemy Spawner, spawn appropriate enemies*/
		FActorSpawnParameters paramaters;
		//paramaters.Owner = this;
		paramaters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		//for (int i = 0; i < Count; ++i)
		//{
			//for (TSubclassOf<class AEnemy> enemy : CharatersToSpawn)
			//{
			//	logprint(enemy->GetClass()->GetName());
			//	if (SpawnLocation)
			//	{
			//		GetWorld()->SpawnActor<class AEnemy>(enemy, SpawnLocation->GetTransform(), paramaters);
			//	}
			//}
		//}
		MaxTriggers--;

	}
}


void EnemySpawnTriggerBox::OnEndOverlap(AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	AEnemy* Enemy = Cast<AEnemy>(OtherActor);
	if (Enemy && triggered)
	{
		triggered = false;
	}
}
