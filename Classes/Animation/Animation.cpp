
#include "Animation.h"

void Animation::tick(float time) {
    if (!isPlaying) return;

    currentFrame += speed * time;

    if (currentFrame > frames.size()) {
        currentFrame -= frames.size();
        if (!loop) {isPlaying=false; return;}
    }

    int i = currentFrame;
    sprite.setTextureRect( frames[i] );
    if (flip) sprite.setTextureRect( frames_flip[i] );
}