#include "Scene.h"
#include "Factory.h"
#include "Engine.h"
#include <algorithm>
#include <iostream>

namespace Ethrl {
	void Scene::Initialize() {
		for (auto& actor : m_actors) { actor->Initialize(); }
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

	void Scene::Draw(Renderer& renderer) {
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
