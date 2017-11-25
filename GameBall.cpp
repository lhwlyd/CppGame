#include "stdafx.h"
#include "GameBall.h"
#include <time.h>
#include "Game.h"

GameBall::GameBall() : _velocity(500.0f), _elapsedTimeSinceStart(0.0f) {
    Load("images/ball.png");
    assert(IsLoaded());

    GetSprite().setOrigin(15,15);

    srand(time(NULL));
    _angle = (rand()%360)+1;
}

GameBall::~GameBall(){
    
}

void GameBall::Update(float elapsedTime){
    _elapsedTimeSinceStart += elapsedTime;

    //Delay game from starting until 3 seconds have passed
    if( _elapsedTimeSinceStart < 3.0f )
        return;

    float moveAmount = _velocity * elapsedTime;

    float moveByX = LinearVelocityX(_angle) * moveAmount; 
    float moveByY = LinearVelocityY(_angle) * moveAmount;

    // collide with the left side of the screen
    if( GetPosition().x + moveByX <= 0 + GetWidth()/2 ||
        GetPosition().x + GetHeight()/2 + moveByX >= Game::SCREEN_WIDTH){
            //Ricochet! ?
            _angle = 360.0f - _angle;
            if( _angle > 260.0f && _angle < 280.0f) _angle += 20.0f;
            if( _angle > 80.0f && _angle < 100.0f) _angle += 20.0f;
            moveByX = -moveByX;
    }

    // Cast a VisibleGameObject to Player paddle
    // dynamic_cast checks if the cast is legit, if not, return NULL. Slow! Only use it on Objs or ptrs
    PlayerPaddle* player1 = dynamic_cast<PlayerPaddle*>(Game::GetGameObjectManager().Get("Paddle1"));
    // Make sure the cast is legit
    if(player1 != NULL){
        sf::Rect<float> p1BB = player1->GetBoundingRect();

        if( (p1BB.intersects(GetBoundingRect()) ) ){
            if( GetBoundingRect().left > p1BB.left && 
            GetBoundingRect().left + GetWidth() < p1BB.left + p1BB.width ){
                _angle = 360.0f - (_angle - 180.0f);
                if(_angle > 360.0f) _angle -= 360.0f;
            }


            moveByY = -moveByY;

            // Make sure ball isn't inside paddle
            if(GetBoundingRect().top + GetHeight() > p1BB.top
            && (GetBoundingRect().left > p1BB.left 
            && GetBoundingRect().left + GetWidth() < p1BB.left + player1->GetWidth() ) ){
                SetPosition(GetPosition().x, p1BB.top - GetWidth()/2 -1);
            }

            // Now add "Englsih" based on the players velocity
            float playerVelocity = player1->GetVelocity();

            if(playerVelocity < 0){
                // moving left
                _angle -= 20.0f;
                if(_angle < 0) _angle = 360.0f + _angle;
            } else if(playerVelocity > 0){
                _angle += 20.0f;
                if(_angle > 360.0f) _angle = _angle - 360.0f;
            }

            _velocity += 10.0f;
        }

        if(GetPosition().y - GetHeight()/2 <= 0){
            _angle = 180 - _angle;
            moveByY = -moveByY;
        }

        if(GetPosition().y + GetHeight()/2 + moveByY >= Game::SCREEN_HEIGHT){
            // move to middle of the screen for now and randomize angle
            GetSprite().setPosition(Game::SCREEN_WIDTH/2, Game::SCREEN_HEIGHT/2);
            _angle = (rand()%360) + 1;
            _velocity = 500.0f;
            _elapsedTimeSinceStart = 0.0f;
        }

        GetSprite().move(moveByX, moveByY);
    }  
}

float GameBall::LinearVelocityX(float angle){
    angle -= 90;
    if(angle < 0){
        angle = 360 + angle;
    }
    return (float)std::cos( angle * (3.1415926) / 180.0f );
}

float GameBall::LinearVelocityY(float angle){
    angle -= 90;
    if( angle<0 ) angle = 360 + angle;
    return (float)std::sin( angle * (3.1415926 / 180.0f) );
}