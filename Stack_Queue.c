#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct ROOM {
    char maPhong[10];
    char tenPhong[30];
    char loaiPhong[20];
    float giaPhong;
    int trangThai;
};

typedef struct NODE {
    struct ROOM data;
    struct NODE *pnext;
}NODE;

typedef struct LIST {
    NODE *phead;
    NODE *ptail;
}LIST;

typedef struct STACKNODE {
    struct LIST data;
    struct STACKNODE *next;
}STACKNODE;

typedef struct Request {
    int rq;
    struct ROOM room;

} Request;

typedef struct QueueNode {
    Request rq;
    struct QueueNode *next;

} QueueNode;



void khoitao(LIST *L) {
    L->phead = NULL;
    L->ptail = NULL;
}

NODE *getnode(struct ROOM x) {
    NODE *p = (NODE *)malloc(sizeof(NODE));

    if (p == NULL) {
        printf("Khong du bo nho de cap phat!\n");
        return NULL;
    }

    p->data = x;
    p->pnext = NULL;

    return p;
}

int trungMa(LIST *L, char ma[]) {
    NODE *p = L->phead;

    while (p != NULL) {
        if (strcmp(p->data.maPhong, ma) == 0) {
            return 1;
        }
        p = p->pnext;
    }

    return 0;
}

void themCuoi(LIST *L, struct ROOM x) {
    NODE *p = getnode(x);

    if (p == NULL) {
        return;
    }

    if (L->phead == NULL) {
        L->phead = L->ptail = p;
    } else {
        L->ptail->pnext = p;
        L->ptail = p;
    }
}

void nhapPhong(struct ROOM *room, LIST *L) {
    do {
        printf("Nhap ma phong: ");
        scanf("%9s", room->maPhong);

        if (trungMa(L, room->maPhong)) {
            printf("Ma phong da ton tai! Vui long nhap lai.\n");
        }

    } while (trungMa(L, room->maPhong));

    getchar();

    printf("Nhap ten phong: ");
    fgets(room->tenPhong, sizeof(room->tenPhong), stdin);
    room->tenPhong[strcspn(room->tenPhong, "\n")] = '\0';

    printf("Nhap loai phong: ");
    fgets(room->loaiPhong, sizeof(room->loaiPhong), stdin);
    room->loaiPhong[strcspn(room->loaiPhong, "\n")] = '\0';

    do {
        printf("Nhap gia phong: ");
        scanf("%f", &room->giaPhong);

        if (room->giaPhong <= 0) {
            printf("Gia phong phai lon hon 0!\n");
        }

    } while (room->giaPhong <= 0);

    do {
        printf("Nhap trang thai (0: Trong, 1: Da thue): ");
        scanf("%d", &room->trangThai);

        if (room->trangThai != 0 && room->trangThai != 1) {
            printf("Trang thai khong hop le!\n");
        }

    } while (room->trangThai != 0 && room->trangThai != 1);
}

void input(LIST *L) {
    int n;
    struct ROOM room;

    khoitao(L);

    do {
        printf("Nhap so luong phong: ");
        scanf("%d", &n);

        if (n <= 0) {
            printf("So luong phong phai lon hon 0!\n");
        }

    } while (n <= 0);

    for (int i = 0; i < n; i++) {
        printf("\n========== PHONG %d ==========\n", i + 1);
        nhapPhong(&room, L);
        themCuoi(L, room);
    }

    printf("\nNhap danh sach thanh cong!\n");
}

void output(LIST *L) {
    NODE *p = L->phead;

    if (p == NULL) {
        printf("\nDanh sach rong!\n");
        return;
    }

    printf("\n");
    printf("================================================================================\n");
    printf("%-10s %-25s %-15s %-15s %-12s\n",
           "Ma phong", "Ten phong", "Loai phong",
           "Gia phong", "Trang thai");
    printf("================================================================================\n");

    while (p != NULL) {
        printf("%-10s %-25s %-15s %-15.0f %-12s\n",
               p->data.maPhong,
               p->data.tenPhong,
               p->data.loaiPhong,
               p->data.giaPhong,
               p->data.trangThai == 0 ? "Trong" : "Da thue");

        p = p->pnext;
    }

    printf("================================================================================\n");
}

void timTheoMa(LIST *L) {
    char ma[10];

    printf("Nhap ma phong can tim: ");
    scanf("%9s", ma);

    NODE *p = L->phead;

    while (p != NULL) {
        if (strcmp(p->data.maPhong, ma) == 0) {
            printf("\nTim thay phong:\n");
            printf("Ma phong: %s\n", p->data.maPhong);
            printf("Ten phong: %s\n", p->data.tenPhong);
            printf("Loai phong: %s\n", p->data.loaiPhong);
            printf("Gia phong: %.0f\n", p->data.giaPhong);
            printf("Trang thai: %s\n",
                   p->data.trangThai == 0 ? "Trong" : "Da thue");
            return;
        }

        p = p->pnext;
    }

    printf("Khong tim thay phong!\n");
}

void timTheoTen(LIST *L) {
    char ten[30];

    getchar();

    printf("Nhap ten phong can tim: ");
    fgets(ten, sizeof(ten), stdin);
    ten[strcspn(ten, "\n")] = '\0';

    NODE *p = L->phead;
    int found = 0;

    while (p != NULL) {
        if (strstr(p->data.tenPhong, ten) != NULL) {
            printf("\nMa: %s | Ten: %s | Loai: %s | Gia: %.0f | Trang thai: %s\n",
                   p->data.maPhong,
                   p->data.tenPhong,
                   p->data.loaiPhong,
                   p->data.giaPhong,
                   p->data.trangThai == 0 ? "Trong" : "Da thue");

            found = 1;
        }

        p = p->pnext;
    }

    if (!found) {
        printf("Khong tim thay phong!\n");
    }
}

void timTheoLoai(LIST *L) {
    char loai[20];

    getchar();

    printf("Nhap loai phong can tim: ");
    fgets(loai, sizeof(loai), stdin);
    loai[strcspn(loai, "\n")] = '\0';

    NODE *p = L->phead;
    int found = 0;

    while (p != NULL) {
        if (strcmp(p->data.loaiPhong, loai) == 0) {
            printf("\nMa: %s | Ten: %s | Gia: %.0f | Trang thai: %s\n",
                   p->data.maPhong,
                   p->data.tenPhong,
                   p->data.giaPhong,
                   p->data.trangThai == 0 ? "Trong" : "Da thue");

            found = 1;
        }

        p = p->pnext;
    }

    if (!found) {
        printf("Khong tim thay phong!\n");
    }
}

void timTheoKhoangGia(LIST *L) {
    float min, max;
    int found = 0;

    printf("Nhap gia thap nhat: ");
    scanf("%f", &min);

    printf("Nhap gia cao nhat: ");
    scanf("%f", &max);

    if (min > max) {
        printf("Khoang gia khong hop le!\n");
        return;
    }

    NODE *p = L->phead;

    while (p != NULL) {
        if (p->data.giaPhong >= min &&
            p->data.giaPhong <= max) {

            printf("\nMa: %s | Ten: %s | Loai: %s | Gia: %.0f | Trang thai: %s\n",
                   p->data.maPhong,
                   p->data.tenPhong,
                   p->data.loaiPhong,
                   p->data.giaPhong,
                   p->data.trangThai == 0 ? "Trong" : "Da thue");

            found = 1;
        }

        p = p->pnext;
    }

    if (!found) {
        printf("Khong co phong trong khoang gia nay!\n");
    }
}

void timKiem(LIST *L) {
    int choice;

    printf("\n========== TIM KIEM ==========\n");
    printf("1. Theo ma phong\n");
    printf("2. Theo ten phong\n");
    printf("3. Theo loai phong\n");
    printf("4. Theo khoang gia\n");
    printf("0. Quay lai\n");
    printf("Nhap lua chon: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            timTheoMa(L);
            break;

        case 2:
            timTheoTen(L);
            break;

        case 3:
            timTheoLoai(L);
            break;

        case 4:
            timTheoKhoangGia(L);
            break;

        case 0:
            break;

        default:
            printf("Lua chon khong hop le!\n");
    }
}

void xoaTheoMa(LIST *L) {
    char ma[10];

    printf("Nhap ma phong can xoa: ");
    scanf("%9s", ma);

    NODE *p = L->phead;
    NODE *q = NULL;

    while (p != NULL) {
        if (strcmp(p->data.maPhong, ma) == 0) {

            if (q == NULL) {
                L->phead = p->pnext;
            } else {
                q->pnext = p->pnext;
            }

            if (p == L->ptail) {
                L->ptail = q;
            }

            free(p);

            printf("Xoa phong thanh cong!\n");
            return;
        }

        q = p;
        p = p->pnext;
    }

    printf("Khong tim thay ma phong!\n");
}

void xoaTheoTen(LIST *L) {
    char ten[30];

    getchar();

    printf("Nhap ten phong can xoa: ");
    fgets(ten, sizeof(ten), stdin);
    ten[strcspn(ten, "\n")] = '\0';

    NODE *p = L->phead;
    NODE *q = NULL;

    while (p != NULL) {
        if (strcmp(p->data.tenPhong, ten) == 0) {

            if (q == NULL) {
                L->phead = p->pnext;
            } else {
                q->pnext = p->pnext;
            }

            if (p == L->ptail) {
                L->ptail = q;
            }

            free(p);

            printf("Xoa phong thanh cong!\n");
            return;
        }

        q = p;
        p = p->pnext;
    }

    printf("Khong tim thay ten phong!\n");
}

void xoaPhong(LIST *L) {
    int choice;

    printf("\n========== XOA PHONG ==========\n");
    printf("1. Xoa theo ma\n");
    printf("2. Xoa theo ten\n");
    printf("0. Quay lai\n");
    printf("Nhap lua chon: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            xoaTheoMa(L);
            break;

        case 2:
            xoaTheoTen(L);
            break;

        case 0:
            break;

        default:
            printf("Lua chon khong hop le!\n");
    }
}

void capNhat(LIST *L) {
    char ma[10];

    printf("Nhap ma phong can cap nhat: ");
    scanf("%9s", ma);

    NODE *p = L->phead;

    while (p != NULL) {
        if (strcmp(p->data.maPhong, ma) == 0) {

            getchar();

            printf("Nhap ten phong moi: ");
            fgets(p->data.tenPhong,
                  sizeof(p->data.tenPhong), stdin);

            p->data.tenPhong[
                strcspn(p->data.tenPhong, "\n")
            ] = '\0';

            printf("Nhap loai phong moi: ");
            fgets(p->data.loaiPhong,
                  sizeof(p->data.loaiPhong), stdin);

            p->data.loaiPhong[
                strcspn(p->data.loaiPhong, "\n")
            ] = '\0';

            do {
                printf("Nhap gia phong moi: ");
                scanf("%f", &p->data.giaPhong);

                if (p->data.giaPhong <= 0) {
                    printf("Gia phong phai lon hon 0!\n");
                }

            } while (p->data.giaPhong <= 0);

            do {
                printf("Nhap trang thai moi (0: Trong, 1: Da thue): ");
                scanf("%d", &p->data.trangThai);

            } while (p->data.trangThai != 0 &&
                     p->data.trangThai != 1);

            printf("Cap nhat thanh cong!\n");
            return;
        }

        p = p->pnext;
    }

    printf("Khong tim thay phong!\n");
}

void hoanDoi(struct ROOM *a, struct ROOM *b) {
    struct ROOM temp = *a;
    *a = *b;
    *b = temp;
}

void sapXepMa(LIST *L, int tangDan) {
    NODE *p;
    NODE *q;

    for (p = L->phead; p != NULL; p = p->pnext) {
        for (q = p->pnext; q != NULL; q = q->pnext) {

            int dieuKien;

            if (tangDan) {
                dieuKien = strcmp(p->data.maPhong,
                                   q->data.maPhong) > 0;
            } else {
                dieuKien = strcmp(p->data.maPhong,
                                   q->data.maPhong) < 0;
            }

            if (dieuKien) {
                hoanDoi(&p->data, &q->data);
            }
        }
    }

    printf("Sap xep theo ma thanh cong!\n");
}

void sapXepTen(LIST *L, int tangDan) {
    NODE *p;
    NODE *q;

    for (p = L->phead; p != NULL; p = p->pnext) {
        for (q = p->pnext; q != NULL; q = q->pnext) {

            int dieuKien;

            if (tangDan) {
                dieuKien = strcmp(p->data.tenPhong,
                                   q->data.tenPhong) > 0;
            } else {
                dieuKien = strcmp(p->data.tenPhong,
                                   q->data.tenPhong) < 0;
            }

            if (dieuKien) {
                hoanDoi(&p->data, &q->data);
            }
        }
    }

    printf("Sap xep theo ten thanh cong!\n");
}

void sapXepGia(LIST *L, int tangDan) {
    NODE *p;
    NODE *q;

    for (p = L->phead; p != NULL; p = p->pnext) {
        for (q = p->pnext; q != NULL; q = q->pnext) {

            if ((tangDan && p->data.giaPhong > q->data.giaPhong) ||
                (!tangDan && p->data.giaPhong < q->data.giaPhong)) {

                hoanDoi(&p->data, &q->data);
            }
        }
    }

    printf("Sap xep theo gia thanh cong!\n");
}

void sapXep(LIST *L) {
    int choice;
    int tangDan;

    printf("\n========== SAP XEP ==========\n");
    printf("1. Theo ma\n");
    printf("2. Theo ten\n");
    printf("3. Theo gia\n");
    printf("0. Quay lai\n");
    printf("Nhap lua chon: ");
    scanf("%d", &choice);

    if (choice == 0) {
        return;
    }

    printf("1. Tang dan\n");
    printf("2. Giam dan\n");
    printf("Nhap lua chon: ");
    scanf("%d", &tangDan);

    if (tangDan != 1 && tangDan != 2) {
        printf("Lua chon khong hop le!\n");
        return;
    }

    switch (choice) {
        case 1:
            sapXepMa(L, tangDan == 1);
            break;

        case 2:
            sapXepTen(L, tangDan == 1);
            break;

        case 3:
            sapXepGia(L, tangDan == 1);
            break;

        default:
            printf("Lua chon khong hop le!\n");
    }
}

void ghiFile(LIST *L) {
    FILE *f = fopen("hotel_output.txt", "w");

    if (f == NULL) {
        printf("Khong the mo file!\n");
        return;
    }

    NODE *p = L->phead;

    while (p != NULL) {   
        fprintf(f, "|%s|%s|%s|%.0f|%s|\n",
                p->data.maPhong,
                p->data.tenPhong,
                p->data.loaiPhong,
                p->data.giaPhong,
                p->data.trangThai == 0 ? "Trong" : "Da thue");

        p = p->pnext;
    }

    fclose(f);

    printf("Da ghi danh sach vao file hotel_output.txt!\n");
}

void docFile(LIST *L) {
    FILE *f = fopen("hotel_input.txt", "r");

    if (f == NULL) {
        printf("Khong tim thay file hotel_input.txt!\n");
        return;
    }

    khoitao(L);

    struct ROOM room;

    while (fscanf(f, "%9[^|]|%29[^|]|%19[^|]|%f|%d\n",
                  room.maPhong,
                  room.tenPhong,
                  room.loaiPhong,
                  &room.giaPhong,
                  &room.trangThai) == 5) {

        themCuoi(L, room);
    }

    fclose(f);

    printf("Da doc du lieu tu file hotel.txt!\n");
}

void giaiPhong(LIST *L) {
    NODE *p;

    while (L->phead != NULL) {
        p = L->phead;
        L->phead = L->phead->pnext;
        free(p);
    }

    L->ptail = NULL;
}

void menu() {
    printf("\n");
    printf("============================================\n");
    printf("       HE THONG QUAN LY KHACH SAN\n");
    printf("============================================\n");
    printf("1. Nhap danh sach phong\n");
    printf("2. Them phong moi\n");
    printf("3. Hien thi danh sach phong\n");
    printf("4. Tim kiem phong\n");
    printf("5. Xoa phong\n");
    printf("6. Cap nhat thong tin phong\n");
    printf("7. Sap xep danh sach\n");
    printf("8. Ghi danh sach ra file\n");
    printf("9. Doc danh sach tu file\n");
    printf("10. Undo\n");
    printf("11. Redo\n");
    printf("0. Thoat\n");
    printf("============================================\n");
    printf("Nhap lua chon: ");
}

LIST clone(LIST *L){
    LIST copy;
    khoitao(&copy);
    NODE *p = L->phead;
    while (p != NULL) {
        themCuoi(&copy, p->data);
        p = p->pnext;
    }
    return copy;
}

void push(STACKNODE **top, LIST *L) {
    STACKNODE *newNode = (STACKNODE *)malloc(sizeof(STACKNODE));
    if (newNode == NULL) {
        printf("Khong du bo nho de cap phat!\n");
        return;
    } 
    newNode->data = clone(L);
    newNode->next = *top;
    *top = newNode;
}

void pop(STACKNODE **top, LIST *L){
    STACKNODE *temp = *top;
    if (*top==NULL) {
        printf("Stack rong!\n");
        return;
    }
    *top = (*top)->next;
    giaiPhong(L);
    *L = temp->data;
    free(temp);
}
void clearStack(STACKNODE **top) {
    while (*top != NULL) {
        STACKNODE *temp = *top;
        *top = (*top)->next;
        giaiPhong(&temp->data); 
        free(temp);            
    }
}
int main() {
    STACKNODE *UndoStack = NULL;
    STACKNODE *RedoStack = NULL;
    LIST L;
    struct ROOM room;
    int choice;


    khoitao(&L);

    do {
        menu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                input(&L);
                break;

            case 2:
                push(&UndoStack, &L);
                clearStack(&RedoStack);
                printf("\n========== THEM PHONG ==========\n");
                nhapPhong(&room, &L);
                themCuoi(&L, room);
                printf("Them phong thanh cong!\n");
                
                break;
            case 3:
                output(&L);
                break;

            case 4:
                timKiem(&L);
                break;

            case 5:
                push(&UndoStack, &L);
                clearStack(&RedoStack);
                xoaPhong(&L);
                break;

            case 6:
                push(&UndoStack, &L);
                clearStack(&RedoStack);
                capNhat(&L);
                
                break;
            case 7:
                push(&UndoStack, &L);
                clearStack(&RedoStack);
                sapXep(&L);
                
                break;

            case 8:
                ghiFile(&L);
                break;

            case 9:
                docFile(&L);
                break;

            case 10:
                if (UndoStack != NULL) {
                    push(&RedoStack, &L);
                    pop(&UndoStack, &L);
                    printf("Hoan tac thanh cong!\n");
                } else {
                    printf("Khong co thao tac de hoan tac!\n");
                }
                break;
            case 11:
                if (RedoStack != NULL) {
                    push(&UndoStack, &L);
                    pop(&RedoStack, &L);
                    printf("Lam lai thanh cong!\n");
                } else {
                    printf("Khong co thao tac de lam lai!\n");
                }
                break;
                
            case 0:
                printf("\nKet thuc chuong trinh!\n");
                break;

            default:
                printf("Lua chon khong hop le!\n");  
        }
        if(choice!=0){
            printf("\nNhan Enter de tiep tuc...");
            getchar(); 
            getchar(); 
            system("cls"); 
        }
    } while (choice != 0);
    free(UndoStack);
    free(RedoStack);
    giaiPhong(&L);
    return 0;
}