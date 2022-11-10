#pragma once
#include "Editor\EditorWindow.h"
class CTransformWindow :
    public CEditorWindow
{
    friend class CEditorGUIManager;

protected:
    CTransformWindow();
    virtual ~CTransformWindow();

private:
    class CEditorInput* m_Pos[3];
    class CEditorInput* m_Rot[3];
    class CEditorInput* m_Scale[3];

    class CEditorInput* m_RPos[3];
    class CEditorInput* m_RRot[3];
    class CEditorInput* m_RScale[3];

    class CEditorInput* m_Pivot[3];

    CSharedPtr<class CSceneComponent>   m_SelectComponent;

public:
    void SetSelectComponent(class CSceneComponent* Component);

    void SetPos(const Vector3& Pos);
    void SetRotation(const Vector3& Rot);
    void SetScale(const Vector3& Scale);

    void SetRelativePos(const Vector3& Pos);
    void SetRelativeRotation(const Vector3& Rot);
    void SetRelativeScale(const Vector3& Scale);

    void SetPivot(const Vector3& Pivot);

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

public:
    //World
    void PosXCallback();
    void PosYCallback();
    void PosZCallback();
    void RotXCallback();
    void RotYCallback();
    void RotZCallback();
    void ScaleXCallback();
    void ScaleYCallback();
    void ScaleZCallback();

    //Relative
    void RelativePosXCallback();
    void RelativePosYCallback();
    void RelativePosZCallback();
    void RelativeRotXCallback();
    void RelativeRotYCallback();
    void RelativeRotZCallback();
    void RelativeScaleXCallback();
    void RelativeScaleYCallback();
    void RelativeScaleZCallback();

    //Pivot
    void PivotCallback();
    void PivotXCallback();
    void PivotYCallback();
    void PivotZCallback();
};

