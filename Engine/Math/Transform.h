#pragma once
#include "Vector2.h"
#include "Matrix3x3.h"
#include "MathUtils.h"
#include "Serialization/Serializable.h"

namespace Ethrl {
	struct Transform : public ISerializable	{
        glm::vec3 position{ 0 };
        glm::quat rotation;
		glm::vec3 scale{ 1 };

        glm::vec3 GetRight() { return ((glm::mat4)(*this))[0]; }
        glm::vec3 GetUp() { return ((glm::mat4)(*this))[1]; }
        glm::vec3 GetForward() { return ((glm::mat4)(*this))[2]; }

		glm::mat4 matrix;

		Transform() = default;
        Transform(const glm::vec3& position, const glm::quat& rotation = glm::vec3{ 0 }, const glm::vec3& scale = glm::vec3{ 1 }) :
			position{ position },
			rotation{ rotation },
			scale{ scale } 
		{}

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		void Update() {
            matrix = *this;
		}

		void Update(const glm::mat4& parent) {
			matrix = parent * (glm::mat4)*this;
		}

		operator glm::mat4 () const {
			glm::mat4 mxScale = glm::scale(scale);
			glm::mat4 mxRotation = glm::mat4_cast(rotation);
			glm::mat4 mxTranslation = glm::translate(position);

			return { mxTranslation * mxRotation * mxScale };
		}
	};
}