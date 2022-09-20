#include "Animation2DData.h"

CAnimation2DData::CAnimation2DData()
{
}

CAnimation2DData::~CAnimation2DData()
{
	size_t	Size = m_vecNotify.size();

	for (size_t i = 0; i < Size; ++i)
	{
		SAFE_DELETE(m_vecNotify[i]);
	}
}

void CAnimation2DData::SetSequence(CAnimationSequence2D* Sequence)
{
	if (Sequence)
		m_SequenceName = Sequence->GetName();

	m_Sequence = Sequence;
}

void CAnimation2DData::Save(FILE* File)
{
	int	Length = (int)m_Name.length();
	fwrite(&Length, 4, 1, File);
	fwrite(m_Name.c_str(), 1, Length, File);

	Length = (int)m_SequenceName.length();
	fwrite(&Length, 4, 1, File);
	fwrite(m_SequenceName.c_str(), 1, Length, File);

	fwrite(&m_Frame, 4, 1, File);
	fwrite(&m_Time, 4, 1, File);
	fwrite(&m_FrameTime, 4, 1, File);
	fwrite(&m_PlayTime, 4, 1, File);
	fwrite(&m_PlayScale, 4, 1, File);

	fwrite(&m_Loop, 1, 1, File);
	fwrite(&m_Reverse, 1, 1, File);
}

void CAnimation2DData::Load(FILE* File)
{
	int	Length = 0;
	char	Name[256] = {};
	fread(&Length, 4, 1, File);
	fread(Name, 1, Length, File);

	m_Name = Name;

	Length = 0;
	char	SequenceName[256] = {};
	fread(&Length, 4, 1, File);
	fread(SequenceName, 1, Length, File);

	m_SequenceName = SequenceName;

	fread(&m_Frame, 4, 1, File);
	fread(&m_Time, 4, 1, File);
	fread(&m_FrameTime, 4, 1, File);
	fread(&m_PlayTime, 4, 1, File);
	fread(&m_PlayScale, 4, 1, File);

	fread(&m_Loop, 1, 1, File);
	fread(&m_Reverse, 1, 1, File);
}
