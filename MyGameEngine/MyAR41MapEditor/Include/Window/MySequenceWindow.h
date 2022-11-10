#pragma once
#include "Editor\EditorWindow.h"
class CMySequenceWindow :
    public CEditorWindow
{
    friend class CEditorGUIManager;

protected:
    CMySequenceWindow();
    virtual ~CMySequenceWindow();

private:
    class CAnimationSequence2D* m_Sequence;

    //�ʿ��� ������
    EImageType m_ImageType;
    class CEditorListBox* m_List; //�̹��� ����Ʈ
    std::vector<const TCHAR*> m_vecFullPathFileName; //Ǯ��� ���� ����(�����Ҵ�)
    //class CTexture* m_Texture;

    std::vector<Animation2DFrameData> m_vecFrame; //�ش��ε����� �� Start End ����Ʈ

    class CEditorInput* m_SequenceName; //��ǲ_���ϸ� string
    class CEditorInput* m_FrameCount; //��ǲ_�� �� int
    class CEditorInput* m_LoopCount; //��ǲ_���� ������ int
    class CEditorInput* m_InputStartEnd[2]; //�������� x, y float
    class CEditorInput* m_InputWidthHeight[2]; // �̹��� �ʺ�, ���� float

    //�̸����� ����
    class CEditorText* m_Messege; //�̸����� �޽���

    class CEditorImage* m_PreviewImage; //�̸����� �̹���
    class CEditorSliderBar* m_Slide;

    class CEditorInput* m_PlayScale; //����
    bool m_Play;
    float m_Time;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

private:
    void SelectLoadImageButtonCallback(); //�̹��� �ε� ��ư
    void SelectLoadSequenceCallback(); //������ �ε� ��ư
    const std::string TCHARToString(const TCHAR* ptsz);

    void SetList(); //����Ʈ ���� �Լ�
    void SetSlide(EImageType Type); //�����̵� ���� �Լ�

    void AddFullPath(const TCHAR* FullPath); //�����Ҵ�

    void SelectListCallback(int SelectIndex, const std::string& Item);
    void CreateSequence(EImageType type);
    void SaveSequence(); //������ ����� ������ ����� �Լ�
    void LoadSequence(class CAnimationSequence2D* Sequence); //���� �������� ������ �� �����ϴ� �Լ�

    void PlayButton();
    void PauseButton();
    void StopButton();
    void ClearSetting(); //��� �ʱ�ȭ

    void SliderCallback();
    void SetAtlasFrame(int FrameCount);

};

