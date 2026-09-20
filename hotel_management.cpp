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
} NODE;

typedef struct LIST {
    NODE *phead;
    NODE *ptail;
} LIST;

void khoitao(LIST *L) {
    L->phead = NULL;
    L->ptail = NULL;
}

// STRUCT CHO CAY NHI PHAN (MA PHONG)
typedef struct NodeMa {
    char maPhong[10];
    struct ROOM *thongTin;      
    struct NodeMa *left, *right;
} NodeMa;

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
//TRUNG MA  
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
//2.THEM PHAN TU MOI
void themCuoi(LIST *L, struct ROOM x) {
    NODE *p = getnode(x);
    if (p == NULL) return;

    if (L->phead == NULL) {
        L->phead = L->ptail = p;
    } else {
        L->ptail->pnext = p;
        L->ptail = p;
    }
}
//NHAP THONG TIN PHONG
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
//1.NHAP DANH SACH
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
//3.HIEN THI DANH SACH
void output(LIST *L) {
    NODE *p = L->phead;

    if (p == NULL) {
        printf("\nDanh sach rong!\n");
        return;
    }

    printf("\n");
    printf("================================================================================\n");
    printf("%-10s %-25s %-15s %-15s %-12s\n",
           "Ma phong", "Ten phong", "Loai phong", "Gia phong", "Trang thai");
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
//TREE==============================================================
NodeMa* insertNodeMa(NodeMa *root, struct ROOM *room) {
    if (root == NULL) {
        NodeMa *newNode = (NodeMa *)malloc(sizeof(NodeMa));
        strcpy(newNode->maPhong, room->maPhong);
        newNode->thongTin = room;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    int cmp = strcmp(room->maPhong, root->maPhong);
    if (cmp < 0) {
        root->left = insertNodeMa(root->left, room);
    } else if (cmp > 0) {
        root->right = insertNodeMa(root->right, room);
    }
    return root;
}
NodeMa* buildTreeMa(LIST *L) {
    NodeMa *root = NULL;
    NODE *p = L->phead;
    while (p != NULL) {
        root = insertNodeMa(root, &(p->data));
        p = p->pnext;
    }
    return root;
}
NodeMa* searchTheoMaBST(NodeMa *root, const char *maCanTim) {
    if (root == NULL) {
        return NULL; 
    }
    
    int cmp = strcmp(maCanTim, root->maPhong);
    if (cmp == 0) {
        return root; 
    } else if (cmp < 0) {
        return searchTheoMaBST(root->left, maCanTim); 
    } else {
        return searchTheoMaBST(root->right, maCanTim); 
    }
}
void freeTreeMa(NodeMa *root) {
    if (root != NULL) {
        freeTreeMa(root->left);
        freeTreeMa(root->right);
        free(root);
    }
}

// ===================================================================
//4.TIM KIEM PHAN TU
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
            printf("Trang thai: %s\n", p->data.trangThai == 0 ? "Trong" : "Da thue");
            return;
        }
        p = p->pnext;
    }
    printf("Khong tim thay phong!\n");
}

void timTheoMaBST(LIST *L){
	char ma[10];
	printf("Nhap ma phong can tim (BST): ");
    scanf("%9s", ma);
            
    NodeMa *rootMa = buildTreeMa(L);
    NodeMa *resultMa = searchTheoMaBST(rootMa, ma);
            
    if (resultMa != NULL) {
        printf("\nTim thay phong (BST):\n");
        printf("Ma phong: %s\n", resultMa->thongTin->maPhong);
        printf("Ten phong: %s\n", resultMa->thongTin->tenPhong);
        printf("Loai phong: %s\n", resultMa->thongTin->loaiPhong);
        printf("Gia phong: %.0f\n", resultMa->thongTin->giaPhong);
    	printf("Trang thai: %s\n", resultMa->thongTin->trangThai == 0 ? "Trong" : "Da thue");
    } else {
        printf("Khong tim thay ma phong nay tren cay nhi phan!\n");
    }
    freeTreeMa(rootMa);
}
void timKiem(LIST *L) {
    int choice;

    printf("\n========== TIM KIEM ==========\n");
    printf("1. Tim theo ma phong (Danh sach lien ket)\n");
    printf("2. Tim theo ma phong (Cay nhi phan - BST)\n");
    printf("0. Quay lai\n");
    printf("Nhap lua chon: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            timTheoMa(L);
            break;

        case 2:
            timTheoMaBST(L);
            break;

        case 0:
            break;

        default:
            printf("Lua chon khong hop le!\n");
    }
}
//5.XOA PHAN TU===========================================================================
void xoaTheoMa(LIST *L) {
	
	if (L->phead == NULL) {
        printf("\nDanh sach hien dang rong! Khong co phong nao de xoa.\n");
        return;
    }
    
    char ma[10];
    printf("Nhap ma phong can xoa: ");
    scanf("%9s", ma);
    
    while (getchar() != '\n');

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
void xoaPhong(LIST *L) {
    int choice;
    do {
        printf("\n========== XOA PHONG ==========\n");
        printf("1. Xoa theo ma phong\n");
        printf("0. Quay lai Menu chinh\n");
        printf("Nhap lua chon: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                xoaTheoMa(L);
                break;

            case 0:
                printf("Dang quay lai...\n");
                break;

            default:
                printf("Lua chon khong hop le! Vui long nhap lai.\n");
        }
    } while (choice != 0);
}
//=================================================================================
//6.CAP NHAT THONG TIN
void capNhat(LIST *L) {
    char ma[10];
    printf("Nhap ma phong can cap nhat: ");
    scanf("%9s", ma);

    NODE *p = L->phead;
    while (p != NULL) {
        if (strcmp(p->data.maPhong, ma) == 0) {
            getchar();
            printf("Nhap ten phong moi: ");
            fgets(p->data.tenPhong, sizeof(p->data.tenPhong), stdin);
            p->data.tenPhong[strcspn(p->data.tenPhong, "\n")] = '\0';

            printf("Nhap loai phong moi: ");
            fgets(p->data.loaiPhong, sizeof(p->data.loaiPhong), stdin);
            p->data.loaiPhong[strcspn(p->data.loaiPhong, "\n")] = '\0';

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
            } while (p->data.trangThai != 0 && p->data.trangThai != 1);

            printf("Cap nhat thanh cong!\n");
            return;
        }
        p = p->pnext;
    }
    printf("Khong tim thay phong!\n");
}
//HOAN DOI
void hoanDoi(struct ROOM *a, struct ROOM *b) {
    struct ROOM temp = *a;
    *a = *b;
    *b = temp;
}
//7.SAP XEP========================================================================
void sapXepMa(LIST *L, int tangDan) {
    NODE *p, *q;
    for (p = L->phead; p != NULL; p = p->pnext) {
        for (q = p->pnext; q != NULL; q = q->pnext) {
            int dieuKien;
            if (tangDan) {
                dieuKien = strcmp(p->data.maPhong, q->data.maPhong) > 0;
            } else {
                dieuKien = strcmp(p->data.maPhong, q->data.maPhong) < 0;
            }
            if (dieuKien) {
                hoanDoi(&p->data, &q->data);
            }
        }
    }
    printf("Sap xep theo ma thanh cong!\n");
}

void sapXepGia(LIST *L, int tangDan) {
    NODE *p, *q;
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
    int choice, tangDan;

    printf("\n========== SAP XEP ==========\n");
    printf("1. Theo ma phong\n");
    printf("2. Theo gia phong\n");
    printf("0. Quay lai\n");
    printf("Nhap lua chon: ");
    scanf("%d", &choice);

    if (choice == 0) return;

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
            sapXepGia(L, tangDan == 1);
            break;
        default:
            printf("Lua chon khong hop le!\n");
    }
}
//===================================================================
//8.GHI/DOC FILE=====================================================
void ghiFile(LIST *L) {
    FILE *f = fopen("hotel.txt", "w");
    if (f == NULL) {
        printf("Khong the mo file!\n");
        return;
    }
    NODE *p = L->phead;
    while (p != NULL) {
        fprintf(f, "%s|%s|%s|%.0f|%d\n",
                p->data.maPhong,
                p->data.tenPhong,
                p->data.loaiPhong,
                p->data.giaPhong,
                p->data.trangThai);
        p = p->pnext;
    }
    fclose(f);
    printf("Da ghi danh sach vao file hotel.txt!\n");
}

void docFile(LIST *L) {
    FILE *f = fopen("hotel.txt", "r");
    if (f == NULL) {
        printf("Khong tim thay file hotel.txt!\n");
        return;
    }
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
//================================================================================
//GIAI PHONG
void giaiPhong(LIST *L) {
    NODE *p;
    while (L->phead != NULL) {
        p = L->phead;
        L->phead = L->phead->pnext;
        free(p);
    }
    L->ptail = NULL;
}
//STACK - QUEUE
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
//============================================================
//THONG KE DU LIEU
// 12. THONG KE DU LIEU
void thongKe(LIST *L) {
    if (L->phead == NULL) {
        printf("\nDanh sach phong dang rong!\n");
        return;
    }

    NODE *p = L->phead;

    int tongPhong = 0;
    int phongTrong = 0;
    int phongDaThue = 0;
    float tongGia = 0;
    float giaCaoNhat = p->data.giaPhong;
    float giaThapNhat = p->data.giaPhong;

    while (p != NULL) {
        tongPhong++;
        tongGia += p->data.giaPhong;

        if (p->data.trangThai == 0)
            phongTrong++;
        else
            phongDaThue++;

        if (p->data.giaPhong > giaCaoNhat)
            giaCaoNhat = p->data.giaPhong;

        if (p->data.giaPhong < giaThapNhat)
            giaThapNhat = p->data.giaPhong;

        p = p->pnext;
    }

    float giaTrungBinh = tongGia / tongPhong;

    printf("\n========== THONG KE DU LIEU ==========\n");
    printf("Tong so phong       : %d\n", tongPhong);
    printf("So phong trong      : %d\n", phongTrong);
    printf("So phong da thue    : %d\n", phongDaThue);
    printf("Gia phong trung binh: %.0f\n", giaTrungBinh);
    printf("Gia phong cao nhat  : %.0f\n", giaCaoNhat);
    printf("Gia phong thap nhat : %.0f\n", giaThapNhat);
    printf("======================================\n");
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
    printf("12. Thong ke du lieu\n");
    printf("0. Thoat\n");
    printf("============================================\n");
    printf("Nhap lua chon: ");
}

int main() {
    LIST L;
    STACKNODE *UndoStack = NULL;
    STACKNODE *RedoStack = NULL;
    struct ROOM room;
    int choice;

    khoitao(&L);

    do {
        menu();
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); 
            choice = -1; 
        }

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
            case 12:
            	thongKe(&L);
            	break;
            case 0:
                printf("\nKet thuc chuong trinh!\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (choice != 0);
	free(UndoStack);
    free(RedoStack);
    giaiPhong(&L);
    return 0;
}
