// Fill out your copyright notice in the Description page of Project Settings.


#include "NSmallCoinItem.h"

ANSmallCoinItem::ANSmallCoinItem()
{
	PointValue = 10;
	ItemType = "SmallCoin";
}

void ANSmallCoinItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
}
