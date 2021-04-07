#include "pch.h"
#include "CppLib.h"



extern "C"
{
    CPPLIB_API void zaszum(RGBApixel** bitmapa, RGBApixel** bitmapanowa, int stopien, int llinii, int k, int szer, int wys)
    {
       // int z = 1;

        RGBApixel nowy;
        int wyn1, wyn2, wyn3;
        int jest1, jest2, jest3;
        int randd;
        for (int i = k; i < szer; i++)
        {
            for (int j = 0; j < wys; j++)
            {
                jest1 = bitmapa[i][j].Red;
                jest2 = bitmapa[i][j].Green;
                jest3 = bitmapa[i][j].Blue;
                wyn1 =bitmapanowa[i][j].Red ^ jest1;
                wyn2 = bitmapanowa[i][j].Green ^ jest2;
                wyn3 = bitmapanowa[i][j].Blue ^ jest3;
                randd = ((wyn1 + wyn2) * wyn3) % 100;
                if (randd < stopien)
                {
                    nowy.Red = wyn1;
                    nowy.Green = wyn2;
                    nowy.Alpha = NULL;
                    nowy.Blue = wyn3;
                 
                    bitmapa[i][j] = nowy;
               }
            }
        }
    }
}