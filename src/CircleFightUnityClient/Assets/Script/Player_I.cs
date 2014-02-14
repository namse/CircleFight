using UnityEngine;
using System.Collections;

public struct data{
	public int mSize;
	public short mType;
};

public class Player_I : MonoBehaviour {
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
		Movement ();
		transform.Translate (Vector3.right * mVelocityX * Time.deltaTime);
		transform.Translate (Vector3.right * mVelocityY * Time.deltaTime);
		
		mVelocityX = mVelocityX + mAcceleration * Time.deltaTime;
		mVelocityY = mVelocityY + mAcceleration * Time.deltaTime;
	}

	void Movement()
	{
		if(Input.GetKey(KeyCode.W))
		{
			transform.Translate(Vector2.up * 3 * Time.deltaTime);
			Camera.main.transform.Translate(Vector2.up * 3 * Time.deltaTime);



			/*
			Network client;
			client = this.gameObject.GetComponent<Network>();
			client.Init ();
			data a;
			a.mSize = 8;
			a.mType = 1
			client.writer.Write (a.mSize);
			client.writer.Write (a.mType);
			client.writer.Flush ();
			*/
		}
		else if(Input.GetKey(KeyCode.S))
		{
			transform.Translate(Vector2.up * -3 * Time.deltaTime);
			Camera.main.transform.Translate(Vector2.up * -3 * Time.deltaTime);
		}

		if(Input.GetKey(KeyCode.A))
		{
			transform.Translate(Vector2.right * -3 * Time.deltaTime);
			Camera.main.transform.Translate(Vector2.right * -3 * Time.deltaTime);
		}
		else if(Input.GetKey(KeyCode.D))
		{
			transform.Translate(Vector2.right * 3 * Time.deltaTime);
			Camera.main.transform.Translate(Vector2.right * 3 * Time.deltaTime);
		}
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
