#pragma once
#include "LatinEngine/Latin.h"
#include "tileson.hpp"

struct Level;

class Game : public LATIN::Application
{
public:
	void Start() override
	{
		tson::Tileson t;
		
		map = t.parse(fs::path("map.json"));
        if (map->getStatus() == tson::ParseStatus::OK)
        {
			LATIN::TextureData data;

			tson::Tileset* tileset = map->getTileset("Sprite-0001");
            std::string s = tileset->getImage().u8string();
            data.Path = s.c_str();
            Tiles.Create(data);
			
        }

        tileLayer = map->getLayer("Tile Layer 1"); //This is a Tile Layer.


	}

	void Update() override
	{
		LATIN::Renderer::Clear({ 0, 0, 0 });
        if (tileLayer->getType() == tson::LayerType::TileLayer)
        {
            //pos = position in tile units
            for (auto& [pos, tileObject] : tileLayer->getTileObjects()) //Loops through absolutely all existing tileObjects
            {
                tson::Tileset* tileset = tileObject.getTile()->getTileset();
                tson::Rect drawingRect = tileObject.getDrawingRect();
                tson::Vector2f position = tileObject.getPosition();
                
                LATIN::RenderData rdata;
                rdata.Position = { position.x, -position.y };
                rdata.Scale = { drawingRect.width, drawingRect.height };
                glm::vec2 min = { drawingRect.x, drawingRect.y };
                min /= 48.0f;
                glm::vec2 max = { drawingRect.x + drawingRect.width, drawingRect.y + drawingRect.height };
                max /= 48.0f;
                rdata.TexCoordsMin = min;
                rdata.TexCoordsMax = max;
                rdata.texture = &Tiles;
                LATIN::Renderer::DrawQuad(rdata);

                if (LATIN::Input::GetKey('A').Pressed)
                    LATIN::Camera::Size += 2.0f;
                //Here you can determine the offset that should be set on a sprite
                //Example on how it would be done using SFML (where sprite presumably is a member of a generated game object):
                //sf::Sprite *sprite = storeAndLoadImage(tileset->getImage().u8string(), {0, 0});
                //if (sprite != nullptr)
                //{
                //    sprite->setTextureRect({drawingRect.x, drawingRect.y, drawingRect.width, drawingRect.height});
                //    sprite->setPosition({position.x, position.y});
                //    m_window.draw(*sprite);
                //}
            }
        }
	}
private:
	std::unique_ptr<tson::Map> map;
	LATIN::Texture Tiles;
    tson::Layer* tileLayer;
};

int main()
{
	StartLatinEngine(Game, 640, 480);
	return 0;
}