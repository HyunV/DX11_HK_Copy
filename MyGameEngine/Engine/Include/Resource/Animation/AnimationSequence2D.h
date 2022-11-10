#pragma once
#include "../../Ref.h"
//애니메이션 모션 하나하나의 텍스처 및 데이터를 가지고 있는 클래스
class CAnimationSequence2D :
    public CRef
{
    friend class CAnimationManager;

private:
    CAnimationSequence2D();
    CAnimationSequence2D(const CAnimationSequence2D& Anim);
    ~CAnimationSequence2D();

private:
    class CScene* m_Scene;
    CSharedPtr<class CTexture> m_Texture; //원본이미지
    std::vector<Animation2DFrameData>   m_vecFrameData;//start, end로 나눔
    EAnimation2DType    m_Anim2DType;

    //내 변수
    Animation2DFrameData m_StartEndPoint;
    int m_FrameCount;

    int m_LoopCount; // 애니메이션 "반복"돌때 시작되는 위치

public:
    EAnimation2DType GetAnim2DType()    const
    {
        return m_Anim2DType;
    }

    void SetScene(class CScene* Scene)
    {
        m_Scene = Scene;
    }

    void SetLoopCount(int Count)
    {
        m_LoopCount = Count;
    }

    int GetLoopCount()
    {
        return m_LoopCount;
    }
    void SetAnimation2DType(EAnimation2DType Type)
    {
        m_Anim2DType = Type;
    }
public:
    class CTexture* GetTexture()    const
    {
        return m_Texture;
    }

    const Animation2DFrameData& GetFrameData(int Index) const
    {
        return m_vecFrameData[Index];
    }

    int GetFrameCount() const
    {
        return (int)m_vecFrameData.size();
    }

    void SetFrameCount(int count)
    {
        m_FrameCount = count;
    }

public:
    bool Init(class CTexture* Texture);
    bool Init(const std::string& Name, const TCHAR* FileName,
        const std::string& PathName = TEXTURE_PATH);
    bool InitFullPath(const std::string& Name, const TCHAR* FullPath);
    bool Init(const std::string& Name, const std::vector<const TCHAR*>& vecFileName,
        const std::string& PathName = TEXTURE_PATH);
    bool InitFullPath(const std::string& Name, const std::vector<const TCHAR*>& vecFullPath);
    void AddFrame(const Vector2& Start, const Vector2& End);
    void AddFrame(float StartX, float StartY, float EndX, float EndY);
    void AddFrameAll(int Count, const Vector2& Start, const Vector2& End);
    void AddFrameAll(int Count, float StartX, float StartY, float EndX,
        float EndY);
    void DeleteFrame(int Index);
    void ClearFrame();
    CAnimationSequence2D* Clone();
    bool Save(const char* FullPath);
    bool Load(const char* FullPath);
    bool Save(const char* FileName, const std::string& PathName);
    bool Load(const char* FileName, const std::string& PathName);
};

