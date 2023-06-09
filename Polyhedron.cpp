#include <GL/glut.h>  // (or others, depending on the system in use)

#include "Polyhedron.h"


Polyhedron::Polyhedron(string _fname, Vector3d _c, double _rotY, Vector3d _clr) : ObjLoader(_fname) {
	//cout << "Polyhedron constructor. " << endl;
	center = _c;
	rotY = _rotY;
	color = _clr;
}

Polyhedron::Polyhedron(const Polyhedron& other) {
	//cout << "Polyhedron copy constructor. " << endl;
	center = other.center;
	rotY = other.rotY;
	color = other.color;
	filename = other.filename;
	//////////////////////////////////////////////////////////
	//other data from obj loader

	verts = other.verts;
	vts = other.vts;
	vns = other.vns;
	faces = other.faces;
}

void Polyhedron::Recenter() {
	//TODO
	Vector3d sum(0, 0, 0);
	for (int i = 0; i < verts.size(); i++) {
		sum += verts[i];
	}
	cout << "sum = " << sum << endl;
	Vector3d modelledCenter = sum / (1.0 * verts.size());
	cout << "modelledCenter = " << modelledCenter << endl;
	for (int i = 0; i < verts.size(); i++) {
		verts[i] -= modelledCenter;
	}
}

void Polyhedron::RecenterXZ() {
	//TODO 
	
}

void Polyhedron::Draw() {
	//TODO 
	//cout << "Polyhedron::Draw color = " << color << endl;
	glColor3d(color.GetX(), color.GetY(), color.GetZ());
	glPushMatrix();
	glTranslated(center.GetX(), center.GetY(), center.GetZ());
	glPointSize(1.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < verts.size(); i++) {
		glVertex3d(verts[i].GetX(), verts[i].GetY(), verts[i].GetZ());
	}
	glEnd();
	
	glPopMatrix();

	glPushMatrix();
	glTranslated(center.GetX(), center.GetY(), center.GetZ());
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < faces.size(); i++) {
		//faces[i].Print();
		int& id1 = faces[i].ids[0];
		int& id2 = faces[i].ids[1];
		int& id3 = faces[i].ids[2];
		int& nid1 = faces[i].normalIds[0];
		int& nid2 = faces[i].normalIds[1];
		int& nid3 = faces[i].normalIds[2];
		glNormal3d(vns[nid1 - 1].GetX(), vns[nid1 - 1].GetY(), vns[nid1 - 1].GetZ());
		glVertex3d(verts[id1 - 1].GetX(), verts[id1 - 1].GetY(), verts[id1 - 1].GetZ());
		glNormal3d(vns[nid2 - 1].GetX(), vns[nid2 - 1].GetY(), vns[nid2 - 1].GetZ());
		glVertex3d(verts[id2 - 1].GetX(), verts[id2 - 1].GetY(), verts[id2 - 1].GetZ());
		glNormal3d(vns[nid3 - 1].GetX(), vns[nid3 - 1].GetY(), vns[nid3 - 1].GetZ());
		glVertex3d(verts[id3 - 1].GetX(), verts[id3 - 1].GetY(), verts[id3 - 1].GetZ());
	}

	glEnd();
	glPopMatrix();
}