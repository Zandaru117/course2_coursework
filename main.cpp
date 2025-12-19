#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include <deque>

// Структура для точки линии
struct Dot {
    ci::vec2 pos;
    double birthTime;
};

class DrawApp : public ci::app::App {
  public:
    void mouseDown( ci::app::MouseEvent event ) override;
    void mouseDrag( ci::app::MouseEvent event ) override;
    void update() override;
    void draw() override;

    std::deque<Dot> mPoints;
    double mLifetime = 5.0; // Время жизни линии в секундах
};

void DrawApp::mouseDown( ci::app::MouseEvent event ) {
    mPoints.push_back({ event.getPos(), getElapsedSeconds() });
}

void DrawApp::mouseDrag( ci::app::MouseEvent event ) {
    mPoints.push_back({ event.getPos(), getElapsedSeconds() });
}

void DrawApp::update() {
    double currentTime = getElapsedSeconds();
    // Удаляем старые точки из начала очереди
    while ( ! mPoints.empty() && (currentTime - mPoints.front().birthTime) > mLifetime ) {
        mPoints.pop_front();
    }
}

void DrawApp::draw() {
    // Темный фон
    ci::gl::clear( ci::Color( 0.1f, 0.1f, 0.1f ) ); 
    
    if( mPoints.size() < 2 ) return;

    // Включаем поддержку прозрачности (alpha blending)
    ci::gl::enableAlphaBlending();

    // Рисуем линии
    ci::gl::begin( GL_LINE_STRIP );
    for( const auto& dot : mPoints ) {
        // Вычисляем прозрачность в зависимости от "возраста"
        float age = (float)(getElapsedSeconds() - dot.birthTime);
        float alpha = 1.0f - (age / (float)mLifetime);
        
        // Голубой с затуханием (ColorA - это цвет с альфа-каналом)
        ci::gl::color( ci::ColorA( 0.0f, 0.8f, 1.0f, alpha ) ); 
        ci::gl::vertex( dot.pos );
    }
    ci::gl::end();
}

// Макрос запуска приложения тоже требует явного указания рендерера
CINDER_APP( DrawApp, ci::app::RendererGl )