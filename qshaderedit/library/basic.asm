[VertexProgram]
!!ARBvp1.0

PARAM mvp[4]  = { state.matrix.mvp };
PARAM mvi[4] = { state.matrix.modelview.inverse };

ATTRIB iVertex = vertex.position;
ATTRIB iNormal = vertex.normal;

OUTPUT oPos     = result.position;
OUTPUT normal   = result.texcoord[0];
OUTPUT viewVec  = result.texcoord[1];

DP4 oPos.x, mvp[0], iVertex;
DP4 oPos.y, mvp[1], iVertex;
DP4 oPos.z, mvp[2], iVertex;
DP4 oPos.w, mvp[3], iVertex;

MOV normal, iNormal;

PARAM cameraPos = state.matrix.modelview.row[3];
TEMP cp;
DP4 cp.x, mvi[0], cameraPos;
DP4 cp.y, mvi[1], cameraPos;
DP4 cp.z, mvi[2], cameraPos;
SUB viewVec, cp, iVertex;

END
[FragmentProgram]
!!ARBfp1.0

PARAM specExp = 8;
PARAM color = { 1, 0, 0, 0 };
#PARAM lightVec = state.light[0].position;
PARAM lightVec = {0.577, 0.577, 0.577, 0};

TEMP normal, viewVec, reflVec, diffuse, specular, light;

DP3		normal.w, fragment.texcoord[0], fragment.texcoord[0];
RSQ		normal.w, normal.w;
MUL		normal, fragment.texcoord[0], normal.w;

DP3		viewVec.w, fragment.texcoord[1], fragment.texcoord[1];
RSQ		viewVec.w, viewVec.w;
MUL		viewVec, fragment.texcoord[1], viewVec.w;

DP3		reflVec, viewVec, normal;
MUL		reflVec, reflVec, normal;
MAD		reflVec, reflVec, 2, -viewVec;

DP3_SAT	diffuse, lightVec, normal;
DP3_SAT	specular, reflVec, lightVec;
POW		specular, specular.x, specExp.x;

MAD		light, diffuse, color, specular;
MAD		result.color, color, 0.1, light;

END
