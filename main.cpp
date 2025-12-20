#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include <deque> // для точек


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
    double mLifetime = 3.0; // Время жизни линии в секундах
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
    ci::gl::clear( ci::Color( 0.1f, 0.1f, 0.1f ) ); // темный экран
    
    if( mPoints.size() < 2 ) return;

    // Включаем поддержку прозрачности
    ci::gl::enableAlphaBlending();

    // Рисуем линии
    ci::gl::begin( GL_LINE_STRIP ); // точки карте, соедени их
    for( const auto& dot : mPoints ) {
        float age = (float)(getElapsedSeconds() - dot.birthTime);
        float alpha = 1.0f - (age / (float)mLifetime);
        
        ci::gl::color( ci::ColorA( 0.0f, 0.8f, 1.0f, alpha ) ); // точки видеокарте
        ci::gl::vertex( dot.pos );
    }
    ci::gl::end();
}

CINDER_APP( DrawApp, ci::app::RendererGl )