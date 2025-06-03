

int DELAY_TIME = 10;

void loop(){
    t_start = time.time();

    /* LOOP LOGIC */

    t_end = time.time();

    int delta = t_end - t_start; // convert to milisec and int
    
    if (delta < DELAY_TIME){
        delay(DELAY_TIME - delta);
    }
    else{
        // LOOP TAKES MORE THEN THE DELAY_TIME.
        // THIS IS A PROBLEM AND WE NEED TO ADJUST TO HIGHER DELAY TIME.
    }
}