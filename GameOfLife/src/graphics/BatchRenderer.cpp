#include "BatchRenderer.h"

#include <array>
#include <cstddef>
#include  "Shader.h"

const std::string PATH = "batch path";

BatchRenderer::BatchRenderer(const glm::mat4& prMatrix)
	: mPrMatrix(prMatrix)
{}

BatchRenderer::~BatchRenderer()
{}

void BatchRenderer::init()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glCullFace(GL_BACK);

	//glPolygonMode(GL_FRONT_AND_BACK , GL_LINE);

	glGenBuffers(1, &mVbo);
	glGenVertexArrays(1, &mVao);
	glGenBuffers(1, &mIbo);

	glBindVertexArray(mVao);

	glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	glBufferData(GL_ARRAY_BUFFER, BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(SHADER_ATTRIB_POS);
	glVertexAttribPointer(SHADER_ATTRIB_POS, 2, GL_FLOAT, GL_FALSE, VERTEX_SIZE_BYTES, static_cast<void*>(nullptr));

	glEnableVertexAttribArray(SHADER_ATTRIB_COL);
	glVertexAttribPointer(SHADER_ATTRIB_COL, 4, GL_UNSIGNED_BYTE, GL_TRUE, VERTEX_SIZE_BYTES, reinterpret_cast<void*>(offsetof(VertexData, VertexData::mColour)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIbo);

	auto indicies = new uint32_t[INDICIE_SIZE];

	uint32_t offset = 0;
	for(int i = 0; i < INDICIE_SIZE; i += 6)
	{
		indicies[i] = offset + 0;
		indicies[i + 1] = offset + 1;
		indicies[i + 2] = offset + 2;

		indicies[i + 3] = offset + 2;
		indicies[i + 4] = offset + 3;
		indicies[i + 5] = offset + 0;

		offset += 4;
	}

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, INDICIE_SIZE, indicies, GL_STATIC_DRAW);

	delete[] indicies;

	glBindVertexArray(0);

	mShader = std::make_unique<Shader>(PATH + ".vert", PATH + ".frag");
	mShader->use();
	mShader->setMat4("prMatrix", mPrMatrix);
}

void BatchRenderer::dispose()
{
	glDeleteVertexArrays(1, &mVao);
	glDeleteBuffers(1, &mVbo);
	glDeleteBuffers(1, &mIbo);
}

void BatchRenderer::flush()
{
	if(mDrawing || mNumVertices == 0)
	{
		return;
	}

	glBindVertexArray(mVao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIbo);

	glDrawElements(GL_TRIANGLES, mNumVertices, GL_UNSIGNED_INT, nullptr);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void BatchRenderer::submit(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& col)
{
	if(!mDrawing)
	{
		return;
	}

	if(mNumVertices >= INDICIE_SIZE)
	{
		end();
		flush();
		begin();
	}

	int r = col.r * 255.0f;
	int g = col.g * 255.0f;
	int b = col.b * 255.0f;
	int a = col.a * 255.0f;

	uint32_t color = 0;
	color = a << 24 | b << 16 | g << 8 | r;
	
	submitVertex(pos, color);
	submitVertex(pos + glm::vec2(0.0f, size.y), color);
	submitVertex(pos + glm::vec2(size.x, size.y), color);
	submitVertex(pos + glm::vec2(size.x, 0.0f), color);

	mNumVertices += 6;
}


void BatchRenderer::begin()
{
	glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	mGpuData = static_cast<VertexData*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
	mDrawing = true;
	mNumVertices = 0;
}

void BatchRenderer::end()
{
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	mDrawing = false;
}

void BatchRenderer::submitVertex(const glm::vec2& pos, uint32_t col)
{
	mGpuData->mPos = pos;
	mGpuData->mColour = col;

	mGpuData++;
}
