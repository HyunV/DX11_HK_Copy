#pragma once

enum AXIS2D
{
	AXIS2D_X,
	AXIS2D_Y,
	AXIS2D_MAX
};

enum AXIS
{
	AXIS_X,
	AXIS_Y,
	AXIS_Z,
	AXIS_MAX
};

enum class MeshType : unsigned char
{
	Sprite,
	UI,
	Static,
	Animation
};

enum class BufferType : unsigned char
{
	Vertex,
	Index
};

//쉐이더는 크게 그래픽, 컴퓨트로 나뉜다.
enum class ShaderType : unsigned char
{
	Graphic, 
	Compute
};

enum class ComponentType : unsigned char
{
	Scene,
	Object
};

enum class SceneComponentType : unsigned char
{
	Sprite
};