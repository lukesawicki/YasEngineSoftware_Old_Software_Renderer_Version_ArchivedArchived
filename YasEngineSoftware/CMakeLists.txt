cmake_minimum_required(VERSION 3.25)
project(YasEngineSoftware)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)
find_package(SDL2 REQUIRED SDL2)
add_executable(YasEngineSoftware
        BackupCpp.cpp
        Circle.cpp
        Circle.hpp
        Collider.cpp
        Collider.hpp
        CosinusPointsGenerator.cpp
        CosinusPointsGenerator.hpp
        Destroyable.cpp
        Destroyable.hpp
        FibonacciPointsGenerator.cpp
        FibonacciPointsGenerator.hpp
        GameObject.hpp
        InputOutputHandler.hpp
        Main.cpp
        Math.cpp
        Math.hpp
        MathematicsFunSurface.cpp
        MathematicsFunSurface.hpp
        PixelsTable.cpp
        PixelsTable.hpp
        Player.cpp
        Player.hpp
        PointsGenerator.hpp
        PointsSet.hpp
        PrimeNumbersPointsGenerator.cpp
        PrimeNumbersPointsGenerator.hpp
        Projectile.cpp
        Projectile.hpp
        SinusPointsGenerator.cpp
        SinusPointsGenerator.hpp
        Spawner.cpp
        Spawner.hpp
        temporary.cpp
        TimePicker.cpp
        TimePicker.hpp
        Timer.hpp
        VariousTools.hpp
        Vector2D.hpp
        Vector4D.hpp
        ViewPort.hpp
        YasEngine.cpp
        YasEngine.hpp
        YasGraphicsLibrary.cpp
        YasGraphicsLibrary.hpp
        ScreenWriter.hpp
        ScreenWriter.cpp
        FontObject.cpp FontObject.hpp FontSurface.hpp FontSurface.cpp)
target_link_libraries(YasEngineSoftware
        PRIVATE SDL2
        PRIVATE libSDL2_mixer.so
        )
