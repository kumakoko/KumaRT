#include "../LibKRT/krt_lib_pch.h"
#include "demo_01_world.h"

int main()
{
    std::shared_ptr<Demo01World> w = std::make_shared<Demo01World>();
    w->Build();
    w->RenderScene();
    w->SavePixelToImageFile("demo_01.png");
    return 0;
}