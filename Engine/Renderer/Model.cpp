#include "Model.h"
#include "Core/Logger.h"

namespace Ethrl {
	bool Model::Create(std::string name, ...) {
        Assimp::Importer importer;

        const aiScene* scene = importer.ReadFile(name, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            LOG("Error loading assimp file %s", importer.GetErrorString());
            return false;
        }

        ProcessNode(scene->mRootNode, scene);

		return true;
	}

    void Model::ProcessNode(aiNode* node, const aiScene* scene) {
        // Process the current node meshes
        for (unsigned int I = 0; I < node->mNumMeshes; I++) {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[I]];
            ProcessMesh(mesh, scene);
        }

        // Process the current node children
        for (unsigned int I = 0; I < node->mNumChildren; I++) {
            ProcessNode(node->mChildren[I], scene); 
        }
    }

    void Model::ProcessMesh(aiMesh* mesh, const aiScene* scene) {
        std::vector<Vertex_T> Vertices;

        // Get model vertex attributes
        for (size_t I = 0; I < mesh->mNumVertices; I++) {
            Vertex_T Vertex;

            Vertex.Position = { mesh->mVertices[I].x, mesh->mVertices[I].y, mesh->mVertices[I].z };
            Vertex.Normal = { mesh->mNormals[I].x, mesh->mNormals[I].y, mesh->mNormals[I].z };
            Vertex.Tangent = { mesh->mTangents[I].x, mesh->mTangents[I].y, mesh->mTangents[I].z };

            if (mesh->mTangents) {
                Vertex.Tangent = { mesh->mTangents[I].x, mesh->mTangents[I].y, mesh->mTangents[I].z };
            } else {
                Vertex.Tangent = { 0, 0, 0 };
            }

            if (mesh->mTextureCoords[0]) {
                Vertex.TexCoord = { mesh->mTextureCoords[0][I].x, mesh->mTextureCoords[0][I].y};
            } else {
                Vertex.TexCoord = { 0, 0 };
            }
            Vertices.push_back(Vertex);
        }

        // Create vertex buffer and attributes
        m_vertexbuffer.CreateVertexBuffer((GLsizei)(sizeof(Vertex_T) * Vertices.size()), (GLsizei)Vertices.size(), Vertices.data());
        m_vertexbuffer.SetAttribute(0, 3, sizeof(Vertex_T), 0);
        m_vertexbuffer.SetAttribute(1, 2, sizeof(Vertex_T), offsetof(Vertex_T, TexCoord));
        m_vertexbuffer.SetAttribute(2, 3, sizeof(Vertex_T), offsetof(Vertex_T, Normal));
        m_vertexbuffer.SetAttribute(3, 3, sizeof(Vertex_T), offsetof(Vertex_T, Tangent));

        // Get model index vertices
        std::vector<GLuint> Indices;
        for (size_t I = 0; I < mesh->mNumFaces; I++) {
            aiFace Face = mesh->mFaces[I];
            for (size_t J = 0; J < Face.mNumIndices; J++) {
                Indices.push_back(Face.mIndices[J]);
            }
        }
        // Create index vertex buffer
        m_vertexbuffer.CreateIndexBuffer(GL_UNSIGNED_INT, (GLsizei)Indices.size(), Indices.data());
    }
}