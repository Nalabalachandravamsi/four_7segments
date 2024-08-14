#include "header.h"
void setup() {
    // Initialize the output and input pointers
    volatile char *outf, *outk, *outa, *outc, *inl, *outb, x,first_number,second_number;
    volatile char row, coloum, count = 0,result;
    volatile long i,index;
    outf = (volatile char*)0x31; outk = (volatile char*)0x108; outa = (volatile char*)0x22; outc = (volatile char*)0x28; inl = (volatile char*)0x109; outb = (volatile char*)0x25;
    volatile char numbers[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x67};
    volatile unsigned char digit[] = {0x06, 0x66, 0x07, 0x5b, 0x6d, 0x7f, 0x3f, 0x4f, 0x7d, 0x67,0x70,0x40,0x76,0xd0}; // index: 0-2=coloum0, 3-6=coloum1, 7-9=coloum2, 10-13=coloum
    *outc = 0;
    *outa = 0;
    *outk = 0;
    *outf = 0;
    while (1) {
        for (row = 0; row < 4; row++) {
            *outb = 1 << row; // Select the row
            x = *inl; // Read the input
            if (x) {
                for (coloum = 0; coloum < 4; coloum++) {
                    if (x == 1 << coloum) {
                      for(i=0;i<200000;i++);           // debouncing time
                        // Assign values based on count
                        if (count == 0) {    // used to display first number
                            if (coloum == 0) *outa = digit[row];
                            if (coloum == 1) *outa = digit[3 + row];
                            if (coloum == 2) *outa = digit[7 + row];
                            for(index=0;index<10;index++){
                              if(numbers[index] == *outa){
                                first_number=index;
                              }
                            }
                        } else if (count == 1) {   // used to display arthmatic symbol
                            if (coloum == 0) *outk = digit[row];
                            if (coloum == 1) *outk = digit[3 + row];
                            if (coloum == 2) *outk = digit[7 + row];
                            if (coloum == 3) *outk = digit[10 + row];
                        } else if (count == 2) {      // used to display second number
                            if (coloum == 0) *outf = digit[row];
                            if (coloum == 1) *outf = digit[3 + row];
                            if (coloum == 2) *outf = digit[7 + row];
                            for(index=0;index<10;index++){
                              if(numbers[index] == *outf){
                                second_number=index;
                              }
                            }
                        }                         
                        // Increment count for the next press
                        count++;                       
                    }
                }
            }
            if(count>2){
              for(i=0;i<100000;i++);
              if(*outk == 0x70) result=first_number + second_number;
              if(*outk == 0x40) result=first_number - second_number;
              if(*outk == 0x76) result=first_number*second_number;
              if(*outk == (0xffffffd0)) result=first_number % second_number;
              if(result>9){
                *outf=numbers[result%10];
                *outk=numbers[result/10];
                *outa=0;
                *outc=0;
              }
              if(result<10){
                *outf=numbers[result];
                *outk=0;
                *outa=0;
                *outc=0;
              }
            }
        }
    }
}

void loop() {
    // The main code will run repeatedly here, but it is empty in this case
}
