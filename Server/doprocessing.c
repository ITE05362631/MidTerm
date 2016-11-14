#include <stdio.h>
#include <string.h>

#define TRUE 1

int guess_num[4] = {0,0,0,0};  //存儲生成的隨機數字
int answer[4] = {0,0,0,0};  //client傳來的所猜答案
int recv_message[4] = {-1,-1,-1,-1}; //client傳來的前四個字節
int result[2] = {0,0};  //存儲猜測結果中的數字

//生成隨機四位數，存在guess_num中
void getTheGuessNum()  
{  
    int i,j;  
    int flag = 0;         
    srand(time(NULL));  
    for (i = 0;i < 4;)  
    {  
        guess_num[i] = rand() % 10; 
        for (j = 0;j < i;j ++)  
        {  
            if (guess_num[j] == guess_num[i])     
            {  
                flag = 1;  
                break;  
            }  
            flag = 0;  
        }  
        if (flag == 0)    
        {  
            i++;  
        }  
    }  
} 

//將client傳來的字節轉換成數字，存在answer中
void messageToAnswer(){
    answer[0] = (char)recv_message[0]-'0';
    answer[1] = (char)recv_message[1]-'0';
    answer[2] = (char)recv_message[2]-'0';
    answer[3] = (char)recv_message[3]-'0';
}

//檢查是否猜測成功
int isSuccess(){
    int flag = 0;
    if(result[0] == 4){
        flag = 1;
    } 
    return flag;
}

//生成猜測結果，將結果存在result中
void getResult(){
    int i;
    int j;
    result[0] = 0;
    result[1] = 0;
    for(i = 0;i<4;i++){
        if(answer[i] == guess_num[i]){
            result[0]++;
            continue;
        }
        for(j = 0;j<4;j++){
            if(answer[i] == guess_num[j]){
                result[1] ++;
                break;
            }
        }
    }
}

void doprocessing(int new_socket){
    int i;
    char *reply_message;
    char recv_message2[4];
    puts("Connection accepted");
    getTheGuessNum();
    while (TRUE)
    {   
        if (recv(new_socket, recv_message2, 4, 0) < 0)
        {
            perror("recv error");
            break;
        }
        else
        {
            recv_message[0] = recv_message2[0];
            recv_message[1] = recv_message2[1];
            recv_message[2] = recv_message2[2];
            recv_message[3] = recv_message2[3];
            messageToAnswer();
            getResult();
            if(isSuccess())
            {
                reply_message = "success";
                write(new_socket,reply_message,strlen(reply_message));
                break;
            }
            else{
                reply_message = (char *)malloc(sizeof(char)*4);
                sprintf(reply_message,"%dA%dB",result[0],result[1]);
                write(new_socket,reply_message,4);
                free(reply_message);
            }
        }
    }
}