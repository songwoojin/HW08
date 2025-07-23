// Fill out your copyright notice in the Description page of Project Settings.


#include "NBigCoinItem.h"

ANBigCoinItem::ANBigCoinItem()
{
	PointValue = 50;
	ItemType = "BigCoin";
}

void ANBigCoinItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
}
