#include "SVG.h"


 string rgb(string type,Color fillColor){
	string cmd = type + "=\"rgb(";
 	cmd += to_string(fillColor.red)   + ",";
	cmd += to_string(fillColor.green) + ",";
 	cmd += to_string(fillColor.blue)  + ")\"";
	return cmd;
}

void SVG::fillCircle(Vec2d c, float radius){
	stringstream cmd;
	cmd << "<circle cx=\"" << c.x << "\" cy=\"" << c.y;
	cmd << "\" r=\"" << radius << "\" ";
	cmd << rgb("fill",fillColor) << "/>";
	cmds.push_back(cmd.str());
}
void SVG::drawLine(Vec2d a, Vec2d b){
	stringstream cmd;
	cmd << "<line x1=\"" << a.x << "\" y1=\"" << a.y;
	cmd << "\" x2=\"" << b.x << "\" y2=\" " << b.y;
	cmd << rgb("stroke",fillColor);
	cmd << "\" stroke-width=\"" << strokeSize << "\"/>";
	cmds.push_back(cmd.str());
}

SVG::SVG(int width,int height){
	stringstream cmd;
	cmd << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\"";
	cmd << " width=\"" << width << "\" height=\"" << height << "\">";
	cmds.push_back(cmd.str());
}

void SVG::end(){
	cmds.push_back("</svg>");
}

void SVG::write(string filename){
	ofstream fout;
	fout.open(filename);
	for(string s: cmds){
		fout << s << "\n";
	}
	fout.close();
}
