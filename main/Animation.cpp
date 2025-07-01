#include "Animation.h"
#include "mazeMaps.h"



Animation::Animation(LedMatrix* matrix){
    this->matrix = matrix;
    this->frame = 0;
    this->is_animation_done = false;
    this->cycle = 0;
    this->tick = 0;
}


void Animation::winAnimation(){
    // Compute the radius for this frame
    int radius;
    if (this->frame <= MAX_RADIUS) {
        // Shrinking phase
        radius = MAX_RADIUS - this->frame;
    } else {
        // Expanding phase
        radius = this->frame - MAX_RADIUS;
    }

    // Prepare and draw the frame
    uint32_t map_colors[256];
    for (int y = 0; y < 16; ++y) {
        for (int x = 0; x < 16; ++x) {
            int dx = x - 8;
            int dy = y - 8;
            int dist_sq = dx * dx + dy * dy;
            map_colors[y * 16 + x] = (dist_sq <= radius * radius)
                ? colors[MazeMaps::BlockType::BALL]
                : colors[MazeMaps::BlockType::EMPTY];
        }
    }

    this->matrix->setBoard(map_colors);
    this->matrix->update(10);

    this->frame += 1;
}
    

void Animation::disconnectedAnimation(){
    this->frame += 1;
}

void Animation::update(int dt){
    tick += dt;

    if(tick >= 250){

        if(cycle == NUM_CYCLES){
            this->is_animation_done = true;
            return;
        }


        switch (this->type)
        {
        case WIN:
            winAnimation();

            if(this->frame == WIN_FRAME_NUM){
                this->frame = 0;
                this->cycle += 1;
            }


            break;

        case DISCONNECTED:
                
            disconnectedAnimation();

            if(this->frame == DISCONNECTED_FRAME_NUM){
                this->frame = 0;
                this->cycle += 1;
            }

            break;
        
        default:
            break;
        }

        this->tick = 0;
    }
}



void Animation::setup(Type type){
    this->type = type;
    this->frame = 0;
    this->is_animation_done = false;
    this->cycle = 0;
    this->tick = 0;
}



bool Animation::isDone(){
    return this->is_animation_done;
}
