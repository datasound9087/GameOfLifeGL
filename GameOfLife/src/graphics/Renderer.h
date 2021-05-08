#pragma once

#include  <memory>
#include <string>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

class Font;

class Renderer
{
public:

	virtual ~Renderer() = default;

	virtual void init() = 0;
	virtual void dispose() = 0;
	virtual void flush() = 0;
	virtual void submit(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& col) = 0;

	virtual void begin() {}
	virtual void end() {}
};
