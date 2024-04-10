#include "Head.h"

queue<Face>FaceToProcess;
set<Face> UsedFaces;
map<Plane, set<int>> VertToPlane;
extern vector<Verticies> V;
extern int p;
extern set<pair<int,int>> Line;
void test(){
    cout<<p;
}
void GenerateOutLine()
{
    //SetTriangle();
    //SetFlat();
    //SetCube();

    sort(V.begin(),V.end(),cmp);
    printV();
    bool foundinitialface = false;
    for(int i = 1; i < p-1; i++) {
        for(int j = i+1; j < p; j++) {
            if(CheckifConvex(V[0],V[i],V[j])){
                cout<<i<<j;
                FaceToProcess.push(CreateFace(0,i,j));
                FaceToProcess.push(CreateFace(0,j,i));
                FaceToProcess.push(CreateFace(i,j,0));
                UsedFaces.insert(CreateSortedFace(0,i,j));
                Line.insert(CreatePair(0,i));
                Line.insert(CreatePair(0,j));
                Line.insert(CreatePair(i,j));
                foundinitialface = true;
                break;
            }
        }
        if(foundinitialface)break;
    }
        //cout<<"new"<<endl;
        //printSet();
        //printQ();
       // cout<<"Lines"<<endl;
        //printLine();

    while(!FaceToProcess.empty()){
        //cout<<"new"<<endl;
        auto Faceidx = FaceToProcess.front();
        int a = Faceidx.p1;
        int b = Faceidx.p2;
        int c = Faceidx.p3;
        FaceToProcess.pop();
        Verticies A = V[a];
        Verticies B = V[b];

        printQ();
        printSet();
        for(int i = 0;i<p;i++){
            if(i==a||i==b)continue; //loop through all vert without itself
            Face F;
            F = CreateSortedFace(i,a,b);

            if(CheckifConvex(A,B,V[i])&&UsedFaces.find(F) == UsedFaces.end()){ //if face not exist and can be
                cout<<"success"<<a<<b<<i<<endl;
                FaceToProcess.push(CreateFace(a,i,b));
                FaceToProcess.push(CreateFace(b,i,a));
                UsedFaces.insert(F);
                Line.insert(CreatePair(i,a));
                Line.insert(CreatePair(i,b));
                Line.insert(CreatePair(a,b));

                //2d convex hull
                Verticies I = V[i];
                Verticies C = V[c];
                Plane NewP = GetPlane(A,B,I);
                if(NewP.exist){
                    VertToPlane[NewP].insert(a);
                    VertToPlane[NewP].insert(b);
                    VertToPlane[NewP].insert(i);
                }
            }
            else{
                //cout<<a<<b<<i<<"cannot"<<" ";
            }
        }
    }
    //PrintMap();
    //cout<<VertToPlane.size();
    for (const auto MapPair : VertToPlane) {
        vector<int>proj(3);
        Plane plane = MapPair.first;
        set<int> v = MapPair.second;
        if(plane.a !=0){ //yz
            proj[0] = 0;
            proj[1] = 1;
            proj[2] = 1;
        }
        else if (plane.b !=0){//xz
            proj[0] = 1;
            proj[1] = 0;
            proj[2] = 1;
        }
        else{//xy
            proj[0] = 1;
            proj[1] = 1;
            proj[2] = 0;
        }
        vector<pair<double,int>> vs;
        for (int idx:v){
            if(proj[0] == 1){
                vs.push_back({V[idx].x,idx});
            }
            else if(proj[1] == 1){
                vs.push_back({V[idx].y,idx});
            }
        }

        sort(vs.begin(),vs.end(),cmp1);
        int startidx = vs[0].second;
        int firstidx = startidx;
        //cout<<startidx;
        vector<double> StartPos = MakeProjPos(proj,startidx);
        //PrintPlane(plane);
        //cout<<StartPos[0]<<" "<<StartPos[1]<<" ";

        for (int idx:v){
            for (int idx1:v){
                if(idx!=idx1)Line.erase(CreatePair(idx,idx1));
            }
         }
        while(true){
            for (int candidx:v){
                if(candidx == startidx) continue;
                vector<double> CandPos = MakeProjPos(proj,candidx);
                bool candvalid = true;
                for (int checkidx:v){
                    if(checkidx == candidx||checkidx == startidx) continue;

                    vector<double> CheckPos = MakeProjPos(proj,checkidx);
                    //cout<<startidx<<" "<<candidx<<" "<<checkidx<<endl;
                    if(!FindOrientation(StartPos,CandPos,CheckPos)){

                        candvalid = false;

                        break;
                    }
                    else{
                        //cout<<startidx<<" "<<candidx<<" "<<checkidx<<" "<<candvalid<<endl;
                    }
                }

                if(candvalid){
                    Line.insert(CreatePair(candidx,startidx));
                    startidx = candidx;
                    StartPos = CandPos;
                    break;
                }
            }
            if(startidx==firstidx)break;
        }

    }
    //cout<<endl<<"Line";
    //printLine();

}
