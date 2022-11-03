#pragma once
#include "Renderer.h"
#include "VertexBuffer.h"
#include "Math/MathUtils.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Ethrl {
	class Model : public Resource {
	public:
        struct Vertex_T {
            glm::vec3 Position;
            glm::vec2 TexCoord;
            glm::vec3 Normal;
            glm::vec3 Tangent;
        };

    public:
        bool Create(std::string name, ...) override;

	private:
        void ProcessNode(aiNode* node, const aiScene* scene);
        void ProcessMesh(aiMesh* mesh, const aiScene* scene);

    public:
        VertexBuffer m_vertexbuffer;
    };
}
