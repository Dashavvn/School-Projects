#include "OBJ.h"

void printVec(Vec3 v){
	printf("{%f,%f,%f}\n",v.x,v.y,v.z);
}

void writeOBJ(Mesh* mesh, const char* filename){
	FILE* fout = fopen(filename,"w");
	for(Vertex v: mesh->vertices){
		fprintf(fout,"v\t%f\t%f\t%f\n",v.position.x,v.position.y,v.position.z);
	}
	//should index these...
	for(Vertex v: mesh->vertices){
		fprintf(fout,"vn\t%f\t%f\t%f\n",v.normal.x,v.normal.y,v.normal.z);
	}
	for(int i =0; i < mesh->indices.size(); i += 3){
		int a = mesh->indices[i]+1;
		int b = mesh->indices[i+1]+1;
		int c = mesh->indices[i+2]+1;
		fprintf(fout,"f\t%d//%d\t%d//%d\t%d//%d\n",a,a,b,b,c,c);
	}
	fclose(fout);
}

int countSlashes( char* s ){
	if(s == NULL)
		return 0;
	int rv = 0;
	while(*s != 0){
		if(*s == '/')
			rv += 1;
		++s;
	}
	return rv;
}





Mesh* loadOBJ(const char* filename){
	struct Face{
		Vec3 pos;
		Vec3 tex;
		Vec3 nor;
	};



	Mesh* theMesh = new Mesh;
	FILE* fin = fopen(filename, "r");
	bool hasNormals = false;
	bool hasTexture = false;
	char buffer[513];
	char token[16];
	char* ptr;
	int line = 1;
	vector<Vec3> vertices;
	vector<Vec3> normals;
	vector<Vec2> textures;

	Vec3 vec;

	vector<Face> faces;



	while(!feof(fin)){
		vec = {0,0,0};
		fscanf(fin,"%s",token);
		fgets(buffer,512,fin);
		if(!strcmp(token,"#")){
			//comments
		}else if(!strcmp(token,"v")){
			sscanf(buffer,"%f%f%f",&vec.z,&vec.y,&vec.x);
			vertices.push_back(vec);
		}else if(!strcmp(token,"vt")){
			hasTexture = true;
			Vec2 v;
			sscanf(buffer,"%f%f",&v.x,&v.y);
			textures.push_back(v);
		}else if(!strcmp(token,"vn")){
			hasNormals = true;
			sscanf(buffer,"%f%f%f",&vec.x,&vec.y,&vec.z);
			normals.push_back(vec);
		}else if(!strcmp(token,"vp")){
			sscanf(buffer,"%f%f%f",&vec.x,&vec.y,&vec.z);
		}else if(!strcmp(token,"f")){
			Face f;
			if(9 == sscanf(buffer,"%f/%f/%f %f/%f/%f %f/%f/%f",
					&f.pos.x,&f.tex.x,&f.nor.x,
					&f.pos.y,&f.tex.y,&f.nor.y,
					&f.pos.z,&f.tex.z,&f.nor.z)){
			}else if(6 == sscanf(buffer,"%f//%f %f//%f %f//%f",
					&f.pos.x,&f.tex.x,&f.pos.y,&f.nor.y,&f.pos.z,&f.nor.z)){
				f.tex = {0,0,0};
			}else if(6 == sscanf(buffer,"%f/%f %f/%f %f/%f",
					&f.pos.x,&f.tex.x,&f.pos.y,&f.tex.y,&f.pos.z,&f.tex.z)){
				printf("missing normal\n");
				f.nor = {0,0,0};
			}else{
				sscanf(buffer,"%f%f%f",&f.pos.x,&f.pos.y,&f.pos.z);
				f.tex = {0,0,0};
				f.nor = {0,0,0};
			}
			faces.push_back(f);
		}else{
			printf("unexpected type [fix this] -- %s\n",token);
		}
	}
	fclose(fin);
	map<string,int> mapping;

	//printf("read lines\n");

	for(int i =0; i < faces.size(); ++i){
		int aIndex = (int)faces[i].pos.data[0]-1;
		int bIndex = (int)faces[i].pos.data[1]-1;
		int cIndex = (int)faces[i].pos.data[2]-1;
		Vec3 a = vertices[cIndex] - vertices[aIndex];
		Vec3 b = vertices[bIndex] - vertices[aIndex];
		Vec3 faceNormal = a.cross(b);
		for(int j = 0; j < 3; ++j){
			int vIndex = (int)faces[i].pos.data[j]-1;
			int tIndex = (int)faces[i].tex.data[j]-1;
			int nIndex = (int)faces[i].nor.data[j]-1;

			string key = to_string(vIndex) + "/" + to_string(tIndex) + "/" + to_string(nIndex);
			auto k = mapping.find(key);
			if(k != mapping.end()){
				//found the vertex
				int index = k->second;
				if(!hasNormals){
					theMesh->vertices[index].normal = theMesh->vertices[index].normal + faceNormal;
				}
				theMesh->indices.push_back(index);
			}else{
				//did not find vertex
				mapping[key] = theMesh->vertices.size();
				theMesh->indices.push_back(theMesh->vertices.size());
				Vertex v;
				v.position = vertices[vIndex];
				if(tIndex >= 0){
					v.tex   = textures[tIndex];
					v.tex.y = 1-v.tex.y;
				}
				if(nIndex >= 0){
					v.normal = normals[nIndex];
				}else{
					v.normal = faceNormal;
				}
				theMesh->vertices.push_back(v);
			}
		}
	}

	for(int i =0 ;i < theMesh->vertices.size(); ++i){
		theMesh->vertices[i].normal.normalize();
	}


	return theMesh;
}
