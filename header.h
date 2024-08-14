void port_intialization (void);
void delay1(char);





void port_intialization (void){
  volatile char *dirf,*dirk,*dira,*dirc,*dirl,*dirb;
  dirf=0x30;dirk=0x107;dira=0x21;dirc=0x27,dirl=0x10a,dirb=0x24;
  *dirf=0xff,*dirk=0xff;*dira=0xff;*dirc=0xff,*dirl=0x00,*dirb=0x0f;
}
void delay1(char num){
  volatile long i;
  while(num){
    for(i=0;i<50000;i++);
    num--;
  }
}

  
