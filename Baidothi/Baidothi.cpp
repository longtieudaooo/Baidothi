#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const int MAX = 100;

// Cau 2: Ham Nhap do thi tu file
void Nhap(int A[][MAX], int &n)
{
    ifstream fin("Grap.txt");

    if (!fin)
    {
        cout << "Khong mo duoc file Grap.txt!";
        n = 0;
        return;
    }

    fin >> n;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fin >> A[i][j];
        }
    }

    fin.close();
    cout << "Doc file thanh cong!\n";
}

// Cau 3: Ham Hien Thi ma tran trong so
void HienThi(int A[][MAX], int n)
{
    cout << "\nMa tran trong so cua do thi:\n\n";

    cout << setw(5) << "";

    for (int i = 0; i < n; i++)
		cout << setw(5) << "V" << i + 1;
    for (int i = 0; i < n; i++)
    {
		cout << setw(5) << "V" << i + 1;
        for (int j = 0; j < n; j++)
        {
            cout << setw(5) << A[i][j];
        }

        cout << endl;
    }
}

// Cau 4: Tim duong di ngan nhat bang Dijkstra
void TimDuongDi(int A[][MAX], int n, int u, int v)
{
    int d[MAX];
    int truoc[MAX];
    bool daXet[MAX];

    // Khoi tao
    for (int i = 0; i < n; i++)
    {
        d[i] = 1000000000;
        truoc[i] = -1;
        daXet[i] = false;
    }

    d[u] = 0;

    // Thuat toan Dijkstra
    for (int k = 0; k < n; k++)
    {
        int x = -1;
        int minDist = 1000000000;

        for (int i = 0; i < n; i++)
        {
            if (!daXet[i] && d[i] < minDist)
            {
                minDist = d[i];
                x = i;
            }
        }

        if (x == -1)
            break;

        daXet[x] = true;

        for (int y = 0; y < n; y++)
        {
            if (A[x][y] > 0 && !daXet[y])
            {
                if (d[x] + A[x][y] < d[y])
                {
                    d[y] = d[x] + A[x][y];
                    truoc[y] = x;
                }
            }
        }
    }

    // Kiem tra co duong di hay khong
    if (d[v] == 1000000000)
    {
        cout << "\nKhong co duong di tu V"
             << u + 1 << " den V" << v + 1 << endl;
        return;
    }

    // Truy vet duong di
    int duongDi[MAX];
    int dem = 0;

    for (int x = v; x != -1; x = truoc[x])
    {
        duongDi[dem++] = x;
    }

    cout << "\nDuong di ngan nhat tu V"
         << u + 1 << " den V" << v + 1 << ":\n";

    for (int i = dem - 1; i >= 0; i--)
    {
        cout << "V" << duongDi[i] + 1;

        if (i > 0)
            cout << " -> ";
    }

    cout << "\nTong trong so: " << d[v] << endl;
}

// Cau 5: Ham main
int main()
{
    int A[MAX][MAX];
    int n = 0;

    // Goi ham Nhap
    Nhap(A, n);

    if (n == 0)
        return 0;

    // Goi ham Hien Thi
    HienThi(A, n);

    // Tim duong di tu V1 den V6
    TimDuongDi(A, n, 0, 5);

    return 0;
}

