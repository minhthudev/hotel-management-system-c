#include <stdio.h>
#include <stdlib.h>
//Menu
void showMenu() {
    printf("=====================================================\n");
    printf("|       HE THONG QUAN LY KHACH SAN (HOTEL CLI)      |\n");
    printf("=====================================================\n");
    printf("|  [1] Danh sach phong & Tinh trang                 |\n");
    printf("|  [2] Dat phong (Check-in)                         |\n");
    printf("|  [3] Tra phong & Tinh tien (Check-out)            |\n");
    printf("|  [4] Quan ly thong tin khach hang                 |\n");
    printf("|  [5] Bao cao doanh thu                            |\n");
    printf("|  [0] Thoat chuong trinh                           |\n");
    printf("=====================================================\n");
    printf("Nhap lua chon cua ban: ");
}
void printRoomList() {
    system("cls");
    printf("---------------- DANH SACH PHONG --------------------\n");

    printf("Nhan Enter de quay lai Menu...");
    getchar();getchar();
}
//Data
typedef struct {
    char IdKH[50];
    
}KhachHang;
typedef struct{
    char RoomId[50];
}Room;
//Node
typedef struct Node {
    void *data;
    struct Node *next;
    struct Node *prev;
} Node;

Node* CreateNode(void* NewData){
    Node* tmp=(Node*)malloc(sizeof(Node));  
    tmp->data = NewData;
    tmp->next = NULL;
    tmp->prev = NULL;
    return tmp;
}
void AddHead(Node** list, void* NewData){
    Node* tmp = CreateNode(NewData);
    if(*list==NULL){
        *list = tmp;
    }
    else {
        tmp->next=*list;
        (*list)->prev=tmp;
        *list = tmp;
        
    }
}
void AddTail(Node **list,void* NewData){
    Node* tmp = CreateNode(NewData);
    if (*list  == NULL) {
        (*list) = tmp;
    }
    else{
        Node* tail = *list;
        while (tail->next!=NULL) tail=tail->next;
        tail->next=tmp;
        tmp->prev=tail;
    }
}

int main(){
    Node* FirstRoom = NULL;
    Node* FirstKH = NULL;
    int choice;
    while (1) {
        system("cls");
        showMenu();
        if(scanf("%d",&choice)!=1){
            printf("\nLua chon khong hop le! Nhan Enter de thu lai...");
            continue;
        }
        
        switch(choice){
            case 1://Dang Ky Phong

            break;
            case 2://Check out

            break;
            case 4://Cap Nhat Thong Tin Phong
            break;
            case 5://Cap Nhat Thong Tin Khach Hang
            break;
            case 6://Xem DanhSach KH
            break;
            case 7: //Xem DanhSach Phong
            break;
            case 8: //Sap xep thong tin phong
            case 9: //Sap xep thong tin khach hang
            case 10:// Nhap DL tu file
            case 11://Xuat DL ra file
            case 12://Thong ke Du Lieu
            case 13:// Xem lich su thao tac
            case 0://Ket thuc chuong trinh va xuat file
            printf("\nKet thuc chuong trinh!\n");
            return 0;
            default:
                printf("Lua chon khong hop le. Nhan Enter de thu lai. ");
                getchar(); getchar();
        }

    }
}