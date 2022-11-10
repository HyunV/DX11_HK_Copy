#include "TransformWindow.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorLabel.h"
#include "Editor/EditorImage.h"
#include "Editor/EditorText.h"
#include "Editor/EditorInput.h"
#include "Editor/EditorListBox.h"
#include "Editor/EditorComboBox.h"
#include "Editor/EditorTree.h"
#include "Component/SceneComponent.h"

CTransformWindow::CTransformWindow()
{
}

CTransformWindow::~CTransformWindow()
{
}

void CTransformWindow::SetSelectComponent(CSceneComponent* Component)
{
	m_SelectComponent = Component;
}

void CTransformWindow::SetPos(const Vector3& Pos)
{
	m_Pos[0]->SetFloat(Pos.x);
	m_Pos[1]->SetFloat(Pos.y);
	m_Pos[2]->SetFloat(Pos.z);
}

void CTransformWindow::SetRotation(const Vector3& Rot)
{
	m_Rot[0]->SetFloat(Rot.x);
	m_Rot[1]->SetFloat(Rot.y);
	m_Rot[2]->SetFloat(Rot.z);
}

void CTransformWindow::SetScale(const Vector3& Scale)
{
	m_Scale[0]->SetFloat(Scale.x);
	m_Scale[1]->SetFloat(Scale.y);
	m_Scale[2]->SetFloat(Scale.z);
}

void CTransformWindow::SetRelativePos(const Vector3& Pos)
{
	m_RPos[0]->SetFloat(Pos.x);
	m_RPos[1]->SetFloat(Pos.y);
	m_RPos[2]->SetFloat(Pos.z);
}
void CTransformWindow::SetRelativeRotation(const Vector3& Rot)
{
	m_RRot[0]->SetFloat(Rot.x);
	m_RRot[1]->SetFloat(Rot.y);
	m_RRot[2]->SetFloat(Rot.z);
}
void CTransformWindow::SetRelativeScale(const Vector3& Scale)
{
	m_RScale[0]->SetFloat(Scale.x);
	m_RScale[1]->SetFloat(Scale.y);
	m_RScale[2]->SetFloat(Scale.z);
}

void CTransformWindow::SetPivot(const Vector3& Pivot)
{
	m_Pivot[0]->SetFloat(Pivot.x);
	m_Pivot[1]->SetFloat(Pivot.y);
	m_Pivot[2]->SetFloat(Pivot.z);
}

bool CTransformWindow::Init()
{
	CEditorLabel* Label = CreateWidget<CEditorLabel>("월드 위치");

	Label->SetColor(255, 0, 0, 255);
	Label->SetAlign(0.5f, 0.5f);
	Label->SetSizeY(30.f);

	CEditorSameLine* Line = CreateWidget<CEditorSameLine>("Line");

	m_Pos[0] = CreateWidget<CEditorInput>("PosX", 80.f, 30.f);
	m_Pos[0]->SetHideName("PosX");
	m_Pos[0]->SetInputType(EImGuiInputType::Float);

	Line = CreateWidget<CEditorSameLine>("Line");

	m_Pos[1] = CreateWidget<CEditorInput>("PosY", 80.f, 30.f);
	m_Pos[1]->SetHideName("PosY");
	m_Pos[1]->SetInputType(EImGuiInputType::Float);

	Line = CreateWidget<CEditorSameLine>("Line");

	m_Pos[2] = CreateWidget<CEditorInput>("PosZ", 80.f, 30.f);
	m_Pos[2]->SetHideName("PosZ");
	m_Pos[2]->SetInputType(EImGuiInputType::Float);

	// ============== Rotation
	Label = CreateWidget<CEditorLabel>("월드 회전");

	Label->SetColor(255, 0, 0, 255);
	Label->SetAlign(0.5f, 0.5f);
	Label->SetSizeY(30.f);

	Line = CreateWidget<CEditorSameLine>("Line");

	m_Rot[0] = CreateWidget<CEditorInput>("RotX", 80.f, 30.f);
	m_Rot[0]->SetHideName("RotX");
	m_Rot[0]->SetInputType(EImGuiInputType::Float);

	Line = CreateWidget<CEditorSameLine>("Line");

	m_Rot[1] = CreateWidget<CEditorInput>("RotY", 80.f, 30.f);
	m_Rot[1]->SetHideName("RotY");
	m_Rot[1]->SetInputType(EImGuiInputType::Float);

	Line = CreateWidget<CEditorSameLine>("Line");

	m_Rot[2] = CreateWidget<CEditorInput>("RotZ", 80.f, 30.f);
	m_Rot[2]->SetHideName("RotZ");
	m_Rot[2]->SetInputType(EImGuiInputType::Float);

	// ============== Scale
	Label = CreateWidget<CEditorLabel>("월드 크기");

	Label->SetColor(255, 0, 0, 255);
	Label->SetAlign(0.5f, 0.5f);
	Label->SetSizeY(30.f);

	Line = CreateWidget<CEditorSameLine>("Line");

	m_Scale[0] = CreateWidget<CEditorInput>("ScaleX", 80.f, 30.f);
	m_Scale[0]->SetHideName("ScaleX");
	m_Scale[0]->SetInputType(EImGuiInputType::Float);

	Line = CreateWidget<CEditorSameLine>("Line");

	m_Scale[1] = CreateWidget<CEditorInput>("ScaleY", 80.f, 30.f);
	m_Scale[1]->SetHideName("ScaleY");
	m_Scale[1]->SetInputType(EImGuiInputType::Float);

	Line = CreateWidget<CEditorSameLine>("Line");

	m_Scale[2] = CreateWidget<CEditorInput>("ScaleZ", 80.f, 30.f);
	m_Scale[2]->SetHideName("ScaleZ");
	m_Scale[2]->SetInputType(EImGuiInputType::Float);
	
	//===================피봇

	//피봇
	Label = CreateWidget<CEditorLabel>("피봇");

	Label->SetColor(255, 0, 255, 255);
	Label->SetAlign(0.5f, 0.5f);
	Label->SetSizeY(30.f);

	Line = CreateWidget<CEditorSameLine>("Line");

	m_Pivot[0] = CreateWidget<CEditorInput>("PivotX", 80.f, 30.f);
	m_Pivot[0]->SetHideName("PivotX");
	m_Pivot[0]->SetInputType(EImGuiInputType::Float);

	Line = CreateWidget<CEditorSameLine>("Line");

	m_Pivot[1] = CreateWidget<CEditorInput>("PivotY", 80.f, 30.f);
	m_Pivot[1]->SetHideName("PivotY");
	m_Pivot[1]->SetInputType(EImGuiInputType::Float);

	Line = CreateWidget<CEditorSameLine>("Line");

	m_Pivot[2] = CreateWidget<CEditorInput>("PivotZ", 80.f, 30.f);
	m_Pivot[2]->SetHideName("PivotZ");
	m_Pivot[2]->SetInputType(EImGuiInputType::Float);


	//=================Relative Pos

	//Label = CreateWidget<CEditorLabel>(" ");
	//Label->SetColor(0, 0, 0, 0);

	Label = CreateWidget<CEditorLabel>("상대 위치");

	Label->SetColor(0, 0, 255, 255);
	Label->SetAlign(0.5f, 0.5f);
	Label->SetSizeY(30.f);

	Line = CreateWidget<CEditorSameLine>("Line");

	m_RPos[0] = CreateWidget<CEditorInput>("RPosX", 80.f, 30.f);
	m_RPos[0]->SetHideName("RPosX");
	m_RPos[0]->SetInputType(EImGuiInputType::Float);

	Line = CreateWidget<CEditorSameLine>("Line");

	m_RPos[1] = CreateWidget<CEditorInput>("RPosY", 80.f, 30.f);
	m_RPos[1]->SetHideName("RPosY");
	m_RPos[1]->SetInputType(EImGuiInputType::Float);

	Line = CreateWidget<CEditorSameLine>("Line");

	m_RPos[2] = CreateWidget<CEditorInput>("RPosZ", 80.f, 30.f);
	m_RPos[2]->SetHideName("RPosZ");
	m_RPos[2]->SetInputType(EImGuiInputType::Float);

	// ============== Relative Rotation
	Label = CreateWidget<CEditorLabel>("상대 회전");

	Label->SetColor(0, 0, 255, 255);
	Label->SetAlign(0.5f, 0.5f);
	Label->SetSizeY(30.f);

	Line = CreateWidget<CEditorSameLine>("Line");

	m_RRot[0] = CreateWidget<CEditorInput>("RRotX", 80.f, 30.f);
	m_RRot[0]->SetHideName("RRotX");
	m_RRot[0]->SetInputType(EImGuiInputType::Float);

	Line = CreateWidget<CEditorSameLine>("Line");

	m_RRot[1] = CreateWidget<CEditorInput>("RRotY", 80.f, 30.f);
	m_RRot[1]->SetHideName("RRotY");
	m_RRot[1]->SetInputType(EImGuiInputType::Float);

	Line = CreateWidget<CEditorSameLine>("Line");

	m_RRot[2] = CreateWidget<CEditorInput>("RRotZ", 80.f, 30.f);
	m_RRot[2]->SetHideName("RRotZ");
	m_RRot[2]->SetInputType(EImGuiInputType::Float);

	// ============== Scale
	Label = CreateWidget<CEditorLabel>("상대 크기");

	Label->SetColor(0, 0, 255, 255);
	Label->SetAlign(0.5f, 0.5f);
	Label->SetSizeY(30.f);

	Line = CreateWidget<CEditorSameLine>("Line");

	m_RScale[0] = CreateWidget<CEditorInput>("RScaleX", 80.f, 30.f);
	m_RScale[0]->SetHideName("RScaleX");
	m_RScale[0]->SetInputType(EImGuiInputType::Float);

	Line = CreateWidget<CEditorSameLine>("Line");

	m_RScale[1] = CreateWidget<CEditorInput>("RScaleY", 80.f, 30.f);
	m_RScale[1]->SetHideName("RScaleY");
	m_RScale[1]->SetInputType(EImGuiInputType::Float);

	Line = CreateWidget<CEditorSameLine>("Line");

	m_RScale[2] = CreateWidget<CEditorInput>("RScaleZ", 80.f, 30.f);
	m_RScale[2]->SetHideName("RScaleZ");
	m_RScale[2]->SetInputType(EImGuiInputType::Float);

	//콜백
	m_Pos[0]->SetInputCallback<CTransformWindow>(this, &CTransformWindow::PosXCallback);
	m_Pos[1]->SetInputCallback<CTransformWindow>(this, &CTransformWindow::PosYCallback);
	m_Pos[2]->SetInputCallback<CTransformWindow>(this, &CTransformWindow::PosZCallback);

	m_Rot[0]->SetInputCallback<CTransformWindow>(this, &CTransformWindow::RotXCallback);
	m_Rot[1]->SetInputCallback<CTransformWindow>(this, &CTransformWindow::RotYCallback);
	m_Rot[2]->SetInputCallback<CTransformWindow>(this, &CTransformWindow::RotZCallback);

	m_Scale[0]->SetInputCallback<CTransformWindow>(this, &CTransformWindow::ScaleXCallback);
	m_Scale[1]->SetInputCallback<CTransformWindow>(this, &CTransformWindow::ScaleYCallback);
	m_Scale[2]->SetInputCallback<CTransformWindow>(this, &CTransformWindow::ScaleZCallback);

	//상대좌표 콜백
	m_RPos[0]->SetInputCallback<CTransformWindow>(this, &CTransformWindow::RelativePosXCallback);
	m_RPos[1]->SetInputCallback<CTransformWindow>(this, &CTransformWindow::RelativePosYCallback);
	m_RPos[2]->SetInputCallback<CTransformWindow>(this, &CTransformWindow::RelativePosZCallback);

	m_RRot[0]->SetInputCallback<CTransformWindow>(this, &CTransformWindow::RelativeRotXCallback);
	m_RRot[1]->SetInputCallback<CTransformWindow>(this, &CTransformWindow::RelativeRotYCallback);
	m_RRot[2]->SetInputCallback<CTransformWindow>(this, &CTransformWindow::RelativeRotZCallback);

	m_RScale[0]->SetInputCallback<CTransformWindow>(this, &CTransformWindow::RelativeScaleXCallback);
	m_RScale[1]->SetInputCallback<CTransformWindow>(this, &CTransformWindow::RelativeScaleYCallback);
	m_RScale[2]->SetInputCallback<CTransformWindow>(this, &CTransformWindow::RelativeScaleZCallback);

	//피봇 콜백
	m_Pivot[0]->SetInputCallback<CTransformWindow>(this, &CTransformWindow::PivotCallback);
	m_Pivot[1]->SetInputCallback<CTransformWindow>(this, &CTransformWindow::PivotCallback);
	m_Pivot[2]->SetInputCallback<CTransformWindow>(this, &CTransformWindow::PivotCallback);

	return true;
}

void CTransformWindow::Update(float DeltaTime)
{
	CEditorWindow::Update(DeltaTime);

	if (m_SelectComponent)
	{
		if (!m_SelectComponent->GetActive())
			m_SelectComponent = nullptr;
	}
}

void CTransformWindow::PosXCallback()
{
	if (m_SelectComponent)
	{
		m_SelectComponent->SetWorldPositionX(m_Pos[0]->GetFloat());

	}
}

void CTransformWindow::PosYCallback()
{
	if (m_SelectComponent)
	{
		m_SelectComponent->SetWorldPositionY(m_Pos[1]->GetFloat());
	}
}

void CTransformWindow::PosZCallback()
{
	if (m_SelectComponent)
	{
		m_SelectComponent->SetWorldPositionZ(m_Pos[2]->GetFloat());
	}
}

void CTransformWindow::RotXCallback()
{
	if (m_SelectComponent)
	{
		m_SelectComponent->SetWorldRotationX(m_Rot[0]->GetFloat());		
	}
}

void CTransformWindow::RotYCallback()
{
	if (m_SelectComponent)
	{
		m_SelectComponent->SetWorldRotationZ(m_Rot[1]->GetFloat());	
	}
}

void CTransformWindow::RotZCallback()
{
	if (m_SelectComponent)
	{
		m_SelectComponent->SetWorldRotationZ(m_Rot[2]->GetFloat());
	}
}

void CTransformWindow::ScaleXCallback()
{
	if (m_SelectComponent)
	{
		m_SelectComponent->SetWorldScaleX(m_Scale[0]->GetFloat());
	}
}

void CTransformWindow::ScaleYCallback()
{
	if (m_SelectComponent)
	{
		m_SelectComponent->SetWorldScaleY(m_Scale[1]->GetFloat());
	}
}

void CTransformWindow::ScaleZCallback()
{
	if (m_SelectComponent)
	{
		m_SelectComponent->SetWorldScaleZ(m_Scale[2]->GetFloat());
	}		
}
//부모가 있을 때 상대좌표
void CTransformWindow::RelativePosXCallback()
{
	if (m_SelectComponent)
	{
		if (m_SelectComponent->GetParent())
		{
			m_SelectComponent->SetRelativePositionX(m_RPos[0]->GetFloat());
		}
	}
}
void CTransformWindow::RelativePosYCallback()
{
	if (m_SelectComponent)
	{
		if (m_SelectComponent->GetParent())
		{
			m_SelectComponent->SetRelativePositionY(m_RPos[1]->GetFloat());
		}
	}
}
void CTransformWindow::RelativePosZCallback()
{
	if (m_SelectComponent)
	{
		if (m_SelectComponent->GetParent())
		{
			m_SelectComponent->SetRelativePositionZ(m_RPos[2]->GetFloat());
		}
	}
}
void CTransformWindow::RelativeRotXCallback()
{
	if (m_SelectComponent)
	{
		if (m_SelectComponent->GetParent())
		{
			m_SelectComponent->SetRelativeRotationY(m_RRot[0]->GetFloat());
		}
	}
}
void CTransformWindow::RelativeRotYCallback()
{
	if (m_SelectComponent)
	{
		if (m_SelectComponent->GetParent())
		{
			m_SelectComponent->SetRelativeRotationY(m_RRot[1]->GetFloat());
		}
	}
}
void CTransformWindow::RelativeRotZCallback()
{
	if (m_SelectComponent)
	{
		if (m_SelectComponent->GetParent())
		{
			m_SelectComponent->SetRelativeRotationZ(m_RRot[2]->GetFloat());
		}
	}
}
void CTransformWindow::RelativeScaleXCallback()
{
	if (m_SelectComponent)
	{
		if (m_SelectComponent->GetParent())
		{
			m_SelectComponent->SetRelativeScaleX(m_RScale[0]->GetFloat());
		}
	}
}
void CTransformWindow::RelativeScaleYCallback()
{
	if (m_SelectComponent)
	{
		if (m_SelectComponent->GetParent())
		{
			m_SelectComponent->SetRelativeScaleY(m_RScale[1]->GetFloat());
		}
	}
}
void CTransformWindow::RelativeScaleZCallback()
{
	if (m_SelectComponent)
	{
		if (m_SelectComponent->GetParent())
		{
			m_SelectComponent->SetRelativeScaleZ(m_RScale[2]->GetFloat());
		}
	}
}
void CTransformWindow::PivotCallback()
{
	if (m_SelectComponent)
	{
		m_SelectComponent->SetPivot(
			m_Pivot[0]->GetFloat(), 
			m_Pivot[1]->GetFloat(), 
			m_Pivot[2]->GetFloat());
	}
}
void CTransformWindow::PivotXCallback()
{
}
void CTransformWindow::PivotYCallback()
{

}
void CTransformWindow::PivotZCallback()
{

}