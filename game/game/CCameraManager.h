#pragma once

#define CAMERANODE				(CAMERAMANAGER->GetCameraNode())
#define CAMERA					(CAMERAMANAGER->GetCamera())

#define CAMERA_MIN_DISTANCE		2.0f
#define CAMERA_MAX_DISTANCE		25.0f

#define SELECTUNIT_MAX_DISTANCE	75.0f

enum ECameraType
{
	CAMERATYPE_Undefined,

	CAMERATYPE_AnimatedPath,
	CAMERATYPE_Free,
	CAMERATYPE_FreeFly,
	CAMERATYPE_Orbit,
};

class CCameraManager : public Object
{
	URHO3D_OBJECT( CCameraManager, Object );
public:
								CCameraManager( Context * pcContext );
	virtual					   ~CCameraManager();

	void						SetCameraType( ECameraType eCameraType, Node * pTarget = NULL ){ eType = eCameraType; pTargetNode = pTarget; UpdateCameraBase(); }
	void						SetCameraPosition( Vector3 cPosition, Quaternion cRotation = Quaternion() );

	void						UpdateCameraBase();

	//Getters
	Node					  * GetCameraNode();
	Camera					  * GetCamera(){ return GetCameraNode()->GetComponent<Camera>(); }

	Node					  * GetNodeRaycast();

	float						GetCameraDistance(){ return fCameraDistance; }
	float						GetCameraPitch(){ return fCameraPitch; }
	float						GetCameraYaw(){ return fCameraYaw; }

	float						GetMouseYaw(){ return fMouseYaw; }

	//Eventos Registrados
	void						HandlePostUpdate( StringHash cEventType, VariantMap & vEventData );
private:
	void						OnMoveCamera( float fTime );
private:
	WeakPtr<Node>				pCameraNode;

	ECameraType					eType;
	Node					  * pTargetNode;

	float						fDeltaMouseMoveWheel;

	//Orbit Camera
	float						fCameraDistance;
	float						fCameraPitch;
	float						fCameraYaw;

	Vector3						cLookAtBase;

	float						fMouseYaw;
};