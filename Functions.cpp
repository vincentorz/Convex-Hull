#include "Head.h"
#include<bits/stdc++.h>
#include <iostream>
using namespace std;
extern vector<Verticies>V;
extern queue<Face>FaceToProcess;
extern set<Face> UsedFaces;
extern map<Plane, set<int>> VertToPlane;
extern set<pair<int,int>>Line;
extern int p;
void printV(){
    for(auto i:V)cout<<i.x<<" "<<i.y<<" "<<i.z<<endl;
}
void printVert(Verticies V){
    cout<<V.x<<" "<<V.y<<" "<<V.z<<endl;
}

void printSet(){
    for(auto i:UsedFaces)cout<<i.p1<<" "<<i.p2<<" "<<i.p3<<endl;
}
void printQ(){
    queue<Face> temp_queue = FaceToProcess;
    while (!temp_queue.empty()) {
        auto x =  temp_queue.front();

        cout <<x.p1 << " "<<x.p2<<endl;
        temp_queue.pop();
    }
}

void printLine(){
    for(auto i:Line)cout<<i.first<<" "<<i.second<<endl;
}
void PrintPlane(const Plane& plane) {
    cout<<"Plane";
    cout << "a =  " << plane.a << " ";
    cout << "b =  " << plane.b << " ";
    cout << "c = " << plane.c << " ";
    cout << "t =  " << plane.t << " ";
    cout << endl;
}
void PrintMap(){
    for (const auto& pair : VertToPlane) {
        const Plane& plane = pair.first;
        const std::set<int>& values = pair.second;

        std::cout << "Plane: x=" << plane.a << " y=" << plane.b << " z=" << plane.c << " t=" << plane.t << std::endl;
        std::cout << "Verticies: ";
        for (int value : values) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }

}
Plane GetPlane(Verticies A,Verticies B,Verticies C){
    Vect v1,v2;
    v1.x = B.x-A.x;
    v1.y = B.y-A.y;
    v1.z = B.z-A.z;

    v2.x = C.x-A.x;
    v2.y = C.y-A.y;
    v2.z = C.z-A.z;
    Plane E;
    double a = v1.y * v2.z - v1.z * v2.y;
    double b= v1.z * v2.x - v1.x * v2.z;
    double c= v1.x * v2.y - v1.y * v2.x;

    double t = a*A.x+b*A.y+c*A.z;

    if (a != 0) {
        E.a = 1;
        E.b = b / a;
        E.c = c / a;
        E.t = t / a;
    }
    else if (b != 0) {
        E.a = 0;
        E.b = 1;
        E.c = c / b;
        E.t = t / b;
    }
    else if (c != 0) {
        E.a = 0;
        E.b = 0;
        E.c = 1;
        E.t = t / c;
    }
    else{
        E.a = 0;
        E.b = 0;
        E.c = 0;
        E.t = 0;
        E.exist = false;
    }
    return E;
}
bool CheckifConvex(Verticies A,Verticies B,Verticies C){
    Plane E = GetPlane(A,B,C);
    //PrintPlane(E);
    bool f1,f2,f3;
    f1 = false;
    f3 = true;
    for(int i = 0;i<p;i++){
        Verticies vert = V[i];
        double d = vert.x*E.a+vert.y*E.b+vert.z*E.c-E.t;
        //cout<<"i = "<<i<<" "<<"d =  "<<d<<endl;
        if(!f1) {
            if(d==0){
                f1 = false;
            }
            else if(d>0){
                f1 = true;
                f2 = true;
            }
            else{
                f1 = true;
                f2 = false;
            }

        }
        else if(f2!=(d>0)&&d!=0){
            f3 = false;
            break;
        }
    }
    return f3;
}
vector<double> MakeProjPos(vector<int> proj, int vidx) {
    vector<double> original(3);
    //cout<<"vidx"<<vidx<<" ";
    //printVert(V[vidx]);
    original[0] = V[vidx].x;
    original[1] = V[vidx].y;
    original[2] = V[vidx].z;
    vector<double> result;
    for (int i = 0; i < 3; i++) {
        //cout<<proj[i];
        //cout<<original[i];
        if (proj[i]==1) result.push_back(original[i]);
    }
    //for(auto i:result) cout<<i;
    return result;
}
bool FindOrientation(vector<double>original,vector<double>cand,vector<double>check){
    /*
    std::cout << "originalx = " << original[0] << std::endl;
    std::cout << "originaly = " << original[1] << std::endl;

    std::cout << "Printing cand:" << std::endl;
    std::cout << "candx = " << cand[0] << std::endl;
    std::cout << "candy = " << cand[1] << std::endl;

    std::cout << "Printing check:" << std::endl;
    std::cout << "checkx = " << check[0] << std::endl;
    std::cout << "checky = " << check[1] << std::endl;
    */
    double x1,x2,y1,y2;
    x1 = cand[0]-original[0];
    y1 = cand[1]-original[1];
    x2 = check[0]-cand[0];
    y2 = check[1]-cand[1];
    /*
    std::cout << "x1: " << x1 << ", ";
    std::cout << "y1: " << y1 << ", ";
    std::cout << "x2: " << x2 << ", ";
    std::cout << "y2: " << y2 << std::endl;
    */
    double crossProductZ = x1*y2-y1*x2;
    /*
    if (crossProductZ < 0) {
        std::cout << "<0" << std::endl;
    } else if (crossProductZ == 0) {
        std::cout << "=0" << std::endl;
    } else {
        std::cout << ">0" << std::endl;
    }
    */
    return crossProductZ<=0;
}
bool cmp(Verticies A,Verticies B){
    if (A.x !=B.x) return A.x<B.x;
    if(A.y!=B.y)return A.y<B.y;
    if(A.z!=B.z)return A.z<B.z;
}
bool cmp1(const std::pair<double, int>& a, const std::pair<double, int>& b) {
    return a.first < b.first;
}

Face CreateSortedFace(int a,int b,int c){
    if (a > b) swap(a, b);
    if (a > c) swap(a, c);
    if (b > c) swap(b, c);
    Face A;
    A.p1 = a;
    A.p2 = b;
    A.p3 = c;
    return A;
}
Face CreateFace(int a,int b,int c){
    Face A;
    A.p1 = a;
    A.p2 = b;
    A.p3 = c;
    return A;
}
pair<int, int> CreatePair(int a, int b) {
    if (a < b) {
        return make_pair(a, b);
    } else {
        return make_pair(b, a);
    }

}
Verticies CreateVerticies(double a,double b,double c){
    Verticies A;
    A.x = a;
    A.y = b;
    A.z = c;
    return A;
}
void SetCube(){
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            for(int k = 0; k < 2; k++) {
                V.push_back(CreateVerticies(i,j,k));
            }
        }
    }
    //V.push_back(CreateVerticies(0.5,0,0));
    p = V.size();
}
void SetFlat(){
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            V.push_back(CreateVerticies(i,j,0));
        }
    }
    p = V.size();
}
void SetTriangle(){
    V.push_back(CreateVerticies(1,1,1));
    V.push_back(CreateVerticies(-1,-1,1));
    V.push_back(CreateVerticies(-1,1,-1));
    V.push_back(CreateVerticies(1,-1,-1));
    p = V.size();
}
void SetE(){
    V.push_back(CreateVerticies(0,0,2.3));
    V.push_back(CreateVerticies(0,1,0));
    V.push_back(CreateVerticies(1,-1.7,0));
    V.push_back(CreateVerticies(-1,-1,0));
    V.push_back(CreateVerticies(0,0,1));
    p = V.size();
}
void SetRandom(int amount){
    srand(time(nullptr));
    int maxp = 5;
    int minp = 1;

    int a = maxp-minp;

    set<Verticies> V_r;
    for (int i = 0; i < amount ; i++) {
        while(true){
            Verticies v;
            v.x = rand()%a+minp;
            v.y = rand()%a+minp;
            v.z = rand()%a+minp;
            if(V_r.find(v)==V_r.end()){
                V_r.insert(v);
                break;
            }
        }
    }
    for(auto i:V_r)V.push_back(i);
    p = amount;


}
void Setico(){
    double phi = 1.5;
    V.push_back(CreateVerticies(0, 1, phi));
    V.push_back(CreateVerticies(0, -1, phi));

    V.push_back(CreateVerticies(0, 1, phi*-1));
    V.push_back(CreateVerticies(0, -1, phi*-1));

    V.push_back(CreateVerticies(1, phi, 0));
    V.push_back(CreateVerticies(-1, phi, 0));

    V.push_back(CreateVerticies(1, phi*-1, 0));
    V.push_back(CreateVerticies(-1, phi*-1, 0));

    V.push_back(CreateVerticies(phi,0, 1));
    V.push_back(CreateVerticies(phi, 0, -1));

    V.push_back(CreateVerticies(phi*-1, 0, 1));
    V.push_back(CreateVerticies(phi*-1, 0, -1));
    p = V.size();
}
