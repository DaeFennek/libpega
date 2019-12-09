#pragma once

#include <vector>
#include <unordered_map>
#include <memory>
#include "vector3f.h"
#include "aabb.h"
#include "colorrgba.h"
#include "geometry_data.h"
#include "wii_displaylist.h"

namespace renderer {
    class Renderer;
}

namespace wiicraft {

constexpr uint8_t BLOCK_LEFT_FACE = 0x01;
constexpr uint8_t BLOCK_RIGHT_FACE = (BLOCK_LEFT_FACE << 1);
constexpr uint8_t BLOCK_FRONT_FACE = (BLOCK_RIGHT_FACE << 1);
constexpr uint8_t BLOCK_BACK_FACE = (BLOCK_FRONT_FACE << 1);
constexpr uint8_t BLOCK_TOP_FACE = (BLOCK_BACK_FACE << 1);
constexpr uint8_t BLOCK_BOTTOM_FACE = (BLOCK_TOP_FACE << 1);

struct ChunkPosition
{
    int32_t x = 0, y = 0;
};

struct BlockPosition
{
    uint32_t x = 0, y = 0, z = 0;
};


struct BlockRenderData
{
    uint8_t FaceMask = 0;
    size_t Faces = 0;
    struct BlockPosition BlockPosition;
};


enum class BlockType : uint8_t
{
    AIR = 0,
    STONE = 4,
    GRASS = 2,
    DIRT = 3,
    WOOD = 17,
    LEAF = 18
};

class ChunkSection
{
public:
    static constexpr uint32_t CHUNK_SECTION_SIZE_X = 16;
    static constexpr uint32_t CHUNK_SECTION_SIZE_Y = 256;
    static constexpr uint32_t CHUNK_SECTION_SIZE_Z = 16;
    static constexpr uint32_t CHUNK_SIZE = 16;
    static constexpr uint32_t CHUNK_AMOUNT = CHUNK_SECTION_SIZE_Y / CHUNK_SIZE;

    static ChunkPosition WorldPositionToChunkPosition(const math::Vector3f &worldPosition);
    static std::vector<ChunkPosition> GenerateChunkMap(const math::Vector3f &worldPosition);

    ChunkSection();
    ~ChunkSection();
    ChunkSection(const ChunkSection&) = delete;
    ChunkSection& operator = (const ChunkSection&) = delete;
    ChunkSection(ChunkSection&&) = delete;
    ChunkSection& operator = (ChunkSection&&) = delete;

    void SetTo(const BlockType& blockType);
    void Render(renderer::Renderer& renderer);
    void UpdateChunkDisplayList(uint32_t chunkIndex, size_t chunkFaceAmmount,
                                const std::unordered_map<BlockType, std::vector<BlockRenderData>>& chunkBlockList,
                                renderer::Renderer& renderer,
                                const renderer::ColorRGBA& color = renderer::ColorRGBA::WHITE);

    inline void SetLoaded(bool value);
    inline bool IsLoaded() const;
    inline void SetPosition(const ChunkPosition &position);
    inline math::Vector3f GetWorldPosition() const;
    inline const ChunkPosition& GetPosition() const;
    inline BlockType *** GetBlocks();
    inline const BlockType * const * const * GetBlocks() const;

private:
    void GenerateChunk(uint32_t chunkIndex, renderer::Renderer& renderer);
    bool IsBlockVisible(uint32_t x, uint32_t y, uint32_t z, BlockRenderData& blockRenderVO) const;


private:
    std::vector<std::unique_ptr<renderer::DisplayList>> mChunkDisplayList;
    ChunkPosition mPosition;
    BlockType*** mBlocks;
    bool mLoaded, mDirty;
};

inline void wiicraft::ChunkSection::SetLoaded(bool value)
{
    mLoaded = value;   
    if (value)
        mDirty = true;
}

inline bool ChunkSection::IsLoaded() const
{
    return mLoaded;
}

inline void ChunkSection::SetPosition(const ChunkPosition &position)
{
    mPosition = position;
}

inline math::Vector3f ChunkSection::GetWorldPosition() const
{
    return {static_cast<float>(mPosition.x * static_cast<int32_t>(CHUNK_SIZE)), 0.0f,
                static_cast<float>(mPosition.y * static_cast<int32_t>(CHUNK_SIZE))};
}

inline const ChunkPosition &ChunkSection::GetPosition() const
{
    return mPosition;
}

inline BlockType ***ChunkSection::GetBlocks()
{
    return mBlocks;
}

inline const BlockType * const * const * ChunkSection::GetBlocks() const
{
    return mBlocks;
}

}
