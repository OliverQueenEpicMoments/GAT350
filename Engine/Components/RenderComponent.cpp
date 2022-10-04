#include "RenderComponent.h"


namespace neu
{
    bool RenderComponent::Write(const rapidjson::Value& value) const
    {
        return true;
    }

    bool RenderComponent::Read(const rapidjson::Value& value)
    {
        READ_DATA(value, sort_order);

        return true;
    }

}

