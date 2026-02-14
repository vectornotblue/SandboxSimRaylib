#include <raylib.h>


int main() 
{
    
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    const int arrayRows = 192;
    const int arrayColumns = 108;
    int mouseRadius = 1;
    int plotSize = screenHeight/arrayColumns;
    int array[arrayRows][arrayColumns] = {0};
    int tempArray[arrayRows][arrayColumns] = {0};
    InitWindow(screenWidth, screenHeight, "Sandbox Simulation");
    SetTargetFPS(60);
    double lastTime = GetTime();
    double currentTime = 0.0, tickPeriod = .02;
    int waterDispersity = 4;
    
    while (!WindowShouldClose())
    {
        if(IsKeyPressed(KEY_R)){
            for(int i = 0; i < arrayRows; i++){
                for(int j = 0; j < arrayColumns; j++){
                    array[i][j] = 0; 
                    tempArray[i][j] = 0;
                }
            }
        }
        currentTime = GetTime();
        if (currentTime-lastTime>tickPeriod){
            lastTime = currentTime;
            for(int i = 0; i<arrayRows; i++){
                for(int j = 0; j < arrayColumns; j++){
                    if(array[i][j] ==2)
                    {
                        tempArray[i][j] =2;
                    }else if((array[i][j] == 1)&&(j+1 <arrayColumns))
                    {
                        int checkDir = GetRandomValue(0,1) == 0 ? -1:1;
                        if(tempArray[i][j+1] != 0){
                            if(tempArray[i+checkDir][j+1] ==0 && tempArray[i+checkDir][j]==0){
                                tempArray[i][j] = 0;
                                tempArray[i+checkDir][j+1] = 1;
                            }else if(tempArray[i-checkDir][j+1] ==0&& tempArray[i-checkDir][j]==0){
                                tempArray[i][j] = 0;
                                tempArray[i-checkDir][j+1] = 1;
                            }else{
                                tempArray[i][j] = 1;
                            }    
                        }else{
                            tempArray[i][j] = 0;
                            tempArray[i][j+1] = 1;
                        }
                    } else if((array[i][j] ==3) &&(j+1 <arrayColumns)){

                        int checkDir = GetRandomValue(0,1) == 0 ? -1:1;
                        if(tempArray[i][j+1] != 0){
                            if(tempArray[i+checkDir][j+1] ==0 && tempArray[i+checkDir][j]==0){
                                tempArray[i][j] = 0;
                                tempArray[i+checkDir][j+1] = 3;
                            }else if(tempArray[i-checkDir][j+1] ==0&& tempArray[i-checkDir][j]==0){
                                tempArray[i][j] = 0;
                                tempArray[i-checkDir][j+1] = 3;
                            }else{
                                int checkDir2 = GetRandomValue(0,1) == 0 ? -1:1;
                                bool foundNewCell = false;/* WATER NOT DISPERSING YET
                                for(int k = 0; !foundNewCell && k < waterDispersity; k++){
                                    if(tempArray[i+k*checkDir2][j] ==0){
                                        tempArray[i+k*checkDir2][j] = 3;
                                        foundNewCell = true;
                                    }else if (tempArray[i-k*checkDir2][j]){
                                        tempArray[i-k*checkDir2][j] = 3;
                                        foundNewCell = true;
                                    }
                                } */
                                tempArray[i][j] = foundNewCell? 0:3;
                            }    
                        }else{
                            tempArray[i][j] = 0;
                            tempArray[i][j+1] = 3;
                        }
                    }
                }   
            }
            for(int i = 0; i<arrayRows; i++){
                for(int j = 0; j < arrayColumns; j++){
                    array[i][j] = tempArray[i][j];
                }
            }
        }
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            int rowClicked = GetMousePosition().x/plotSize;
            int columnClicked = GetMousePosition().y/plotSize;
            for(int i = rowClicked-mouseRadius+1; i < rowClicked+mouseRadius; i++){
                for( int j = columnClicked-mouseRadius+1; j< columnClicked+mouseRadius; j++){
                    if(array[i][j] == 0){
                        array[i][j] = 1;
                    }
                }
            }
            
            
        }
        if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
            int rowClicked = GetMousePosition().x/plotSize;
            int columnClicked = GetMousePosition().y/plotSize;
            for(int i = rowClicked-mouseRadius+1; i < rowClicked+mouseRadius; i++){
                for( int j = columnClicked-mouseRadius+1; j< columnClicked+mouseRadius; j++){
                    if(array[i][j] == 0){
                        array[i][j] = 2;
                    }
                }
            }
        }
        if(IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)){
            int rowClicked = GetMousePosition().x/plotSize;
            int columnClicked = GetMousePosition().y/plotSize;
            for(int i = rowClicked-mouseRadius+1; i < rowClicked+mouseRadius; i++){
                for( int j = columnClicked-mouseRadius+1; j< columnClicked+mouseRadius; j++){
                    if(array[i][j] == 0){
                        array[i][j] = 3;
                    }
                }
            }
        }


        BeginDrawing();
        ClearBackground(WHITE);
        for(int i = 0; i < arrayRows; i++){
            for(int j = 0; j < arrayColumns; j++){
                if(array[i][j] == 0){
                    DrawRectangle(i*plotSize, j*plotSize, plotSize, plotSize,BLACK);
                }else if(array[i][j] == 2){
                    DrawRectangle(i*plotSize, j*plotSize, plotSize, plotSize,GRAY);
                }else if(array[i][j] == 3){
                    DrawRectangle(i*plotSize, j*plotSize, plotSize, plotSize,BLUE);
                }else{
                    DrawRectangle(i*plotSize, j*plotSize, plotSize, plotSize,YELLOW);
                }
            }
        }
        DrawRectangle(0,0,950,30, BLACK);
        DrawText("(R)-Restart     (L Mouse)-Sand     (M Mouse)-Water     (R Mouse)-Stone", 0, 0, 25, BLUE);
        EndDrawing();
    }
    
    CloseWindow();
}