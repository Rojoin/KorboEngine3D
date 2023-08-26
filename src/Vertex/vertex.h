#pragma once
static const float W = 1.0f;

struct Position
{
	float x;
	float y;
	float z;

	Position(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Position(float x, float y)
	{
		this->x = x;
		this->y = y;
		this->z = 0;
	}

	Position()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
};

struct UV
{
	float uv_x;
	float uv_y;

	UV(float uv_x, float uv_y)
	{
		this->uv_x = uv_x;
		this->uv_y = uv_y;
	}

	UV()
	{
		uv_x = 0.0f;
		uv_y = 0.0f;
	}
};

struct Color
{
	float red;
	float green;
	float blue;
	float alpha;

	Color(float red, float green, float blue, float alpha)
	{
		this->red = red;
		this->green = green;
		this->blue = blue;
		this->alpha = alpha;
	}

	Color(float red, float green, float blue)
	{
		this->red = red;
		this->green = green;
		this->blue = blue;
		this->alpha = 1.0f;
	}

	Color(float red, float green)
	{
		this->red = red;
		this->green = green;
		this->blue = 0.0f;
		this->alpha = 1.0f;
	}

	Color(float red)
	{
		this->red = red;
		this->green = 0.0f;
		this->blue = 0.0f;
		this->alpha = 1.0f;
	}

	Color()
	{
		this->red = 0.0f;
		this->green = 0.0f;
		this->blue = 0.0f;
		this->alpha = 1.0f;
	}
};

struct Vertex
{
	Position pos;
	UV uv;
	Color color;

	Vertex(Position pos, UV uv,Color color)
	{
		this->pos = pos;
		this->uv = uv;
		this->color = color;
	}

	Vertex(Position pos, UV uv)
	{
		this->pos = pos;
		this->uv = uv;
		color = Color::Color();
	}

	Vertex(Position pos)
	{
		this->pos = pos;
		this->uv = UV::UV();
		color = Color::Color();
	}
	Vertex()
	{
		this->pos = Position::Position();
		this->uv = UV::UV();
		color = Color::Color();
	}
};