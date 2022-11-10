#pragma once
#include "Framework/Component.h"

namespace Ethrl {
    class CameraController : public Component {
    public:
        CLASS_DECLARATION(CameraController)

        virtual void Update() override;

        virtual bool Write(const rapidjson::Value& value) const override;
        virtual bool Read(const rapidjson::Value& value) override;

    private:
        float speed = 0;
    };
}