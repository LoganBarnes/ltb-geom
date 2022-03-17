// ///////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2022 Logan Barnes - All Rights Reserved
// ///////////////////////////////////////////////////////////////////////////////////////

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG
#include <spdlog/spdlog.h>

#include "ltb/app/application_data.hpp"
#include "ltb/app/glfw_vulkan_imgui_app.hpp"

#include <doctest/doctest.h>

class HelloTriangleApp : public ltb::app::GlfwVulkanImguiApp {
public:
    ~HelloTriangleApp() override = default;

private:
    auto update() -> void override {}
    auto render() -> void override {}
    auto resized() -> void override {}
    auto dropped_files(std::vector<std::filesystem::path> const& /*paths*/) -> void override {}
};

auto main() -> int {
    spdlog::set_level(spdlog::level::debug);

    // auto extensions = HelloTriangleApp::get_extensions();
    // auto layers     = HelloTriangleApp::get_validation_layers();

    auto result = HelloTriangleApp{}
                      .init_window({
                          "VK Playground",
                          {1280, 720},
                          ltb::app::WindowType::Resizable,
                          4,
                      })
                      .and_then([](auto* app) { return app->init_vulkan({}); })
                      .and_then(&HelloTriangleApp::run);

    if (!result) {
        spdlog::error("{}", result.error().debug_error_message());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}