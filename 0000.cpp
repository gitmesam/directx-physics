

// [9781556229138][Introduction to 3D Game Programming with DirectX 9][2003]
void ComputeNormal(D3DXVECTOR3* p0,
D3DXVECTOR3* p1,
D3DXVECTOR3* p2,
D3DXVECTOR3* out)
{
D3DXVECTOR3 u = *p1 - *p0;
D3DXVECTOR3 v = *p2 - *p0;
D3DXVec3Cross(out, &u, &v);
D3DXVec3Normalize(out, out);
}





// [9781556229138][Introduction to 3D Game Programming with DirectX 9][2003]
void Camera::getViewMatrix(D3DXMATRIX* V)
{
// Keep camera's axes orthogonal to each other:
D3DXVec3Normalize(&_look, &_look);
D3DXVec3Cross(&_up, &_look, &_right);
D3DXVec3Normalize(&_up, &_up);
D3DXVec3Cross(&_right, &_up, &_look);
D3DXVec3Normalize(&_right, &_right);
// Build the view matrix:
float x = -D3DXVec3Dot(&_right, &_pos);
float y = -D3DXVec3Dot(&_up, &_pos);
float z = -D3DXVec3Dot(&_look, &_pos);
(*V)(0, 0) = _right.x;
(*V)(0, 1) = _up.x;
(*V)(0, 2) = _look.x;
(*V)(0, 3) = 0.0f;
(*V)(1, 0) = _right.y;
(*V)(1, 1) = _up.y;
(*V)(1, 2) = _look.y;
(*V)(1, 3) = 0.0f;
(*V)(2, 0) = _right.z;
(*V)(2, 1) = _up.z;
(*V)(2, 2) = _look.z;
(*V)(2, 3) = 0.0f;
(*V)(3, 0) = x;
(*V)(3, 1) = y;
(*V)(3, 2) = z;
(*V)(3, 3) = 1.0f;
}




// [9781556229138][Introduction to 3D Game Programming with DirectX 9][2003]
float Terrain::computeShade(int cellRow, int cellCol,
D3DXVECTOR3* directionToLight)
{
// get heights of three vertices on the quad
float heightA = getHeightmapEntry(cellRow, cellCol);
float heightB = getHeightmapEntry(cellRow, cellCol+1);
float heightC = getHeightmapEntry(cellRow+1, cellCol);
// build two vectors on the quad
D3DXVECTOR3 u(_cellSpacing, heightB - heightA, 0.0f);
D3DXVECTOR3 v(0.0f, heightC - heightA, -_cellSpacing);
// find the normal by taking the cross product of two
// vectors on the quad.
D3DXVECTOR3 n;
D3DXVec3Cross(&n, &u, &v);
D3DXVec3Normalize(&n, &n);
float cosine = D3DXVec3Dot(&n, directionToLight);
if(cosine < 0.0f)
cosine = 0.0f;
return cosine;
}




// [9781584505709][Character Animation With Direct3D][2009]
void InverseKinematics::ApplyLookAtIK(D3DXVECTOR3 &lookAtTarget,
float maxAngle)
{
// Start by transforming to local space
D3DXMATRIX mtxToLocal;
D3DXMatrixInverse(&mtxToLocal, NULL,
&m_pHeadBone->CombinedTransformationMatrix);
D3DXVECTOR3 localLookAt;
D3DXVec3TransformCoord(&localLookAt, &lookAtTarget, &mtxToLocal );
// Normalize local look at target
D3DXVec3Normalize(&localLookAt, &localLookAt);
// Get rotation axis and angle
D3DXVECTOR3 localRotationAxis;
D3DXVec3Cross(&localRotationAxis, &m_headForward, &localLookAt);
D3DXVec3Normalize(&localRotationAxis, &localRotationAxis);
float localAngle = acosf(D3DXVec3Dot(&m_headForward,
&localLookAt));
// Limit angle
localAngle = min( localAngle, maxAngle );
// Apply the transformation to the bone
D3DXMATRIX rotation;
D3DXMatrixRotationAxis(&rotation, &localRotationAxis, localAngle);
m_pHeadBone->CombinedTransformationMatrix = rotation *
m_pHeadBone->CombinedTransformationMatrix;
// Update changes to child bones
if(m_pHeadBone->pFrameFirstChild)
{
m_pSkinnedMesh->UpdateMatrices(
(Bone*)m_pHeadBone->pFrameFirstChild,
&m_pHeadBone->CombinedTransformationMatrix);
}
}




// [9781584505709][Character Animation With Direct3D][2009]
D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
D3DXVECTOR3 right;
//Calculate the right vector
D3DXVec3Cross(&right, &faceNormal, &up);
D3DXVec3Normalize(&right, &right);
//Calculate up vector
D3DXVec3Cross(&up, &faceNormal, &right);
D3DXVec3Normalize(&up, &up);




// [9781592000371][Advanced Animation with DirectX][2003]
// Calculate the cross product of the force vector
// and the vecPtoC vector. This vector is the torque.
D3DXVECTOR3 vecTorque;
D3DXVec3Cross(&vecTorque, &vecPtoC, &vecForce);




// [9781598633610][Beginning DirectX 10 Game Programming][2008]
// compute normals for each face in the model
for (unsigned int i = 0; i < modelObject->numIndices; i+=3)
{
D3DXVECTOR3 v0 = vertices[indices[i]].Pos;
D3DXVECTOR3 v1 = vertices[indices[i + 1]].Pos;
D3DXVECTOR3 v2 = vertices[indices[i + 2]].Pos;
D3DXVECTOR3 normal;
D3DXVECTOR3 cross;
D3DXVec3Cross(&cross, &D3DXVECTOR3(v2 - v0), &D3DXVECTOR3(v1 - v0));
D3DXVec3Normalize(&normal, &cross);
// assign the computed normal to each vertex in this face
vertices[indices[i]].Normal = normal;
vertices[indices[i + 1]].Normal = normal;
vertices[indices[i + 2]].Normal = normal;
}




// [9781931841399][Beginning Direct3D Game Programming, Second Edition][2003]
D3DXVec3Cross(&vCameraUp, &vCameraLook, &vCameraRight); // Cross Product of the RIGHT and LOOK Vector

// Matrices for pitch, yaw and roll
D3DXMatrixRotationAxis(&matPitch, &vCameraRight, fPitch );
D3DXMatrixRotationAxis(&matYaw, &vCameraUp, fYaw );
D3DXMatrixRotationAxis(&matRoll, &vCameraLook, fRoll);

// rotate the LOOK & RIGHT Vectors about the UP Vector
D3DXVec3TransformCoord(&vCameraLook, &vCameraLook, &matYaw);
D3DXVec3TransformCoord(&vCameraRight, &vCameraRight, &matYaw);
// rotate the LOOK & UP Vectors about the RIGHT Vector
D3DXVec3TransformCoord(&vCameraLook, &vCameraLook, &matPitch);
D3DXVec3TransformCoord(&vCameraUp, &vCameraUp, &matPitch);
// rotate the RIGHT & UP Vectors about the LOOK Vector
D3DXVec3TransformCoord(&vCameraRight, &vCameraRight, &matRoll);
D3DXVec3TransformCoord(&vCameraUp, &vCameraUp, &matRoll);

// Update position and view matrices
D3DXMATRIX matR, matTemp;
D3DXQuaternionRotationYawPitchRoll (&qR, fYaw, fPitch, fRoll);
D3DXMatrixRotationQuaternion (&matR, &qR);
D3DXMatrixMultiply (&matView, &matR, &matView);
D3DXMatrixTranslation (&matTemp, vPos.x, vPos.y, vPos.z);
D3DXMatrixMultiply (&matView, &matTemp, &matView);
D3DXMatrixInverse (&matTemp, NULL, &matView);
m_pd3dDevice->SetTransform(D3DTS_VIEW, &matTemp );




// from gists
D3DXVec3Cross( &v3Cross, &v3Up, &vNormal );
fDot = D3DXVec3Dot( &v3Up, &vNormal );
fTheta = acos( fDot );




// 


