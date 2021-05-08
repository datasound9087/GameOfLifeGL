#pragma once
#include "Renderer.h"

#include <vector>
#include <glm/mat4x4.hpp>
#include <glad/glad.h>

class Shader;

#define MAX_NO_SPRITES 30000
#define VERTEX_SIZE_BYTES sizeof(VertexData)
#define SPRITE_SIZE_BYTES (VERTEX_SIZE_BYTES * 4)
#define BUFFER_SIZE SPRITE_SIZE_BYTES * MAX_NO_SPRITES
#define INDICIE_SIZE (MAX_NO_SPRITES * 6)

#define SHADER_ATTRIB_POS 0
#define SHADER_ATTRIB_COL 1

struct VertexData
{
	glm::vec2 mPos;
	uint32_t mColour;
};

class BatchRenderer : public Renderer
{
public:
	BatchRenderer(const glm::mat4& prMatrix);
	~BatchRenderer();

	void init() override;
	void dispose() override;
	void flush() override;
	void submit(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& col) override;

	void begin() override;
	void end() override;

private:

	void submitVertex(const glm::vec2& pos, uint32_t col);

	std::unique_ptr<Shader> mShader;

	glm::mat4 mPrMatrix;

	GLuint mVao, mVbo, mIbo;

	uint32_t mNumVertices;

	bool mDrawing = false;

	VertexData* mGpuData;
};

