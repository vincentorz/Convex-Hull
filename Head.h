#include<bits/stdc++.h>
using namespace std;
struct Verticies {
    double x, y, z;
    bool operator<(const Verticies& other) const {
        if (x != other.x) return x < other.x;
        if (y != other.y) return y < other.y;
        if (z != other.z) return z< other.z;
    }
};

struct Vect{
    double x,y,z;
};
struct Plane{
    double a,b,c,t;
    bool exist = true;
    bool operator==(const Plane& other) const {
        return a == other.a && b == other.b && c == other.c && t == other.t;
    }
    bool operator<(const Plane& other) const {
        if (a != other.a) return a < other.a;
        if (b != other.b) return b < other.b;
        if (c != other.c) return c< other.c;
        return t < other.t;
    }
};
struct Face{ //index of V
    int p1,p2,p3;
    bool operator<(const Face& other) const {
        if (p1 != other.p1) return p1 < other.p1;
        if (p2 != other.p2) return p2 < other.p2;
        return p3 < other.p3;
    }
};

void printV();
void PrintPlane(const Plane& plane);
void PrintMap();

bool CheckifConvex(Verticies A,Verticies B,Verticies C);
Plane GetPlane(Verticies A,Verticies B,Verticies C);
vector<double> MakeProjPos(vector<int> proj, int vidx);
bool FindOrientation(vector<double>original,vector<double>cand,vector<double>check);

bool cmp(Verticies A,Verticies B);
bool cmp1(const std::pair<double, int>& a, const std::pair<double, int>& b);

Face CreateSortedFace(int a,int b,int c);
Face CreateFace(int a,int b,int c);

pair<int, int> CreatePair(int a, int b);
Verticies CreateVerticies(double a,double b,double c);
void SetCube();
void SetFlat();
void SetTriangle();
void printLine();
void printSet();
void printQ();
void test();
void GenerateOutLine();
void SetRandom(int amount);
void Setico();
