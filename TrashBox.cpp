#include "stdafx.h"
#include "TrashBox.h"

void TrashBox::Init()
{
	animator = gameObject->GetComponent<Animator>();

	CLIPMANAGER->AddClip("trashBox", "trashBox.bmp", 59, 45, 1, 1);
	
	animator->AddClip("trashBox", CLIPMANAGER->FindClip("trashBox"));
	animator->SetClip("trashBox");

}
