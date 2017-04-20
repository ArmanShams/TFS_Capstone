// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "Lasso.h"

ALasso::ALasso()
{
	CableComponent = CreateDefaultSubobject<UCableComponent>(TEXT("CableComponent"));
}