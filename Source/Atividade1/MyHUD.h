// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class ATIVIDADE1_API AMyHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	//Construtor da classe
	AMyHUD();

	//Objeto que representará a fonte a ser utilizada
	UPROPERTY(EditAnywhere)
		UFont* BaseFont;

	//Objeto que represetará a textura (imagem) referente a vida
	UPROPERTY(EditAnywhere)
		UTexture2D* LifeTexture;

	//Sobrescrita do método responsável por desenhar o HUD
	virtual void DrawHUD() override;
	
	
};
