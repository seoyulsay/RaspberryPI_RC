#include "Yul_LCD.h"

int LCDAddr = 0x3f;
int BLEN = 1;
int fd;

void write_word(int data){
    int temp = data;
    if ( BLEN == 1 )
        temp |= 0x08;
    else
        temp &= 0xF7;
    wiringPiI2CWrite(fd, temp);
}

void send_command(int comm){
    int buf;
    // Send bit7-4 firstly
    buf = comm & 0xF0;
    buf |= 0x04;			// RS = 0, RW = 0, EN = 1
    write_word(buf);
    delay(2);
    buf &= 0xFB;			// Make EN = 0
    write_word(buf);

    // Send bit3-0 secondly
    buf = (comm & 0x0F) << 4;
    buf |= 0x04;			// RS = 0, RW = 0, EN = 1
    write_word(buf);
    delay(2);
    buf &= 0xFB;			// Make EN = 0
    write_word(buf);
}

void send_data(int data){
    int buf;
    // Send bit7-4 firstly
    buf = data & 0xF0;
    buf |= 0x05;			// RS = 1, RW = 0, EN = 1
    write_word(buf);
    delay(2);
    buf &= 0xFB;			// Make EN = 0
    write_word(buf);

    // Send bit3-0 secondly
    buf = (data & 0x0F) << 4;
    buf |= 0x05;			// RS = 1, RW = 0, EN = 1
    write_word(buf);
    delay(2);
    buf &= 0xFB;			// Make EN = 0
    write_word(buf);
}

void init(){
    send_command(0x33);	// Must initialize to 8-line mode at first
    delay(5);
    send_command(0x32);	// Then initialize to 4-line mode
    delay(5);
    send_command(0x28);	// 2 Lines & 5*7 dots
    delay(5);
    send_command(0x0C);	// Enable display without cursor
    delay(5);
    send_command(0x01);	// Clear Screen
    wiringPiI2CWrite(fd, 0x08);
}

void clear(){
    send_command(0x01);	//clear Screen
}

void writeL(int x, int y, char data[]){
    int addr, i;
    int tmp;
    if (x < 0)  x = 0;
    if (x > 15) x = 15;
    if (y < 0)  y = 0;
    if (y > 1)  y = 1;

    // Move cursor
    addr = 0x80 + 0x40 * y + x;
    send_command(addr);

    tmp = strlen(data);
    for (i = 0; i < tmp; i++){
        send_data(data[i]);
    }
}

char * checkServed(int flag){
    char check[5];
    char reserved[16]="Reserved: ";
    char * preserved = reserved;
    int num=flag; 
    if(num==1){
        strcpy(check," On");
        printf("check: %s\n", check);
    }
    else if(num==2){
        strcpy(check,"Off");
        printf("check: %s\n", check);
    }
    else{
        strcpy(check,"error");
    }
    strcat(preserved, check);
    printf("return: %s\n",preserved);
    return preserved;
}

int lcdOn_nowstat(int num){
    fd = wiringPiI2CSetup(LCDAddr);
    init();

    time_t current_time;
    time(&current_time);

    int here=num;//on 1 off 2
    char state[15];
    char * pstate = state;

    strcat(state,checkServed(here));
    printf("state: %s\n", state);
    writeL(0, 0, ctime(&(current_time)));
    writeL(0, 1, pstate);
    delay(1000);

    // clear();
    return 1;
}
int lcdOn_feedstat(int num){

return 1;
}
