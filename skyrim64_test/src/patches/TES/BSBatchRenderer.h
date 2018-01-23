#pragma once

#include "BSTArray.h"
#include "BSTScatterTable.h"
#include "BSShader/BSShaderManager.h"

class BSBatchRenderer
{
public:
	struct PassInfo
	{
		BSBatchRenderer *m_BatchRenderer;
		uintptr_t UnkPtr2;// pShaderProperty
		uintptr_t UnkPtr3;// pGeometry
		uintptr_t UnkPtr4;
		char _pad[4];
		uint16_t UnkWord1;
		uint8_t UnkByte1;		// Flags

		void Render(unsigned int a2);
		void Unregister();
	};

	struct RenderPassArray
	{
		BSRenderPass *m_Pass[5];
		DWORD m_PassIndexBits;									// OR'd with (1 << PassIndex)

		void Clear(bool Validate);								// Simply zeros this structure
	};

	virtual ~BSBatchRenderer();
	virtual void VFunc01() = 0;									// Registers a pass?
	virtual void VFunc02() = 0;									// Registers a pass?
	virtual void VFunc03() = 0;									// Unknown (render?)

	BSTArray<RenderPassArray> m_RenderArrays;
	BSTDefaultScatterTable<uint32_t, uint32_t> m_TechToArrayMap;// Technique ID -> Index in m_RenderArrays
	uint32_t m_StartingTech;
	uint32_t m_EndingTech;
	char _pad2[0x10];
	int iGroupingAlphas;
	PassInfo *m_Passes[16];
	PassInfo *m_OtherPass;
	void *unk1;
	void *unk2;

	bool HasTechniquePasses(uint32_t StartTech, uint32_t EndTech);

	bool sub_14131E8F0(unsigned int a2, uint32_t& SubPassIndex);
	bool sub_14131E700(uint32_t& Technique, uint32_t& SubPassIndex, __int64 a4);
	bool sub_14131ECE0(uint32_t& Technique, uint32_t& SubPassIndex, __int64 a4);
	bool sub_14131E7B0(uint32_t& Technique, uint32_t& SubPassIndex, __int64 *a4);
	bool sub_14131E960(uint32_t& Technique, uint32_t& SubPassIndex, __int64 a4, unsigned int a5);
	void sub_14131D6E0();

	static void DrawPassGeometry(BSRenderPass *Pass, uint32_t Technique, bool AlphaTest, uint32_t RenderFlags);
	static void DrawGeometryDefault(BSRenderPass *Pass, bool AlphaTest, uint32_t RenderFlags);
	static void DrawGeometrySkinned(BSRenderPass *Pass, bool AlphaTest, uint32_t RenderFlags);
	static void DrawGeometryCustom(BSRenderPass *Pass, bool AlphaTest, uint32_t RenderFlags);
	static void SetupGeometryBlending(BSRenderPass *Pass, BSShader *Shader, bool AlphaTest, uint32_t RenderFlags);
	static void DrawTriStrips(BSRenderPass *Pass);
};
static_assert(sizeof(BSBatchRenderer::PassInfo) == 0x28, "");
static_assert(offsetof(BSBatchRenderer::PassInfo, m_BatchRenderer) == 0x0, "");
static_assert(offsetof(BSBatchRenderer::PassInfo, UnkPtr2) == 0x8, "");
static_assert(offsetof(BSBatchRenderer::PassInfo, UnkPtr3) == 0x10, "");
static_assert(offsetof(BSBatchRenderer::PassInfo, UnkPtr4) == 0x18, "");
static_assert(offsetof(BSBatchRenderer::PassInfo, UnkWord1) == 0x24, "");
static_assert(offsetof(BSBatchRenderer::PassInfo, UnkByte1) == 0x26, "");

static_assert(sizeof(BSBatchRenderer::RenderPassArray) == 0x30, "");

static_assert(sizeof(BSBatchRenderer) == 0x108, "");
static_assert(offsetof(BSBatchRenderer, m_TechToArrayMap) == 0x20, "");
static_assert(offsetof(BSBatchRenderer, m_StartingTech) == 0x50, "");
static_assert(offsetof(BSBatchRenderer, m_EndingTech) == 0x54, "");
static_assert(offsetof(BSBatchRenderer, iGroupingAlphas) == 0x68, "");
static_assert(offsetof(BSBatchRenderer, m_Passes) == 0x70, "");
static_assert(offsetof(BSBatchRenderer, m_OtherPass) == 0xF0, "");
static_assert(offsetof(BSBatchRenderer, unk1) == 0xF8, "");
static_assert(offsetof(BSBatchRenderer, unk2) == 0x100, "");