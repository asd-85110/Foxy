#include<raylib.h>
namespace Event{
    bool Init(Texture2D,Texture2D,Texture2D);
    void Quit();
    void DrawHealth(Vector2);
    extern Texture2D health_bar,health,health_fill;
}