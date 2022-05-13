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
// 
// 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//void cartesianPositionToWindow(Vector2D<int>* point, Vector2D<int>* windowDimensions)
	//{
	//    point->x = point->x + (windowDimensions->x / 2);
	//    point->y = (point->y * -1) + (windowDimensions->y / 2); // point->y = (point->y * -1) + (windowDimensions->y / 2);
	//}

	//void windowPositionToCartesian(Vector2D<int>* point, Vector2D<int>* windowDimensions)
	//{
	//    point->x = point->x - (windowDimensions->x / 2);
	//    point->y = (point->y * -1) + (windowDimensions->y / 2);
	//}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void drawCartesianAxies(Vector2D<int>* windowDimensions, uint8_t* pixels)
//{
//	int centerX = static_cast<int>(0.5F * windowDimensions->x);
//	int centerY = static_cast<int>(0.5F * windowDimensions->y);
//
//	Vector4D<uint8_t> xDrawingColorRed(255, 0, 0, 0); // RED
//	Vector4D<uint8_t> yDrawingColorGreen(0, 255, 0, 0); // GREEN
//
//	for (int i = 0; i < windowDimensions->x; i++) //X
//	{
//		drawPoint(i, centerY, pixels, &xDrawingColorRed, windowDimensions);
//	}
//
//	for (int i = 0; i < windowDimensions->y; i++) //Y
//	{
//		drawPoint(centerX, i, pixels, &yDrawingColorGreen, windowDimensions);
//	}
//}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//int main()
//{
//    SDL_Init(SDL_INIT_VIDEO);
//
//    SDL_Window* window = SDL_CreateWindow("YasEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 320, 240, SDL_WINDOW_RESIZABLE);
//
//    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
//
//    int width = 320;
//    int height = 240;
//
//    // Since we are going to display a low resolution buffer,
//    // it is best to limit the window size so that it cannot
//    // be smaller than our internal buffer size.
//    SDL_SetWindowMinimumSize(window, width, height);
//
//    SDL_RenderSetLogicalSize(renderer, width, height);
//    SDL_RenderSetIntegerScale(renderer, SDL_TRUE);
//
//    SDL_Texture* screenTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
//
//    //this->pixels = new Uint8[windowDimensions.x * windowDimensions.y * NUMBER_OF_COLORS];
//    //{
//    //    for (int y = 0; y < windowDimensions.y; y++)
//    //    {
//    //        for (int x = 0; x < windowDimensions.x; x++)
//    //        {
//    //            pixels[NUMBER_OF_COLORS * (y * windowDimensions.x + x) + RED_POSITION] = drawingColor.x; // windowDimensions->x <- WINDOW WIDTH
//    //            pixels[NUMBER_OF_COLORS * (y * windowDimensions.x + x) + GREEN_POSITION] = drawingColor.y;
//    //            pixels[NUMBER_OF_COLORS * (y * windowDimensions.x + x) + BLUE_POSITION] = drawingColor.z;
//    //            pixels[NUMBER_OF_COLORS * (y * windowDimensions.x + x) + ALPHA_POSITION] = drawingColor.w;
//    //        }
//    //    }
//    //}
//
//
//    SDL_SetTextureBlendMode(screenTexture, SDL_BLENDMODE_BLEND);
//
//
//    int pixelsTableSize = width * height * 4;
//
//    Uint8* pixelsTable = new Uint8[pixelsTableSize];
//
//    for (int y = 0; y < height; y++)
//    {
//        for (int x = 0; x < width; x++)
//        {
//            ///0xffffffff
//            //pixels[NUMBER_OF_COLORS * (y * windowDimensions.x + x) + ALPHA_POSITION] = drawingColor.w;
//            pixelsTable[4 * (y * width + x) + 0] = 255;
//            pixelsTable[4 * (y * width + x) + 1] = 255;
//            pixelsTable[4 * (y * width + x) + 2] = 255;
//            pixelsTable[4 * (y * width + x) + 3] = 255;
//        }
//    }
//
//    //Uint8* NEW_RED = new Uint8(0);
//    //Uint8* NEW_GREEN = new Uint8(0);
//    //Uint8* NEW_BLUE = new Uint8(0);
//    //Uint8* ALPHA_OPAQUE = new Uint8(SDL_ALPHA_OPAQUE);
//
//
//
//    Uint8 NEW_RED = 55;
//    Uint8 NEW_GREEN = 55;
//    Uint8 NEW_BLUE = 55;
//    Uint8 ALPHA_OPAQUE = SDL_ALPHA_OPAQUE;
//
//    //SDL_SetRenderDrawColor(renderer, NEW_RED, NEW_GREEN, NEW_BLUE, ALPHA_OPAQUE);
//
//    while (1)
//    {
//        SDL_Event event;
//        while (SDL_PollEvent(&event))
//        {
//            if (event.type == SDL_QUIT) exit(0);
//        }
//
//        for (int y = 0; y < height; y++)
//        {
//            for (int x = 0; x < width; x++)
//            {
//                //pixelsTable[x + y * width] = 0x000000;
//                //pixels[NUMBER_OF_COLORS * (y * windowDimensions.x + x) + ALPHA_POSITION] = drawingColor.w;
//                pixelsTable[4 * (y * width + x) + 0] = 0;
//                pixelsTable[4 * (y * width + x) + 1] = 0;
//                pixelsTable[4 * (y * width + x) + 2] = 0;
//                pixelsTable[4 * (y * width + x) + 3] = 0;
//            }
//        }
//
//        for (int y = 0; y < 50; y++)
//        {
//            for (int x = 0; x < 50; x++)
//            {
//                if (y == x)
//                {
//                    // pixelsTable[x + y * width] = 0xFF000030;
//
//                    pixelsTable[4 * (y * width + x) + 0] = 255;
//                    pixelsTable[4 * (y * width + x) + 1] = 0;
//                    pixelsTable[4 * (y * width + x) + 2] = 0;
//                    pixelsTable[4 * (y * width + x) + 3] = 255;
//                }
//            }
//        }
//        // SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
//        SDL_RenderClear(renderer);
//        //SDL_RenderClear(renderer);
//        SDL_UpdateTexture(screenTexture, NULL, pixelsTable, width * 4);
//        SDL_RenderCopy(renderer, screenTexture, NULL, NULL);
//        SDL_RenderPresent(renderer);
//    }
//}

//                                                                            80                                     120
//-----------------------------------------------------------------------------|---------------------------------------|