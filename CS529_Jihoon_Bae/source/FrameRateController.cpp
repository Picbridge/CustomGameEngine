#include "pch.h"

FrameRateController* FrameRateController::instance = nullptr;

FrameRateController* FrameRateController::GetInstance()
{
    if (!instance) {
        instance = new FrameRateController();
    }
    return instance;
}

void FrameRateController::SetTargetFPS(const unsigned int target)
{
    frameTime = std::chrono::duration<double, std::ratio<1>>(1.0 / target);
}

void FrameRateController::Update()
{
    frameStart = std::chrono::high_resolution_clock::now();
}

void FrameRateController::LateUpdate()
{
    auto frameEnd = std::chrono::high_resolution_clock::now();
    auto elapsed = frameEnd - frameStart;
    if (elapsed < frameTime) {
        std::this_thread::sleep_for(frameTime - elapsed);
    }
    m_deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(std::chrono::high_resolution_clock::now() - frameStart).count();
    frameStart = std::chrono::high_resolution_clock::now(); // reset frame start time

}