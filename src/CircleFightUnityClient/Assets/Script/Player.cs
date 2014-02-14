using UnityEngine;
using System.Collections;

public class Player : MonoBehaviour {
	private float mX;
	private float mY;
	private float mVelocityX;
	private float mVelocityY;
	private float mAcceleration;
	private float mAngle;
	
	// Use this for initialization
	void Start ()
	{
		mX = mY = mVelocityX = mVelocityY = mAcceleration = mAngle = 0;
	}
	
	// Update is called once per frame
	void Update ()
	{
		transform.Translate (Vector3.right * mVelocityX * Time.deltaTime);
		transform.Translate (Vector3.right * mVelocityY * Time.deltaTime);
		
		mVelocityX = mVelocityX + mAcceleration * Time.deltaTime;
		mVelocityY = mVelocityY + mAcceleration * Time.deltaTime;
	}
	
	public void Init(float pX, float pY, float pVelocityX, float pVelocityY, float pAcceleration, float pAngle)
	{
		mX = pX;
		mY = pY;
		mVelocityX = pVelocityX;
		mVelocityY = pVelocityY;
		mAcceleration = pAcceleration;
		mAngle = pAngle;
		
		SetPosition (mX, mY);
		SetVelocity (mVelocityX, mVelocityY);
		SetAcceleration (mAcceleration);
		SetAngle (mAngle);
	}
	
	public void SetPosition (float pX, float pY)
	{
		mX = pX;
		mY = pY;
	}
	public void SetVelocity(float pVelocityX, float pVelocityY)
	{
		mVelocityX = pVelocityX;
		mVelocityY = pVelocityY;
	}
	public void SetVelocityX(float pVelocityX)
	{
		mVelocityX = pVelocityX;
	}
	public void SetVelocityY(float pVelocityY)
	{
		mVelocityY = pVelocityY;
	}
	public void SetAcceleration(float pAcceleration)
	{
		mAcceleration = pAcceleration;
	}
	public void SetAngle(float pAngle)
	{
		mAngle = pAngle;
		transform.rotation = Quaternion.AngleAxis (mAngle, Vector3.right);
	}
	
	public float GetAngle()
	{
		return mAngle;
	}
}
