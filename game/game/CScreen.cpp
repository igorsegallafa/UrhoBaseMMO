#include "stdafx.h"
#include "CScreen.h"

void CScreen::Init()
{
	//Criar a Cena
	pScene = new Scene( context_ );
}

void CScreen::Run()
{
	if( pScene )
		pScene->SetUpdateEnabled( true );
}

void CScreen::Pause()
{
	if( pScene )
		pScene->SetUpdateEnabled( false );
}

void CScreen::Dispose()
{
	//Pausa a cena e remove todo conteúdo dela
	if( pScene )
	{
		pScene->SetUpdateEnabled( false );
		pScene->Clear();
		pScene->Remove();
	}

	USERINTERFACE->GetRoot()->RemoveAllChildren();
}