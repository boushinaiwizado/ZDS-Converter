#include <stdio.h>
#include <math.h>

void sumOperation16B(int* binary1,int* binary2,int* result)
{
  int carry = 0;
  for(int i = 0;i<=15;i++)
  {
    //printf("%d. %d %d\n",i,binary1[i],binary2[i]);
    if(binary1[i] == 1 && binary2[i] == 1 && carry == 0)
    {
      result[i] = 0;
      carry = 1;
    }
    else if(binary1[i] == 1 && binary2[i] == 1)
    {
      result[i] = 1;
      carry = 1;//Carry is already 1, this is just to keep a track
    }
    else if((binary1[i] == 1 || binary2[i] == 1) && carry == 1 )
    {
      result[i] = 0;
      carry = 1;//Carry is already 1, this is just to keep a track
    }
    else if(binary1[i] == 1 || binary2[i] == 1)
    {
      result[i] = 1;
    }
    else if(binary1[i] == 0 && binary2[i]==0 && carry == 1)
    {
      result[i] = 1;
      carry = 0;
    }
    else 
    {
      result[i] = 0;
    }
  }
}

//0 for negative,1 for positive
void getBinary16B(int* binary,int number,int negative)
{
  int size = 0;
  if(negative)
  {
  do
  {
    if(number%2 == 0)
    {
      binary[size] = 0;
    }
    else
    {
      binary[size] = 1;
    }
    size++;
    if(number == 1)
    {
      break;
    }
    number = number >> 1;
    
  }while(1);

  /*for(int i = size;i>0;i--)
  {
    printf("%d" ,binary[i-1]);
  }*/
  for(int i = size;i<16;i++)
  {
    binary[i] = 0;
  }
  }
  else
  {
    number -= number*2; 
    do
  {
    if(number%2 == 0)
    {
      binary[size] = 1;
      //printf("\n%d\n",size);
    }
    else
    {
      binary[size] = 0;
    }
    size++;
    if(number == 1 )
    {
      break;
    }
    number = number >> 1;
    
  }while(1);

  /*for(int i = size;i>0;i--)
  {
    printf("%d" ,binary[i-1]);
  }*/
  for(int i = size;i<16;i++)
  {
    binary[i] = 1;
  }
  int binaryOne[] = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  sumOperation16B(binary, binaryOne,binary);
  }
}
//Prints Binary number
void printBinary16B(int* binary)
{
  for(int i = 15;i>=0;i--)
  {
    printf("%d" ,binary[i]);
  }
  printf("\n");
}
//Takes binary number and returns hex in out parameter, also prints it
void convertBinaryToHex16B(int* binary,char* out)
{
  int sum = 0;int indexHex = 3;
  for(int i = 0;i<=3;i++)
  {
    //Sums up every four bits 
    for(int j = 0;j<=3;j++)
    {
      sum += binary[j+i*4] * pow(2,j);
      /*printf("%d ",j+i*4);
      printf("%lf\n" ,binary[j+i*4] * pow(2,j));*/
      
    }
    //Picks hex value accordingly to sum value
    //printf("%d\n",sum);
    if(sum > 9)
    {
      switch(sum)
      {
        case 10:out[indexHex] = 'A';break;
        case 11:out[indexHex] = 'B';break;
        case 12:out[indexHex] = 'C';break;
        case 13:out[indexHex] = 'D';break;
        case 14:out[indexHex] = 'E';break;
        case 15:out[indexHex] = 'F';break;
        default:printf("\nWut : %d\n",sum);
      }
    }
    else
    {
      out[indexHex] = sum + '0';
    }
    sum = 0;
    indexHex--;
  }
  out[4] = '\0';
  printf("%s\n",out);
}


int main(void) {
  int number1,number2,negative;
  int binary1[16],binary2[16],binarySumResult[16];
  char output[5];
  scanf("%d",&number1);
  if(number1 < 0)
  {
    negative = 0;
  }
  else
  {
    negative = 1;
  }
  getBinary16B(binary1,number1,negative);
  scanf("%d",&number2);
  if(number2 < 0)
  {
    negative = 0;
  }
  else
  {
    negative = 1;
  }
  getBinary16B(binary2,number2,negative);
  /*printBinary16B(binary1);
  printBinary16B(binary2);*/
  convertBinaryToHex16B(binary1,output);
  convertBinaryToHex16B(binary2,output);
  sumOperation16B(binary1, binary2, binarySumResult);
  printf("Binarni soucet je: ");convertBinaryToHex16B(binarySumResult, output);
  if(number2 > 0)
  {
    getBinary16B(binary2, number2 - number2*2, 0);
  }
  else
  {
    getBinary16B(binary2,number2 -number2*2,1);
  }
   
  sumOperation16B(binary1, binary2, binarySumResult);
  printf("Binarni rozdil je: ");convertBinaryToHex16B(binarySumResult, output);
  return 0;
}