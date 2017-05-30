// Fill out your copyright notice in the Description page of Project Settings.

#include "Atividade1.h"
#include "MyHUD.h"
#include "Personagem.h"

AMyHUD::AMyHUD() {

	//Carrega uma fonte disponível na Engine
	ConstructorHelpers::FObjectFinder<UFont> LoadFont
	(TEXT("Font'/Engine/EngineFonts/Roboto.Roboto'"));
	//Verifica se conseguiu carregar a fonte
	if (LoadFont.Succeeded()) {
		//Atribui a fonte obtida para a variável BaseFont.
		BaseFont = LoadFont.Object;
	}

	//Carrega a textura (imagem) referente a vida
	ConstructorHelpers::FObjectFinder<UTexture2D> LoadTexture
	(TEXT("Texture2D'/Game/Textures/Heart.Heart'"));
	//Verifica se conseguiu carregar a textura (imagem)
	if (LoadTexture.Succeeded()) {
		//Atribui a textura obtida para a variável LifeTexture.
		LifeTexture = LoadTexture.Object;
	}

}

void AMyHUD::DrawHUD() {
	//Chama o método DrawHUD da superclasse.
	Super::DrawHUD();

	//Obter o tamanho da tela
	FVector2D ScreenDimensions = FVector2D(Canvas->SizeX,
		Canvas->SizeY);

	//Obter o Pawn que está sendo controlado pelo Player
	APawn* Pawn = UGameplayStatics::GetPlayerPawn(this, 0);
	//Realiza o cast de Pawn para Personagem
	APersonagem* Personagem = Cast<APersonagem>(Pawn);

	//Definir o que será escrito na tela
	//É necessário criar FStrings
	//https://wiki.unrealengine.com/Logs,_Printing_Messages_To_Yourself_During_Runtime
	FString LifeString = FString::Printf(TEXT("Life: %d"),
		Personagem->GetLife());
	FString CollectedString = FString::Printf(TEXT("%d / 10"),
		Personagem->GetCollected());

	//Desenha a string referente a vida do personagem, com cor
	//vermelha, nas posições X = 200 e Y = 50, utilizando a fonte
	//BaseFont com escala 2.0
	//DrawText(LifeString, FColor::Red, 200, 50, BaseFont, 2.0f);
	DrawText(CollectedString, FColor::Blue,
		ScreenDimensions.X - 300, 50, BaseFont, 2.0f);

	
	float PositionX = 200;
	for (int i = 0; i < Personagem->GetLife(); i++) {
		DrawTextureSimple(LifeTexture, PositionX, 50, 0.3f);
		PositionX += 50.0f;
	}

}



