cmake_minimum_required(VERSION 3.10)
project(coursework)

set(CMAKE_CXX_STANDARD 20)


set(CINDER_PATH "C:/msys64/home/Пользователь/Cinder")

add_executable(coursework main.cpp)


target_include_directories(coursework PRIVATE "${CINDER_PATH}/include")

target_link_libraries(coursework PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/libcinder.a"
    opengl32
    gdiplus
    gdi32
    comdlg32
    user32
    advapi32
    shell32
    ole32
    oleaut32
    uuid
    ws2_32
    wininet    
    iphlpapi   
    shlwapi    
    version    
)