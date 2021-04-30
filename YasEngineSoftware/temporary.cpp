//void drawPoints(const std::vector<Vector2D<float>*>& cubePoints, SDL_Renderer* renderer)
//{
//    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
//    for (auto v : cubePoints)
//    {
//        SDL_RenderDrawPoint(renderer, (int)v->x, (int)v->y);
//    }
//}
//
//float calculateY(float x, const Vector2D<float>& point0, const Vector2D<float>& point1)
//{
//    return ((point1.y - point0.y) / point1.x - point0.x) * (x - point0.x) + point0.y;
//}
//
//
//float twoPointsDistance(const Vector2D<float>& point0, const Vector2D<float>& point1)
//{
//    return sqrt(pow(point1.x - point0.x, 2.0) + pow(point1.y - point0.y, 2.0F));
//}
//
//int twoPointsDistance(const Vector2D<int>& point0, const Vector2D<int>& point1)
//{
//    return sqrt(pow(point1.x - point0.x, 2.0) + pow(point1.y - point0.y, 2.0F));
//}

//-----------------------------------------------------------------------------|---------------------------------------|
//                                                                            80                                     120
                                        //2021-01-17-1125pm

//void drawBresenhamLine(Vector2D<float>* point0, Vector2D<float>* point1, SDL_Renderer* renderer);
//void drawBresenhamLine20200117_01(Vector2D<float>* point0, Vector2D<float>* point1, SDL_Renderer* renderer);
//void drawBresenhamLine20200117_02(Vector2D<int>* point0, Vector2D<int>* point1, SDL_Renderer* renderer);

//void drawBresenhamLine(Vector2D<float>* point0, Vector2D<float>* point1, SDL_Renderer* renderer)
//{
//    float deltaX = point1->x - point0->x; // good name is delta or delay
//    float deltaY = point1->y - point0->y;
//
//    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
//
//    float deltaError = 0;
//    if (deltaX != 0)
//    {
//        deltaError = abs(deltaY / deltaX);
//    }
//
//    float error = 0.0F;
//    float y = point0->y;
//
//    for (int i = (int) point0->x; i <= point1->x; i++)
//    {
//        SDL_RenderDrawPoint(renderer, i, y);
//        //pw.setColor(i, (int) y, Color.GREEN);
//        //y = calculateY(i, point0, point1);
//        error = error + deltaError;
//        if (error >= 0.5F)
//        {
//            y = (int) (y + signum(deltaY));
//            error = error - 1;
//        }
//    }
//}
//
//void drawBresenhamLine20200117_01(Vector2D<float>* point0, Vector2D<float>* point1, SDL_Renderer* renderer)
//{
//    float deltaX = point1->x - point0->x;
//    float deltaY = point1->y - point0->y;
//
//    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
//
//    float deltaError = 0;
//    if (deltaX != 0)
//    {
//        deltaError = abs(deltaY / deltaX);
//    }
//
//    float error = 0.0F;
//    float y = point0->y;
//
//    for (int i = (int) point0->x; i <= point1->x; i++)
//    {
//        SDL_RenderDrawPoint(renderer, i, y);
//        //pw.setColor(i, (int) y, Color.GREEN);
//        //y = calculateY(i, point0, point1);
//        error = error + deltaError;
//        if (error >= 0.5F)
//        {
//            y = (int) (y + signum(deltaY));
//            error = error - 1;
//        }
//    }
//}
//
//
////One performance issue is the 1/2 factor in the initial value of D. Since all of this is about the sign
////of the accumulated difference, then everything can be multiplied by 2 with no consequence.
//void drawBresenhamLine20200117_02(Vector2D<int>* point0, Vector2D<int>* point1, SDL_Renderer* renderer)
//{
//    int deltaX = point1->x - point0->x;
//    int deltaY = point1->y - point0->y;
//
//    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
//
//    float deltaError = 0;
//    deltaError = (2 * deltaY) - deltaX;
//
//    int y = point0->y;
//
//    for (int i = (int) point0->x; i <= point1->x; i++)
//    {
//        SDL_RenderDrawPoint(renderer, i, y);
//        if (deltaError >0)
//        {
//            y = y + 1;
//            deltaError = deltaError - 2*deltaX;
//        }
//        deltaError = deltaError + 2*deltaY;
//    }
//}

//                                                                            80                                     120
//-----------------------------------------------------------------------------|---------------------------------------|