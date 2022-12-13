#include "Font.h"

void HersheySymbol::parse(string line){
    vector<Vec2d> current;
    //id
    int pairs = stoi(line.substr(5,3));
    left = line[8]-'R';
    right = line[9]-'R';
    for(int i =10; i < line.size(); i+=2){
        if(line[i] == ' ' and line[i+1] == 'R'){
            lines.push_back(current);
            current.clear();
        }else{
            Vec2d pt = {(float)(line[i]-'R'),(float)(line[i+1]-'R')};
            current.push_back(pt);
        }
    }
    lines.push_back(current);
}

//or translate?
void HersheySymbol::draw(Image* img, Vec2d center, Color c){
    for(vector<Vec2d> run: lines){
        for(int i =0; i < run.size()-1; ++i){
            Line l = {run[i]+center,run[i+1]+center};
            l.draw(img,c);  
        }
    }
}


void HersheySymbol::scale(float f){
    left *= f;
    right *= f;
    for(int i =0; i < lines.size(); ++i){
        for(int j = 0; j < lines[i].size(); ++j){
            lines[i][j] = lines[i][j]*f;
        }
    }
}

void HersheyFont::load(string filename){
    ifstream fin;
    fin.open(filename);
    string line = "";
    while(getline(fin,line)){
        HersheySymbol s;
        s.parse(line);
        symbols.push_back(s);
    }
    fin.close();
}

void HersheyFont::scale(float f){
    for(int i =0; i < symbols.size(); ++i){
        symbols[i].scale(f);
    }
}

void HersheyFont::draw(string text,Image* img, Vec2d center, Color c){
    for(char ch: text){
        center.x += abs(symbols[ch-32].left);
        symbols[ch-32].draw(img,center,c);
        center.x += abs(symbols[ch-32].right);
    }
}
