#include "Vector2.h"

Vector2 Vector2::Axis[AXIS2D_MAX] =
{
    Vector2(1.f, 0.f),
    Vector2(0.f, 1.f)
};

Vector2::Vector2() :
    x(0.f),
    y(0.f)
{
}

Vector2::Vector2(float _x, float _y) :
    x(_x),
    y(_y)
{
}

Vector2::Vector2(const Vector2& v) :
    x(v.x),
    y(v.y)
{
}

Vector2::Vector2(const DirectX::XMVECTOR& v)
{
    // XMVECTOR를 XMFLOAT2로 변환해준다.
    // XMFLOAT2와 이 구조체는 메모리 구조가 같으므로 강제로 형변환해서
    // 변환해주도록 한다.
    DirectX::XMStoreFloat2((DirectX::XMFLOAT2*)this, v);
}

Vector2& Vector2::operator=(const Vector2& v)
{
    x = v.x;
    y = v.y;

    return *this;
}

Vector2& Vector2::operator=(const DirectX::XMVECTOR& v)
{
    DirectX::XMStoreFloat2((DirectX::XMFLOAT2*)this, v);

    return *this;
}

Vector2& Vector2::operator=(float f)
{
    x = f;
    y = f;

    return *this;
}

bool Vector2::operator==(const Vector2& v) const
{
    return x == v.x && y == v.y;
}

bool Vector2::operator==(const DirectX::XMVECTOR& v) const
{
    Vector2 v1;
    DirectX::XMStoreFloat2((DirectX::XMFLOAT2*)&v1, v);

    return x == v1.x && y == v1.y;
}

bool Vector2::operator!=(const Vector2& v) const
{
    return x != v.x || y != v.y;
}

bool Vector2::operator!=(const DirectX::XMVECTOR& v) const
{
    Vector2 v1;
    DirectX::XMStoreFloat2((DirectX::XMFLOAT2*)&v1, v);

    return x != v1.x || y != v1.y;
}

float& Vector2::operator[](int Index)
{
    if (Index < 0 || Index > 1)
    {
        assert(false);
    }

    if (Index == 0)
        return x;

    return y;
}

// operator +
Vector2 Vector2::operator+(const Vector2& v) const
{
    return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator+(const DirectX::XMVECTOR& v) const
{
    Vector2 v1(v);

    return Vector2(x + v1.x, y + v1.y);
}

Vector2 Vector2::operator+(float f) const
{
    return Vector2(x + f, y + f);
}

// operator +=
void Vector2::operator+=(const Vector2& v)
{
    x += v.x;
    y += v.y;
}

void Vector2::operator+=(const DirectX::XMVECTOR& v)
{
    Vector2 v1(v);

    x += v1.x;
    y += v1.y;
}

void Vector2::operator+=(float f)
{
    x += f;
    y += f;
}

// operator -
Vector2 Vector2::operator-(const Vector2& v) const
{
    return Vector2(x - v.x, y - v.y);
}

Vector2 Vector2::operator-(const DirectX::XMVECTOR& v) const
{
    Vector2 v1(v);

    return Vector2(x - v1.x, y - v1.y);
}

Vector2 Vector2::operator-(float f) const
{
    return Vector2(x - f, y - f);
}

// operator -=
void Vector2::operator-=(const Vector2& v)
{
    x -= v.x;
    y -= v.y;
}

void Vector2::operator-=(const DirectX::XMVECTOR& v)
{
    Vector2 v1(v);

    x -= v1.x;
    y -= v1.y;
}

void Vector2::operator-=(float f)
{
    x -= f;
    y -= f;
}

// operator *
Vector2 Vector2::operator*(const Vector2& v) const
{
    return Vector2(x * v.x, y * v.y);
}

Vector2 Vector2::operator*(const DirectX::XMVECTOR& v) const
{
    Vector2 v1(v);

    return Vector2(x * v1.x, y * v1.y);
}

Vector2 Vector2::operator*(float f) const
{
    return Vector2(x * f, y * f);
}

// operator *=
void Vector2::operator*=(const Vector2& v)
{
    x *= v.x;
    y *= v.y;
}

void Vector2::operator*=(const DirectX::XMVECTOR& v)
{
    Vector2 v1(v);

    x *= v1.x;
    y *= v1.y;
}

void Vector2::operator*=(float f)
{
    x *= f;
    y *= f;
}

// operator /
Vector2 Vector2::operator/(const Vector2& v) const
{
    return Vector2(x / v.x, y / v.y);
}

Vector2 Vector2::operator/(const DirectX::XMVECTOR& v) const
{
    Vector2 v1(v);

    return Vector2(x / v1.x, y / v1.y);
}

Vector2 Vector2::operator/(float f) const
{
    return Vector2(x / f, y / f);
}

// operator /=
void Vector2::operator/=(const Vector2& v)
{
    x /= v.x;
    y /= v.y;
}

void Vector2::operator/=(const DirectX::XMVECTOR& v)
{
    Vector2 v1(v);

    x /= v1.x;
    y /= v1.y;
}

void Vector2::operator/=(float f)
{
    x /= f;
    y /= f;
}

const Vector2& Vector2::operator++()
{
    x += 1.f;
    y += 1.f;

    return *this;
}

const Vector2& Vector2::operator++(int)
{
    x += 1.f;
    y += 1.f;

    return *this;
}

const Vector2& Vector2::operator--()
{
    x -= 1.f;
    y -= 1.f;

    return *this;
}

const Vector2& Vector2::operator--(int)
{
    x -= 1.f;
    y -= 1.f;

    return *this;
}
//##########################오퍼레이터 끝##########################################

float Vector2::Length() const //길이(X)
{
    // XMVector2Length함수는 해당 벡터의 크기를 구해서 XMVECTOR 타입으로 변환해서 리턴한다.
    // 이때 X값만을 뽑아내기 위해 XMVectorGetX 함수를 이용하여 크기 값만을 얻어온다.
    return DirectX::XMVectorGetX(DirectX::XMVector2Length(Convert()));
}

void Vector2::Normalize() //정규화(단위벡터화)
{
    *this = DirectX::XMVector2Normalize(Convert());
}

float Vector2::Distance(const Vector2& v) const //벡터 뺄셈?
{
    Vector2 v1 = *this - v;

    return v1.Length();
}

float Vector2::Dot(const Vector2& v) const //내적해서 x값만 얻는다?
{
    return DirectX::XMVectorGetX(DirectX::XMVector2Dot(Convert(), v.Convert()));
}

float Vector2::Angle(const Vector2& v) const
{
    return 0.0f;
}

//Vector2->XMFLOAT->XMVECTOR2
DirectX::XMVECTOR Vector2::Convert()    const
{
    //XMFLOAT를 XMVECTOR에 적재하는 함수: XMLoadFloat2
    return DirectX::XMLoadFloat2((DirectX::XMFLOAT2*)this);
}

//Vector2->XMVECTOR->XMFLOAT
void Vector2::Convert(const DirectX::XMVECTOR& v)
{
    //XMVECTOR를 XMFLOAT* 로 저장하는 함수
    DirectX::XMStoreFloat2((DirectX::XMFLOAT2*)this, v);
}
