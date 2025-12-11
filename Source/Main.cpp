#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include "Renderer.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "Plane.h"
#include "Scene.h"
#include "Sphere.h"
#include "Random.h"
#include "Material.h"

#include <iostream>

int main() {
	constexpr int SCREEN_WIDTH = 1920;
	constexpr int SCREEN_HEIGHT = 1080;

	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Ray Tracer", SCREEN_WIDTH, SCREEN_HEIGHT);

	Framebuffer framebuffer(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

	float aspectRatio = (float)framebuffer.width / framebuffer.height;
	Camera camera(70.0f, aspectRatio);
	camera.SetView({ 0, 2, 5 }, { 0, 0, 0 });

	Scene scene;

	/*
	auto red = std::make_shared<Lambertian>(color3_t{ 1.0f, 0.0f, 0.0f });
	auto green = std::make_shared<Lambertian>(color3_t{ 0.0f, 1.0f, 0.0f });
	auto blue = std::make_shared<Lambertian>(color3_t{ 0.0f, 0.0f, 1.0f });
	auto light = std::make_shared<Emissive>(color3_t{ 1.0f, 1.0f, 1.0f }, 3.0f);
	auto metal = std::make_shared<Metal>(color3_t{ 1.0f, 1.0f, 1.0f }, 0.0f);
	std::shared_ptr<Material> materials[] = { red, green, blue, light, metal };

	for (int i = 0; i < 15; i++) {
		glm::vec3 position = random::getReal(glm::vec3{ -3.0f }, glm::vec3{ 3.0f });

		std::unique_ptr<Object> sphere = std::make_unique<Sphere>(Transform{ position }, random::getReal(0.2f, 1.0f), materials[random::getInt(4)]);
		scene.AddObject(std::move(sphere));
	}

	auto gray = std::make_shared<Lambertian>(color3_t{ 0.2f, 0.2f, 0.2f });
	std::unique_ptr<Plane> plane = std::make_unique<Plane>(Transform{ glm::vec3{ 0.0f, 0.0f, 0.0f } }, gray);
	scene.AddObject(std::move(plane));
	*/

	auto ground_material = std::make_shared<Lambertian>(color3_t(0.5f, 0.5f, 0.5f));
	scene.AddObject(std::make_unique<Plane>(Transform{ { 0.0f, 0.0f, 0.0f } }, ground_material));

	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			glm::vec3 position(a + 0.9f * random::getReal(), 0.2f, b + 0.9f * random::getReal());

			if ((position - glm::vec3(4.0f, 0.2f, 0.0f)).length() > 0.9f) {
				std::shared_ptr<Material> sphere_material;

				auto choose_mat = random::getReal();
				if (choose_mat < 0.8f) {
					// diffuse
					auto albedo = HSVtoRGB({ 360.0f * random::getReal(), 1.0f, 1.0f });
					sphere_material = std::make_shared<Lambertian>(albedo);
					scene.AddObject(std::make_unique<Sphere>(Transform{ position }, 0.2f, sphere_material));
				}
				else if (choose_mat < 0.95f) {
					// metal
					auto albedo = color3_t{ random::getReal(0.5f, 1.0f) };
					auto fuzz = random::getReal(0.5f);
					sphere_material = std::make_shared<Metal>(albedo, fuzz);
					scene.AddObject(std::make_unique<Sphere>(Transform{ position }, 0.2f, sphere_material));
				}
				else {
					// glass
					sphere_material = std::make_shared<Dielectric>(HSVtoRGB(360.0f * random::getReal(), 1.0f, 1.0f), 1.0f);
					scene.AddObject(std::make_unique<Sphere>(Transform{ position }, 0.2f, sphere_material));
				}
			}
		}
	}

	auto material1 = std::make_shared<Dielectric>(color3_t{ 1.0f, 1.0f, 1.0f }, 1.5f);
	scene.AddObject(make_unique<Sphere>(Transform{ glm::vec3{ 0.0f, 1.0f, 0.0f } }, 1.0f, material1));

	auto material2 = std::make_shared<Lambertian>(color3_t(0.4f, 0.2f, 0.1f));
	scene.AddObject(make_unique<Sphere>(Transform{ glm::vec3{ -4.0f, 1.0f, 0.0f } }, 1.0f, material2));

	auto material3 = std::make_shared<Metal>(color3_t(0.7f, 0.6f, 0.5f), 0.0f);
	scene.AddObject(make_unique<Sphere>(Transform{ glm::vec3{ 4.0f, 1.0f, 0.0f } }, 1.0f, material3));

	SDL_Event event;
	bool quit = false;
	while (!quit) {
		
		while (SDL_PollEvent(&event)) {
			
			if (event.type == SDL_EVENT_QUIT) {
				quit = true;
			}
			
			if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
				quit = true;
			}
		}

		framebuffer.Clear({ 0, 0, 0, 255 });
		scene.Render(framebuffer, camera, 150);

		framebuffer.Update();

		renderer.CopyFramebuffer(framebuffer);
		renderer.Show();
	}
}