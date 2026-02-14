#include <raylib.h>


int main() 
{
    
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    const int arrayRows = 1920;
    const int arrayColumns = 1080;
    int mouseRadius = 5;
    int plotSize = screenHeight/arrayColumns;
    int array[arrayRows][arrayColumns] = {0};
    int tempArray[arrayRows][arrayColumns] = {0};
    InitWindow(screenWidth, screenHeight, "Sandbox Simulation");
    SetTargetFPS(60);
    double lastTime = GetTime();
    double currentTime = 0.0, tickPeriod = .02;
    array[5][10]=1;
    array[6][11]=1;
    array[4][11]=1;
    while (!WindowShouldClose())
    {
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
                        if(tempArray[i][j+1] != 0){
                            if(tempArray[i+1][j+1] ==0 && tempArray[i+1][j]==0){
                                tempArray[i][j] = 0;
                                tempArray[i+1][j+1] = 1;
                            }else if(tempArray[i-1][j+1] ==0&& tempArray[i-1][j]==0){
                                tempArray[i][j] = 0;
                                tempArray[i-1][j+1] = 1;
                            }else{
                                tempArray[i][j] = 1;
                            }    
                        }else{
                            tempArray[i][j] = 0;
                            tempArray[i][j+1] = 1;
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
            for(int i = rowClicked-mouseRadius; i < rowClicked+mouseRadius; i++){
                for( int j = columnClicked-mouseRadius; j< columnClicked+mouseRadius; j++){
                    if(array[i][j] == 0){
                        array[i][j] = 1;
                    }
                }
            }
            
            
        }
        if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
            int rowClicked = GetMousePosition().x/plotSize;
            int columnClicked = GetMousePosition().y/plotSize;
            array[rowClicked][columnClicked] = 2;
        }


        BeginDrawing();
        ClearBackground(WHITE);
        for(int i = 0; i < arrayRows; i++){
            for(int j = 0; j < arrayColumns; j++){
                if(array[i][j] == 0){
                    DrawRectangle(i*plotSize, j*plotSize, plotSize-1, plotSize-1,BLACK);
                }else if(array[i][j] == 2){
                    DrawRectangle(i*plotSize, j*plotSize, plotSize-1, plotSize-1,GRAY);
                }else{
                    DrawRectangle(i*plotSize, j*plotSize, plotSize-1, plotSize-1,BLUE);
                }
            }
        }

        EndDrawing();
    }
    
    CloseWindow();
}