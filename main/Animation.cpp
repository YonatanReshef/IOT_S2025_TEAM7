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

    this->frame += 1;
}
    

void Animation::disconnectedAnimation() {
    uint32_t map_colors[256];

    // Create a flickering checkerboard effect based on the frame number
    for (int y = 0; y < 16; ++y) {
        for (int x = 0; x < 16; ++x) {
            // Flicker between checkerboard patterns every frame
            bool flicker = ((x + y + this->frame) % 2 == 0);

            map_colors[y * 16 + x] = flicker
                ? colors[MazeMaps::BlockType::WALL]   // Random 'on' block (WALL or BALL)
                : colors[MazeMaps::BlockType::EMPTY]; // Off
        }
    }

    // Optional: Make the center pixel blink
    if ((this->frame % 4) < 2) {
        map_colors[8 * 16 + 8] = colors[MazeMaps::BlockType::BALL];
    }

    this->matrix->setBoard(map_colors);

    this->frame += 1;
}

void Animation::stoppedAnimation() {
    uint32_t map_colors[256];

    // Shrink from full screen (size 16) down to center (size 0)
    int max_size = 16;
    int size = max_size - (frame % (max_size + 1)); // size from 16 to 0

    // Calculate square bounds (centered)
    int half = size / 2;
    int xmin = 8 - half;
    int xmax = 7 + half + (size % 2); // +1 if size is odd
    int ymin = 8 - half;
    int ymax = 7 + half + (size % 2); // +1 if size is odd

    for (int y = 0; y < 16; ++y) {
        for (int x = 0; x < 16; ++x) {
            bool inside = (x >= xmin && x <= xmax && y >= ymin && y <= ymax);

            map_colors[y * 16 + x] = inside
                ? colors[MazeMaps::BlockType::WALL]   // Active square
                : colors[MazeMaps::BlockType::EMPTY]; // Background
        }
    }

    this->matrix->setBoard(map_colors);
    this->frame += 1;
}



void Animation::update(int dt){
    tick += dt;

    if(tick >= 200){

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
            
        case STOPPED:

            stoppedAnimation();

            if(this->frame == STOPPED_FRAME_NUM){
                this->frame = 0;
                this->cycle += 1;
            }
            
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
