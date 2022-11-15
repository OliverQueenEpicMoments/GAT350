#include "Scene.h"
#include "Factory.h"
#include "Engine.h"
#include <algorithm>
#include <iostream>

namespace Ethrl {
	void Scene::Initialize() {
		for (auto& actor : m_actors) { actor->Initialize(); }
	}

    bool Scene::Create(std::string name, ...) {
        rapidjson::Document document;
        bool Success = Ethrl::json::Load(name, document);
        if (!Success) {
            LOG("Error loading scene fine %s", name);
            return false;
        }
        Read(document);
        Initialize();
        return true;
    }

	void Scene::Update() {
		auto iter = m_actors.begin();
		while (iter != m_actors.end()) {
			(*iter)->Update();
			if ((*iter)->m_destroy) {
				iter = m_actors.erase(iter);
			} else {
				iter++;
			}
		}
	}

    void Scene::PreRender(Renderer& renderer) {
        // Get active camera component
        CameraComponent* camera = nullptr;
        for (auto& actor : m_actors) {
            if (!actor->IsActive()) continue;

            auto component = actor->GetComponent<CameraComponent>();
            if (component) {
                camera = component;
                break;
            }
        }

        // Get light components
        std::vector<LightComponent*> lights;
        for (auto& actor: m_actors) {
            if (!actor->IsActive()) continue;

            auto component = actor->GetComponent<LightComponent>();
            if (component) {
                lights.push_back(component);
            }
        }

        // Get all shader programs in the resource system
        auto programs = g_resources.Get<Program>();

        // Set all shader programs camera and lights uniforms
        for (auto& program : programs) {
            // Set camera in shader program
            camera->SetProgram(program);

            // Set lights in shader program
            int Index = 0;
            for (auto light : lights) {
                light->SetProgram(program, Index++);
            }

            program->SetUniform("light_count", Index);
            program->SetUniform("ambient_color", g_renderer.ambient_color);
        }
    }

	void Scene::Render(Renderer& renderer) {
        // Get camera / set renderer view/projection
        auto Camera = GetActorFromName("Camera");
        if (Camera) {
            g_renderer.SetView(Camera->GetComponent<CameraComponent>()->GetView());
            g_renderer.SetProjectionMatrix(Camera->GetComponent<CameraComponent>()->GetProjection());
        }

        // Draw actors
		for (auto& actor : m_actors) {
			actor->Draw(renderer);
		}
	}

	void Scene::Add(std::unique_ptr<Actor> actor) {
		actor->m_scene = this;
		m_actors.push_back(std::move(actor));
	}

	void Scene::RemoveAll() {
		for (auto& actor : m_actors) { actor->SetDestroy(); }

		m_actors.clear();
	}

	bool Scene::Write(const rapidjson::Value& value) const {
		return true;
	}

	bool Scene::Read(const rapidjson::Value& value) {
        // Read clear color
        READ_NAME_DATA(value, "clear_color", g_renderer.clear_color);
        READ_NAME_DATA(value, "ambient_color", g_renderer.ambient_color);

		if (!value.HasMember("actors") || !value["actors"].IsArray()) {
			return false;
		}

		// read actors
		for (auto& actorValue : value["actors"].GetArray()) {
			std::string type;
			READ_DATA(actorValue, type);

			auto actor = Factory::Instance().Create<Actor>(type);
			if (actor) {
				// read actor
				actor->Read(actorValue);

				bool prefab = false;
				READ_DATA(actorValue, prefab);

				if (prefab) {
					std::string name = actor->GetName();
					Factory::Instance().RegisterPrefab(name, std::move(actor));
				} else {
					Add(std::move(actor));
				}
			}
		}
		return true;
	}

}
