#include "Application.h"

int main(int argc, char** argv)
{
    Vox::Application app({ "Voxel Engine", 1280, 720 });

    app.Run();

    return 0;
}