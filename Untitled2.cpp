#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// =========================================================
// 1. KHAI BAO CAC STRUCT DU LIEU & DANH SACH LIEN KET
// =========================================================

// --- 1.1. PHONG ---
struct ROOM {
    char maPhong[10];
    char tenPhong[30];
    char loaiPhong[20];
    float giaPhong;
    int trangThai; // 0: Trong, 1: Da thue
};

typedef struct NODE {
    struct ROOM data;
    struct NODE *pnext;
} NODE;

typedef struct LIST {
    NODE *phead;
    NODE *ptail;
} LIST;

// --- 1.2. KHACH HANG ---
struct KhachHang {
    char maKH[10];
    char hoTen[50];
    char diaChi[100];
    char sdt[15];
};

typedef struct NODE_KH {
    struct KhachHang data;
    struct NODE_KH *pnext;
} NODE_KH;

typedef struct LIST_KH {
    NODE_KH *phead;
    NODE_KH *ptail;
} LIST_KH;

// --- 1.3. NHAN VIEN ---
struct NhanVien {
    char maNV[10];
    char hoTen[50];
    char chucVu[30];
    char sdt[15];
};

typedef struct NODE_NV {
    struct NhanVien data;
    struct NODE_NV *pnext;
} NODE_NV;

typedef struct LIST_NV {
    NODE_NV *phead;
    NODE_NV *ptail;
} LIST_NV;

// --- 1.4. DAT PHONG ---
struct DatPhong {
    char maDP[10];
    char maKH[10];
    char maNV[10];
    char ngayDat[15];
    float tongTien;
};

typedef struct NODE_DP {
    struct DatPhong data;
    struct NODE_DP *pnext;
} NODE_DP;

typedef struct LIST_DP {
    NODE_DP *phead;
    NODE_DP *ptail;
} LIST_DP;

// --- 1.5. CHI TIET DAT PHONG ---
struct ChiTietDatPhong {
    char maDP[10];
    char maPhong[10];
    int soNgayO;
    float donGia;
    float thanhTien;
};

typedef struct NODE_CTDP {
    struct ChiTietDatPhong data;
    struct NODE_CTDP *pnext;
} NODE_CTDP;

typedef struct LIST_CTDP {
    NODE_CTDP *phead;
    NODE_CTDP *ptail;
} LIST_CTDP;

// --- 1.6. LICH SU THAO TAC ---
struct LichSu {
    char thoiGian[10]; // VD: "10:20"
    char hanhDong[100]; // VD: "Them P001"
};

typedef struct NODE_LS {
    struct LichSu data;
    struct NODE_LS *pnext;
} NODE_LS;

typedef struct LIST_LS {
    NODE_LS *phead;
    NODE_LS *ptail;
} LIST_LS;

// --- 1.7. CAY NHI PHAN TIM KIEM (BST) CHO MA PHONG ---
typedef struct NodeMa {
    char maPhong[10];
    struct ROOM *thongTin;
    struct NodeMa *left, *right;
} NodeMa;

// --- 1.8. STACK (UNDO / REDO) & QUEUE ---
typedef struct STACKNODE {
    LIST data;
    struct STACKNODE *next;
} STACKNODE;

typedef struct QueueNode {
    int rq;
    struct QueueNode *next;
} QueueNode;

// =========================================================
// 2. CAC HAM TIEN ICH DUNG CHUNG (TOI UU NHAP XUAT)
// =========================================================

void xoaBoDem() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Ham nhap chuoi an toan va tu dong xoa ky tu xuong dong '\n'
void nhapChuoi(char *str, int size) {
    fgets(str, size, stdin);
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
        i++;
    }
}

// Lay gio he thong hien tai theo dinh dang HH:MM
void layGioHienTai(char *buffer) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    sprintf(buffer, "%02d:%02d", tm_info->tm_hour, tm_info->tm_min);
}

// =========================================================
// 3. KHOI TAO VA QUAN LY LICH SU THAO TAC (LINKED LIST)
// =========================================================

void khoiTaoPhong(LIST *L) { L->phead = L->ptail = NULL; }
void khoiTaoKH(LIST_KH *L) { L->phead = L->ptail = NULL; }
void khoiTaoNV(LIST_NV *L) { L->phead = L->ptail = NULL; }
void khoiTaoDP(LIST_DP *L) { L->phead = L->ptail = NULL; }
void khoiTaoCTDP(LIST_CTDP *L) { L->phead = L->ptail = NULL; }
void khoiTaoLS(LIST_LS *L) { L->phead = L->ptail = NULL; }

void ghiLichSu(LIST_LS *L, const char *tenThaoTac, const char *maDoiTuong) {
    NODE_LS *p = (NODE_LS *)malloc(sizeof(NODE_LS));
    if (p == NULL) return;

    layGioHienTai(p->data.thoiGian);
    if (maDoiTuong != NULL && maDoiTuong[0] != '\0') {
        sprintf(p->data.hanhDong, "%s %s", tenThaoTac, maDoiTuong);
    } else {
        sprintf(p->data.hanhDong, "%s", tenThaoTac);
    }
    p->pnext = NULL;

    if (L->phead == NULL) {
        L->phead = L->ptail = p;
    } else {
        L->ptail->pnext = p;
        L->ptail = p;
    }
}

void hienThiLichSu(LIST_LS *L) {
    if (L->phead == NULL) {
        printf("\nChua co lich su thao tac nao!\n");
        return;
    }
    printf("\n================ LICH SU THAO TAC ================\n");
    NODE_LS *p = L->phead;
    while (p != NULL) {
        printf("[%s] %s  ", p->data.thoiGian, p->data.hanhDong);
        p = p->pnext;
    }
    printf("\n==================================================\n");
}

// =========================================================
// 4. QUAN LY PHONG (LINKED LIST + BST + STACK)
// =========================================================

NODE *getnodePhong(struct ROOM x) {
    NODE *p = (NODE *)malloc(sizeof(NODE));
    if (p == NULL) {
        printf("Khong du bo nho!\n");
        return NULL;
    }
    p->data = x;
    p->pnext = NULL;
    return p;
}

void themCuoiPhong(LIST *L, struct ROOM x) {
    NODE *p = getnodePhong(x);
    if (p == NULL) return;
    if (L->phead == NULL) {
        L->phead = L->ptail = p;
    } else {
        L->ptail->pnext = p;
        L->ptail = p;
    }
}

NODE *timNodePhong(LIST *L, const char *ma) {
    NODE *p = L->phead;
    while (p != NULL) {
        if (strcmp(p->data.maPhong, ma) == 0) return p;
        p = p->pnext;
    }
    return NULL;
}

void giaiPhongListPhong(LIST *L) {
    NODE *p;
    while (L->phead != NULL) {
        p = L->phead;
        L->phead = L->phead->pnext;
        free(p);
    }
    L->ptail = NULL;
}

// --- STACK UNDO / REDO ---
LIST cloneListPhong(LIST *L) {
    LIST copy;
    khoiTaoPhong(&copy);
    NODE *p = L->phead;
    while (p != NULL) {
        themCuoiPhong(&copy, p->data);
        p = p->pnext;
    }
    return copy;
}

void push(STACKNODE **top, LIST *L) {
    STACKNODE *newNode = (STACKNODE *)malloc(sizeof(STACKNODE));
    if (newNode == NULL) return;
    newNode->data = cloneListPhong(L);
    newNode->next = *top;
    *top = newNode;
}

void pop(STACKNODE **top, LIST *L) {
    if (*top == NULL) return;
    STACKNODE *temp = *top;
    *top = (*top)->next;
    giaiPhongListPhong(L);
    *L = temp->data;
    free(temp);
}

void clearStack(STACKNODE **top) {
    while (*top != NULL) {
        STACKNODE *temp = *top;
        *top = (*top)->next;
        giaiPhongListPhong(&temp->data);
        free(temp);
    }
}

// --- NHAP & HIEN THI PHONG ---
void nhapMotPhong(struct ROOM *room, LIST *L) {
    do {
        printf("Nhap ma phong: ");
        scanf("%9s", room->maPhong);
        if (timNodePhong(L, room->maPhong) != NULL) {
            printf("Ma phong da ton tai! Vui long nhap lai.\n");
        }
    } while (timNodePhong(L, room->maPhong) != NULL);

    xoaBoDem();
    printf("Nhap ten phong: ");
    nhapChuoi(room->tenPhong, sizeof(room->tenPhong));

    printf("Nhap loai phong: ");
    nhapChuoi(room->loaiPhong, sizeof(room->loaiPhong));

    do {
        printf("Nhap gia phong (> 0): ");
        scanf("%f", &room->giaPhong);
    } while (room->giaPhong <= 0);

    do {
        printf("Nhap trang thai (0: Trong, 1: Da thue): ");
        scanf("%d", &room->trangThai);
    } while (room->trangThai != 0 && room->trangThai != 1);
}

void inputDanhSachPhong(LIST *L, LIST_LS *LS) {
    int n;
    struct ROOM room;
    giaiPhongListPhong(L);

    do {
        printf("Nhap so luong phong: ");
        scanf("%d", &n);
    } while (n <= 0);

    for (int i = 0; i < n; i++) {
        printf("\n--- Nhap phong thu %d ---\n", i + 1);
        nhapMotPhong(&room, L);
        themCuoiPhong(L, room);
        ghiLichSu(LS, "Them", room.maPhong);
    }
    printf("\nNhap danh sach thanh cong!\n");
}

void outputPhong(LIST *L) {
    NODE *p = L->phead;
    if (p == NULL) {
        printf("\nDanh sach phong rong!\n");
        return;
    }
    printf("\n================================================================================\n");
    printf("%-10s %-25s %-15s %-15s %-12s\n",
           "Ma phong", "Ten phong", "Loai phong", "Gia phong", "Trang thai");
    printf("================================================================================\n");
    while (p != NULL) {
        printf("%-10s %-25s %-15s %-15.0f %-12s\n",
               p->data.maPhong, p->data.tenPhong, p->data.loaiPhong,
               p->data.giaPhong, p->data.trangThai == 0 ? "Trong" : "Da thue");
        p = p->pnext;
    }
    printf("================================================================================\n");
}

// --- CAY NHI PHAN TIM KIEM (BST) ---
NodeMa *insertNodeMa(NodeMa *root, struct ROOM *room) {
    if (root == NULL) {
        NodeMa *newNode = (NodeMa *)malloc(sizeof(NodeMa));
        strcpy(newNode->maPhong, room->maPhong);
        newNode->thongTin = room;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    int cmp = strcmp(room->maPhong, root->maPhong);
    if (cmp < 0) root->left = insertNodeMa(root->left, room);
    else if (cmp > 0) root->right = insertNodeMa(root->right, room);
    return root;
}

NodeMa *searchBST(NodeMa *root, const char *ma) {
    if (root == NULL) return NULL;
    int cmp = strcmp(ma, root->maPhong);
    if (cmp == 0) return root;
    if (cmp < 0) return searchBST(root->left, ma);
    return searchBST(root->right, ma);
}

void freeTreeMa(NodeMa *root) {
    if (root != NULL) {
        freeTreeMa(root->left);
        freeTreeMa(root->right);
        free(root);
    }
}

void timKiemPhong(LIST *L) {
    int choice;
    char ma[10];
    printf("\n1. Tim tren Danh sach lien ket\n2. Tim tren Cay nhi phan (BST)\n0. Quay lai\nChon: ");
    scanf("%d", &choice);
    if (choice == 0) return;

    printf("Nhap ma phong can tim: ");
    scanf("%9s", ma);

    if (choice == 1) {
        NODE *p = timNodePhong(L, ma);
        if (p != NULL) {
            printf("Tim thay: %s | %s | %s | %.0f | %s\n",
                   p->data.maPhong, p->data.tenPhong, p->data.loaiPhong,
                   p->data.giaPhong, p->data.trangThai == 0 ? "Trong" : "Da thue");
        } else {
            printf("Khong tim thay phong!\n");
        }
    } else if (choice == 2) {
        NodeMa *root = NULL;
        for (NODE *p = L->phead; p != NULL; p = p->pnext) {
            root = insertNodeMa(root, &(p->data));
        }
        NodeMa *res = searchBST(root, ma);
        if (res != NULL) {
            printf("Tim thay (BST): %s | %s | %s | %.0f | %s\n",
                   res->thongTin->maPhong, res->thongTin->tenPhong, res->thongTin->loaiPhong,
                   res->thongTin->giaPhong, res->thongTin->trangThai == 0 ? "Trong" : "Da thue");
        } else {
            printf("Khong tim thay phong tren BST!\n");
        }
        freeTreeMa(root);
    }
}

// --- XOA, CAP NHAT, SAP XEP, THONG KE, FILE ---
void xoaPhong(LIST *L, STACKNODE **UndoStack, STACKNODE **RedoStack, LIST_LS *LS) {
    if (L->phead == NULL) {
        printf("\nDanh sach rong!\n");
        return;
    }
    char ma[10];
    printf("Nhap ma phong can xoa: ");
    scanf("%9s", ma);

    NODE *p = L->phead, *q = NULL;
    while (p != NULL) {
        if (strcmp(p->data.maPhong, ma) == 0) {
            push(UndoStack, L);
            clearStack(RedoStack);

            if (q == NULL) L->phead = p->pnext;
            else q->pnext = p->pnext;
            if (p == L->ptail) L->ptail = q;

            ghiLichSu(LS, "Xoa", ma);
            free(p);
            printf("Xoa phong %s thanh cong!\n", ma);
            return;
        }
        q = p;
        p = p->pnext;
    }
    printf("Khong tim thay ma phong!\n");
}

void capNhatPhong(LIST *L, STACKNODE **UndoStack, STACKNODE **RedoStack, LIST_LS *LS) {
    char ma[10];
    printf("Nhap ma phong can cap nhat: ");
    scanf("%9s", ma);

    NODE *p = timNodePhong(L, ma);
    if (p == NULL) {
        printf("Khong tim thay phong!\n");
        return;
    }

    push(UndoStack, L);
    clearStack(RedoStack);

    xoaBoDem();
    printf("Nhap ten phong moi: ");
    nhapChuoi(p->data.tenPhong, sizeof(p->data.tenPhong));

    printf("Nhap loai phong moi: ");
    nhapChuoi(p->data.loaiPhong, sizeof(p->data.loaiPhong));

    do {
        printf("Nhap gia phong moi (> 0): ");
        scanf("%f", &p->data.giaPhong);
    } while (p->data.giaPhong <= 0);

    do {
        printf("Nhap trang thai moi (0: Trong, 1: Da thue): ");
        scanf("%d", &p->data.trangThai);
    } while (p->data.trangThai != 0 && p->data.trangThai != 1);

    ghiLichSu(LS, "Cap nhat", ma);
    printf("Cap nhat thanh cong!\n");
}

void sapXepPhong(LIST *L, STACKNODE **UndoStack, STACKNODE **RedoStack, LIST_LS *LS) {
    int choice, tangDan;
    printf("\n1. Sap xep theo Ma phong\n2. Sap xep theo Gia phong\n0. Quay lai\nChon: ");
    scanf("%d", &choice);
    if (choice != 1 && choice != 2) return;

    printf("1. Tang dan\n2. Giam dan\nChon: ");
    scanf("%d", &tangDan);
    if (tangDan != 1 && tangDan != 2) return;

    push(UndoStack, L);
    clearStack(RedoStack);

    for (NODE *p = L->phead; p != NULL; p = p->pnext) {
        for (NODE *q = p->pnext; q != NULL; q = q->pnext) {
            int doiCho = 0;
            if (choice == 1) {
                doiCho = (tangDan == 1) ? (strcmp(p->data.maPhong, q->data.maPhong) > 0)
                                        : (strcmp(p->data.maPhong, q->data.maPhong) < 0);
            } else {
                doiCho = (tangDan == 1) ? (p->data.giaPhong > q->data.giaPhong)
                                        : (p->data.giaPhong < q->data.giaPhong);
            }
            if (doiCho) {
                struct ROOM temp = p->data;
                p->data = q->data;
                q->data = temp;
            }
        }
    }
    ghiLichSu(LS, "Sap xep", "DS Phong");
    printf("Sap xep thanh cong!\n");
}

void thongKePhong(LIST *L) {
    if (L->phead == NULL) {
        printf("\nDanh sach phong rong!\n");
        return;
    }
    int tong = 0, trong = 0, daThue = 0;
    float tongGia = 0, maxGia = L->phead->data.giaPhong, minGia = L->phead->data.giaPhong;

    for (NODE *p = L->phead; p != NULL; p = p->pnext) {
        tong++;
        tongGia += p->data.giaPhong;
        if (p->data.trangThai == 0) trong++;
        else daThue++;
        if (p->data.giaPhong > maxGia) maxGia = p->data.giaPhong;
        if (p->data.giaPhong < minGia) minGia = p->data.giaPhong;
    }
    printf("\n========== THONG KE PHONG ==========\n");
    printf("Tong so phong  : %d (Trong: %d | Da thue: %d)\n", tong, trong, daThue);
    printf("Gia trung binh : %.0f\n", tongGia / tong);
    printf("Gia cao nhat   : %.0f\n", maxGia);
    printf("Gia thap nhat  : %.0f\n", minGia);
    printf("====================================\n");
}

void ghiFilePhong(LIST *L, LIST_LS *LS) {
    FILE *f = fopen("hotel_output.txt", "w");
    if (f == NULL) {
        printf("Khong the mo file!\n");
        return;
    }
    for (NODE *p = L->phead; p != NULL; p = p->pnext) {
        fprintf(f, "%s|%s|%s|%.0f|%d\n",
                p->data.maPhong, p->data.tenPhong, p->data.loaiPhong,
                p->data.giaPhong, p->data.trangThai);
    }
    fclose(f);
    ghiLichSu(LS, "Ghi file", "hotel_output.txt");
    printf("Da ghi ra file hotel_output.txt!\n");
}

void docFilePhong(LIST *L, LIST_LS *LS) {
    FILE *f = fopen("hotel_input.txt", "r");
    if (f == NULL) {
        printf("Khong tim thay file hotel_input.txt!\n");
        return;
    }
    struct ROOM room;
    int dem = 0;
    while (fscanf(f, "%9[^|]|%29[^|]|%19[^|]|%f|%d\n",
                  room.maPhong, room.tenPhong, room.loaiPhong,
                  &room.giaPhong, &room.trangThai) == 5) {
        if (timNodePhong(L, room.maPhong) == NULL) {
            themCuoiPhong(L, room);
            dem++;
        }
    }
    fclose(f);
    ghiLichSu(LS, "Doc file", "hotel_input.txt");
    printf("Da doc them %d phong tu file hotel_input.txt!\n", dem);
}

// =========================================================
// 5. QUAN LY KHACH HANG & NHAN VIEN (LINKED LIST)
// =========================================================

NODE_KH *timNodeKH(LIST_KH *L, const char *maKH) {
    for (NODE_KH *p = L->phead; p != NULL; p = p->pnext) {
        if (strcmp(p->data.maKH, maKH) == 0) return p;
    }
    return NULL;
}

void themKhachHang(LIST_KH *L, LIST_LS *LS) {
    struct KhachHang kh;
    do {
        printf("Nhap ma KH: ");
        scanf("%9s", kh.maKH);
        if (timNodeKH(L, kh.maKH) != NULL) printf("Ma KH da ton tai!\n");
    } while (timNodeKH(L, kh.maKH) != NULL);

    xoaBoDem();
    printf("Nhap ho va ten KH: ");
    nhapChuoi(kh.hoTen, sizeof(kh.hoTen));
    printf("Nhap dia chi: ");
    nhapChuoi(kh.diaChi, sizeof(kh.diaChi));
    printf("Nhap SDT: ");
    nhapChuoi(kh.sdt, sizeof(kh.sdt));

    NODE_KH *p = (NODE_KH *)malloc(sizeof(NODE_KH));
    p->data = kh;
    p->pnext = NULL;

    if (L->phead == NULL) L->phead = L->ptail = p;
    else { L->ptail->pnext = p; L->ptail = p; }

    ghiLichSu(LS, "Them KH", kh.maKH);
    printf("Them khach hang thanh cong!\n");
}

void hienThiKhachHang(LIST_KH *L) {
    if (L->phead == NULL) {
        printf("\nDanh sach khach hang rong!\n");
        return;
    }
    printf("\n%-10s %-25s %-25s %-15s\n", "Ma KH", "Ho va Ten", "Dia chi", "SDT");
    printf("---------------------------------------------------------------------------\n");
    for (NODE_KH *p = L->phead; p != NULL; p = p->pnext) {
        printf("%-10s %-25s %-25s %-15s\n", p->data.maKH, p->data.hoTen, p->data.diaChi, p->data.sdt);
    }
}

NODE_NV *timNodeNV(LIST_NV *L, const char *maNV) {
    for (NODE_NV *p = L->phead; p != NULL; p = p->pnext) {
        if (strcmp(p->data.maNV, maNV) == 0) return p;
    }
    return NULL;
}

void themNhanVien(LIST_NV *L, LIST_LS *LS) {
    struct NhanVien nv;
    do {
        printf("Nhap ma NV: ");
        scanf("%9s", nv.maNV);
        if (timNodeNV(L, nv.maNV) != NULL) printf("Ma NV da ton tai!\n");
    } while (timNodeNV(L, nv.maNV) != NULL);

    xoaBoDem();
    printf("Nhap ho va ten NV: ");
    nhapChuoi(nv.hoTen, sizeof(nv.hoTen));
    printf("Nhap chuc vu: ");
    nhapChuoi(nv.chucVu, sizeof(nv.chucVu));
    printf("Nhap SDT: ");
    nhapChuoi(nv.sdt, sizeof(nv.sdt));

    NODE_NV *p = (NODE_NV *)malloc(sizeof(NODE_NV));
    p->data = nv;
    p->pnext = NULL;

    if (L->phead == NULL) L->phead = L->ptail = p;
    else { L->ptail->pnext = p; L->ptail = p; }

    ghiLichSu(LS, "Them NV", nv.maNV);
    printf("Them nhan vien thanh cong!\n");
}

void hienThiNhanVien(LIST_NV *L) {
    if (L->phead == NULL) {
        printf("\nDanh sach nhan vien rong!\n");
        return;
    }
    printf("\n%-10s %-25s %-20s %-15s\n", "Ma NV", "Ho va Ten", "Chuc vu", "SDT");
    printf("----------------------------------------------------------------------\n");
    for (NODE_NV *p = L->phead; p != NULL; p = p->pnext) {
        printf("%-10s %-25s %-20s %-15s\n", p->data.maNV, p->data.hoTen, p->data.chucVu, p->data.sdt);
    }
}

// =========================================================
// 6. QUAN LY DAT PHONG & CHI TIET DAT PHONG (LINKED LIST)
// =========================================================

NODE_DP *timNodeDP(LIST_DP *L, const char *maDP) {
    for (NODE_DP *p = L->phead; p != NULL; p = p->pnext) {
        if (strcmp(p->data.maDP, maDP) == 0) return p;
    }
    return NULL;
}

void taoPhieuDatPhong(LIST_DP *LDP, LIST_CTDP *LCT, LIST *LPhong, LIST_KH *LKH, LIST_NV *LNV, LIST_LS *LLS) {
    if (LPhong->phead == NULL || LKH->phead == NULL || LNV->phead == NULL) {
        printf("\nCan co it nhat 1 Phong, 1 Khach hang va 1 Nhan vien truoc khi dat phong!\n");
        return;
    }

    struct DatPhong dp;
    do {
        printf("Nhap ma Dat Phong (VD: DP01): ");
        scanf("%9s", dp.maDP);
        if (timNodeDP(LDP, dp.maDP) != NULL) printf("Ma dat phong da ton tai!\n");
    } while (timNodeDP(LDP, dp.maDP) != NULL);

    do {
        printf("Nhap ma Khach Hang: ");
        scanf("%9s", dp.maKH);
        if (timNodeKH(LKH, dp.maKH) == NULL) printf("Ma KH khong ton tai!\n");
    } while (timNodeKH(LKH, dp.maKH) == NULL);

    do {
        printf("Nhap ma Nhan Vien phu trach: ");
        scanf("%9s", dp.maNV);
        if (timNodeNV(LNV, dp.maNV) == NULL) printf("Ma NV khong ton tai!\n");
    } while (timNodeNV(LNV, dp.maNV) == NULL);

    xoaBoDem();
    printf("Nhap ngay dat (VD: 28/10/2026): ");
    nhapChuoi(dp.ngayDat, sizeof(dp.ngayDat));
    dp.tongTien = 0;

    int soPhongDat;
    do {
        printf("Nhap so luong phong muon dat: ");
        scanf("%d", &soPhongDat);
    } while (soPhongDat <= 0);

    for (int i = 0; i < soPhongDat; i++) {
        struct ChiTietDatPhong ct;
        strcpy(ct.maDP, dp.maDP);

        NODE *phongNode = NULL;
        do {
            printf("  + Nhap ma phong thu %d: ", i + 1);
            scanf("%9s", ct.maPhong);
            phongNode = timNodePhong(LPhong, ct.maPhong);
            if (phongNode == NULL) {
                printf("    Ma phong khong ton tai!\n");
            } else if (phongNode->data.trangThai == 1) {
                printf("    Phong nay da duoc thue! Vui long chon phong khac.\n");
                phongNode = NULL;
            }
        } while (phongNode == NULL);

        do {
            printf("  + Nhap so ngay o (> 0): ");
            scanf("%d", &ct.soNgayO);
        } while (ct.soNgayO <= 0);

        ct.donGia = phongNode->data.giaPhong;
        ct.thanhTien = ct.donGia * ct.soNgayO;
        dp.tongTien += ct.thanhTien;

        // Cap nhat trang thai phong sang Da thue
        phongNode->data.trangThai = 1;

        // Them vao DSLK Chi Tiet Dat Phong
        NODE_CTDP *nodeCT = (NODE_CTDP *)malloc(sizeof(NODE_CTDP));
        nodeCT->data = ct;
        nodeCT->pnext = NULL;
        if (LCT->phead == NULL) LCT->phead = LCT->ptail = nodeCT;
        else { LCT->ptail->pnext = nodeCT; LCT->ptail = nodeCT; }
    }

    // Them vao DSLK Dat Phong
    NODE_DP *nodeDP = (NODE_DP *)malloc(sizeof(NODE_DP));
    nodeDP->data = dp;
    nodeDP->pnext = NULL;
    if (LDP->phead == NULL) LDP->phead = LDP->ptail = nodeDP;
    else { LDP->ptail->pnext = nodeDP; LDP->ptail = nodeDP; }

    ghiLichSu(LLS, "Dat phong", dp.maDP);
    printf("\nDat phong thanh cong! Tong tien: %.0f\n", dp.tongTien);
}

void hienThiDatPhong(LIST_DP *LDP, LIST_CTDP *LCT) {
    if (LDP->phead == NULL) {
        printf("\nChua co phieu dat phong nao!\n");
        return;
    }
    printf("\n================ DANH SACH PHIEU DAT PHONG ================\n");
    for (NODE_DP *p = LDP->phead; p != NULL; p = p->pnext) {
        printf("\nMa DP: %-8s | Ma KH: %-8s | Ma NV: %-8s | Ngay: %-12s | Tong: %.0f\n",
               p->data.maDP, p->data.maKH, p->data.maNV, p->data.ngayDat, p->data.tongTien);
        printf("  Chi tiet cac phong da dat:\n");
        for (NODE_CTDP *ct = LCT->phead; ct != NULL; ct = ct->pnext) {
            if (strcmp(ct->data.maDP, p->data.maDP) == 0) {
                printf("    - Phong: %-8s | So ngay: %-3d | Don gia: %-10.0f | Thanh tien: %.0f\n",
                       ct->data.maPhong, ct->data.soNgayO, ct->data.donGia, ct->data.thanhTien);
            }
        }
    }
    printf("===========================================================\n");
}

// =========================================================
// 7. HANG DOI YEU CAU (QUEUE) & GIAI PHONG BO NHO
// =========================================================

void addQueue(QueueNode **head, int rq) {
    QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
    newNode->rq = rq;
    newNode->next = NULL;
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    QueueNode *p = *head;
    while (p->next != NULL) p = p->next;
    p->next = newNode;
}

void giaiPhongTatCa(LIST *LPhong, LIST_KH *LKH, LIST_NV *LNV, LIST_DP *LDP, LIST_CTDP *LCT, LIST_LS *LLS,
                    STACKNODE **UndoStack, STACKNODE **RedoStack) {
    giaiPhongListPhong(LPhong);
    clearStack(UndoStack);
    clearStack(RedoStack);

    while (LKH->phead != NULL) { NODE_KH *t = LKH->phead; LKH->phead = t->pnext; free(t); }
    while (LNV->phead != NULL) { NODE_NV *t = LNV->phead; LNV->phead = t->pnext; free(t); }
    while (LDP->phead != NULL) { NODE_DP *t = LDP->phead; LDP->phead = t->pnext; free(t); }
    while (LCT->phead != NULL) { NODE_CTDP *t = LCT->phead; LCT->phead = t->pnext; free(t); }
    while (LLS->phead != NULL) { NODE_LS *t = LLS->phead; LLS->phead = t->pnext; free(t); }
}

void execute(QueueNode **Q, LIST *LPhong, LIST_KH *LKH, LIST_NV *LNV, LIST_DP *LDP, LIST_CTDP *LCT,
             LIST_LS *LLS, STACKNODE **UndoStack, STACKNODE **RedoStack) {
    QueueNode *p = *Q;
    if (p == NULL) return;

    struct ROOM room;
    while (p != NULL) {
        switch (p->rq) {
            case 1:
                inputDanhSachPhong(LPhong, LLS);
                break;
            case 2:
                push(UndoStack, LPhong);
                clearStack(RedoStack);
                printf("\n========== THEM PHONG ==========\n");
                nhapMotPhong(&room, LPhong);
                themCuoiPhong(LPhong, room);
                ghiLichSu(LLS, "Them", room.maPhong);
                printf("Them phong thanh cong!\n");
                break;
            case 3:
                outputPhong(LPhong);
                break;
            case 4:
                timKiemPhong(LPhong);
                break;
            case 5:
                xoaPhong(LPhong, UndoStack, RedoStack, LLS);
                break;
            case 6:
                capNhatPhong(LPhong, UndoStack, RedoStack, LLS);
                break;
            case 7:
                sapXepPhong(LPhong, UndoStack, RedoStack, LLS);
                break;
            case 8:
                ghiFilePhong(LPhong, LLS);
                break;
            case 9:
                docFilePhong(LPhong, LLS);
                break;
            case 10:
                if (*UndoStack != NULL) {
                    push(RedoStack, LPhong);
                    pop(UndoStack, LPhong);
                    ghiLichSu(LLS, "Undo", "");
                    printf("Hoan tac (Undo) thanh cong!\n");
                } else {
                    printf("Khong co thao tac de hoan tac!\n");
                }
                break;
            case 11:
                if (*RedoStack != NULL) {
                    push(UndoStack, LPhong);
                    pop(RedoStack, LPhong);
                    ghiLichSu(LLS, "Redo", "");
                    printf("Lam lai (Redo) thanh cong!\n");
                } else {
                    printf("Khong co thao tac de lam lai!\n");
                }
                break;
            case 12:
                thongKePhong(LPhong);
                break;
            case 13:
                themKhachHang(LKH, LLS);
                break;
            case 14:
                hienThiKhachHang(LKH);
                break;
            case 15:
                themNhanVien(LNV, LLS);
                break;
            case 16:
                hienThiNhanVien(LNV);
                break;
            case 17:
                taoPhieuDatPhong(LDP, LCT, LPhong, LKH, LNV, LLS);
                break;
            case 18:
                hienThiDatPhong(LDP, LCT);
                break;
            case 19:
                hienThiLichSu(LLS);
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }

        if (p->rq != 0) {
            printf("\nNhan Enter de tiep tuc...");
            xoaBoDem();
            getchar();
            system("cls");
        }
        QueueNode *temp = p;
        p = p->next;
        free(temp);
    }
    *Q = NULL;
}

void menu() {
    printf("\n======================================================\n");
    printf("             HE THONG QUAN LY KHACH SAN\n");
    printf("======================================================\n");
    printf(" [QUAN LY PHONG]              [KHACH HANG & NHAN VIEN]\n");
    printf(" 1. Nhap danh sach phong      13. Them khach hang\n");
    printf(" 2. Them phong moi            14. Hien thi khach hang\n");
    printf(" 3. Hien thi danh sach phong  15. Them nhan vien\n");
    printf(" 4. Tim kiem phong            16. Hien thi nhan vien\n");
    printf(" 5. Xoa phong\n");
    printf(" 6. Cap nhat phong            [DAT PHONG & LICH SU]\n");
    printf(" 7. Sap xep danh sach         17. Tao phieu dat phong\n");
    printf(" 8. Ghi danh sach ra file     18. Xem DS dat phong & Chi tiet\n");
    printf(" 9. Doc danh sach tu file     19. Xem lich su thao tac\n");
    printf(" 10. Undo  | 11. Redo\n");
    printf(" 12. Thong ke du lieu phong   0. Thoat chuong trinh\n");
    printf("======================================================\n");
    printf("Nhap lua chon: ");
}

int main() {
    QueueNode *Q = NULL;
    LIST LPhong;
    LIST_KH LKH;
    LIST_NV LNV;
    LIST_DP LDP;
    LIST_CTDP LCT;
    LIST_LS LLS;
    STACKNODE *UndoStack = NULL;
    STACKNODE *RedoStack = NULL;

    khoiTaoPhong(&LPhong);
    khoiTaoKH(&LKH);
    khoiTaoNV(&LNV);
    khoiTaoDP(&LDP);
    khoiTaoCTDP(&LCT);
    khoiTaoLS(&LLS);

    int choice;
    do {
        menu();
        if (scanf("%d", &choice) != 1) {
            xoaBoDem();
            choice = -1;
        }

        if (choice == 0) {
            printf("\nKet thuc chuong trinh!\n");
        } else {
            addQueue(&Q, choice);
            execute(&Q, &LPhong, &LKH, &LNV, &LDP, &LCT, &LLS, &UndoStack, &RedoStack);
        }
    } while (choice != 0);

    giaiPhongTatCa(&LPhong, &LKH, &LNV, &LDP, &LCT, &LLS, &UndoStack, &RedoStack);
    return 0;
}
