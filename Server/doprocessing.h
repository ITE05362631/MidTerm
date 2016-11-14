#ifndef _DO_PROCESSING_H
#define _DO_PROCESSING_H

void getTheGuessNum();
//將client傳來的字節轉換成數字，存在answer中
void messageToAnswer();
//檢查是否猜測成功
int isSuccess();
//生成猜測結果，將結果存在result中
void getResult();
//執行猜數字程式
void deprocessing(int sock);

#endif