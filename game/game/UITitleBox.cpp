#include "stdafx.h"
#include "UITitleBox.h"

#include "CGame.h"

namespace GUI
{
TitleBox::TitleBox( Context * pcContext ) : Object( pcContext )
{
}

TitleBox::~TitleBox()
{
}

BOOL TitleBox::Init()
{
	BuildWindow1();

	return TRUE;
}

void TitleBox::HandleUpdate( StringHash cEventType, VariantMap & vEventData )
{
}

void TitleBox::BuildWindow1()
{
	auto * instructionText_ = new Text(context_);
	instructionText_->SetText( "Wrong Password. Try again!" );
	instructionText_->SetFont( RESOURCECACHE->GetResource<Font>( "Fonts/Anonymous Pro.ttf" ), 18 );
	instructionText_->SetColor( Color::CYAN );
	instructionText_->SetPosition( 0, 600 );
	instructionText_->SetTextEffect( TextEffect::TE_STROKE );

	//GetSubsystem<UI>()->GetRoot()->AddChild( instructionText_ );
}
}