#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <math.h>



int main(){

  

    
   FILE *p = fopen("Test.yuv", "rb");
   fseek(p, 0, SEEK_END);
   int FileLen = ftell(p);
   fseek(p, 0, SEEK_SET);
   int Width = 320;
   int Height= 240;
   int L = Width*Height;
   int HL= Width*Height/2;
   printf("FileLen:%d",FileLen);
   int FrameNum = FileLen / L;
   printf("FrameNum:%d",FrameNum);
   FILE * newfb = fopen("320x240yuv420p.yuv","wb");
   
   for(int m=0; m<FrameNum;m++){
      uint8_t  S_Y[76800] = {0};
      uint8_t  S_U[19200] = {0};
      uint8_t  S_V[19200] = {0};
      uint8_t  Rubbish[1] = {0};
      uint8_t * S_Y_Index = S_Y;
      uint8_t * S_U_Index = S_U;
      uint8_t * S_V_Index = S_V;
      for (size_t i = 0; i < L; i++)
      {
         if (i%2 ==0)
         {
            fread(S_Y_Index++, 1, 1, p);
         }
         if (i%4 ==1)
         {
            if (i%8 ==1)
            {
               fread(S_U_Index++, 1, 1, p);
            }else
            {
               fread(Rubbish, 1, 1, p);
            }
         }
         if (i%4 ==3)
         {
            if (i%8 ==3)
            {
               fread(S_V_Index++, 1, 1, p);
            }else
            {
               fread(Rubbish, 1, 1, p);
            }
         }
      }
      fwrite(&S_Y, 1, sizeof(S_Y),  newfb);
      fwrite(&S_U, 1, sizeof(S_U),  newfb);
      fwrite(&S_V, 1, sizeof(S_V),  newfb);   
  }
   
   fclose(p);
   fclose(newfb);


   return 0;
}
